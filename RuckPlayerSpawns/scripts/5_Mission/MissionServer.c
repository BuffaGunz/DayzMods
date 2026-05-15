modded class MissionServer
{
	private ref RuckSpawnController m_RuckSpawn;

	override void OnInit()
	{
		super.OnInit();

		RuckSpawnPaths.EnsureDirs();

		m_RuckSpawn = new RuckSpawnController();
		m_RuckSpawn.Init();
	}

	override PlayerBase OnClientNewEvent(PlayerIdentity identity, vector pos, ParamsReadContext ctx)
	{
		vector ori;
		vector newPos;

		bool useBed = (m_RuckSpawn && m_RuckSpawn.TryGetSpawn(newPos, ori));
		if (useBed)
			pos = newPos;

		PlayerBase pb = super.OnClientNewEvent(identity, pos, ctx);

		if (useBed && pb)
			pb.SetOrientation(ori);

		return pb;
	}

};
