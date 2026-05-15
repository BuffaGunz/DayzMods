modded class DayZPlayerImplement extends DayZPlayer
{
	override void EEKilled(Object killer)
	{
		if (GetGame() && GetGame().IsServer())
		{
			// Force-finalize laggy stats
			StatUpdateByPosition(AnalyticsManagerServer.STAT_DISTANCE);
			StatUpdateByTime(AnalyticsManagerServer.STAT_PLAYTIME);

			PlayerIdentity id = GetIdentity();
			if (id)
			{
				float playtime = StatGet(AnalyticsManagerServer.STAT_PLAYTIME);
				float pk       = StatGet(AnalyticsManagerServer.STAT_PLAYERS_KILLED);
				float ik       = StatGet(AnalyticsManagerServer.STAT_INFECTED_KILLED);
				float dist     = StatGet(AnalyticsManagerServer.STAT_DISTANCE);
				float longest  = StatGet(AnalyticsManagerServer.STAT_LONGEST_SURVIVOR_HIT);

				// Push death TEXT + stats snapshot together
				string msg = RuckusLoadingHintsConfig.Get().death_message;

				ref Param6<string, float, float, float, float, float> p =
					new Param6<string, float, float, float, float, float>(msg, playtime, pk, ik, dist, longest);

				GetRPCManager().SendRPC("Ruckus", "HandleRuckDeathStats", p, true, id);

				Print("[Ruckus] Death RPC pushed (text+stats) to client: " + id.GetName());
			}
		}

		// Give RPC a moment to arrive before death screen builds message
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(DelayedDeath, 250, false, killer);
	}

	void DelayedDeath(Object killer)
	{
		SendDeathJuncture(-1, 0);
		super.EEKilled(killer);
	}

	void ShowDeadScreen(bool show, float duration)
	{
		#ifndef NO_GUI
		if (show && IsPlayerSelected())
		{
			#ifdef PLATFORM_PS4
			OnlineServices.SetMultiplayState(false);
			#endif

			string message = "";
			if (!GetGame().GetMission().IsPlayerRespawning())
			{
				message = BuildDeathMessageWithStats();
			}

			#ifdef PLATFORM_CONSOLE
			GetGame().GetUIManager().ScreenFadeIn(duration, message, FadeColors.DARK_RED, FadeColors.WHITE);
			#else
			GetGame().GetUIManager().ScreenFadeIn(duration, message, FadeColors.BLACK, FadeColors.WHITE);
			#endif
		}
		else
		{
			GetGame().GetUIManager().ScreenFadeOut(duration);

			if (duration > 0)
				GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(StopDeathDarkeningEffect, duration * 1000, false);
			else
				GetGame().GetCallQueue(CALL_CATEGORY_GUI).Call(StopDeathDarkeningEffect);
		}
		#endif
	}

	protected string BuildDeathMessageWithStats()
	{
		RuckusLoadingHintsConfig cfg = RuckusLoadingHintsConfig.Get();

		// Prefer server-pushed text for THIS death (avoids stale local JSON)
		string baseMsg = cfg.GetLastDeathText();
		if (baseMsg == "")
			baseMsg = cfg.death_message;

		string stats = BuildStatsBlock();
		if (stats != "")
			return baseMsg + "\n\n" + stats;

		return baseMsg;
	}

	protected string BuildStatsBlock()
	{
		RuckusLoadingHintsConfig cfg = RuckusLoadingHintsConfig.Get();
		Param5<float, float, float, float, float> s = cfg.GetLastDeathStats();

		if (s)
		{
			ref FullTimeData t = new FullTimeData();
			TimeConversions.ConvertSecondsToFullTime(s.param1, t);

			string resultStr = "-Survivor Stats-";
			resultStr += "\nTime Alive: " + t.FormatedNonZero();
			resultStr += "\nLives Taken: " + StatValue(s.param2);
			resultStr += "\nUndead Put Down: " + StatValue(s.param3);
			resultStr += "\nLand Traveled On Foot: " + StatDistance(s.param4);
			resultStr += "\nBest Shot!: " + StatDistance(s.param5, true);
			return resultStr;
		}

		// Fallback if RPC didn't arrive
		PlayerBase player = PlayerBase.Cast(this);
		if (!player) return "";

		ref FullTimeData t2 = new FullTimeData();
		TimeConversions.ConvertSecondsToFullTime(player.StatGet(AnalyticsManagerServer.STAT_PLAYTIME), t2);

		string fallback = "-Survivor Stats-";
		fallback += "\nTime Alive: " + t2.FormatedNonZero();
		fallback += "\nLives Taken: " + StatValue(player.StatGet(AnalyticsManagerServer.STAT_PLAYERS_KILLED));
		fallback += "\nUndead Put Down: " + StatValue(player.StatGet(AnalyticsManagerServer.STAT_INFECTED_KILLED));
		fallback += "\nLand Traveled On Foot: " + StatDistance(player.StatGet(AnalyticsManagerServer.STAT_DISTANCE));
		fallback += "\nBest Shot!: " + StatDistance(player.StatGet(AnalyticsManagerServer.STAT_LONGEST_SURVIVOR_HIT), true);
		return fallback;
	}

	protected string StatDistance(float total_distance, bool meters_only = false)
	{
		if (total_distance > 0)
		{
			string distanceString;

			float kilometers = total_distance * 0.001;
			kilometers = Math.Round(kilometers);
			if (kilometers >= 10 && !meters_only)
			{
				distanceString = StatValue(kilometers, true) + " #STR_distance_unit_abbrev_kilometer_0";
			}
			else
			{
				distanceString = StatValue(total_distance) + " #STR_distance_unit_abbrev_meter_0";
			}

			return distanceString;
		}

		return "0 #STR_distance_unit_abbrev_meter_0";
	}

	protected string StatValue(float total_value, bool show_decimals = false)
	{
		if (total_value > 0)
		{
			string resultStr;

			int total_value_int = total_value;
			string number_str = total_value_int.ToString();

			if (total_value >= 1000)
			{
				int count;
				int first_length = number_str.Length() % 3;
				if (first_length > 0)
					count = 3 - first_length;

				for (int i = 0; i < number_str.Length(); ++i)
				{
					resultStr += number_str.Get(i);
					count++;

					if (count >= 3)
					{
						resultStr += " ";
						count = 0;
					}
				}
			}
			else
			{
				resultStr = number_str;
			}

			if (show_decimals)
			{
				string total_value_str = total_value.ToString();
				int decimal_idx = total_value_str.IndexOf(".");

				if (decimal_idx > -1)
				{
					resultStr.TrimInPlace();
					resultStr += total_value_str.Substring(decimal_idx, total_value_str.Length() - decimal_idx);
				}
			}

			return resultStr;
		}

		return "0";
	}
}
