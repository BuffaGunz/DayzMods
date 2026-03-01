class RuckPlane extends CrashBase
{
	EntityAI m_Container;
	string m_KeyType;
	bool m_ContainerLanded;
	float m_DescentSpeed;

	private vector m_DriftOffset;
	private float m_MaxDriftRadius;
	private float m_DriftSpeed;
	private float m_DriftAngle;

	vector m_DropLocation;
	float m_Angle;
	float m_Height = 200.0;
	float m_Speed = 35.0;
	float m_DropRadius = 20.0;
	bool m_HasDropped;
	
	protected string m_RuckPlane_EngineSoundSet;
	protected EffectSound m_RuckPlane_EngineSound;

	static string m_LastDirection = "";

	static void SpawnSite()
	{
		auto settings = AirDropSettings.Get();
		vector dropLocation;
		string customTail = "Supply drop inbound for"; 

		if (settings.EnableCustomDropSites && settings.CustomDropSites.Count() > 0)
		{
			DropSiteData selectedSite = settings.CustomDropSites.GetRandomElement();
			dropLocation = selectedSite.Position;
			customTail = selectedSite.NotificationMessage; 
			dropLocation[1] = GetGame().SurfaceY(dropLocation[0], dropLocation[2]);
		}
		else
		{
			dropLocation = FindValidDropSite();
			dropLocation[1] = GetGame().SurfaceY(dropLocation[0], dropLocation[2]);
		}

		ref array<string> directions = { "SouthWest", "SouthEast", "NorthWest", "NorthEast" };
		if (m_LastDirection != "") directions.RemoveItem(m_LastDirection);
		string dir = directions.GetRandomElement();
		m_LastDirection = dir;

		vector startPos;
		float pitch = 0, roll = 0, yaw = 0;
		float worldSize = GetGame().GetWorld().GetWorldSize();

		switch (dir)
		{
			case "SouthWest":
				startPos = Vector(100, 200, 100);
				pitch = 40;
				roll = 180;
				yaw = 30;
				break;
			case "SouthEast":
				startPos = Vector(worldSize - 100, 200, 100);
				pitch = 40;
				roll = 180;
				yaw = 30;
				break;
			case "NorthWest":
				startPos = Vector(100, 200, worldSize - 100);
				pitch = 40;
				roll = 180;
				yaw = 30;
				break;
			case "NorthEast":
				startPos = Vector(worldSize - 100, 200, worldSize - 100);
				pitch = 40;
				roll = 180;
				yaw = 30;
				break;
		}

		RuckPlane plane = RuckPlane.Cast(GetGame().CreateObject("RuckPlane", startPos, false, true));
		if (plane)
		{
			plane.SetDropLocation(dropLocation);
			vector orientation = Vector(yaw, pitch, roll);
			plane.SetOrientation(orientation);
		}
		
		if (AirDropSettings.Get().EnableDropNotification)
		{
			SendDropNotification(dropLocation, customTail);
		}

	}

	void SetDropLocation(vector dropLocation)
	{
		m_DropLocation = dropLocation;

		vector direction = m_DropLocation - GetPosition();
		direction.Normalize();

		m_Angle = Math.Atan2(direction[2], direction[0]);
	}

    void RuckPlane()
	{
		StartFlightLoop();
		m_RuckPlane_EngineSoundSet = "RuckPlane_Loop_SoundSet";
	}
	
	override void EEInit()
	{
		super.EEInit();
		if (m_RuckPlane_EngineSoundSet && GetGame().IsClient())
		{
			PlaySoundSetLoop(m_RuckPlane_EngineSound, m_RuckPlane_EngineSoundSet, 3.0, 3.0);
		}
	}

	override void EEDelete(EntityAI parent)
	{
		super.EEDelete(parent);
		if (m_RuckPlane_EngineSound)
		{
			StopSoundSet(m_RuckPlane_EngineSound);
		}
	}


	void StartFlightLoop()
	{
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.FlightUpdate, 10, true);
	}

	void FlightUpdate()
	{
		if (!GetGame().IsServer())
			return;

		vector pos = GetPosition();

		vector vel = Vector(Math.Cos(m_Angle), 0, Math.Sin(m_Angle)) * m_Speed * 0.0100;
		pos += vel;

		pos[1] = GetGame().SurfaceY(pos[0], pos[2]) + m_Height;
		SetPosition(pos);

		vector dir = Vector(-Math.Cos(m_Angle), 0, -Math.Sin(m_Angle));
		SetDirection(dir);

		vector delta = pos - m_DropLocation;
		delta[1] = 0; 
		float dist = delta.Length();

		if (!m_HasDropped && dist < m_DropRadius)
		{
			DropContainer();
			m_HasDropped = true;
		}

		if (!IsInWorldBounds(pos))
		{
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).Remove(this.FlightUpdate);
			GetGame().ObjectDelete(this);
		}

	}
	
	static string PickEnabledContainerType()
	{
		auto settings = AirDropSettings.Get();

		ref array<string> candidates = new array<string>();

		if (settings && settings.EnableContainerBlue)   candidates.Insert("AirdropContainerBlue");
		if (settings && settings.EnableContainerRed)    candidates.Insert("AirdropContainerRed");
		if (settings && settings.EnableContainerYellow) candidates.Insert("AirdropContainerYellow");
		if (settings && settings.EnableContainerOrange) candidates.Insert("AirdropContainerOrange");

		if (candidates.Count() == 0)
		{
			candidates.Insert("AirdropContainerBlue");
			candidates.Insert("AirdropContainerRed");
			candidates.Insert("AirdropContainerYellow");
			candidates.Insert("AirdropContainerOrange");
		}

		return candidates.GetRandomElement();
	}

	static string KeyTypeFor(string containerType)
	{
		switch (containerType)
		{
			case "AirdropContainerBlue":   return "ShippingContainerKeys_Blue";
			case "AirdropContainerRed":    return "ShippingContainerKeys_Red";
			case "AirdropContainerYellow": return "ShippingContainerKeys_Yellow";
			case "AirdropContainerOrange": return "ShippingContainerKeys_Orange";
		}
		return "";
	}


	void DropContainer()
	{
		string selectedType = PickEnabledContainerType();
		m_KeyType = KeyTypeFor(selectedType);

		m_DropLocation = GetPosition(); 
		m_Container = EntityAI.Cast(GetGame().CreateObject(selectedType, m_DropLocation, false, false));

		if (!m_Container)
			return;

		m_Container.SetOrientation(GetOrientation()); 
		m_Container.SetAffectPathgraph(true, true);
		GetGame().UpdatePathgraphRegionByObject(m_Container);

		m_ContainerLanded = false;
		m_DescentSpeed = 40.0;

		m_DriftOffset = "0 0 0";
		m_DriftAngle = Math.RandomFloatInclusive(0, Math.PI2);
		m_MaxDriftRadius = 50.0; 
		m_DriftSpeed = 0.2;     

		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.UpdateDropLoop, 10, true);
	}

	void UpdateDropLoop()
	{
		AirDropSettings settings = AirDropSettings.Get();
		
		if (!m_Container || !m_Container.IsAlive())
		{
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).Remove(this.UpdateDropLoop);
			return;
		}

		vector pos = m_Container.GetPosition();
		float groundY = GetGame().SurfaceY(pos[0], pos[2]);

		if (!m_ContainerLanded && pos[1] > groundY + 0.05)
		{
			pos[1] = Math.Max(pos[1] - m_DescentSpeed * 0.0100, groundY);

			m_DriftAngle += m_DriftSpeed * 0.0100;
			if (m_DriftAngle > Math.PI2)
				m_DriftAngle -= Math.PI2;

			float driftX = Math.Cos(m_DriftAngle) * 0.01; 
			float driftZ = Math.Sin(m_DriftAngle) * 0.01;

			vector driftStep = Vector(driftX, 0, driftZ);
			m_DriftOffset = m_DriftOffset + driftStep;

			if (vector.Distance("0 0 0", m_DriftOffset) > m_MaxDriftRadius)
			{
				m_DriftOffset = m_DriftOffset.Normalized() * m_MaxDriftRadius;
			}

			pos[0] = m_DropLocation[0] + m_DriftOffset[0];
			pos[2] = m_DropLocation[2] + m_DriftOffset[2];

			m_Container.SetPosition(pos);
		}
		else if (!m_ContainerLanded)
		{
			m_ContainerLanded = true;

			#ifdef SERVER
				string ctype = m_Container.GetType();  

				#ifdef BASICMAP
					RuckBasicMarkerService.ServerCreateMarkerForContainer(ctype, m_Container);
				#endif
				#ifdef LBmaster_Groups
					RuckLBMasterMarkerService.ServerCreateMarkerForContainer(ctype, m_Container);
				#endif
				#ifdef EXPANSIONMODNAVIGATION
					RuckExpansionMarkerService.ServerCreateMarkerForContainer(ctype, m_Container);
				#endif
				#ifdef RUCKMAP
					RuckMapDropCache.ServerAdd(m_Container);
				#endif
			#endif

			pos[1] = groundY;
			pos[0] = m_DropLocation[0] + m_DriftOffset[0];
			pos[2] = m_DropLocation[2] + m_DriftOffset[2];
			m_Container.SetPosition(pos);

			vector ori = m_Container.GetOrientation();
			ori[0] = Math.WrapFloat(ori[0] + 90.0, 0.0, 360.0);
			m_Container.SetOrientation(ori);

			vector normal = GetGame().SurfaceGetNormal(pos[0], pos[2]);

			vector forward = m_Container.GetDirection();
			if (Math.AbsFloat(forward * normal) > 0.99)
				forward = vector.Direction(pos, pos + "0 0 1");

			vector right = forward * normal;
			right.Normalize();

			forward = normal * right;
			forward.Normalize();

			vector mat[3];
			mat[0] = forward; 
			mat[1] = normal;
			mat[2] = right; 

			vector terrainOri = Math3D.MatrixToAngles(mat);
			m_Container.SetOrientation(terrainOri);

			m_Container.PlaceOnSurface();

			bool GasSpawned = false;

			if (settings && settings.EnableGasZones)
			{
				int chance = Math.Clamp(settings.GasZoneChancePercent, 0, 100);
				if (chance >= 100 || (chance > 0 && Math.RandomIntInclusive(1, 100) <= chance))
				{
					vector droppos = m_Container.GetPosition();
					droppos[1] = GetGame().SurfaceY(droppos[0], droppos[2]) + 0.5;
					
					ContaminatedArea_Static AreaCloud = ContaminatedArea_Static.Cast(GetGame().CreateObject("ContaminatedArea_Static", droppos));
					ContaminatedArea_Dynamic AreaDmg  = ContaminatedArea_Dynamic.Cast(GetGame().CreateObject("ContaminatedArea_Dynamic", droppos));

					if (AreaCloud || AreaDmg)
					{
						GasSpawned = true;

						if (AreaCloud)
						{
							AreaCloud.SetSynchDirty();
							GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(GetGame().ObjectDelete, 15 * 60 * 1000, false, AreaCloud);
						}

						if (AreaDmg)
						{
							AreaDmg.SetSynchDirty();
							GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(GetGame().ObjectDelete, 15 * 60 * 1000, false, AreaDmg);
						}
					}
				}
			}

			m_Container.SetAffectPathgraph(true, true);
			GetGame().UpdatePathgraphRegionByObject(m_Container);
			m_Container.SetSynchDirty();

			FillContainerWithRandomLoot(m_Container);

			if (GasSpawned)
				SpawnZombiesAtDrop_NBC(m_Container, m_KeyType);
			else
				SpawnZombiesAtDrop(m_Container, m_KeyType);

			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).Remove(this.UpdateDropLoop);
		}
	}	
	
	static vector FindValidDropSite()
	{
		float worldSize = GetGame().GetWorld().GetWorldSize();
		float margin = 1000;
		float minXZ = margin;
		float maxXZ = worldSize - margin;

		const int MAX_ATTEMPTS = 200;

		for (int i = 0; i < MAX_ATTEMPTS; i++)
		{
			vector site = Vector(Math.RandomFloatInclusive(minXZ, maxXZ), 0, Math.RandomFloatInclusive(minXZ, maxXZ));
			site[1] = GetGame().SurfaceY(site[0], site[2]);

			if (site[1] <= 0)
			{
				PrintFormat("[PlaneDrop] Rejected position %1,%2: invalid surface Y (%3)", site[0], site[2], site[1]);
				continue;
			}

			vector normal = GetGame().SurfaceGetNormal(site[0], site[2]);
			if (normal[1] < 0.95)
			{
				PrintFormat("[PlaneDrop] Rejected position %1,%2: slope too steep", site[0], site[2]);
				continue;
			}

			bool waterNearby = false;
			const float waterCheckRadius = 15.0;

			for (float angle = 0; angle < 360; angle += 30)
			{
				vector offset = Vector(Math.Cos(angle) * waterCheckRadius, 0, Math.Sin(angle) * waterCheckRadius);
				vector checkPos = site + offset;

				string surfType;
				GetGame().SurfaceGetType(checkPos[0], checkPos[2], surfType);
				surfType.ToLower();

				if (GetGame().SurfaceIsSea(checkPos[0], checkPos[2]) || surfType.Contains("pond") || surfType.Contains("lake") || surfType.Contains("river") || surfType.Contains("swamp") || surfType.Contains("water"))
				{
					waterNearby = true;
					PrintFormat("[PlaneDrop] Rejected position %1,%2: water/sea within 30m", checkPos[0], checkPos[2]);
					break;
				}
			}

			if (waterNearby)
				continue;

			array<Object> objects = {};
			array<CargoBase> dummy = {};
			GetGame().GetObjectsAtPosition(site, 15.0, objects, dummy);

			bool blocked = false;
			foreach (Object obj : objects)
			{
				if (!obj) continue;

				string type = obj.GetType();
				type.ToLower();

				if (type.Contains("treehard") || type.Contains("treesoft") || type.Contains("bushhard") || type.Contains("bushsoft") || type.Contains("rock") || type.Contains("stone") || type.Contains("wreck") || type.Contains("fence") || type.Contains("wall") || type.Contains("rail") || type.Contains("wreck") || type.Contains("house") || type.Contains("bldr_"))
				{
					blocked = true;
					PrintFormat("[PlaneDrop] Rejected position %1,%2: blocked by %3 within 30m", site[0], site[2], type);
					break;
				}
			}

			if (blocked)
				continue;

			PrintFormat("[PlaneDrop] Valid Drop site found: %1,%2", site[0], site[2]);
			return site;
		}

		Print("[PlaneDrop] Failed to find valid Drop site after max attempts.");
		return Vector(7500, 0, 7500);
	}

	bool IsInWorldBounds(vector pos)
	{
		float size = GetGame().GetWorld().GetWorldSize();
		return pos[0] >= -10 && pos[0] <= size + 10 && pos[2] >= -10 && pos[2] <= size + 10;
	}
	
	static void SpawnZombiesAtDrop_NBC(EntityAI container, string keyName)
	{
		auto settings = AirDropSettings.Get();
		int zombieCount = Math.Clamp(settings.ZombieCount, 1, 40);

		ref array<string> zombieTypes = {
			"ZmbM_NBC_Grey",
			"ZmbM_NBC_White",
			"ZmbM_NBC_Yellow"
		};

		vector wreckPos = container.GetPosition();
		ref array<DayZInfected> spawnedZombies = new array<DayZInfected>();

		for (int i = 0; i < zombieCount; ++i)
		{
			float minRadius = 10.0;
			float maxRadius = 25.0;

			float angle = Math.RandomFloat(0, 360);
			float radius = Math.RandomFloat(minRadius, maxRadius);

			float xOffset = radius * Math.Cos(angle);
			float zOffset = radius * Math.Sin(angle);

			vector zombiePos = wreckPos + Vector(xOffset, 0, zOffset);
			zombiePos[1] = GetGame().SurfaceY(zombiePos[0], zombiePos[2]);

			DayZInfected zmb = DayZInfected.Cast(GetGame().CreateObject(zombieTypes.GetRandomElement(), zombiePos, false, true, true));
			if (zmb)
			{
				zmb.PlaceOnSurface();
				zmb.SetOrientation(Vector(0, Math.RandomFloat(0, 360), 0));
				zmb.SetAffectPathgraph(true, true);
				zmb.SetSynchDirty();
				spawnedZombies.Insert(zmb);
			}
		}

		if (keyName != "" && spawnedZombies.Count() > 0)
		{
			DayZInfected keyZombie = spawnedZombies.GetRandomElement();
			ItemBase keyItem = ItemBase.Cast(keyZombie.GetInventory().CreateInInventory(keyName));
			if (keyItem)
			{
				keyItem.SetHealth01("", "", 0.10);
				PrintFormat("[AirDrop] Spawned key '%1' on NBC zombie: %2", keyName, keyZombie);
			}
			else
			{
				PrintFormat("[AirDrop] ERROR: Failed to create key '%1' on NBC zombie: %2", keyName, keyZombie);
			}
		}
	}


	static void SpawnZombiesAtDrop(EntityAI container, string keyName)
	{
		auto settings = AirDropSettings.Get();
		int zombieCount = Math.Clamp(settings.ZombieCount, 1, 40);

		ref array<string> zombieTypes;

		if (settings.EnableCustomZombieTypes && settings.CustomZombieTypes.Count() > 0)
		{
			zombieTypes = settings.CustomZombieTypes;
		}
		else
		{
			zombieTypes = {
				"ZmbF_BlueCollarFat_Blue", "ZmbF_BlueCollarFat_Green", "ZmbF_BlueCollarFat_Red", "ZmbF_BlueCollarFat_White",
				"ZmbF_CitizenANormal_Beige", "ZmbF_CitizenANormal_Blue", "ZmbF_CitizenANormal_Brown", "ZmbF_CitizenBSkinny", "ZmbF_Clerk_Normal_Blue", "ZmbF_Clerk_Normal_Green", "ZmbF_Clerk_Normal_Red", "ZmbF_Clerk_Normal_White",
				"ZmbF_DoctorSkinny", "ZmbF_HikerSkinny_Blue", "ZmbF_HikerSkinny_Green", "ZmbF_HikerSkinny_Grey", "ZmbF_HikerSkinny_Red", "ZmbF_JoggerSkinny_Blue", "ZmbF_JoggerSkinny_Brown", "ZmbF_JoggerSkinny_Green", "ZmbF_JoggerSkinny_Red",
				"ZmbF_JournalistNormal_Blue", "ZmbF_JournalistNormal_Green", "ZmbF_JournalistNormal_Red", "ZmbF_JournalistNormal_White", "ZmbF_MechanicNormal_Beige", "ZmbF_MechanicNormal_Green", "ZmbF_MechanicNormal_Grey", "ZmbF_MechanicNormal_Orange",
				"ZmbF_MilkMaidOld_Beige", "ZmbF_MilkMaidOld_Black", "ZmbF_MilkMaidOld_Green", "ZmbF_MilkMaidOld_Grey", "ZmbF_NurseFat", "ZmbF_NurseFat_Winter", "ZmbM_ParamedicNormal_Blue", "ZmbF_ParamedicNormal_Green", "ZmbF_ParamedicNormal_Red",
				"ZmbF_PatientOld", "ZmbF_PatientOld_Winter", "ZmbF_PoliceWomanNormal", "ZmbF_ShortSkirt_beige", "ZmbF_ShortSkirt_black", "ZmbF_ShortSkirt_brown", "ZmbF_ShortSkirt_checks", "ZmbF_ShortSkirt_green",
				"ZmbF_ShortSkirt_grey", "ZmbF_ShortSkirt_red", "ZmbF_ShortSkirt_stripes", "ZmbF_ShortSkirt_white", "ZmbF_ShortSkirt_yellow", "ZmbF_SkaterYoung_Brown", "ZmbF_SkaterYoung_Striped", "ZmbF_SkaterYoung_Violet",
				"ZmbF_SurvivorNormal_Blue", "ZmbF_SurvivorNormal_Orange", "ZmbF_SurvivorNormal_Red", "ZmbF_SurvivorNormal_White", "ZmbF_VillagerOld_Blue", "ZmbF_VillagerOld_Green", "ZmbF_VillagerOld_Red", "ZmbF_VillagerOld_White",
				"ZmbM_CitizenASkinny_Blue", "ZmbM_CitizenASkinny_Brown", "ZmbM_CitizenASkinny_Grey", "ZmbM_CitizenASkinny_Red", "ZmbM_CitizenBFat_Blue", "ZmbM_CitizenBFat_Green", "ZmbM_CitizenBFat_Red",
				"ZmbM_ClerkFat_Brown", "ZmbM_ClerkFat_Grey", "ZmbM_ClerkFat_Khaki", "ZmbM_ClerkFat_White", "ZmbM_CommercialPilotOld_Blue", "ZmbM_CommercialPilotOld_Brown", "ZmbM_CommercialPilotOld_Grey", "ZmbM_CommercialPilotOld_Olive",
				"ZmbM_ConstrWorkerNormal_Beige", "ZmbM_ConstrWorkerNormal_Black", "ZmbM_ConstrWorkerNormal_Green", "ZmbM_ConstrWorkerNormal_Grey",
				"ZmbM_DoctorFat", "ZmbM_DoctorFat_Winter", "ZmbM_FarmerFat_Beige", "ZmbM_FarmerFat_Blue", "ZmbM_FarmerFat_Brown", "ZmbM_FarmerFat_Green", "ZmbM_FirefighterNormal",
				"ZmbM_FishermanOld_Blue", "ZmbM_FishermanOld_Green", "ZmbM_FishermanOld_Grey", "ZmbM_FishermanOld_Red", "ZmbM_Gamedev_Black", "ZmbM_Gamedev_Blue", "ZmbM_Gamedev_Gray",
				"ZmbM_HandymanNormal_Beige", "ZmbM_HandymanNormal_Blue", "ZmbM_HandymanNormal_Green", "ZmbM_HandymanNormal_Grey", "ZmbM_HandymanNormal_White", "ZmbM_HeavyIndustryWorker",
				"ZmbM_HermitSkinny_Beige", "ZmbM_HermitSkinny_Black", "ZmbM_HermitSkinny_Green", "ZmbM_HermitSkinny_Red", "ZmbM_HikerSkinny_Blue", "ZmbM_HikerSkinny_Green", "ZmbM_HikerSkinny_Yellow",
				"ZmbM_HunterOld_Autumn", "ZmbM_HunterOld_Spring", "ZmbM_HunterOld_Summer", "ZmbM_HunterOld_Winter", "ZmbM_Jacket_beige", "ZmbM_Jacket_black", "ZmbM_Jacket_blue", "ZmbM_Jacket_bluechecks", "ZmbM_Jacket_brown",
				"ZmbM_Jacket_greenchecks", "ZmbM_Jacket_grey", "ZmbM_Jacket_khaki", "ZmbM_Jacket_magenta", "ZmbM_Jacket_stripes", "ZmbM_JoggerSkinny_Blue", "ZmbM_JoggerSkinny_Green", "ZmbM_JoggerSkinny_Red", "ZmbM_JournalistSkinny",
				"ZmbM_MechanicSkinny_Blue", "ZmbM_MechanicSkinny_Green", "ZmbM_MechanicSkinny_Grey", "ZmbM_MechanicSkinny_Red", "ZmbM_MotobikerFat_Beige", "ZmbM_MotobikerFat_Black", "ZmbM_MotobikerFat_Blue",
				"ZmbM_NBC_Grey", "ZmbM_NBC_White", "ZmbM_NBC_Yellow", "ZmbM_OffshoreWorker_Green", "ZmbM_OffshoreWorker_Orange", "ZmbM_OffshoreWorker_Red", "ZmbM_OffshoreWorker_Yellow",
				"ZmbM_ParamedicNormal_Black", "ZmbM_ParamedicNormal_Blue", "ZmbM_ParamedicNormal_Green", "ZmbM_ParamedicNormal_Red", "ZmbM_PatientSkinny", "ZmbM_PatientSkinny_Winter",
				"ZmbM_PatrolNormal_Autumn", "ZmbM_PatrolNormal_Flat", "ZmbM_PatrolNormal_PautRev", "ZmbM_PatrolNormal_Summer", "ZmbM_PatrolNormal_Winter", "ZmbM_PolicemanFat", "ZmbM_PolicemanSpecForce", "ZmbM_PolicemanSpecForce_Heavy", "ZmbM_PrisonerSkinny",
				"ZmbM_SkaterYoung_Blue", "ZmbM_SkaterYoung_Brown", "ZmbM_SkaterYoung_Green", "ZmbM_SkaterYoung_Grey", "ZmbM_SoldierNormal", "ZmbM_VillagerOld_Blue", "ZmbM_VillagerOld_Green", "ZmbM_VillagerOld_White",
				"ZmbM_eastSoldier_Heavy_Navy", "ZmbM_eastSoldier_normal_Navy", "ZmbM_priestPopSkinny", "ZmbM_usSoldier_Heavy_Woodland", "ZmbM_usSoldier_Officer_Desert", "ZmbM_usSoldier_normal_Desert", "ZmbM_usSoldier_normal_Woodland"
			};
		}

		vector wreckPos = container.GetPosition();
		ref array<DayZInfected> spawnedZombies = new array<DayZInfected>();

		for (int i = 0; i < zombieCount; ++i)
		{
			float minRadius = 10.0;
			float maxRadius = 25.0;

			float angle = Math.RandomFloat(0, 360);
			float radius = Math.RandomFloat(minRadius, maxRadius);

			float xOffset = radius * Math.Cos(angle);
			float zOffset = radius * Math.Sin(angle);

			vector zombiePos = wreckPos + Vector(xOffset, 0, zOffset);
			zombiePos[1] = GetGame().SurfaceY(zombiePos[0], zombiePos[2]);

			DayZInfected zmb = DayZInfected.Cast(GetGame().CreateObject(zombieTypes.GetRandomElement(), zombiePos, false, true, true));
			if (zmb)
			{
				zmb.PlaceOnSurface();
				zmb.SetOrientation(Vector(0, Math.RandomFloat(0, 360), 0));
				zmb.SetAffectPathgraph(true, true);
				zmb.SetSynchDirty();
				spawnedZombies.Insert(zmb);
			}
		}

		if (keyName != "" && spawnedZombies.Count() > 0)
		{
			DayZInfected keyZombie = spawnedZombies.GetRandomElement();
			ItemBase keyItem = ItemBase.Cast(keyZombie.GetInventory().CreateInInventory(keyName));
			if (keyItem)
			{
				keyItem.SetHealth01("", "", 0.10);
				PrintFormat("[AirDrop] Spawned key '%1' on zombie: %2", keyName, keyZombie);
			}
			else
			{
				PrintFormat("[AirDrop] ERROR: Failed to create key '%1' on zombie: %2", keyName, keyZombie);
			}
		}
	}
	
	static EntityAI FindAttachmentByType(EntityAI parent, string typeName)
	{
		for (int i = 0; i < parent.GetInventory().AttachmentCount(); i++)
		{
			EntityAI attachment = parent.GetInventory().GetAttachmentFromIndex(i);
			if (attachment && attachment.GetType() == typeName)
			{
				return attachment;
			}
		}
		return null;
	}

	static void FillContainerWithRandomLoot(EntityAI container)
	{
		string containerType = container.GetType();
		string crateType = "";

		switch (containerType)
		{
			case "AirdropContainerRed":    crateType = "RuckStorageRed"; break;
			case "AirdropContainerBlue":   crateType = "RuckStorageBlue"; break;
			case "AirdropContainerYellow": crateType = "RuckStorageYellow"; break;
			case "AirdropContainerOrange": crateType = "RuckStorageOrange"; break;
			default:
				Print("⚠️ Unknown container type: " + containerType);
				return;
		}

		EntityAI crate = FindAttachmentByType(container, crateType);
		if (!crate)
		{
			Print("⚠️ No attached storage crate of type " + crateType + " found on container: " + containerType);
			return;
		}

		// Fetch config once
		auto settings = AirDropSettings.Get();
		ref array<string> lootPool = new array<string>();

		int maxLoot = 0;

		if (crateType == "RuckStorageRed")
		{
			maxLoot = Math.Clamp(settings.MaxLootItemsRed, 1, 30);
			if (HasCustomLootFor("Red", settings))
				lootPool = settings.CustomLootItemsRed;
			else
				lootPool.InsertAll({
					"FNX45","VSS","ASVAL","Vikhr","SV98","Winchester70","Mosin9130","SKS","AKM","AK74",
					"AKS74U","AK101","M4A1","M16A2","FAMAS","Aug","AugShort","FAL","SVD","SVD_Wooden",
					"Engraved1911","B95","Saiga","Deagle","Deagle_Gold","Scout","CZ550","R12","M14","M79",
					"PlateCarrierVest","PlateCarrierVest_Black","PlateCarrierVest_Green","PlateCarrierVest_Camo","PlateCarrierVest_Winter",
					"GorkaHelmet","GorkaHelmet_Black","Mich2001Helmet","AliceBag_Green","AliceBag_Black","AliceBag_Camo",
					"OMKPants_Navy","OMKJacket_Navy","MilitaryBoots_Black","MilitaryBelt",
					"Plastic_Explosive","AmmoBox_762x54_20Rnd","Ammo_308Win","AmmoBox_545x39_20Rnd","AmmoBox_556x45_20Rnd",
					"AmmoBox_762x39_20Rnd","AmmoBox_9x39AP_20Rnd","Ammo_40mm_Explosive","Ammo_40mm_ChemGas",
					"NVGoggles","NVGHeadstrap","Headtorch_Grey","Headtorch_Black","UniversalLight", "M67Grenade", "RGD5Grenade",
					"M4_Suppressor","AK_Suppressor","PistolSuppressor", "AmmoBox_00buck_10rnd", "AmmoBox_22_50Rnd", "AmmoBox_308WinTracer_20Rnd", "AmmoBox_357_20Rnd", "AmmoBox_762x39_20Rnd", "AmmoBox_9x19_25rnd"
				});
		}
		else if (crateType == "RuckStorageBlue")
		{
			maxLoot = Math.Clamp(settings.MaxLootItemsBlue, 1, 30);
			if (HasCustomLootFor("Blue", settings))
				lootPool = settings.CustomLootItemsBlue;
			else
				lootPool.InsertAll({
					"NailBox", "Shovel", "Hatchet", "SledgeHammer", "CombinationLock", "MetalPlate", "Pickaxe",
					"Pliers", "SeaChest", "WoodAxe", "WoodenCrate", "BarbedWire", "Barrel_Green", "Barrel_Red",
					"CarTent", "Crowbar", "Hammer", "HandSaw", "MetalWire", "Whetstone", "LargeTent",
					"Hacksaw", "CombinationLock", "CombinationLock4"
				});
		}
		else if (crateType == "RuckStorageYellow")
		{
			maxLoot = Math.Clamp(settings.MaxLootItemsYellow, 1, 30);
			if (HasCustomLootFor("Yellow", settings))
				lootPool = settings.CustomLootItemsYellow;
			else
				lootPool.InsertAll({
					"SalineBagIV", "BandageDressing", "Epinephrine", "Morphine", "VitaminBottle", "BloodBagEmpty", "TetracyclineAntibiotics",
					"GasMask_Filter", "IodineTincture", "NBCBootsGray", "NBCGlovesGray", "NBCHoodGray", "NBCJacketGray","NBCPantsGray",
					"PainkillerTablets", "StartKitIV", "BloodTestKit", "CharcoalTablets", "ChelatingTablets", "AntiChemInjector",
					"GP5GasMask", "AirborneMask", "HipPack_Medical", "FirstAidKit"
				});
		}
		else if (crateType == "RuckStorageOrange")
		{
			maxLoot = Math.Clamp(settings.MaxLootItemsOrange, 1, 30);
			if (HasCustomLootFor("Orange", settings))
				lootPool = settings.CustomLootItemsOrange;
			else
				lootPool.InsertAll({
					"SKS", "IJ70", "TacticalBaconCan", "Canteen", "Battery9V", "Compass", "DuctTape", "TunaCan", "CrabCan", "Honey",
					"Lunchmeat", "PeachesCan", "PorkCan", "SodaCan_Cola", "SodaCan_Fronta", "SodaCan_Kvass", "SodaCan_Pipsi", "SodaCan_Spite", "SpaghettiCan",
					"AmmoBox_00buck_10rnd", "AmmoBox_22_50Rnd", "AmmoBox_308WinTracer_20Rnd", "AmmoBox_357_20Rnd", "AmmoBox_762x39_20Rnd", "AmmoBox_9x19_25rnd",
					"Izh18", "Izh18Shotgun", "Izh43Shotgun", "Winchester70", "CZ527", "CZ75", "BearTrap", "LandMineTrap", "HipPack_Party", "HipPack_Green",
					"LongHorn", "MKII", "Scout", "P1", "Ruger1022", "ElectronicRepairKit", "LeatherSewingKit"
				});
		}
		else
		{
			Print("⚠️ Unknown crate type: " + crateType);
			return;
		}

		ref map<string, ref array<string>> weaponBonusLoot = GetWeaponBonusLootweaponMap();

		ref array<string> shuffledLoot = new array<string>;
		shuffledLoot.Copy(lootPool);
		ShuffleStringArray(shuffledLoot);

		int lootIndex = 0;

		for (int i = 0; i < maxLoot; ++i)
		{
			if (lootIndex >= shuffledLoot.Count())
			{
				ShuffleStringArray(shuffledLoot);
				lootIndex = 0;
			}

			string itemName = shuffledLoot.Get(lootIndex);
			lootIndex++;

			ItemBase item = ItemBase.Cast(crate.GetInventory().CreateInInventory(itemName));
			if (item)
			{
				if (settings.PristineLoot)
				{
					item.SetHealth01("", "", 1.0);
				}
				else
				{
					item.SetHealth01("", "", Math.RandomFloat(0.4, 1.0));
				}

				if (weaponBonusLoot.Contains(itemName))
				{
					ref array<string> bonusItems = weaponBonusLoot.Get(itemName);
					foreach (string bonusName : bonusItems)
					{
						ItemBase bonusItem = ItemBase.Cast(crate.GetInventory().CreateInInventory(bonusName));
						if (bonusItem)
						{
							if (settings.PristineLoot)
							{
								bonusItem.SetHealth01("", "", 1.0);
							}
							else
							{
								bonusItem.SetHealth01("", "", Math.RandomFloat(0.6, 1.0));
							}
						}
						else
						{
							Print("⚠️ Failed to spawn bonus item: " + bonusName + " for weapon: " + itemName);
						}
					}
				}
			}
			else
			{
				Print("⚠️ Cannot add " + itemName + " to crate inventory " + crateType);
			}
		}

	}
	
	static void ShuffleStringArray(ref array<string> arr)
	{
		int count = arr.Count();
		for (int i = 0; i < count; i++)
		{
			int j = Math.RandomInt(i, count); 
			if (i != j)
			{
				string temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}

	static bool HasCustomLootFor(string color, AirDropSettings settings)
	{
		if (!settings) return false;

		if (color == "Red")
		{
			return settings.EnableCustomLootItemsRed && settings.CustomLootItemsRed && settings.CustomLootItemsRed.Count() > 0;
		}
		else if (color == "Blue")
		{
			return settings.EnableCustomLootItemsBlue && settings.CustomLootItemsBlue && settings.CustomLootItemsBlue.Count() > 0;
		}
		else if (color == "Yellow")
		{
			return settings.EnableCustomLootItemsYellow && settings.CustomLootItemsYellow && settings.CustomLootItemsYellow.Count() > 0;
		}
		else if (color == "Orange")
		{
			return settings.EnableCustomLootItemsOrange && settings.CustomLootItemsOrange && settings.CustomLootItemsOrange.Count() > 0;
		}

		return false;
	}
	
	static ref map<string, ref array<string>> GetWeaponBonusLootweaponMap()
	{
		auto weaponMap = new map<string, ref array<string>>();

		ref array<string> arr;

		arr = new array<string>();
		arr.InsertAll({"Mag_MKII_10Rnd", "AmmoBox_22_50Rnd"});
		weaponMap.Insert("MKII", arr);

		arr = new array<string>();
		arr.InsertAll({"Mag_CZ75_15Rnd", "PistolSuppressor", "TLRLight", "AmmoBox_9x19_25rnd"});
		weaponMap.Insert("CZ75", arr);

		arr = new array<string>();
		arr.InsertAll({"Mag_Glock_15Rnd", "PistolSuppressor", "TLRLight", "AmmoBox_9x19_25rnd"});
		weaponMap.Insert("Glock19", arr);

		arr = new array<string>();
		arr.InsertAll({"Mag_FNX45_15Rnd", "PistolSuppressor", "TLRLight", "FNP45_MRDSOptic", "AmmoBox_45ACP_25rnd"});
		weaponMap.Insert("FNX45", arr);

		arr = new array<string>();
		arr.InsertAll({"Mag_CZ61_20Rnd", "PistolSuppressor", "AmmoBox_380_35rnd"});
		weaponMap.Insert("CZ61", arr);

		arr = new array<string>();
		arr.InsertAll({"MP5_PlasticHndgrd", "MP5k_StockBttstck", "Mag_MP5_15Rnd", "Mag_MP5_30Rnd", "BUISOptic", "PistolSuppressor", "AmmoBox_9x19_25rnd"});
		weaponMap.Insert("MP5K", arr);

		arr = new array<string>();
		arr.InsertAll({"Mag_UMP_25Rnd", "ReflexOptic", "PistolSuppressor", "TLRLight", "AmmoBox_45ACP_25rnd"});
		weaponMap.Insert("UMP45", arr);

		arr = new array<string>();
		arr.InsertAll({"PSO11Optic", "Mag_VSS_10Rnd", "AmmoBox_9x39AP_20Rnd"});
		weaponMap.Insert("VSS", arr);

		arr = new array<string>();
		arr.InsertAll({"Mag_VAL_20Rnd", "ACOGOptic", "TLRLight", "AmmoBox_9x39AP_20Rnd"});
		weaponMap.Insert("ASVAL", arr);

		arr = new array<string>();
		arr.InsertAll({"PSO1Optic", "Mag_Vikhr_30Rnd", "AmmoBox_9x39AP_20Rnd"});
		weaponMap.Insert("Vikhr", arr);

		arr = new array<string>();
		arr.InsertAll({"ACOGOptic_6x", "Mag_SV98_10Rnd", "AmmoBox_762x54_20Rnd"});
		weaponMap.Insert("SV98", arr);

		arr = new array<string>();
		arr.InsertAll({"SportingOptic", "Mag_CZ527_5rnd", "AmmoBox_762x39_20Rnd"});
		weaponMap.Insert("CZ527", arr);

		arr = new array<string>();
		arr.InsertAll({"HuntingOptic", "AmmoBox_308Win_20Rnd"});
		weaponMap.Insert("Winchester70", arr);

		arr = new array<string>();
		arr.InsertAll({"Mosin_Compensator", "PUScopeOptic", "AmmoBox_762x54_20Rnd"});
		weaponMap.Insert("Mosin9130", arr);

		arr = new array<string>();
		arr.InsertAll({"PUScopeOptic", "AmmoBox_762x39_20Rnd"});
		weaponMap.Insert("SKS", arr);

		arr = new array<string>();
		arr.InsertAll({"AK_PlasticBttstck", "AK_PlasticHndgrd", "AK_Suppressor", "Mag_AKM_30Rnd", "AmmoBox_762x39_20Rnd"});
		weaponMap.Insert("AKM", arr);

		arr = new array<string>();
		arr.InsertAll({"AK74_WoodBttstck", "AK74_Hndgrd", "Mag_AK74_45Rnd", "AmmoBox_545x39_20Rnd"});
		weaponMap.Insert("AK74", arr);

		arr = new array<string>();
		arr.InsertAll({"AKS74U_Bttstck", "Mag_AK74_30Rnd", "AmmoBox_545x39_20Rnd"});
		weaponMap.Insert("AKS74U", arr);

		arr = new array<string>();
		arr.InsertAll({"AK_PlasticBttstck", "AK_PlasticHndgrd", "Mag_AK101_30Rnd", "AmmoBox_556x45_20Rnd"});
		weaponMap.Insert("AK101", arr);

		arr = new array<string>();
		arr.InsertAll({"M4_OEBttstck", "M4_PlasticHndgrd", "M4_CarryHandleOptic", "Mag_CMAG_40Rnd", "AmmoBox_556x45_20Rnd"});
		weaponMap.Insert("M4A1", arr);

		arr = new array<string>();
		arr.InsertAll({"Mag_CMAG_30Rnd", "AmmoBox_556x45_20Rnd"});
		weaponMap.Insert("M16A2", arr);

		arr = new array<string>();
		arr.InsertAll({"Mag_FAMAS_25Rnd", "AmmoBox_556x45_20Rnd"});
		weaponMap.Insert("FAMAS", arr);

		arr = new array<string>();
		arr.InsertAll({"Mag_Aug_30Rnd", "BUISOptic", "M4_T3NRDSOptic", "TLRLight", "AmmoBox_556x45_20Rnd"});
		weaponMap.Insert("Aug", arr);

		arr = new array<string>();
		arr.InsertAll({"Mag_Aug_30Rnd", "AmmoBox_556x45_20Rnd"});
		weaponMap.Insert("AugShort", arr);

		arr = new array<string>();
		arr.InsertAll({"Fal_FoldingBttstck", "Fal_OeBttstck", "ACOGOptic", "Mag_FAL_20Rnd", "AmmoBox_308Win_20Rnd"});
		weaponMap.Insert("FAL", arr);

		arr = new array<string>();
		arr.InsertAll({"Mag_SVD_10Rnd", "KashtanOptic", "AmmoBox_762x54_20Rnd"});
		weaponMap.Insert("SVD", arr);

		arr = new array<string>();
		arr.InsertAll({"Mag_SVD_10Rnd", "PSO11Optic", "AmmoBox_762x54_20Rnd"});
		weaponMap.Insert("SVD_Wooden", arr);

		arr = new array<string>();
		arr.InsertAll({"PistolSuppressor", "Mag_1911_7Rnd", "AmmoBox_45ACP_25rnd"});
		weaponMap.Insert("Colt1911", arr);

		arr = new array<string>();
		arr.InsertAll({"PistolSuppressor", "Mag_1911_7Rnd", "AmmoBox_45ACP_25rnd"});
		weaponMap.Insert("Engraved1911", arr);

		arr = new array<string>();
		arr.InsertAll({"HuntingOptic", "Ammo_308Win"});
		weaponMap.Insert("B95", arr);

		arr = new array<string>();
		arr.InsertAll({"Saiga_Bttstck", "Mag_Saiga_8Rnd", "AmmoBox_00buck_10rnd"});
		weaponMap.Insert("Saiga", arr);

		arr = new array<string>();
		arr.InsertAll({"SportingOptic", "Mag_Ruger1022_30Rnd", "AmmoBox_22_50Rnd"});
		weaponMap.Insert("Ruger1022", arr);

		arr = new array<string>();
		arr.InsertAll({"Mag_Deagle_9rnd", "AmmoBox_357_20Rnd"});
		weaponMap.Insert("Deagle", arr);

		arr = new array<string>();
		arr.InsertAll({"Mag_Deagle_9rnd", "AmmoBox_357_20Rnd"});
		weaponMap.Insert("Deagle_Gold", arr);

		arr = new array<string>();
		arr.InsertAll({"Mag_Scout_5Rnd", "ACOGOptic_6x", "AmmoBox_556x45_20Rnd"});
		weaponMap.Insert("Scout", arr);

		arr = new array<string>();
		arr.InsertAll({"HuntingOptic", "Mag_CZ550_10rnd", "AmmoBox_308Win_20Rnd"});
		weaponMap.Insert("CZ550", arr);

		arr = new array<string>();
		arr.InsertAll({"PP19_Bttstck", "PistolSuppressor", "Mag_PP19_64Rnd", "AmmoBox_9x19_25rnd"});
		weaponMap.Insert("PP19", arr);

		arr = new array<string>();
		arr.InsertAll({"PistolOptic", "AmmoBox_308Win_20Rnd"});
		weaponMap.Insert("LongHorn", arr);

		arr = new array<string>();
		arr.InsertAll({"Mag_P1_8Rnd", "PistolSuppressor", "AmmoBox_9x19_25rnd"});
		weaponMap.Insert("P1", arr);

		arr = new array<string>();
		arr.InsertAll({"Mag_SSG82_5rnd", "AmmoBox_9x39AP_20Rnd"});
		weaponMap.Insert("SSG82", arr);

		arr = new array<string>();
		arr.InsertAll({"AmmoBox_00buck_10rnd"});
		weaponMap.Insert("MP133Shotgun", arr);

		arr = new array<string>();
		arr.InsertAll({"UniversalLight", "ReflexOptic", "AmmoBox_00buck_10rnd"});
		weaponMap.Insert("R12", arr);

		arr = new array<string>();
		arr.InsertAll({"Mag_M14_20Rnd", "ACOGOptic_6x", "AmmoBox_308Win_20Rnd"});
		weaponMap.Insert("M14", arr);
		
		arr = new array<string>();
		arr.InsertAll({"GasMask_Filter"});
		weaponMap.Insert("AirborneMask", arr);

		arr = new array<string>();
		arr.InsertAll({"GasMask_Filter"});
		weaponMap.Insert("GP5GasMask", arr);
		
		arr = new array<string>();
		arr.InsertAll({"BandageDressing", "Thermometer", "StartKitIV", "BloodBagEmpty", "BloodTestKit"});
		weaponMap.Insert("FirstAidKit", arr);
		
		arr = new array<string>();
		arr.InsertAll({"PlateCarrierHolster_Camo", "PlateCarrierPouches_Camo"});
		weaponMap.Insert("PlateCarrierVest_Camo", arr);

		arr = new array<string>();
		arr.InsertAll({"PlateCarrierHolster_Black", "PlateCarrierPouches_Black"});
		weaponMap.Insert("PlateCarrierVest_Black", arr);
		
		arr = new array<string>();
		arr.InsertAll({"Zagorky", "ChernarusMap"});
		weaponMap.Insert("HipPack_Green", arr);

		arr = new array<string>();
		arr.InsertAll({"BandageDressing", "VitaminBottle"});
		weaponMap.Insert("HipPack_Medical", arr);

		arr = new array<string>();
		arr.InsertAll({"Derringer_Pink"});
		weaponMap.Insert("HipPack_Party", arr);
		
		arr = new array<string>();
		arr.InsertAll({"NailBox", "NailBox"});
		weaponMap.Insert("NailBox", arr);
		
		arr = new array<string>();
		arr.InsertAll({"NVGoggles"});
		weaponMap.Insert("NVGHeadstrap", arr);
		
		arr = new array<string>();
		arr.InsertAll({"Mag_IJ70_8Rnd"});
		weaponMap.Insert("IJ70", arr);
		
		arr = new array<string>();
		arr.InsertAll({"AmmoBox_00buck_10rnd"});
		weaponMap.Insert("Izh18Shotgun", arr);
		
		arr = new array<string>();
		arr.InsertAll({"AmmoBox_00buck_10rnd"});
		weaponMap.Insert("Izh43Shotgun", arr);
		
		arr = new array<string>();
		arr.InsertAll({"AmmoBox_762x39_20Rnd"});
		weaponMap.Insert("Izh18", arr);
		
		arr = new array<string>();
		arr.InsertAll({"RemoteDetonator"});
		weaponMap.Insert("Plastic_Explosive", arr);

		return weaponMap;
	}

	static void SendDropNotification(vector pos, string customMessage)
	{
		auto settings = AirDropSettings.Get();
		if (!settings.EnableDropNotification)
			return;

		string baseMsg = RuckLocationFinder.BuildAirdropMessage(pos);

		string msg;
		if (AirDropSettings.Get().EnableCustomDropSites && customMessage != "" && customMessage != "Supply drop inbound for")
		{
			msg = customMessage;
		}
		else
		{
			msg = baseMsg;
		}

		if (settings.ShowCoordinatesInNotification)
		{
			msg = msg + string.Format(" [x:%1 z:%2]", Math.Round(pos[0]).ToString(), Math.Round(pos[2]).ToString());
		}

		array<Man> players = new array<Man>;
		GetGame().GetPlayers(players);

		foreach (Man player : players)
		{
			PlayerBase pb = PlayerBase.Cast(player);
			if (pb && pb.IsAlive())
			{
				#ifdef EXPANSIONMOD
				PlayerIdentity id = pb.GetIdentity();
				ExpansionNotification(settings.NotificationTitle, msg, "set:dayz_inventory image:explosive", COLOR_EXPANSION_NOTIFICATION_MISSION, 15.0).Create(id);
				#else
				pb.MessageStatus(msg);
				NotificationSystem.SendNotificationToPlayerExtended(pb, 15, settings.NotificationTitle, msg, "set:dayz_inventory image:explosive");
				#endif
			}
		}
	}
};