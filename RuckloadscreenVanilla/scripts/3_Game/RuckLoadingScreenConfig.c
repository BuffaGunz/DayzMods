class RuckusHintPage
{
	string m_Headline;
	string m_Description;
	string m_ImagePath;
}

class RuckusLoadingHintsConfig
{
	int version = 1;

	string discord_invite = "https://discord.gg/W35b8TKDU3";
	string death_message = "Ah well, I suppose it has come to this... Such is life. -Ned Kelly-";

	ref array<ref RuckusHintPage> hints;

	ref Param5<float, float, float, float, float> m_LastDeathStats;
	string m_LastDeathText;

	private static ref RuckusLoadingHintsConfig m_Instance;

	void RuckusLoadingHintsConfig()
	{
		hints = new array<ref RuckusHintPage>();
	}

	static RuckusLoadingHintsConfig Get()
	{
		if (!m_Instance)
			Load();
		return m_Instance;
	}

	static string GetConfigFolder()
	{
		return "$profile:Ruckus";
	}

	static string GetConfigPath()
	{
		return GetConfigFolder() + "/Loadingscreenhints.json";
	}

	private static void Load()
	{
		string folder = GetConfigFolder();
		string path   = GetConfigPath();

		if (!FileExist(folder))
			MakeDirectory(folder);

		ref RuckusLoadingHintsConfig cfg = new RuckusLoadingHintsConfig();

		if (FileExist(path))
		{
			JsonFileLoader<RuckusLoadingHintsConfig>.JsonLoadFile(path, cfg);
			Print("[Ruckus] ✅ Config loaded: " + path);
		}
		else
		{
			cfg.MakeDefaults_FirstCreate();
			JsonFileLoader<RuckusLoadingHintsConfig>.JsonSaveFile(path, cfg);
			Print("[Ruckus] 📝 Config created: " + path);
		}

		if (!cfg.hints)
			cfg.hints = new array<ref RuckusHintPage>();

		cfg.m_LastDeathStats = null;
		cfg.m_LastDeathText = "";

		m_Instance = cfg;
	}

	void MakeDefaults_FirstCreate()
	{
		if (!hints) hints = new array<ref RuckusHintPage>();
		hints.Clear();

		AddHint("Discord","Join our Discord for support and more server info, click on Discord button in game.","");
		AddHint("Zombie Skinning","Skinning a zombie can gives you access to guts, meat and bones all 3 can be used for fishing.","");
		AddHint("Freinds or Foe?","Its a harsh world out there and resources are hard to come by be careful who you trust.","");
		AddHint("Universal Weapon Parts","Most scopes are universal and most same type ammo mags compatible.","");
		AddHint("Combat Log","Combat Logging is strictly prohibited. Survivors must stay on the server for at least 5 minutes after combat.","");
		AddHint("Map","Find a map ingame and press M to display on screen, a pen is needed to apply custom markers.","");
		AddHint("Base Building","Base building is vanilla. Raid anytime no glitching or watchtower raiding.","");
		AddHint("No Build Zones","No building in military zones, bunkers or hospitals If found they will be deleted without warning.","");
		AddHint("Universal Wheels","The olga, sarka, ada and gunter can all fit eachothers wheels might not look the best but will get you back on the road faster.","");
		AddHint("Fallen Loot","Crashed cargo planes always have a locked container full of high tier loot keys can be found on zombies nearby.","");

		AddHint("#str_hint_notarunner0",       "#str_hint_notarunner1",       "");
		AddHint("#str_hint_goinland0",        "#str_hint_goinland1",        "");
		AddHint("#str_hint_mytrustyknife0",   "#str_hint_mytrustyknife1",   "");
		AddHint("#str_hint_patchyourselfup0", "#str_hint_patchyourselfup1", "");
		AddHint("#str_hint_freshfood0",       "#str_hint_freshfood1",       "");
		AddHint("#str_hint_gunjam0",          "#str_hint_gunjam1",          "");
		AddHint("#str_hint_badblood0",        "#str_hint_badblood1",        "");
		AddHint("#str_hint_infectedslayer0",  "#str_hint_infectedslayer1",  "");
		AddHint("#str_hint_hope0",            "#str_hint_hope1",            "");
		AddHint("#str_hint_handyman0",        "#str_hint_handyman1",        "");
		AddHint("#str_hint_navigator0",       "#str_hint_navigator1",       "");
		AddHint("#str_hint_beans0",           "#str_hint_beans1",           "");
		AddHint("#str_hint_weather0",         "#str_hint_weather1",         "");
		AddHint("#str_hint_nutrition0",       "#str_hint_nutrition1",       "");
		AddHint("#str_hint_nighttime0",       "#str_hint_nighttime1",       "");
		AddHint("#str_hint_watchyourfeet0",   "#str_hint_watchyourfeet1",   "");
		AddHint("#str_hint_ragsoflife0",      "#str_hint_ragsoflife1",      "");
		AddHint("#str_hint_maskon0",          "#str_hint_maskon1",          "");
		AddHint("#str_hint_taintedsource0",   "#str_hint_taintedsource1",   "");
		AddHint("#str_hint_keepitclean0",     "#str_hint_keepitclean1",     "");
		AddHint("#str_hint_warmandcozy0",     "#str_hint_warmandcozy1",     "");
		AddHint("#str_hint_earlybird0",       "#str_hint_earlybird1",       "");
		AddHint("#str_hint_deadlymist0",      "#str_hint_deadlymist1",      "");
		AddHint("#str_hint_sharpshooter0",    "#str_hint_sharpshooter1",    "");
		AddHint("#str_hint_thoroughcheckup0", "#str_hint_thoroughcheckup1", "");
		AddHint("#str_hint_stabbedintheback0","#str_hint_stabbedintheback1","");
		AddHint("#str_hint_lightasafeather0", "#str_hint_lightasafeather1", "");
		AddHint("#str_hint_loadingfirearms0", "#str_hint_loadingfirearms1", "");
		AddHint("#str_hint_keepitcool0",      "#str_hint_keepitcool1",      "");
		AddHint("#str_hint_planningahead0",   "#str_hint_planningahead1",   "");
		AddHint("#str_hint_heavyduty0",       "#str_hint_heavyduty1",       "");
		AddHint("#str_hint_bequietorloud0",   "#str_hint_bequietorloud1",   "");
		AddHint("#str_hint_baitandtrap0",     "#str_hint_baitandtrap1",     "");
		AddHint("#str_hint_heylisten0",       "#str_hint_heylisten1",       "");
	}

	protected void AddHint(string headline, string desc, string imagePath)
	{
		RuckusHintPage hp = new RuckusHintPage();
		hp.m_Headline = headline;
		hp.m_Description = desc;
		hp.m_ImagePath = imagePath;
		hints.Insert(hp);
	}

	Param5<float, float, float, float, float> GetLastDeathStats()
	{
		return m_LastDeathStats;
	}

	string GetLastDeathText()
	{
		return m_LastDeathText;
	}

	void SetLastDeathStats(ref Param5<float, float, float, float, float> s)
	{
		m_LastDeathStats = s;
	}

	void SetLastDeathText(string s)
	{
		m_LastDeathText = s;
	}

	void ClearLastDeathStats()
	{
		m_LastDeathStats = null;
		m_LastDeathText = "";
	}

	void ApplyFromServer(int newVersion, string discord, string deathmsg, array<ref RuckusHintPage> newHints)
	{
		version = newVersion;
		discord_invite = discord;
		death_message = deathmsg;

		if (newHints)
			hints = newHints;
		else if (!hints)
			hints = new array<ref RuckusHintPage>();
	}

	void SaveClientCopy()
	{
		string folder = GetConfigFolder();
		string path   = GetConfigPath();

		if (!FileExist(folder))
			MakeDirectory(folder);

		ref Param5<float, float, float, float, float> tmpStats = m_LastDeathStats;
		string tmpText = m_LastDeathText;

		m_LastDeathStats = null;
		m_LastDeathText = "";

		JsonFileLoader<RuckusLoadingHintsConfig>.JsonSaveFile(path, this);

		m_LastDeathStats = tmpStats;
		m_LastDeathText = tmpText;

		Print("[Ruckus] Client config saved: " + path);
	}
}
