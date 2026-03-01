class PlaneCrashRuckTown
{
	string name;
	vector pos;   
	string type; 
	float radius; 
}

class PlaneCrashRuckLocationFinder
{
	static bool  INCLUDE_NAME_LOCAL    = true;   
	static float MIN_RADIUS_CLAMP      = 150.0;  
	static float RADIUS_PADDING        = 0.0;    
	static bool  CAPITALIZE_DIRECTIONS = false;  
	static float COMPASS_OFFSET_DEG    = 0.0;    
	static string MSG_NEAR = "Plane crash spotted in %1.";
	static string MSG_AWAY = "Plane crash spotted %1 %2 of %3.";

	protected static ref array<ref PlaneCrashRuckTown> s_Towns;
	protected static bool s_Built;

	static string BuildPlaneCrashMessage(vector crashPos)
	{
		EnsureBuilt();

		float dist;
		PlaneCrashRuckTown town = FindNearestTown(crashPos, dist);
		if (!town)
			return "Plane crash spotted";

		float effectiveRadius = town.radius + RADIUS_PADDING;
		if (dist <= effectiveRadius)
			return string.Format(MSG_NEAR, town.name);

		float brg = BearingDeg(town.pos, crashPos);
		if (COMPASS_OFFSET_DEG != 0.0) brg = Normalize0_360(brg + COMPASS_OFFSET_DEG);

		string dirWords = ToCardinalWords8(brg);
		if (CAPITALIZE_DIRECTIONS) dirWords = CapitalizeDirection(dirWords);

		return string.Format(MSG_AWAY, PrettyDistance(dist), dirWords, town.name);
	}

	protected static void EnsureBuilt()
	{
		if (s_Built) return;
		BuildTownIndex();
		s_Built = true;
	}
	
	protected static bool IsTownType(string t)
	{
		if (t == "Capital" || t == "City" || t == "Village") return true;

		if (INCLUDE_NAME_LOCAL && (t == "Local")) return true;

		if (t == "NameCity" || t == "NameCityCapital" || t == "NameVillage") return true;
		if (INCLUDE_NAME_LOCAL && t == "NameLocal") return true;

		return false;
	}

	protected static float DefaultRadiusFor(string type)
	{

		if (type == "Capital") return 1000.0;
		if (type == "City")    return 800.0;
		if (type == "Village") return 500.0;
		if (type == "Local")   return 300.0;

		if (type == "NameCityCapital") return 1000.0;
		if (type == "NameCity")        return 800.0;
		if (type == "NameVillage")     return 500.0;

		return 300.0;
	}

	protected static void BuildTownIndex()
	{
		s_Towns = new array<ref PlaneCrashRuckTown>;

		string world = GetGame().GetWorldName();                 
		string basePath = "CfgWorlds " + world + " Names";
		int n = GetGame().ConfigGetChildrenCount(basePath);

		for (int i = 0; i < n; i++)
		{
			string child; GetGame().ConfigGetChildName(basePath, i, child);
			string node = basePath + " " + child;

			string type; if (!GetGame().ConfigGetText(node + " type", type)) continue;
			if (!IsTownType(type)) continue;

			string name; if (!GetGame().ConfigGetText(node + " name", name)) continue;
			vector cfgPos = GetGame().ConfigGetVector(node + " position");
			vector pos = Vector(cfgPos[0], 0, cfgPos[1]); 

			float effective = DefaultRadiusFor(type);

			string pathA = node + " radiusA";
			string pathB = node + " radiusB";

			bool hasA = GetGame().ConfigIsExisting(pathA);
			bool hasB = GetGame().ConfigIsExisting(pathB);

			float rA = -1;
			float rB = -1;

			if (hasA) rA = GetGame().ConfigGetFloat(pathA);
			if (hasB) rB = GetGame().ConfigGetFloat(pathB);

			if (hasA && hasB)      effective = 0.5 * (rA + rB);
			else if (hasA)         effective = rA;
			else if (hasB)         effective = rB;

			auto t = new PlaneCrashRuckTown;
			t.name   = name;
			t.pos    = pos;
			t.type   = type;
			t.radius = Math.Max(effective, MIN_RADIUS_CLAMP);

			s_Towns.Insert(t);
		}
	}

	protected static PlaneCrashRuckTown FindNearestTown(vector p, out float distMeters)
	{
		PlaneCrashRuckTown best; float bestSq = 1e20;
		foreach (PlaneCrashRuckTown t : s_Towns)
		{
			float dx = p[0] - t.pos[0];
			float dz = p[2] - t.pos[2];
			float d2 = dx*dx + dz*dz;
			if (d2 < bestSq) { bestSq = d2; best = t; }
		}
		distMeters = Math.Sqrt(bestSq);
		return best;
	}

	protected static float BearingDeg(vector from, vector to)
	{
		float dx = to[0] - from[0];
		float dz = to[2] - from[2];

		float a = Math.Atan2(dx, -dz) * Math.RAD2DEG;
		if (a < 0) a += 360;
		return a;
	}

	protected static float Normalize0_360(float deg)
	{
		while (deg < 0) deg += 360;
		while (deg >= 360) deg -= 360;
		return deg;
	}

	protected static string ToCardinalWords8(float brgDeg)
	{
		int idx = Math.Round(brgDeg / 45.0);
		idx = idx % 8;

		switch (idx)
		{
			case 0: return "north";
			case 1: return "north east";
			case 2: return "east";
			case 3: return "south east";
			case 4: return "south";
			case 5: return "south west";
			case 6: return "west";
			case 7: return "north west";
		}
		return "unknown";
	}

	protected static string CapitalizeDirection(string s)
	{
		TStringArray parts = new TStringArray;
		s.Split(" ", parts);

		for (int i = 0; i < parts.Count(); i++)
		{
			string p = parts[i];
			if (p.Length() > 0)
			{
				string first = p.Substring(0, 1);
				first.ToUpper(); 

				string rest = "";
				if (p.Length() > 1)
				{
					int len = p.Length() - 1;
					rest = p.Substring(1, len); 
				}

				parts[i] = first + rest;
			}
		}

		return string.Join(" ", parts);
	}

	protected static string PrettyDistance(float dist)
	{
		if (dist < 1000)
		{
			int meters = Math.Round(dist);
			return string.Format("%1 m", meters.ToString());
		}

		float km = dist / 1000.0;
		float rounded = Math.Round(km * 10.0) / 10.0; 
		return string.Format("%1 km", rounded.ToString());
	}

}
