class Ruck3DMarkerManager
{
	protected ref map<int, ref Ruck3DMarker> m_3D = new map<int, ref Ruck3DMarker>;

	protected int m_LastRevision = -1;

	protected bool IsSpawnType(int typeId)
	{
		switch (typeId)
		{
			case RuckMapMarkerTypes.MARKERTYPE_SPAWN_BOAT:
			case RuckMapMarkerTypes.MARKERTYPE_SPAWN_SEDAN:
			case RuckMapMarkerTypes.MARKERTYPE_SPAWN_SEDAN2:
			case RuckMapMarkerTypes.MARKERTYPE_SPAWN_HATCHBACK:
			case RuckMapMarkerTypes.MARKERTYPE_SPAWN_HATCHBACK2:
			case RuckMapMarkerTypes.MARKERTYPE_SPAWN_OFFROAD:
			case RuckMapMarkerTypes.MARKERTYPE_SPAWN_TRUCK:
			case RuckMapMarkerTypes.MARKERTYPE_SPAWN_SIDEBYSIDE:
			case RuckMapMarkerTypes.MARKERTYPE_SPAWN_FEEDSHACK:
			case RuckMapMarkerTypes.MARKERTYPE_SPAWN_DEERSTAND:
			case RuckMapMarkerTypes.MARKERTYPE_SPAWN_BEAR:
			case RuckMapMarkerTypes.MARKERTYPE_SPAWN_CATTLE:
			case RuckMapMarkerTypes.MARKERTYPE_SPAWN_DOMESTIC_ANIMALS:
			case RuckMapMarkerTypes.MARKERTYPE_SPAWN_FOX:
			case RuckMapMarkerTypes.MARKERTYPE_SPAWN_PIG:
			case RuckMapMarkerTypes.MARKERTYPE_SPAWN_HEN:
			case RuckMapMarkerTypes.MARKERTYPE_SPAWN_HARE:
			case RuckMapMarkerTypes.MARKERTYPE_SPAWN_RED_DEER:
			case RuckMapMarkerTypes.MARKERTYPE_SPAWN_ROE_DEER:
			case RuckMapMarkerTypes.MARKERTYPE_SPAWN_SHEEP_GOAT:
			case RuckMapMarkerTypes.MARKERTYPE_SPAWN_WILD_BOAR:
			case RuckMapMarkerTypes.MARKERTYPE_SPAWN_WOLF:
				return true;
		}
		return false;
	}

	protected bool ShouldShow3D(RuckMapMarkerData m)
	{
		if (!m) return false;

		if (IsSpawnType(m.TypeId))
			return false;

		if (m.Id >= 0)
			return true;

		if (m.Name && m.Name != string.Empty)
			return true;

		return false;
	}

	void Update(ChernarusMap mapItem)
	{
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		if (!player || !mapItem)
		{
			ClearAll();
			return;
		}

		RuckMapSettings s = GetRuckMapSettings();
		if (!s || !s.Enable3DMarkers)
		{
			ClearAll();
			return;
		}

		array<ref RuckMapMarkerData> markers = mapItem.GetRuckMarkers();
		if (!markers)
		{
			ClearAll();
			return;
		}

		int rev = mapItem.GetRuckMarkersRevision();
		bool changed = (rev != m_LastRevision);
		m_LastRevision = rev;

		ref map<int, bool> seen = new map<int, bool>;

		foreach (RuckMapMarkerData m : markers)
		{
			if (!ShouldShow3D(m))
				continue;

			seen.Set(m.Id, true);

			Ruck3DMarker w = m_3D.Get(m.Id);
			if (!w)
			{
				w = new Ruck3DMarker(m);
				m_3D.Set(m.Id, w);
			}
			else
			{
				if (changed)
					w.SetData(m);
			}

			w.Update(player);
		}

		for (int i = m_3D.Count() - 1; i >= 0; i--)
		{
			int id = m_3D.GetKey(i);
			if (!seen.Contains(id))
			{
				Ruck3DMarker dead = m_3D.Get(id);
				if (dead) dead.Destroy();
				m_3D.Remove(id);
			}
		}
	}

	void ClearAll()
	{
		if (!m_3D) return;

		for (int i = m_3D.Count() - 1; i >= 0; i--)
		{
			int id = m_3D.GetKey(i);
			Ruck3DMarker w = m_3D.Get(id);
			if (w) w.Destroy();
			m_3D.Remove(id);
		}

		m_LastRevision = -1;
	}
}
