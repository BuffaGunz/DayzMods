class RuckDynamicMarker
{
	string Key;
	int Id;
	vector Pos;
	int TypeId;
	string Name;
	int ColorARGB;

	void RuckDynamicMarker(string key, int id, vector pos, int typeId, string name, int colorARGB)
	{
		Key = key;
		Id = id;
		Pos = pos;
		TypeId = typeId;
		Name = name;
		ColorARGB = colorARGB;
	}
}

class RuckMarkerAPI
{
	protected static ref array<ref RuckDynamicMarker> s_Dynamic;

	static const int RUCK_DYN_ID_MAX = -20000;
	static const int RUCK_DYN_ID_MIN = -29999;

	protected static int s_NextDynamicId = RUCK_DYN_ID_MAX;

	protected static void Ensure()
	{
		if (!s_Dynamic)
			s_Dynamic = new array<ref RuckDynamicMarker>;
	}

	static int Upsert(string key, vector pos, int typeId, string name, int colorARGB = 0)
	{
		if (!GetGame().IsServer())
			return -1;

		Ensure();

		if (!key || key == string.Empty)
			return -1;

		if (!name) name = "";
		if (name.Length() > 32) name = name.Substring(0, 32);

		if (colorARGB == 0)
			colorARGB = ARGB(255, 255, 255, 255);

		float y = GetGame().SurfaceY(pos[0], pos[2]);
		pos[1] = y + 0.35;

		RuckDynamicMarker m = Find(key);
		if (m)
		{
			m.Pos = pos;
			m.TypeId = typeId;
			m.Name = name;
			m.ColorARGB = colorARGB;

			NotifyAllPlayers();
			return m.Id;
		}

		if (s_NextDynamicId < RUCK_DYN_ID_MIN)
			s_NextDynamicId = RUCK_DYN_ID_MAX;

		int id = s_NextDynamicId;
		s_NextDynamicId--;

		s_Dynamic.Insert(new RuckDynamicMarker(key, id, pos, typeId, name, colorARGB));

		NotifyAllPlayers();
		return id;
	}

	static bool Remove(string key)
	{
		if (!GetGame().IsServer())
			return false;

		Ensure();

		for (int i = s_Dynamic.Count() - 1; i >= 0; i--)
		{
			if (s_Dynamic[i] && s_Dynamic[i].Key == key)
			{
				s_Dynamic.Remove(i);
				NotifyAllPlayers();
				return true;
			}
		}

		return false;
	}

	static void ClearAll()
	{
		if (!GetGame().IsServer())
			return;

		Ensure();
		s_Dynamic.Clear();
		NotifyAllPlayers();
	}

	static void AppendTo(out array<ref RuckMapMarkerData> outMarkers)
	{
		if (!GetGame().IsServer()) return;
		Ensure();
		if (!outMarkers) return;

		for (int i = outMarkers.Count() - 1; i >= 0; i--)
		{
			RuckMapMarkerData md = outMarkers[i];
			if (!md) continue;

			int id = md.Id;
			if (id <= RUCK_DYN_ID_MAX && id >= RUCK_DYN_ID_MIN)
				outMarkers.Remove(i);
		}

		foreach (RuckDynamicMarker dm : s_Dynamic)
		{
			if (!dm) continue;
			outMarkers.Insert(new RuckMapMarkerData(dm.Id, dm.Pos, dm.TypeId, dm.Name, dm.ColorARGB));
		}
	}

	protected static RuckDynamicMarker Find(string key)
	{
		Ensure();
		foreach (RuckDynamicMarker m : s_Dynamic)
			if (m && m.Key == key)
				return m;
		return null;
	}

	protected static void NotifyAllPlayers()
	{
		array<Man> players = new array<Man>;
		GetGame().GetPlayers(players);

		foreach (Man man : players)
		{
			PlayerBase pb = PlayerBase.Cast(man);
			if (!pb) continue;

			PlayerIdentity pid = pb.GetIdentity();
			if (!pid) continue;

			ChernarusMap mapItem = FindPlayerMapItem(pb);
			if (!mapItem) continue;

			mapItem.Ruck_BumpServerRevision();
			mapItem.Ruck_SendMarkersToIdentity(pid);
		}
	}

	protected static ChernarusMap FindPlayerMapItem(PlayerBase pb)
	{
		EntityAI inHands = pb.GetHumanInventory().GetEntityInHands();
		ChernarusMap mh = ChernarusMap.Cast(inHands);
		if (mh) return mh;

		array<EntityAI> items = new array<EntityAI>;
		pb.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, items);

		foreach (EntityAI e : items)
		{
			ChernarusMap m = ChernarusMap.Cast(e);
			if (m) return m;
		}

		return null;
	}
}
