class StatsTime
{
	int days;
	int hours;
	int minutes;
}

class StatsPlayer
{
	string pid;
	string name;

	ref StatsTime time;

	int kills;
	int deaths;
	int suicides;

	string first_played;
	string last_played;

	void StatsPlayer()
	{
		time = new StatsTime();
	}
}

class ServerStats
{
	int total_players;
	ref array<ref StatsPlayer> players;
	private static ref map<string, int> s_LoginMS = new map<string, int>();
	private static ref ServerStats m_Instance;

	void ServerStats()
	{
		players = new array<ref StatsPlayer>();
	}

	static ServerStats Get()
	{
		if (!m_Instance)
			Load();
		return m_Instance;
	}
	
	static string GetSteamId(PlayerIdentity id)
	{
		if (!id) return "";
		return id.GetPlainId(); 
	}


	private static void Load()
	{
		string folder = "$profile:Ruckus";
		string path = folder + "/ServerStats.json";

		if (!FileExist(folder))
			MakeDirectory(folder);

		ref ServerStats db = new ServerStats();

		if (FileExist(path))
			JsonFileLoader<ServerStats>.JsonLoadFile(path, db);
		else
			JsonFileLoader<ServerStats>.JsonSaveFile(path, db);

		m_Instance = db;
	}

	void Save()
	{
		total_players = players.Count();
		JsonFileLoader<ServerStats>.JsonSaveFile("$profile:Ruckus/ServerStats.json", this);
	}

	static string Pad2(int v)
	{
		if (v < 10)
		{
			return "0" + v.ToString();
		}
		return v.ToString();
	}
	
	static string NowServerISO()
	{
		int y, mo, d, h, mi;

		GetGame().GetWorld().GetDate(y, mo, d, h, mi);

		if (mi >= 60) mi = 59;
		return Pad2(d) + " " + GetMonthName(mo) + " " + y.ToString() + " " + Pad2(h) + ":" + Pad2(mi);

	}

	static string GetMonthName(int m)
	{
		switch (m)
		{
			case 1: return "Jan";
			case 2: return "Feb";
			case 3: return "Mar";
			case 4: return "Apr";
			case 5: return "May";
			case 6: return "Jun";
			case 7: return "Jul";
			case 8: return "Aug";
			case 9: return "Sep";
			case 10: return "Oct";
			case 11: return "Nov";
			case 12: return "Dec";
		}
		return "???";
	}

	static string NowISO()
	{
		int y;
		int mo;
		int d;
		int h;
		int mi;
		int s;

		GetYearMonthDay(y, mo, d);
		GetHourMinuteSecond(h, mi, s);

		return Pad2(d) + " " + GetMonthName(mo) + " " + y.ToString() + " " + Pad2(h) + ":" + Pad2(mi);
	}

	static void AddMinutes(StatsTime t, int mins)
	{
		if (!t)
		{
			return;
		}
		if (mins <= 0)
		{
			return;
		}

		t.minutes = t.minutes + mins;

		if (t.minutes >= 60)
		{
			t.hours = t.hours + (t.minutes / 60);
			t.minutes = t.minutes % 60;
		}

		if (t.hours >= 24)
		{
			t.days = t.days + (t.hours / 24);
			t.hours = t.hours % 24;
		}
	}

	static string FormatTime(StatsTime t)
	{
		if (!t) return "0m";
		if (t.days > 0) return t.days.ToString() + "d " + t.hours.ToString() + "h";
		if (t.hours > 0) return t.hours.ToString() + "h " + t.minutes.ToString() + "m";
		return t.minutes.ToString() + "m";
	}
	
	static string BuildAllPlayerStats()
	{
		ServerStats db = Get();
		if (!db || !db.players || db.players.Count() == 0)
			return "No player stats yet.";

		string result = "Player Stats\n";

		foreach (StatsPlayer sp : db.players)
		{
			if (!sp) continue;

			string block = sp.name + "\n";
			block = block + "Time Played: " + FormatTime(sp.time) + "\n";
			block = block + "Kills: " + sp.kills.ToString() + "\n";
			block = block + "Deaths: " + sp.deaths.ToString() + "\n";
			block = block + "Suicides: " + sp.suicides.ToString() + "\n\n";

			result = result + block;
		}

		return result;
	}

	static StatsPlayer GetOrCreate(PlayerIdentity id)
	{
		if (!id) return null;

		string sid = GetSteamId(id);
		if (sid == "") return null;

		ServerStats db = Get();

		foreach (StatsPlayer p : db.players)
		{
			if (p.pid == sid)
				return p;
		}

		StatsPlayer np = new StatsPlayer();
		np.pid = sid;            
		np.name = id.GetName();
		np.first_played = NowISO();
		np.last_played = np.first_played;

		db.players.Insert(np);
		db.Save();

		return np;
	}

	static void OnPlayerConnect(PlayerBase player)
	{
		if (!GetGame().IsServer() || !player) return;

		PlayerIdentity id = player.GetIdentity();
		if (!id) return;

		string sid = GetSteamId(id);
		if (sid == "") return;

		StatsPlayer p = GetOrCreate(id);
		if (!p) return;

		p.name = id.GetName();
		p.last_played = NowISO();

		s_LoginMS.Set(sid, GetGame().GetTime());

		Get().Save();
	}

	static void OnPlayerDisconnect(PlayerBase player)
	{
		if (!GetGame().IsServer() || !player) return;

		PlayerIdentity id = player.GetIdentity();
		if (!id) return;

		string sid = GetSteamId(id);
		if (sid == "") return;

		StatsPlayer p = GetOrCreate(id);
		if (!p) return;

		int start;
		if (s_LoginMS.Find(sid, start))
		{
			int delta = GetGame().GetTime() - start;
			int mins = Math.Floor(delta / 60000.0);
			if (mins < 0) mins = 0;

			AddMinutes(p.time, mins);
			s_LoginMS.Remove(sid);
		}

		p.last_played = NowISO();
		Get().Save();
	}

	static void OnPlayerKilled(PlayerBase victim, Object source)
	{
		if (!victim || !victim.GetIdentity()) return;

		StatsPlayer v = GetOrCreate(victim.GetIdentity());
		v.deaths++;

		PlayerBase killer = PlayerBase.Cast(EntityAI.Cast(source).GetHierarchyParent());
		if (!killer) killer = PlayerBase.Cast(source);

		if (killer && killer.GetIdentity())
		{
			StatsPlayer k = GetOrCreate(killer.GetIdentity());

			if (k.pid == v.pid)
				k.suicides++;
			else
				k.kills++;
		}

		Get().Save();
	}
}
