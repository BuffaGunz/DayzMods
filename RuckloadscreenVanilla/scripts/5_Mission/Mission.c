modded class MissionServer
{
	
	override void OnInit()
	{
		super.OnInit();
		RuckusLoadingHintsConfig.Get();
	}

	override void OnClientReadyEvent(PlayerIdentity identity, PlayerBase player)
	{
		super.OnClientReadyEvent(identity, player);

		SendRuckConfig(identity);
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(SendRuckConfig, 2000, false, identity);
	}

	void SendRuckConfig(PlayerIdentity identity)
	{
		if (!identity) return;

		RuckusLoadingHintsConfig cfg = RuckusLoadingHintsConfig.Get();
		if (!cfg) return;

		if (!cfg.hints)
			cfg.hints = new array<ref RuckusHintPage>();

		ref Param4<int, string, string, ref array<ref RuckusHintPage>> p =
			new Param4<int, string, string, ref array<ref RuckusHintPage>>(cfg.version, cfg.discord_invite, cfg.death_message, cfg.hints);

		GetRPCManager().SendRPC("Ruckus", "HandleRuckConfig", p, true, identity);

		Print("[Ruckus] Config pushed to client: " + identity.GetName());
	}
}

modded class MissionGameplay
{
	override void OnInit()
	{
		super.OnInit();

		RuckusLoadingHintsConfig.Get();

		GetRPCManager().AddRPC("Ruckus", "HandleRuckConfig", this, SingleplayerExecutionType.Client);
		GetRPCManager().AddRPC("Ruckus", "HandleRuckDeathStats", this, SingleplayerExecutionType.Client);
	}

	override void OnPlayerRespawned(Man player)
	{
		super.OnPlayerRespawned(player);

		RuckusLoadingHintsConfig.Get().ClearLastDeathStats();
		Print("[Ruckus] Cleared cached death stats/text on respawn.");
	}

	void HandleRuckConfig(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
	{
		if (type != CallType.Client)
			return;

		ref Param4<int, string, string, ref array<ref RuckusHintPage>> p;
		if (!ctx.Read(p)) return;

		int version = p.param1;
		string discord = p.param2;
		string deathmsg = p.param3;
		ref array<ref RuckusHintPage> list = p.param4;

		if (!list)
			list = new array<ref RuckusHintPage>();

		RuckusLoadingHintsConfig cfg = RuckusLoadingHintsConfig.Get();
		cfg.ApplyFromServer(version, discord, deathmsg, list);
		cfg.SaveClientCopy();

		Print("[Ruckus] Config received from server. version=" + version + " hints=" + list.Count());
	}

	void HandleRuckDeathStats(CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target)
	{
		if (type != CallType.Client)
			return;

		ref Param6<string, float, float, float, float, float> p;
		if (!ctx.Read(p)) return;

		RuckusLoadingHintsConfig cfg = RuckusLoadingHintsConfig.Get();

		cfg.SetLastDeathText(p.param1);

		ref Param5<float, float, float, float, float> stats = new Param5<float, float, float, float, float>(p.param2, p.param3, p.param4, p.param5, p.param6);

		cfg.SetLastDeathStats(stats);

		Print("[Ruckus] Death text+stats received (cached).");
	}
}

modded class MissionMainMenu
{
	override void OnInit()
	{
		super.OnInit();
		RuckusLoadingHintsConfig.Get();
	}
}
