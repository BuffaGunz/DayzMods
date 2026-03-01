modded class PlayerBase
{
	override void OnConnect()
	{
		super.OnConnect();

		if (GetGame().IsServer())
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(ServerStats.OnPlayerConnect, 1000, false, this);
	}

	override void OnDisconnect()
	{
		if (GetGame().IsServer())
			ServerStats.OnPlayerDisconnect(this);

		super.OnDisconnect();
	}

	override void EEKilled(Object killer)
	{
		if (GetGame().IsServer())
			ServerStats.OnPlayerKilled(this, killer);

		super.EEKilled(killer);
	}
}
