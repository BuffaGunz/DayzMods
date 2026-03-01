class ServerStatsDiscordConfig
{
	string webhook_url = "";
	int update_seconds = 300;

	string server_name = "My Server";

	bool show_online = true;
	bool show_server_time = true;
	bool show_total_players = true;

	bool show_player_stats = true;

	private static ref ServerStatsDiscordConfig m_Instance;

	static ServerStatsDiscordConfig Get()
	{
		if (!m_Instance)
			Load();
		return m_Instance;
	}

	private static void Load()
	{
		string folder = "$profile:Ruckus";
		string path = folder + "/ServerStatsDiscord.json";

		if (!FileExist(folder))
			MakeDirectory(folder);

		ref ServerStatsDiscordConfig cfg = new ServerStatsDiscordConfig();

		if (FileExist(path))
			JsonFileLoader<ServerStatsDiscordConfig>.JsonLoadFile(path, cfg);
		else
			JsonFileLoader<ServerStatsDiscordConfig>.JsonSaveFile(path, cfg);

		m_Instance = cfg;
	}
}
