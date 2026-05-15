class RuckXML_Pos
{
	float x;
	float z;
};

class RuckXML_Group
{
	string name;
	ref array<ref RuckXML_Pos> pos;

	void RuckXML_Group()
	{
		pos = new array<ref RuckXML_Pos>();
	}
};

class RuckXML_GeneratorPosBubbles
{
	ref array<ref RuckXML_Group> group;

	void RuckXML_GeneratorPosBubbles()
	{
		group = new array<ref RuckXML_Group>();
	}
};

class RuckXML_Mode 
{
	ref RuckXML_GeneratorPosBubbles generator_posbubbles;

	void RuckXML_Mode()
	{
		generator_posbubbles = new RuckXML_GeneratorPosBubbles();
	}
};

class RuckXML_PlayerSpawnPointsRoot
{
	ref RuckXML_Mode fresh;
	ref RuckXML_Mode hop;
	ref RuckXML_Mode travel;

	void RuckXML_PlayerSpawnPointsRoot()
	{
		fresh  = new RuckXML_Mode();
		hop    = new RuckXML_Mode();
		travel = new RuckXML_Mode();
	}
};

class RuckPlayerSpawns
{
	private ref array<vector> m_Positions;

	void RuckPlayerSpawns()
	{
		m_Positions = new array<vector>();
	}

	array<vector> GetPositions()
	{
		return m_Positions;
	}

	int Count()
	{
		return m_Positions.Count();
	}

	bool LoadFromMissionXML(bool includeFresh, bool includeHop, bool includeTravel)
	{
		m_Positions.Clear();

		string path = "$mission:cfgplayerspawnpoints.xml";
		if (!FileExist(path))
			return false;

		FileHandle fh = OpenFile(path, FileMode.READ);
		if (!fh)
			return false;

		string line;

		bool inFresh = false;
		bool inHop = false;
		bool inTravel = false;

		bool inGeneratorPosBubbles = false;

		while (FGets(fh, line) > 0)
		{
			line.TrimInPlace();

			if (line.Contains("<fresh"))
			{
				inFresh = true; inHop = false; inTravel = false;
				inGeneratorPosBubbles = false;
				continue;
			}
			if (line.Contains("<hop"))
			{
				inFresh = false; inHop = true; inTravel = false;
				inGeneratorPosBubbles = false;
				continue;
			}
			if (line.Contains("<travel"))
			{
				inFresh = false; inHop = false; inTravel = true;
				inGeneratorPosBubbles = false;
				continue;
			}

			if (line.Contains("</fresh"))
			{
				inFresh = false; inGeneratorPosBubbles = false;
				continue;
			}
			if (line.Contains("</hop"))
			{
				inHop = false; inGeneratorPosBubbles = false;
				continue;
			}
			if (line.Contains("</travel"))
			{
				inTravel = false; inGeneratorPosBubbles = false;
				continue;
			}

			bool modeAllowed = (inFresh && includeFresh) || (inHop && includeHop) || (inTravel && includeTravel);

			if (!modeAllowed)
				continue;

			if (line.Contains("<generator_posbubbles"))
			{
				inGeneratorPosBubbles = true;
				continue;
			}
			if (line.Contains("</generator_posbubbles"))
			{
				inGeneratorPosBubbles = false;
				continue;
			}

			if (!inGeneratorPosBubbles)
				continue;

			if (line.Contains("<pos") && line.Contains("x=") && line.Contains("z="))
			{
				float x = ExtractAttrFloat(line, "x");
				float z = ExtractAttrFloat(line, "z");
				if (x == 0 && z == 0)
					continue;

				float y = GetGame().SurfaceY(x, z);
				m_Positions.Insert(Vector(x, y, z));
			}
		}

		CloseFile(fh);
		return (m_Positions.Count() > 0);
	}

	static string ExtractAttr(string line, string attr)
	{
		string key1 = " " + attr + "=\"";
		string key2 = "\t" + attr + "=\"";
		string key3 = " " + attr + " = \"";
		string key4 = "\t" + attr + " = \"";

		int s = line.IndexOf(key1);
		int keyLen = key1.Length();

		if (s < 0) { s = line.IndexOf(key2); keyLen = key2.Length(); }
		if (s < 0) { s = line.IndexOf(key3); keyLen = key3.Length(); }
		if (s < 0) { s = line.IndexOf(key4); keyLen = key4.Length(); }

		if (s < 0)
			return "";

		s = s + keyLen;

		string rest = line.Substring(s, line.Length() - s);
		int e = rest.IndexOf("\"");
		if (e < 0)
			return "";

		return rest.Substring(0, e);
	}

	static float ExtractAttrFloat(string line, string attr)
	{
		string v = ExtractAttr(line, attr);
		if (v == "")
			return 0;

		return v.ToFloat();
	}
};

class RuckSpawnController
{
	private ref RuckPlayerSpawns m_Spawns;
	private ref RuckBedRegistry  m_Beds;
	private ref RuckBedFinder    m_Finder;

	private string m_World;
	private int m_SpawnHash;
	private bool m_ScanScheduled;

	private int m_MaxBeds;

	void RuckSpawnController()
	{
		m_World = GetGame().GetWorldName();

		m_Spawns = new RuckPlayerSpawns();

		m_MaxBeds = 500;
		float scanRadius = 400.0;

		m_Beds   = new RuckBedRegistry(m_MaxBeds);
		m_Finder = new RuckBedFinder(scanRadius);

		m_ScanScheduled = false;
	}

	void Init()
	{
		RuckSpawnPaths.EnsureDirs();

		bool includeFresh = true;
		bool includeHop = false;
		bool includeTravel = false;

		if (!m_Spawns.LoadFromMissionXML(includeFresh, includeHop, includeTravel))
			return;

		m_SpawnHash = RuckSpawnHash.Compute(m_Spawns.GetPositions());

		RuckBedCacheData cache;
		if (RuckBedCache.Load(m_World, cache))
		{
			if (cache.spawnHash == m_SpawnHash)
			{
				m_Beds.Clear();
				m_Beds.AddBeds(cache.bedPositions, cache.bedOrientations);
				return;
			}
		}

		if (!m_ScanScheduled)
		{
			m_ScanScheduled = true;
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.ScanAndSave, 8000, false);
		}
	}

	private void ScanAndSave()
	{
		m_Beds.Clear();

		array<vector> positions = m_Spawns.GetPositions();
		for (int i = 0; i < positions.Count(); i++)
		{
			m_Finder.FindBedsNear(positions.Get(i), m_Beds);

			if (m_Beds.Count() >= m_MaxBeds)
				break;
		}

		if (m_Beds.Count() > 0)
			RuckBedCache.Save(m_World, m_SpawnHash, m_Beds.GetPositions(), m_Beds.GetOrientations());
	}

	bool TryGetSpawn(out vector pos, out vector ori)
	{
		pos = "0 0 0";
		ori = "0 0 0";

		if (!m_Beds || m_Beds.Count() == 0)
			return false;

		pos = m_Beds.GetRandom(ori);
		pos[1] = pos[1] + 0.2;
		return true;
	}
};
