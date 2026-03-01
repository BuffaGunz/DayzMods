#ifdef RUCKMAP
class RuckMapCrashCache
{
	protected static ref map<string, vector> s_PosByUID;

	static const float TERRAIN_LIFT = 0.35;

	protected static vector SnapToTerrain(vector p)
	{
		float y = GetGame().SurfaceY(p[0], p[2]);
		p[1] = y + TERRAIN_LIFT;
		return p;
	}

	static string KeyFromPos(vector p)
	{
		p = SnapToTerrain(p);
		int x = Math.Round(p[0]);
		int z = Math.Round(p[2]);
		return string.Format("planecrash_%1_%2", x, z);
	}

	static void ServerAdd(EntityAI obj)
	{
		if (!GetGame().IsServer() || !obj) return;
		if (!PlaneCrashSettings.Get() || !PlaneCrashSettings.Get().EnableRuckMapMarkers) return;

		vector pos = SnapToTerrain(obj.GetPosition());
		string uid = KeyFromPos(obj.GetPosition());

		if (!s_PosByUID)
			s_PosByUID = new map<string, vector>();

		s_PosByUID.Set(uid, pos);

		RuckMarkerAPI.Upsert(uid, pos, RuckMapMarkerTypes.MARKERTYPE_EVENT_PLANECRASH, "Plane Crash", ARGB(255, 255, 0, 0));
	}

	static void ServerRemove(EntityAI obj)
	{
		if (!GetGame().IsServer() || !obj) return;

		string uid = KeyFromPos(obj.GetPosition());

		if (s_PosByUID && s_PosByUID.Contains(uid))
			s_PosByUID.Remove(uid);

		RuckMarkerAPI.Remove(uid);
	}

	static void ServerRecreateAfterLoad(EntityAI obj)
	{
		if (!GetGame().IsServer() || !obj) return;
		ServerAdd(obj);
	}

	static map<string, vector> GetAll()
	{
		return s_PosByUID;
	}
}
#endif
