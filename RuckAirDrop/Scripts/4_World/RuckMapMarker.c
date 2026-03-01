#ifdef RUCKMAP
class RuckMapDropCache
{
	protected static ref map<string, vector> s_PosByUID;

	static const float TERRAIN_LIFT = 0.35;

	protected static vector SnapToTerrain(vector p)
	{
		float y = GetGame().SurfaceY(p[0], p[2]);
		p[1] = y + TERRAIN_LIFT;
		return p;
	}

	static void ServerAdd(EntityAI obj)
	{
		if (!GetGame().IsServer() || !obj) return;
		if (!AirDropSettings.Get() || !AirDropSettings.Get().EnableRuckMapMarkers) return;

		if (!s_PosByUID)
			s_PosByUID = new map<string, vector>;

		string uid = UidFor(obj);
		vector pos = SnapToTerrain(obj.GetPosition());

		s_PosByUID.Set(uid, pos);

		int col = ColorForContainer(obj.GetType());

		RuckMarkerAPI.Upsert(uid, pos, RuckMapMarkerTypes.MARKERTYPE_EVENT_AIRDROP, "Air Drop", col);
	}

	static void ServerRemove(EntityAI obj)
	{
		if (!GetGame().IsServer() || !obj) return;

		string uid = UidFor(obj);

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

	protected static int ColorForContainer(string t)
	{
		if (!t) return ARGB(255, 255, 255, 255);

		string n = t;
		n.ToLower();

		if (n.Contains("red"))  return ARGB(255, 255,   0,   0);
		if (n.Contains("blue")) return ARGB(255,   0,   0, 255);
		if (n.Contains("yellow")) return ARGB(255, 255, 255,   0);
		if (n.Contains("orange")) return ARGB(255, 255, 122,   0);

		return ARGB(255, 255, 255, 255);
	}

	protected static string UidFor(EntityAI obj)
	{
		if (!obj)
			return string.Format("airdrop_nil_%1", Math.RandomInt(1000, 9999));

		vector p = SnapToTerrain(obj.GetPosition());
		int x = Math.Round(p[0]);
		int z = Math.Round(p[2]);
		return string.Format("airdrop_%1_%2", x, z);
	}
}
#endif
