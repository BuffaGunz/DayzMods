enum ERuckMapRPC
{
	RUCK_RPC_MARKER_ADD_REQUEST      = 77801, 
	RUCK_RPC_MARKER_EDIT_REQUEST     = 77802, 
	RUCK_RPC_MARKER_DELETE_REQUEST   = 77803, 
	RUCK_RPC_MARKER_SYNC_REQUEST     = 77804, 
	RUCK_RPC_MARKER_SYNC_RESPONSE    = 77805  
}

modded class ChernarusMap
{
	protected bool m_RuckEnable3DFromServer = false;
	
	protected ref array<ref RuckMapMarkerData> m_RuckMarkers;
	protected int m_RuckNextMarkerId;
	protected int m_RuckMarkersRevision;
	protected ref array<ref RuckMapMarkerData> m_ServerMarkers;
	static const int RUCK_MARKER_MAX = 100;

	void ChernarusMap()
	{
		if (!m_RuckMarkers)
			m_RuckMarkers = new array<ref RuckMapMarkerData>;

		if (!m_ServerMarkers)
			m_ServerMarkers = new array<ref RuckMapMarkerData>;

		m_RuckNextMarkerId = 0;
		m_RuckMarkersRevision = 0;

		if (GetGame().IsServer())
			LoadServerMarkers();
	}

	array<ref RuckMapMarkerData> GetRuckMarkers()
	{
		if (!m_RuckMarkers)
			m_RuckMarkers = new array<ref RuckMapMarkerData>;
		return m_RuckMarkers;
	}

	int GetRuckMarkersRevision()
	{
		return m_RuckMarkersRevision;
	}

	RuckMapMarkerData FindRuckMarkerById(int id)
	{
		if (!m_RuckMarkers)
			return null;

		foreach (RuckMapMarkerData m : m_RuckMarkers)
		{
			if (m && m.Id == id)
				return m;
		}
		return null;
	}
	
	

	override void OnStoreSave(ParamsWriteContext ctx)
	{
		super.OnStoreSave(ctx);

		int dataVersion = 1;
		ctx.Write(dataVersion);

		if (!m_RuckMarkers)
			m_RuckMarkers = new array<ref RuckMapMarkerData>;

		ctx.Write(m_RuckNextMarkerId);
		ctx.Write(m_RuckMarkersRevision);

		int validCount = 0;
		for (int i = 0; i < m_RuckMarkers.Count(); i++)
		{
			if (m_RuckMarkers[i])
				validCount++;
		}

		ctx.Write(validCount);

		for (int j = 0; j < m_RuckMarkers.Count(); j++)
		{
			RuckMapMarkerData m = m_RuckMarkers[j];
			if (!m) continue;

			ctx.Write(m.Id);
			ctx.Write(m.Pos);
			ctx.Write(m.TypeId);
			ctx.Write(m.Name);
			ctx.Write(m.ColorARGB);
		}
	}

	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		if (!super.OnStoreLoad(ctx, version))
			return false;

		int dataVersion = 0;
		if (!ctx.Read(dataVersion))
			return true;

		if (!m_RuckMarkers)
			m_RuckMarkers = new array<ref RuckMapMarkerData>;
		else
			m_RuckMarkers.Clear();

		int nextId = 0;
		if (ctx.Read(nextId))
			m_RuckNextMarkerId = nextId;

		int rev = 0;
		if (ctx.Read(rev))
			m_RuckMarkersRevision = rev;
		else
			m_RuckMarkersRevision = 0;

		int count = 0;
		if (!ctx.Read(count))
			return true;

		for (int i = 0; i < count; i++)
		{
			int id;
			vector pos;
			int typeId;
			string name;
			int colorARGB;

			if (!ctx.Read(id)) break;
			if (!ctx.Read(pos)) break;
			if (!ctx.Read(typeId)) break;
			if (!ctx.Read(name)) name = "";
			if (!ctx.Read(colorARGB)) colorARGB = ARGB(255, 255, 255, 255);

			RuckMapMarkerData m = new RuckMapMarkerData(id, pos, typeId, name, colorARGB);
			m_RuckMarkers.Insert(m);

			if (id >= m_RuckNextMarkerId)
				m_RuckNextMarkerId = id + 1;
		}

		return true;
	}
	
	void Ruck_BumpServerRevision()
	{
		m_RuckMarkersRevision++;
	}

	void Ruck_SendMarkersToIdentity(PlayerIdentity recipient)
	{
		SendMarkersTo(recipient);
	}

	protected void LoadServerMarkers()
	{
		if (!m_ServerMarkers)
			m_ServerMarkers = new array<ref RuckMapMarkerData>;
		else
			m_ServerMarkers.Clear();

		RuckMapSettings settings = GetRuckMapSettings();
		if (!settings)
			return;

		if (settings.EnableServerMarkers)
		{
			int idx = 0;
			foreach (RuckServerMarker sm : settings.ServerMarkers)
			{
				if (!sm) continue;

				int id = -1000 - idx;
				int col = sm.GetColorARGB();
				RuckMapMarkerData m = new RuckMapMarkerData(id, sm.Pos, 0, sm.Name, col);

				m_ServerMarkers.Insert(m);
				idx++;
			}
		}

		if (settings.EnableSpawnCacheMarkers)
		{
			string world = GetGame().GetWorldName();
			RuckSpawnCache cache;

			if (RuckSpawnCache.LoadOrBuild(world, cache) && cache && cache.Points)
			{
				int baseId = -50000;
				int spawnIdx = 0;

				int colVehicle = RuckMarkerColors.Resolve(settings.SpawnVehiclesColor);
				int colBoat    = RuckMarkerColors.Resolve(settings.SpawnBoatsColor);
				int colAnimal  = RuckMarkerColors.Resolve(settings.SpawnAnimalsColor);
				int colHunting = RuckMarkerColors.Resolve(settings.SpawnHuntingColor);

				foreach (RuckSpawnPoint p : cache.Points)
				{
					if (!p) continue;

					int spawnId = baseId - spawnIdx;
					spawnIdx++;

					int typeId;
					int spawnCol;
					string name = "";

					string cat = p.Category;
					cat.ToLower();

					if (cat == "boat")
					{
						typeId = RuckMapMarkerTypes.MARKERTYPE_SPAWN_BOAT;
						spawnCol = colBoat;
					}
					else if (cat == "animal")
					{
						typeId = RuckSpawnCacheBuilder.ResolveAnimalTypeId(p.Name);
						spawnCol = colAnimal;
					}
					else if (cat == "structure")
					{
						typeId = RuckSpawnCacheBuilder.ResolveStaticStructureTypeId(p.Name);
						spawnCol = colHunting;
					}
					else
					{
						typeId = RuckSpawnCacheBuilder.ResolveVehicleTypeId(p.Name);
						spawnCol = colVehicle;
					}

					m_ServerMarkers.Insert(new RuckMapMarkerData(spawnId, p.Pos, typeId, name, spawnCol));
				}
			}
		}
		
		if (GetGame().IsServer())
		{
			RuckMarkerAPI.AppendTo(m_ServerMarkers);
		}
		if (GetGame().IsServer())
		{
			Ruck_PurgeDynamicFromServerMarkers();
		}


	}
	
	protected void Ruck_PurgeDynamicFromServerMarkers()
	{
		if (!m_ServerMarkers) return;

		for (int i = m_ServerMarkers.Count() - 1; i >= 0; i--)
		{
			RuckMapMarkerData m = m_ServerMarkers[i];
			if (!m) continue;

			int id = m.Id;
			if (id <= -20000 && id > -50000)
			{
				m_ServerMarkers.Remove(i);
			}
		}
	}

	override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
	{
		if (rpc_type == ERuckMapRPC.RUCK_RPC_MARKER_SYNC_RESPONSE)
		{
			if (GetGame().IsClient())
				HandleSyncResponse(ctx);
			return;
		}

		if (GetGame().IsServer())
		{
			if (rpc_type == ERuckMapRPC.RUCK_RPC_MARKER_ADD_REQUEST)    { HandleAddRequest(sender, ctx); return; }
			if (rpc_type == ERuckMapRPC.RUCK_RPC_MARKER_EDIT_REQUEST)   { HandleEditRequest(sender, ctx); return; }
			if (rpc_type == ERuckMapRPC.RUCK_RPC_MARKER_DELETE_REQUEST) { HandleDeleteRequest(sender, ctx); return; }
			if (rpc_type == ERuckMapRPC.RUCK_RPC_MARKER_SYNC_REQUEST)   { HandleSyncRequest(sender); return; }
		}

		super.OnRPC(sender, rpc_type, ctx);
	}

	protected void HandleAddRequest(PlayerIdentity sender, ParamsReadContext ctx)
	{
		Param4<vector, int, string, int> p; 
		if (!ctx.Read(p))
			return;

		PlayerBase pb = ResolvePlayer(sender);

		if (!ValidateMarkerRequestOwnership(pb))
		{
			return;
		}

		if (!m_RuckMarkers)
			m_RuckMarkers = new array<ref RuckMapMarkerData>;

		if (m_RuckMarkers.Count() >= RUCK_MARKER_MAX)
		{
			SendMarkersTo(sender);
			return;
		}

		vector pos = p.param1;
		float y = GetGame().SurfaceY(pos[0], pos[2]);
		pos[1] = y + 0.35; 

		int typeId = p.param2;
		string name = p.param3;
		int colorARGB = p.param4; 

		if (!name) name = "";
		if (name.Length() > 32) name = name.Substring(0, 32);

		if (colorARGB == 0)
			colorARGB = ARGB(255, 255, 255, 255);

		int id = m_RuckNextMarkerId;
		m_RuckNextMarkerId++;

		RuckMapMarkerData m = new RuckMapMarkerData(id, pos, typeId, name, colorARGB); 
		m_RuckMarkers.Insert(m);

		m_RuckMarkersRevision++;

		SendMarkersTo(sender);
	}


	protected void HandleEditRequest(PlayerIdentity sender, ParamsReadContext ctx)
	{
		Param4<int, int, string, int> p; 
		if (!ctx.Read(p))
			return;

		PlayerBase pb = ResolvePlayer(sender);
		if (!ValidateMarkerRequestOwnership(pb))
			return;

		int markerId = p.param1;
		int newTypeId = p.param2;
		string newName = p.param3;
		int colorARGB = p.param4; 

		if (!newName) newName = "";
		if (newName.Length() > 32) newName = newName.Substring(0, 32);

		if (colorARGB == 0)
			colorARGB = ARGB(255, 255, 255, 255);

		RuckMapMarkerData m = FindRuckMarkerById(markerId);
		if (!m || m.Id < 0)
			return;

		m.SetType(newTypeId);
		m.SetName(newName);
		m.SetColor(colorARGB); 
		m_RuckMarkersRevision++;

		SendMarkersTo(sender);
	}


	protected void HandleDeleteRequest(PlayerIdentity sender, ParamsReadContext ctx)
	{
		Param1<int> p;
		if (!ctx.Read(p))
			return;

		PlayerBase pb = ResolvePlayer(sender);
		if (!ValidateMarkerRequestOwnership(pb))
			return;

		int markerId = p.param1;
		
		if (markerId < 0)
			return;

		if (!m_RuckMarkers)
			return;

		for (int i = m_RuckMarkers.Count() - 1; i >= 0; i--)
		{
			RuckMapMarkerData m = m_RuckMarkers[i];
			if (m && m.Id == markerId)
			{
				m_RuckMarkers.Remove(i);
				m_RuckMarkersRevision++;
				break;
			}
		}

		SendMarkersTo(sender);
	}

	protected void HandleSyncRequest(PlayerIdentity sender)
	{
		PlayerBase pb = ResolvePlayer(sender);
		if (!ValidateMarkerRequestOwnership(pb))
			return;

		SendMarkersTo(sender);
	}
	
	bool Ruck_Is3DEnabledFromServer()
	{
		return m_RuckEnable3DFromServer;
	}

	protected void HandleSyncResponse(ParamsReadContext ctx)
	{
		Param7<int, ref array<int>, ref array<vector>, ref array<int>, ref array<string>, ref array<int>, bool> p;
		if (!ctx.Read(p))
			return;

		int revision = p.param1;

		m_RuckEnable3DFromServer = p.param7;

		if (!m_RuckMarkers)
			m_RuckMarkers = new array<ref RuckMapMarkerData>;
		else
			m_RuckMarkers.Clear();

		int count = p.param2.Count();
		for (int i = 0; i < count; i++)
		{
			int id = p.param2[i];
			vector pos = p.param3[i];
			int typeId = p.param4[i];
			string name = p.param5[i];

			int colorARGB = ARGB(255, 255, 255, 255);
			if (p.param6 && i < p.param6.Count())
				colorARGB = p.param6[i];

			RuckMapMarkerData m = new RuckMapMarkerData(id, pos, typeId, name, colorARGB);
			m_RuckMarkers.Insert(m);

			if (id >= m_RuckNextMarkerId)
				m_RuckNextMarkerId = id + 1;
		}

		m_RuckMarkersRevision = revision;
	}

	protected PlayerBase ResolvePlayer(PlayerIdentity sender)
	{
		if (!sender)
			return null;

		string sid = sender.GetId();
		if (sid == string.Empty)
			return null;

		array<Man> players = new array<Man>;
		GetGame().GetPlayers(players);

		foreach (Man man : players)
		{
			PlayerBase pb = PlayerBase.Cast(man);
			if (!pb) continue;

			PlayerIdentity pid = pb.GetIdentity();
			if (!pid) continue;

			if (pid.GetId() == sid)
				return pb;
		}

		return null;
	}

	protected bool ValidateMarkerRequestOwnership(PlayerBase pb)
	{
		if (!pb)
			return false;

		if (pb.GetInventory().HasEntityInInventory(this))
			return true;

		EntityAI inHands = pb.GetHumanInventory().GetEntityInHands();
		if (inHands == this)
			return true;

		return false;
	}

	protected void SendMarkersTo(PlayerIdentity recipient)
	{
		if (GetGame().IsServer())
		{
			Ruck_PurgeDynamicFromServerMarkers();
		}

		if (!GetGame().IsServer())
			return;

		if (!m_RuckMarkers)
			m_RuckMarkers = new array<ref RuckMapMarkerData>;

		ref array<int> ids = new array<int>;
		ref array<vector> poses = new array<vector>;
		ref array<int> types = new array<int>;
		ref array<string> names = new array<string>;
		ref array<int> colors = new array<int>;

		foreach (RuckMapMarkerData sm : m_ServerMarkers)
		{
			if (!sm) continue;
			ids.Insert(sm.Id);
			poses.Insert(sm.Pos);
			types.Insert(sm.TypeId);
			names.Insert(sm.Name);
			colors.Insert(sm.ColorARGB);
		}

		ref array<ref RuckMapMarkerData> dyn = new array<ref RuckMapMarkerData>;
		RuckMarkerAPI.AppendTo(dyn);

		foreach (RuckMapMarkerData dm : dyn)
		{
			if (!dm) continue;
			ids.Insert(dm.Id);
			poses.Insert(dm.Pos);
			types.Insert(dm.TypeId);
			names.Insert(dm.Name);
			colors.Insert(dm.ColorARGB);
		}

		foreach (RuckMapMarkerData m : m_RuckMarkers)
		{
			if (!m) continue;
			ids.Insert(m.Id);
			poses.Insert(m.Pos);
			types.Insert(m.TypeId);
			names.Insert(m.Name);
			colors.Insert(m.ColorARGB);
		}

		RuckMapSettings s = GetRuckMapSettings();
		bool enable3D = false;
		if (s)
			enable3D = s.Enable3DMarkers;

		Param7<int, ref array<int>, ref array<vector>, ref array<int>, ref array<string>, ref array<int>, bool> payload = new Param7<int, ref array<int>, ref array<vector>, ref array<int>, ref array<string>, ref array<int>, bool>(m_RuckMarkersRevision, ids, poses, types, names, colors, enable3D);

		GetGame().RPCSingleParam(this, ERuckMapRPC.RUCK_RPC_MARKER_SYNC_RESPONSE, payload, true, recipient);
	}

};
