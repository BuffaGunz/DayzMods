modded class MissionServer
{
	override void OnInit()
	{
		super.OnInit();

		RuckMapSettings s = GetRuckMapSettings();
		if (!s || !s.EnableSpawnCacheMarkers)
			return;

		RuckSpawnCache cache;
		RuckSpawnCache.LoadOrBuild(GetGame().GetWorldName(), cache);
	}
}
