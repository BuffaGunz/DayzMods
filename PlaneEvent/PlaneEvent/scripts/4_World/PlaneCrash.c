class PlaneCrash extends CrashBase
{
	static ref map<EntityAI, int> m_ContainerTimers = new map<EntityAI, int>();
	static const int MAX_CONTAINER_LIFETIME = 3600000; 
	static const int CONTAINER_CHECK_INTERVAL = 30000; 
	
	override string GetSoundSet()
	{
		return "HeliCrash_Distant_SoundSet";
	}

	override void EEOnCECreate()
	{
		super.EEOnCECreate();
		RequestSoundEvent();
	}

	void RequestSoundEvent()
	{
		Param3<bool, vector, int> playSound = new Param3<bool, vector, int>(true, GetPosition(), GetSoundSet().Hash());
		GetGame().RPCSingleParam(null, ERPCs.RPC_SOUND_HELICRASH, playSound, true);
	}

	override void EEInit()
	{
		super.EEInit();
	
		if (!GetGame().IsDedicatedServer())
		{
			m_ParticleEfx = Particle.PlayOnObject(ParticleList.SMOKING_HELI_WRECK, this, Vector(4.7, -2.4, -2));
		}
	}

	override void EEDelete(EntityAI parent)
	{
		if (!GetGame().IsDedicatedServer() && m_ParticleEfx)
			m_ParticleEfx.Stop();
	}

	static vector FindValidCrashSite()
	{
		auto settings = PlaneCrashSettings.Get();
		vector site;

		string worldName = GetGame().GetWorldName();
		float worldSize = GetGame().GetWorld().GetWorldSize();

		Print("🌍 World: " + worldName + " | Size: " + worldSize.ToString());

		if (settings.EnableCustomCrashSites && settings.CustomCrashSites && settings.CustomCrashSites.Count() > 0)
		{
			site = settings.CustomCrashSites.GetRandomElement();
			site[1] = GetGame().SurfaceY(site[0], site[2]);
			Print("📍 Using custom Crash site: " + site);
			return site;
		}

		float margin = 1000;
		float min = margin;
		float max = worldSize - margin;

		site = GenerateCrashSiteInRange(min, max);
		if (site != vector.Zero)
		{
			Print("📍 Using generated Crash site: " + site);
			return site;
		}

		Print("❌ Failed to find valid Crash site, aborting spawn.");
		return vector.Zero;
	}

	static vector GenerateCrashSiteInRange(float minXZ, float maxXZ)
	{
		const int MAX_ATTEMPTS = 500;

		for (int i = 0; i < MAX_ATTEMPTS; i++)
		{
			float x = Math.RandomFloatInclusive(minXZ, maxXZ);
			float z = Math.RandomFloatInclusive(minXZ, maxXZ);
			float y = GetGame().SurfaceY(x, z);
			vector pos = Vector(x, y, z);

			vector normal = GetGame().SurfaceGetNormal(x, z);
			if (normal[1] < 0.95)
			{
				PrintFormat("[PlaneCrash] Rejected position %1,%2: slope too steep", x, z);
				continue;
			}

			// 🌊 Check for water nearby
			bool waterNearby = false;
			const float waterCheckRadius = 15.0;

			for (float angle = 0; angle < 360; angle += 30)
			{
				vector offset = Vector(Math.Cos(angle) * waterCheckRadius, 0, Math.Sin(angle) * waterCheckRadius);
				vector checkPos = pos + offset;

				string surfType;
				GetGame().SurfaceGetType(checkPos[0], checkPos[2], surfType);
				surfType.ToLower();

				if (GetGame().SurfaceIsSea(checkPos[0], checkPos[2]) || surfType.Contains("pond") || surfType.Contains("lake") || surfType.Contains("river") || surfType.Contains("swamp") || surfType.Contains("water"))
				{
					waterNearby = true;
					PrintFormat("[PlaneCrash] Rejected position %1,%2: water/sea within 15m", checkPos[0], checkPos[2]);
					break;
				}
			}

			if (waterNearby)
				continue;

			array<Object> objects = {};
			array<CargoBase> dummy = {};
			GetGame().GetObjectsAtPosition(pos, 15.0, objects, dummy);

			bool blocked = false;
			foreach (Object obj : objects)
			{
				if (!obj) continue;
				
				string type = obj.GetType();
				type.ToLower(); 

				if (type.Contains("treehard") || type.Contains("treesoft") || type.Contains("bushhard") || type.Contains("bushsoft") || type.Contains("rock") || type.Contains("stone") || type.Contains("wreck") || type.Contains("fence") || type.Contains("wall") || type.Contains("rail") || type.Contains("wreck") || type.Contains("house") || type.Contains("bldr_"))
				{
					blocked = true;
					PrintFormat("[PlaneCrash] Rejected position %1,%2: blocked by %3", x, z, type);
					break;
				}
			}

			if (blocked)
				continue;

			PrintFormat("[PlaneCrash] Valid Crash site found: %1,%2", x, z);
			return pos;
		}

		Print("[PlaneCrash] ❌ Failed to find valid Crash site after max attempts.");
		return vector.Zero;
	}

	static void SpawnSite()
	{
		vector crashPos = FindValidCrashSite();
		if (crashPos == vector.Zero)
		{
			Print("[PlaneCrash] ❌ No valid crash site found. Spawn aborted.");
			return;
		}

		array<Object> nearby = {};
		array<CargoBase> dummy = {};
		GetGame().GetObjectsAtPosition(crashPos, 100.0, nearby, dummy);
		foreach (Object obj : nearby)
		{
			if (!obj) continue;

			string type = obj.GetType();
			if (type == "PlaneCrash" || type.Contains("Land_ContainerLocked"))
			{
				Print("⚠️ Crash or container already nearby, skipping spawn.");
				return;
			}
		}

		EntityAI wreck = EntityAI.Cast(GetGame().CreateObject("PlaneCrash", crashPos));
		if (!wreck) return;

		wreck.PlaceOnSurface();

		vector wreckPos = wreck.GetPosition();
		vector wreckNormal = GetGame().SurfaceGetNormal(wreckPos[0], wreckPos[2]);

		vector wreckForward = vector.Direction(wreckPos, wreckPos + "1 0 0");
		vector wreckRight = wreckForward * wreckNormal;
		wreckRight.Normalize();
		wreckForward = wreckNormal * wreckRight;
		wreckForward.Normalize();

		vector wreckMat[3];
		wreckMat[0] = wreckForward;
		wreckMat[1] = wreckNormal;
		wreckMat[2] = wreckRight;

		wreck.SetOrientation(Math3D.MatrixToAngles(wreckMat));
		wreck.SetPosition(wreckPos); 

		wreck.SetAffectPathgraph(true, true);
		wreck.SetSynchDirty();
		GetGame().UpdatePathgraphRegionByObject(wreck);
		Print("[PlaneCrash] Wreck placed and navmesh updated.");

		#ifdef SERVER
			Param3<bool, vector, int> playSound = new Param3<bool, vector, int>(true, wreck.GetPosition(), "HeliCrash_Distant_SoundSet".Hash());
			GetGame().RPCSingleParam(null, ERPCs.RPC_SOUND_HELICRASH, playSound, true);
		#endif

		ref array<string> containerTypes = {
			"WreckContainerBlue",
			"WreckContainerRed",
			"WreckContainerYellow",
			"WreckContainerOrange"
		};
		string selectedType = containerTypes.GetRandomElement();

		string keyName = "";
		switch (selectedType)
		{
			case "WreckContainerBlue":   keyName = "ShippingContainerKeys_Blue"; break;
			case "WreckContainerRed":    keyName = "ShippingContainerKeys_Red"; break;
			case "WreckContainerYellow": keyName = "ShippingContainerKeys_Yellow"; break;
			case "WreckContainerOrange": keyName = "ShippingContainerKeys_Orange"; break;
		}

		vector dir = wreck.GetDirection();
		vector cargoPos = wreck.GetPosition() + (dir * 18.5);

		EntityAI container = EntityAI.Cast(GetGame().CreateObject(selectedType, cargoPos));
		if (container)
		{
			container.PlaceOnSurface();

			vector containerPos = container.GetPosition();
			vector containerNormal = GetGame().SurfaceGetNormal(containerPos[0], containerPos[2]);

			vector forward = vector.Direction(containerPos, containerPos + "1 0 0");
			vector right = forward * containerNormal;
			right.Normalize();
			forward = containerNormal * right;
			forward.Normalize();

			vector mat[3];
			mat[0] = forward;
			mat[1] = containerNormal;
			mat[2] = right;

			container.SetOrientation(Math3D.MatrixToAngles(mat));
			container.SetPosition(containerPos);

			container.SetAffectPathgraph(true, true);
			container.SetSynchDirty();
			GetGame().UpdatePathgraphRegionByObject(container);
			PrintFormat("[PlaneCrash] Container %1 placed and navmesh updated.", selectedType);

			container.SetLifetime(0);
			m_ContainerTimers.Insert(container, 0);
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(CheckContainerLifetime, CONTAINER_CHECK_INTERVAL, true, container);

			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(FillContainerWithRandomLoot, 2000, false, container);
		}

		if (keyName != "")
		{
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(SpawnZombiesWithKey, 2000, false, crashPos, keyName);
		}

		if (PlaneCrashSettings.Get().EnableCrashNotification)
		{
			SendCrashNotification(wreck.GetPosition());
		}

		m_ContainerTimers.Insert(wreck, 0);
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(CheckContainerLifetime, CONTAINER_CHECK_INTERVAL, true, wreck);
	}

	static void CheckContainerLifetime(EntityAI obj)
	{
		if (!obj || !m_ContainerTimers.Contains(obj))
			return;

		vector pos = obj.GetPosition();
		array<Man> players = {};
		GetGame().GetPlayers(players);

		bool nearby = false;
		foreach (Man p : players)
		{
			if (vector.Distance(pos, p.GetPosition()) <= 50)
			{
				nearby = true;
				break;
			}
		}

		if (nearby)
		{
			m_ContainerTimers.Set(obj, 0);
		}
		else
		{
			int elapsed = m_ContainerTimers.Get(obj) + CONTAINER_CHECK_INTERVAL;

			if (elapsed >= MAX_CONTAINER_LIFETIME)
			{
				
				m_ContainerTimers.Remove(obj);

				if (obj.GetType().Contains("Land_ContainerLocked") || obj.GetType().Contains("Container"))
				{
					GetGame().ObjectDelete(obj);
					PrintFormat("[Cleanup] Deleted container: %1", obj);
				}
				else if (obj.GetType().Contains("PlaneCrash") || obj.IsKindOf("ShipWreck"))
				{
					GetGame().ObjectDelete(obj);
					PrintFormat("[Cleanup] Deleted wreck: %1", obj);
				}
			}
			else
			{
				m_ContainerTimers.Set(obj, elapsed);
			}
		}
	}

	static void SpawnZombiesWithKey(vector center, string keyName)
	{
		auto settings = PlaneCrashSettings.Get();

		int zombieCount = settings.ZombieCount;
		if (zombieCount > 40) zombieCount = 40;
		if (zombieCount < 1) zombieCount = 1;

		array<string> zombieTypes;

		if (settings.EnableCustomZombieTypes && settings.CustomZombieTypes.Count() > 0)
		{
			zombieTypes = settings.CustomZombieTypes;
			Print("[PlaneCrash] Using custom zombie types from config.");
		}
		else
		{
			zombieTypes = {
				"ZmbM_PatrolNormal_Summer",
				"ZmbM_PatrolNormal_Autumn",
				"ZmbM_SoldierNormal",
				"ZmbM_eastSoldier_Heavy_Navy",
				"ZmbM_eastSoldier_normal_Navy",
				"ZmbM_usSoldier_Heavy_Woodland",
				"ZmbM_usSoldier_Officer_Desert"
			};
			Print("[PlaneCrash] Using default vanilla zombie types.");
		}

		int keyZombieIndex = Math.RandomInt(0, zombieCount);

		for (int i = 0; i < zombieCount; ++i)
		{
			vector pos = center + Vector(Math.RandomFloat(-10, 10), 0, Math.RandomFloat(-10, 10));
			pos[1] = GetGame().SurfaceY(pos[0], pos[2]);
			string zombieType = zombieTypes.GetRandomElement();

			DayZInfected z = DayZInfected.Cast(GetGame().CreateObject(zombieType, pos, false, true));
			if (z)
			{
				z.SetAffectPathgraph(true, true);
				z.SetSynchDirty();
				PrintFormat("[NavmeshPatch] Zombie navmesh forced for: %1", zombieType);

				if (i == keyZombieIndex && keyName != "")
				{
					ItemBase keyItem = ItemBase.Cast(z.GetInventory().CreateInInventory(keyName));
					if (keyItem)
					{
						keyItem.SetHealth01("", "", 0.10);
						PrintFormat("[PlaneCrash] Spawned key '%1' on zombie: %2", keyName, z);
					}
					else
					{
						PrintFormat("[PlaneCrash] ERROR: Failed to create key '%1' on zombie: %2", keyName, z);
					}
				}
			}
		}
	}
	
	static EntityAI FindAttachmentByType(EntityAI parent, string type)
	{
		for (int i = 0; i < parent.GetInventory().AttachmentCount(); ++i)
		{
			EntityAI attachment = parent.GetInventory().GetAttachmentFromIndex(i);
			if (attachment && attachment.GetType() == type)
				return attachment;
		}
		return null;
	}
	
	static void FillContainerWithRandomLoot(EntityAI container)
	{
		string containerType = container.GetType();
		string crateType = "";

		switch (containerType)
		{
			case "WreckContainerRed":
			case "WreckContainerBlue":
			case "WreckContainerYellow":
			case "WreckContainerOrange":
				crateType = "RuckCrashStorage";
				break;

			default:
				Print("⚠️ Unknown container type: " + containerType);
				return;
		}

		EntityAI crate = FindAttachmentByType(container, crateType);
		if (!crate)
		{
			Print("❌ No attached storage crate of type " + crateType + " found on container: " + containerType);
			return;
		}

		auto settings = PlaneCrashSettings.Get();
		ref array<string> lootPool = new array<string>();
		int maxLoot = 0;

		if (crateType == "RuckCrashStorage")
		{
			maxLoot = Math.Clamp(settings.MaxLootItems, 1, 30);

			if (settings.EnableCustomLootItems && settings.CustomLootItems && settings.CustomLootItems.Count() > 0)
			{
				lootPool = settings.CustomLootItems;
				Print("🧰 Using custom loot items from config");
			}
			else
			{
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
					"M4_Suppressor","AK_Suppressor","PistolSuppressor", "AmmoBox_00buck_10rnd", "AmmoBox_22_50Rnd", "AmmoBox_308WinTracer_20Rnd", "AmmoBox_357_20Rnd", "AmmoBox_762x39_20Rnd", "AmmoBox_9x19_25rnd",
					"SalineBagIV", "BandageDressing", "Epinephrine", "Morphine", "VitaminBottle", "BloodBagEmpty", "TetracyclineAntibiotics",
					"GasMask_Filter", "IodineTincture", "NBCBootsGray", "NBCGlovesGray", "NBCHoodGray", "NBCJacketGray","NBCPantsGray",
					"PainkillerTablets", "StartKitIV", "BloodTestKit", "CharcoalTablets", "ChelatingTablets", "AntiChemInjector",
					"GP5GasMask", "AirborneMask", "HipPack_Medical", "FirstAidKit"
				});
			}
		}
	
		ref map<string, ref array<string>> weaponBonusLoot = GetWeaponBonusLootweaponMap();

		ref array<string> shuffledLoot = new array<string>;
		shuffledLoot.Copy(lootPool);
		ShuffleStringArray(shuffledLoot);

		int lootIndex = 0;
		ref set<string> spawnedWeapons = new set<string>();

		for (int i = 0; i < maxLoot; ++i)
		{
			if (lootIndex >= shuffledLoot.Count())
			{
				ShuffleStringArray(shuffledLoot);
				lootIndex = 0;
			}

			string itemName = shuffledLoot.Get(lootIndex++);
			ItemBase item = ItemBase.Cast(crate.GetInventory().CreateInInventory(itemName));

			if (!item)
			{
				Print("⚠️ Cannot add " + itemName + " to crate inventory");
				continue;
			}

			item.SetHealth01("", "", Math.RandomFloat(0.4, 1.0));

			if (weaponBonusLoot.Contains(itemName))
			{
				ref array<string> bonusItems = weaponBonusLoot.Get(itemName);
				foreach (string bonusName : bonusItems)
				{
					ItemBase bonusItem = ItemBase.Cast(crate.GetInventory().CreateInInventory(bonusName));
					if (bonusItem)
					{
						bonusItem.SetHealth01("", "", Math.RandomFloat(0.6, 1.0));
					}
					else
					{
						Print("⚠️ Failed to spawn bonus item: " + bonusName + " for weapon: " + itemName);
					}
				}
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
		arr.InsertAll({"BandageDressing", "VitaminBottle"});
		weaponMap.Insert("HipPack_Medical", arr);

		arr = new array<string>();
		arr.InsertAll({"NVGoggles"});
		weaponMap.Insert("NVGHeadstrap", arr);
		
		arr = new array<string>();
		arr.InsertAll({"RemoteDetonator"});
		weaponMap.Insert("Plastic_Explosive", arr);

		return weaponMap;
	}
	
	static void SendCrashNotification(vector pos)
	{
		if (!PlaneCrashSettings.Get().EnableCrashNotification)
			return;  

		string msg = string.Format("Downed plane spotted at coordinates x(%1) z(%2)",
			pos[0].ToString(), pos[2].ToString());

		array<Man> players = new array<Man>;
		GetGame().GetPlayers(players);

		foreach (Man player : players)
		{
			PlayerBase pb = PlayerBase.Cast(player);
			if (pb && pb.IsAlive())
			{
				#ifdef EXPANSIONMOD
				ExpansionNotification("Plane Crash", msg, "set:dayz_inventory image:explosive", COLOR_EXPANSION_NOTIFICATION_MISSION, 15).Create();
				#else
				pb.MessageStatus(msg);  // vanilla chat message
				NotificationSystem.SendNotificationToPlayerExtended(pb, 15, "Plane Crash", msg, "set:dayz_inventory image:explosive");
				#endif
			}	
		}
	}
}