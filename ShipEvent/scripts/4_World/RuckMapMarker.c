#ifdef RUCKMAP
class RuckMapWreckCache
{
	protected static ref map<string, vector> s_PosByUID;

	static const float LIFT = 0.35;

	static string KeyFromPos(vector p)
	{
		int x = Math.Round(p[0]);
		int z = Math.Round(p[2]);
		return string.Format("shipwreck_%1_%2", x, z);
	}

	static void ServerAdd(EntityAI obj)
	{
		if (!GetGame().IsServer() || !obj) return;
		if (!ShipWreckSettings.Get() || !ShipWreckSettings.Get().EnableRuckMapMarkers) return;

		vector pos = obj.GetPosition();
		string uid = KeyFromPos(obj.GetPosition());

		if (!s_PosByUID)
			s_PosByUID = new map<string, vector>();

		s_PosByUID.Set(uid, pos);

		RuckMarkerAPI.Upsert(uid, pos, RuckMapMarkerTypes.MARKERTYPE_EVENT_SHIPWRECK, "Ship Wreck", ARGB(255, 255, 122, 0));
	}

	static void ServerRemove(EntityAI obj)
	{
		if (!GetGame().IsServer() || !obj) return;

		vector rawPos = obj.GetPosition();
		string uid = KeyFromPos(rawPos);

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
