class RuckSpawnPaths
{
	static const string ROOT     = "$profile:Ruckus\\";
	static const string MODDIR   = "$profile:Ruckus\\SpawnBeds\\";
	static const string CACHEDIR = "$profile:Ruckus\\SpawnBeds\\cache\\";

	static void EnsureDirs()
	{
		if (!FileExist(ROOT))     MakeDirectory(ROOT);
		if (!FileExist(MODDIR))   MakeDirectory(MODDIR);
		if (!FileExist(CACHEDIR)) MakeDirectory(CACHEDIR);
	}

	static string CacheFileForWorld(string worldName)
	{
		return CACHEDIR + worldName + "_beds.json";
	}
};

class RuckBedCacheData
{
	string world;
	int version;
	int spawnHash;

	ref array<vector> bedPositions;
	ref array<vector> bedOrientations;

	void RuckBedCacheData()
	{
		version = 1;
		world = "";
		spawnHash = 0;
		bedPositions = new array<vector>();
		bedOrientations = new array<vector>();
	}
};

class RuckBedCache
{
	static string GetPathForWorld(string worldName)
	{
		return RuckSpawnPaths.CacheFileForWorld(worldName);
	}

	static bool Load(string worldName, out RuckBedCacheData data)
	{
		RuckSpawnPaths.EnsureDirs();

		string path = GetPathForWorld(worldName);
		if (!FileExist(path))
			return false;

		data = new RuckBedCacheData();
		JsonFileLoader<RuckBedCacheData>.JsonLoadFile(path, data);

		if (!data || !data.bedPositions || data.bedPositions.Count() == 0)
			return false;

		return true;
	}

	static void Save(string worldName, int spawnHash, array<vector> bedPos, array<vector> bedOri)
	{
		RuckSpawnPaths.EnsureDirs();

		RuckBedCacheData data = new RuckBedCacheData();
		data.world = worldName;
		data.spawnHash = spawnHash;
		data.bedPositions = bedPos;
		data.bedOrientations = bedOri;

		string path = GetPathForWorld(worldName);
		JsonFileLoader<RuckBedCacheData>.JsonSaveFile(path, data);
	}
};

class RuckSpawnHash
{
	static int Compute(array<vector> spawns)
	{
		int h = 2166136261;

		for (int i = 0; i < spawns.Count(); i++)
		{
			vector p = spawns.Get(i);

			int x = Math.Round(p[0] * 10);
			int z = Math.Round(p[2] * 10);

			h = (h ^ x) * 16777619;
			h = (h ^ z) * 16777619;
		}

		if (h < 0) h = -h;
		return h;
	}
};

class RuckBedFinder
{
	private float m_SearchRadius;

	void RuckBedFinder(float radius)
	{
		m_SearchRadius = radius;
	}
	
	private string GetProxyNameFromSelection(string selectionName)
	{
		string s = selectionName;
		s.ToLower();

		if (!s.Contains("."))
			return "";

		array<string> parts = new array<string>();
		s.Split("\\", parts);

		for (int i = 0; i < parts.Count(); i++)
		{
			string p = parts.Get(i);
			int dot = p.IndexOf(".");
			if (dot > 0)
				return p.Substring(0, dot);
		}

		return "";
	}

	private bool IsBedSelection(string selName)
	{
		string proxy = GetProxyNameFromSelection(selName);
		if (proxy == "")
			return false;

		if (proxy == "postel_panelak1") return true;
		if (proxy == "postel_manz_kov") return true;
		if (proxy == "matress_white") return true;
		if (proxy == "matress_white_bent") return true;
		if (proxy == "foldingbed_matress") return true;
		if (proxy == "foldingbed_open") return true;

		return false;
	}

	void FindBedsNear(vector center, RuckBedRegistry registry)
	{
		if (!registry) return;

		center[1] = center[1] + 0.5;

		array<Object> objs = new array<Object>();
		array<CargoBase> proxy = new array<CargoBase>();

		GetGame().GetObjectsAtPosition(center, m_SearchRadius, objs, proxy);

		foreach (Object obj : objs)
		{
			House h;
			if (!Class.CastTo(h, obj))
				continue;

			ScanHouseForBeds(h, registry);

			if (registry.Count() >= registry.GetMaxBeds())
				return;
		}
	}
	
	private vector HouseBedOffsetLS(string houseType, string proxy)
	{
		houseType.ToLower();

		if (houseType == "land_house_1w01")
		{
			return "0.30 0 0";
		}
		if (houseType == "land_house_1w07")
		{
			return "0.25 0 -0.10";
		}
		if (houseType == "land_house_1w03")
		{
			return "0.25 0 0";
		}
		if (houseType == "land_house_1w10")
		{
			return "0 0 0";
		}
		if (houseType == "land_house_1w09")
		{
			return "-0.25 0 0";
		}

		return "0 0 0";
	}

	private void ScanHouseForBeds(House h, RuckBedRegistry registry)
	{
		LOD lod = h.GetLODByName(LOD.NAME_GEOMETRY);
		if (!lod) return;

		array<Selection> sels = new array<Selection>();
		lod.GetSelections(sels);

		ref array<vector> clusterCenters = new array<vector>();
		ref array<int>    clusterCounts  = new array<int>();

		float CLUSTER_RADIUS_SQ = 0.8 * 0.8;

		string houseType = h.GetType(); // grab once

		for (int i = 0; i < sels.Count(); i++)
		{
			string selName = sels.Get(i).GetName();
			if (!IsBedSelection(selName))
				continue;

			string proxy = GetProxyNameFromSelection(selName);
			vector localPos = h.GetSelectionPositionLS(selName);

			localPos = localPos + HouseBedOffsetLS(houseType, proxy);

			vector worldPos = h.ModelToWorld(localPos);
			worldPos[1] = worldPos[1] + 0.3;

			int bestIdx = -1;
			float bestDist = 999999;

			for (int c = 0; c < clusterCenters.Count(); c++)
			{
				float d = vector.DistanceSq(clusterCenters.Get(c), worldPos);
				if (d < CLUSTER_RADIUS_SQ && d < bestDist)
				{
					bestDist = d;
					bestIdx = c;
				}
			}

			if (bestIdx == -1)
			{
				clusterCenters.Insert(worldPos);
				clusterCounts.Insert(1);
			}
			else
			{
				int n = clusterCounts.Get(bestIdx);
				vector cur = clusterCenters.Get(bestIdx);

				float nf = n;
				float nextCount = n + 1;
				float inv = 1.0 / nextCount;

				vector newCenter = (cur * nf + worldPos) * inv;

				clusterCenters.Set(bestIdx, newCenter);
				clusterCounts.Set(bestIdx, n + 1);
			}
		}

		vector ori = h.GetOrientation();

		for (int b = 0; b < clusterCenters.Count(); b++)
		{
			registry.AddBed(clusterCenters.Get(b), ori);

			if (registry.Count() >= registry.GetMaxBeds())
				return;
		}
	}

};

class RuckBedRegistry
{
	private ref array<vector> m_Positions;
	private ref array<vector> m_Orientations;
	private int m_MaxBeds;

	void RuckBedRegistry(int maxBeds)
	{
		m_Positions     = new array<vector>();
		m_Orientations  = new array<vector>();
		m_MaxBeds       = maxBeds;
	}

	array<vector> GetPositions()
	{
		return m_Positions;
	}

	array<vector> GetOrientations()
	{
		return m_Orientations;
	}

	int GetMaxBeds()
	{
		return m_MaxBeds;
	}

	void Clear()
	{
		m_Positions.Clear();
		m_Orientations.Clear();
	}

	int Count()
	{
		return m_Positions.Count();
	}

	bool AddBed(vector pos, vector ori)
	{
		if (m_Positions.Count() >= m_MaxBeds)
			return false;

		for (int i = 0; i < m_Positions.Count(); i++)
		{
			if (vector.DistanceSq(m_Positions.Get(i), pos) < 0.25) 
				return false;
		}

		m_Positions.Insert(pos);
		m_Orientations.Insert(ori);
		return true;
	}

	void AddBeds(array<vector> positions, array<vector> orientations)
	{
		if (!positions || positions.Count() == 0)
			return;

		for (int i = 0; i < positions.Count(); i++)
		{
			if (m_Positions.Count() >= m_MaxBeds)
				return;

			vector ori = "0 0 0";
			if (orientations && orientations.Count() > i)
				ori = orientations.Get(i);

			AddBed(positions.Get(i), ori);
		}
	}

	vector GetRandom(out vector ori)
	{
		ori = "0 0 0";

		if (m_Positions.Count() == 0)
			return "0 0 0";

		int idx = Math.RandomInt(0, m_Positions.Count());
		ori = m_Orientations.Get(idx);
		return m_Positions.Get(idx);
	}
};

