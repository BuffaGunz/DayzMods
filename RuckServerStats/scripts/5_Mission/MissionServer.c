modded class MissionServer
{
	override void OnInit()
	{
		super.OnInit();

		ServerStats.Get();

		ServerStatsDiscordConfig cfg = ServerStatsDiscordConfig.Get();
		if (!cfg)
			return;

		if (cfg.webhook_url == "")
		{
			Print("[ServerStatsDiscord] webhook_url is empty. Set it in $profile:Ruckus/ServerStatsDiscord.json");
			return;
		}

		GetDiscordHook().SetAlias("stats", cfg.webhook_url);

		int secs = cfg.update_seconds;
		if (secs < 60) secs = 60; 

		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(PostServerStats, secs * 1000, true);

		PostServerStats();
	}

	void PostServerStats()
	{
		ServerStatsDiscordConfig cfg = ServerStatsDiscordConfig.Get();
		if (!cfg || cfg.webhook_url == "")
			return;

		ServerStats db = ServerStats.Get();
		if (!db)
			return;

		array<Man> online = new array<Man>();
		GetGame().GetPlayers(online);

		db.total_players = db.players.Count();

		int y, mo, d, h, mi;
		GetGame().GetWorld().GetDate(y, mo, d, h, mi);

		bool isDay = (h >= 6 && h < 18);

		
		string icon;
		if (isDay)
			icon = ":sunny:";
		else
			icon = ":crescent_moon:";

		string text = "";

		if (cfg.server_name != "")
			text = text + "**Server:** " + cfg.server_name + "\n";

		if (cfg.show_online)
			text = text + "**Online Now:** " + online.Count().ToString() + "\n";

		if (cfg.show_total_players)
			text = text + "**Total Players:** " + db.total_players.ToString() + "\n";

		if (cfg.show_server_time)
			text = text + "**Server Time:** " + ServerStats.NowServerISO() + " " + icon;
		
		if (cfg.show_player_stats)
		{
			text = text + "\n\n";
			text = text + ServerStats.BuildAllPlayerStats();
		}

		GetDiscordHook().SendEmbed("stats", "Server Status", text);
	}

}
