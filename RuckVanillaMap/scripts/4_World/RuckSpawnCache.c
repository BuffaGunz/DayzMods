enum RuckMapMarkerTypes
{
	MARKERTYPE_MAP_MARKER = 59676706, // assign markers here aswell 
	MARKERTYPE_MAP_BASE,
	MARKERTYPE_MAP_LOOT,
	MARKERTYPE_MAP_BOAT,
	MARKERTYPE_MAP_CONTAINER,
	MARKERTYPE_MAP_HELI,
	MARKERTYPE_MAP_CAR,
	MARKERTYPE_MAP_PLANE,
	MARKERTYPE_MAP_SKULL,
	
	MARKERTYPE_EVENT_PLANECRASH, 
	MARKERTYPE_EVENT_AIRDROP,
	MARKERTYPE_EVENT_SHIPWRECK, 

	MARKERTYPE_SPAWN_BOAT,
	MARKERTYPE_SPAWN_SEDAN,
	MARKERTYPE_SPAWN_SEDAN2,
	MARKERTYPE_SPAWN_HATCHBACK,
	MARKERTYPE_SPAWN_HATCHBACK2,
	MARKERTYPE_SPAWN_OFFROAD,
	MARKERTYPE_SPAWN_TRUCK,
	MARKERTYPE_SPAWN_SIDEBYSIDE,

	MARKERTYPE_SPAWN_FEEDSHACK,
	MARKERTYPE_SPAWN_DEERSTAND,

	MARKERTYPE_SPAWN_BEAR,
	MARKERTYPE_SPAWN_CATTLE,
	MARKERTYPE_SPAWN_DOMESTIC_ANIMALS,
	MARKERTYPE_SPAWN_FOX,
	MARKERTYPE_SPAWN_PIG,
	MARKERTYPE_SPAWN_HEN,
	MARKERTYPE_SPAWN_HARE,
	MARKERTYPE_SPAWN_RED_DEER,
	MARKERTYPE_SPAWN_ROE_DEER,
	MARKERTYPE_SPAWN_SHEEP_GOAT,
	MARKERTYPE_SPAWN_WILD_BOAR,
	MARKERTYPE_SPAWN_WOLF
}

class RuckSpawnPoint
{
	string Category;
	string Name;
	vector Pos;
	float Radius;

	void RuckSpawnPoint(string category = "", string name = "", vector pos = "0 0 0", float radius = 0)
	{
		Category = category;
		Name = name;
		Pos = pos;
		Radius = radius;
	}
}

class RuckAnimalCluster
{
	string Species;

	float SumX;
	float SumZ;
	int Count;

	vector Center;
	float MaxRadius;

	void RuckAnimalCluster(string species, vector firstPos, float r)
	{
		Species = species;

		SumX = firstPos[0];
		SumZ = firstPos[2];
		Count = 1;

		Center = Vector(firstPos[0], 0, firstPos[2]);
		MaxRadius = r;
	}

	void Add(vector pos, float r)
	{
		SumX += pos[0];
		SumZ += pos[2];
		Count++;

		Center = Vector(SumX / Count, 0, SumZ / Count);

		if (r > MaxRadius)
			MaxRadius = r;
	}
}

class RuckSpawnCache extends Managed // This the main class that allows me to assign animal spawns vehicle spawns and hunting stands can be any class name. 
{
	string WorldName;
	int Version = 1;
	autoptr array<ref RuckSpawnPoint> Points = new array<ref RuckSpawnPoint>;

	static string GetCachePath(string world)
	{
		return string.Format("$profile:Ruckus\\SpawnCache\\%1.json", world);
	}

	static bool LoadOrBuild(string world, out RuckSpawnCache outCache)
	{
		string path = GetCachePath(world);

		string dir = "$profile:Ruckus\\SpawnCache\\";
		if (!FileExist(dir))
			MakeDirectory(dir);

		outCache = new RuckSpawnCache;
		outCache.WorldName = world;

		if (FileExist(path))
		{
			JsonFileLoader<RuckSpawnCache>.JsonLoadFile(path, outCache);
			if (outCache && outCache.WorldName == world && outCache.Points)
				return true;
		}

		RuckMapSettings s = GetRuckMapSettings();
		if (!s || !s.EnableSpawnCacheMarkers)
			return false;

		outCache.Points.Clear();
		RuckSpawnCacheBuilder.BuildFromConfig(s, outCache);

		JsonFileLoader<RuckSpawnCache>.JsonSaveFile(path, outCache);
		return true;
	}
}

class RuckSpawnCacheBuilder
{
	static void AddAnimalPointToClusters(string species, vector pos, float r, float clusterRadius, array<ref RuckAnimalCluster> clusters)
	{
		if (!clusters)
			return;

		if (clusterRadius <= 0)
		{
			clusters.Insert(new RuckAnimalCluster(species, pos, r));
			return;
		}

		float maxDistSq = clusterRadius * clusterRadius;

		foreach (RuckAnimalCluster c : clusters)
		{
			if (!c) continue;
			if (c.Species != species) continue;

			if (vector.DistanceSq(c.Center, pos) <= maxDistSq)
			{
				c.Add(pos, r);
				return;
			}
		}

		clusters.Insert(new RuckAnimalCluster(species, pos, r));
	}

	static bool IsTargetStaticStructure(string cls)
	{
		return (cls == "Land_Misc_FeedShack" || cls == "Land_Misc_DeerStand1" || cls == "Land_Misc_DeerStand2");
	}

	static void ParseStaticStructuresWorldScan(RuckSpawnCache cache)
	{
		if (!cache) return;

		float size = 0;
		if (GetGame().GetWorld())
			size = GetGame().GetWorld().GetWorldSize();

		if (size <= 0)
		{
			Print("[RuckSpawnCache] StaticStructures: invalid world size");
			return;
		}

		float step = 300.0;
		float radius = 450.0;

		ref map<string, bool> seen = new map<string, bool>;
		ref array<Object> objects = new array<Object>;
		ref array<CargoBase> proxies = new array<CargoBase>;

		int added = 0;

		for (float x = 0; x <= size; x += step)
		{
			for (float z = 0; z <= size; z += step)
			{
				vector scanPos = Vector(x, 0, z);

				objects.Clear();
				proxies.Clear();
				GetGame().GetObjectsAtPosition(scanPos, radius, objects, proxies);

				foreach (Object obj : objects)
				{
					if (!obj) continue;

					string cls = obj.GetType();
					if (!IsTargetStaticStructure(cls)) continue;

					vector pos = obj.GetPosition();
					if (pos[0] == 0 && pos[2] == 0) continue;

					int rx = Math.Round(pos[0]);
					int rz = Math.Round(pos[2]);
					string key = cls + ":" + rx.ToString() + ":" + rz.ToString();

					if (seen.Contains(key)) continue;
					seen.Insert(key, true);

					cache.Points.Insert(new RuckSpawnPoint("structure", cls, Vector(pos[0], 0, pos[2]), 0));
					added++;
				}
			}
		}

		Print(string.Format("[RuckSpawnCache] StaticStructures: added %1 points", added));
	}

	static void BuildFromConfig(RuckMapSettings s, RuckSpawnCache cache)
	{
		if (!s || !cache) return;

		ref array<ref RuckAnimalCluster> animalClusters = new array<ref RuckAnimalCluster>;

		if (s.EventSpawnsXML && s.EventSpawnsXML != string.Empty)
			ParseCfgEventSpawnsXML(s.EventSpawnsXML, cache);

		if (s.TerritoryXMLs)
		{
			foreach (string terrPath : s.TerritoryXMLs)
			{
				if (!terrPath || terrPath == string.Empty) continue;
				if (!FileExist(terrPath)) continue;

				ParseTerritoriesXML(terrPath, cache, s, animalClusters);
			}
		}

		ParseStaticStructuresWorldScan(cache);

		foreach (RuckAnimalCluster cl : animalClusters)
		{
			if (!cl) continue;
			cache.Points.Insert(new RuckSpawnPoint("animal", cl.Species, cl.Center, cl.MaxRadius));
		}
	}

	static void ParseCfgEventSpawnsXML(string path, RuckSpawnCache cache)
	{
		if (!FileExist(path))
		{
			Print("[RuckSpawnCache] Missing: " + path);
			return;
		}

		FileHandle fh = OpenFile(path, FileMode.READ);
		if (!fh) return;

		string line;
		string currentEvent = "";
		bool inEvent = false;

		while (FGets(fh, line) > 0)
		{
			line.TrimInPlace();

			if (line.Contains("<event") && line.Contains("name="))
			{
				currentEvent = ExtractAttr(line, "name");
				inEvent = (currentEvent != "");
				continue;
			}

			if (inEvent && line.Contains("</event"))
			{
				inEvent = false;
				currentEvent = "";
				continue;
			}

			if (!inEvent)
				continue;

			if (currentEvent != "")
			{
				string tmp = currentEvent;
				tmp.ToLower();
				if (tmp.Contains("heli"))
					continue;
			}

			if (line.Contains("<pos") && line.Contains("x=") && line.Contains("z="))
			{
				float x = ExtractAttrFloat(line, "x");
				float z = ExtractAttrFloat(line, "z");
				if (x == 0 && z == 0)
					continue;

				string category = CategorizeEventName(currentEvent);
				if (category == "skip")
					continue;

				cache.Points.Insert(new RuckSpawnPoint(category, currentEvent, Vector(x, 0, z), 0));
			}
		}

		CloseFile(fh);
		Print("[RuckSpawnCache] Parsed event spawns: " + cache.Points.Count());
	}

	static void ParseTerritoriesXML(string path, RuckSpawnCache cache, RuckMapSettings s, array<ref RuckAnimalCluster> animalClusters)
	{
		FileHandle fh = OpenFile(path, FileMode.READ);
		if (!fh) return;

		string species = GetTerritoryKeyFromPath(path);

		float clusterR = 0;
		if (s) clusterR = s.AnimalClusterRadiusMeters;

		string line;
		while (FGets(fh, line) > 0)
		{
			line.TrimInPlace();

			if (!line.Contains("<zone")) continue;
			if (!line.Contains("x=") || !line.Contains("z=")) continue;

			float x = ExtractAttrFloat(line, "x");
			float z = ExtractAttrFloat(line, "z");
			if (x == 0 && z == 0) continue;

			float r = 0;
			if (line.Contains("r="))
				r = ExtractAttrFloat(line, "r");

			AddAnimalPointToClusters(species, Vector(x, 0, z), r, clusterR, animalClusters);
		}

		CloseFile(fh);
	}
	
	static int ResolveStaticStructureTypeId(string className) // Assigns markers add here if you would like to add your own. could be cool for dino maps etc
	{
		string n = className;
		n.ToLower();

		if (n == "land_misc_feedshack")   return RuckMapMarkerTypes.MARKERTYPE_SPAWN_FEEDSHACK;
		if (n == "land_misc_deerstand1")  return RuckMapMarkerTypes.MARKERTYPE_SPAWN_DEERSTAND;
		if (n == "land_misc_deerstand2")  return RuckMapMarkerTypes.MARKERTYPE_SPAWN_DEERSTAND;

		return RuckMapMarkerTypes.MARKERTYPE_MAP_MARKER;
	}

	static int ResolveVehicleTypeId(string eventName)
	{
		string n = eventName;
		n.ToLower();

		if (n == "vehicleciviliansedan")    return RuckMapMarkerTypes.MARKERTYPE_SPAWN_SEDAN;
		if (n == "vehiclesedan02")          return RuckMapMarkerTypes.MARKERTYPE_SPAWN_SEDAN2;
		if (n == "vehiclehatchback02")      return RuckMapMarkerTypes.MARKERTYPE_SPAWN_HATCHBACK;
		if (n == "vehicleoffroadhatchback") return RuckMapMarkerTypes.MARKERTYPE_SPAWN_HATCHBACK2;
		if (n == "vehicleoffroad02")        return RuckMapMarkerTypes.MARKERTYPE_SPAWN_OFFROAD;
		if (n == "vehicletruck01")          return RuckMapMarkerTypes.MARKERTYPE_SPAWN_TRUCK;
		if (n == "vehicleCrSk_Kawasaki_Mule_SX_4x4") return RuckMapMarkerTypes.MARKERTYPE_SPAWN_SIDEBYSIDE;

		return RuckMapMarkerTypes.MARKERTYPE_SPAWN_HATCHBACK2;
	}

	static int ResolveAnimalTypeId(string key)
	{
		string k = key;
		k.ToLower();

		if (k == "bear")             return RuckMapMarkerTypes.MARKERTYPE_SPAWN_BEAR;
		if (k == "cattle")           return RuckMapMarkerTypes.MARKERTYPE_SPAWN_CATTLE;
		if (k == "domestic_animals") return RuckMapMarkerTypes.MARKERTYPE_SPAWN_DOMESTIC_ANIMALS;
		if (k == "fox")              return RuckMapMarkerTypes.MARKERTYPE_SPAWN_FOX;
		if (k == "pig")              return RuckMapMarkerTypes.MARKERTYPE_SPAWN_PIG;
		if (k == "hen")              return RuckMapMarkerTypes.MARKERTYPE_SPAWN_HEN;
		if (k == "hare")             return RuckMapMarkerTypes.MARKERTYPE_SPAWN_HARE;
		if (k == "red_deer")         return RuckMapMarkerTypes.MARKERTYPE_SPAWN_RED_DEER;
		if (k == "roe_deer")         return RuckMapMarkerTypes.MARKERTYPE_SPAWN_ROE_DEER;
		if (k == "sheep_goat")       return RuckMapMarkerTypes.MARKERTYPE_SPAWN_SHEEP_GOAT;
		if (k == "wild_boar")        return RuckMapMarkerTypes.MARKERTYPE_SPAWN_WILD_BOAR;
		if (k == "wolf")             return RuckMapMarkerTypes.MARKERTYPE_SPAWN_WOLF;

		return RuckMapMarkerTypes.MARKERTYPE_MAP_SKULL;
	}

	static string CategorizeEventName(string eventName)
	{
		string n = eventName;
		n.ToLower();

		if (n.Contains("heli"))
			return "skip";

		if (n.Contains("vehicleboat"))
			return "boat";

		if (n.Contains("vehicle"))
			return "vehicle";

		return "skip";
	}

	static string GetTerritoryKeyFromPath(string path)
	{
		string p = path;
		p.Replace("\\", "/");
		p.ToLower();

		int slash = p.LastIndexOf("/");
		string file = p;
		if (slash >= 0)
		{
			file = p.Substring(slash + 1, p.Length() - (slash + 1));
		}

		int dot = file.LastIndexOf(".");
		if (dot > 0)
			file = file.Substring(0, dot);

		string suffix = "_territories";
		int sidx = file.IndexOf(suffix);
		if (sidx >= 0)
			file = file.Substring(0, sidx);

		if (file == "") file = "animal";
		return file;
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
}
