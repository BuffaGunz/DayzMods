class ShipWreck extends CrashBase
{
	static ref map<EntityAI, int> m_ContainerTimers = new map<EntityAI, int>();
	static const int MAX_CONTAINER_LIFETIME = 3600000; // 1 hour (in ms)
	static const int CONTAINER_CHECK_INTERVAL = 30000; // 30 seconds (in ms)
	
	override void OnStoreSave(ParamsWriteContext ctx)
	{
		super.OnStoreSave(ctx);

		// Save wreck-specific data (e.g., position and orientation)
		vector wreckPos = GetPosition();
		vector wreckDir = GetDirection();
		ctx.Write(wreckPos);
		ctx.Write(wreckDir);

		PrintFormat("[ShipWreck] Saved wreck at pos: %1 dir: %2", wreckPos, wreckDir);
	}

	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		if (!super.OnStoreLoad(ctx, version))
			return false;

		// Load wreck-specific data
		vector wreckPos;
		vector wreckDir;

		ctx.Read(wreckPos);
		ctx.Read(wreckDir);

		SetPosition(wreckPos);
		SetDirection(wreckDir);

		PrintFormat("[ShipWreck] Loaded wreck at pos: %1 dir: %2", wreckPos, wreckDir);

		return true;
	}

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
			vector forward = GetDirection();                         // Wreck's facing direction
			vector offset = (forward * -16.0) + Vector(0, 1.0, 0);     // Forward 15m, 2m above wreck
			m_ParticleEfx = Particle.PlayOnObject(ParticleList.SMOKING_HELI_WRECK, this, offset);
		}
	}

	override void EEDelete(EntityAI parent)
	{
		if (!GetGame().IsDedicatedServer() && m_ParticleEfx)
			m_ParticleEfx.Stop();
	}

	static vector FindValidCrashSite()
	{
		auto settings = ShipWreckSettings.Get();
		vector site; // ✅ Declare once

		// ✅ Use custom site if enabled
		if (settings.EnableCustomCrashSites && settings.CustomCrashSites && settings.CustomCrashSites.Count() > 0)
		{
			site = settings.CustomCrashSites.GetRandomElement();
			site[1] = GetGame().SurfaceY(site[0], site[2]);
			Print("📍 Using custom crash site: " + site);
			return site;
		}

		// ✅ Try entire map range
		site = GenerateCrashSiteInRange(1000, 15000);
		if (site != vector.Zero)
		{
			Print("📍 Using generated crash site: " + site);
			return site;
		}

		// ❌ No valid site found
		Print("❌ Failed to find valid crash site, aborting spawn.");
		return vector.Zero;
	}
	
	static vector GenerateCrashSiteInRange(float minXZ, float maxXZ)
	{
		const int MAX_ATTEMPTS = 50;

		for (int i = 0; i < MAX_ATTEMPTS; i++)
		{
			float x = Math.RandomFloatInclusive(minXZ, maxXZ);
			float z = Math.RandomFloatInclusive(minXZ, maxXZ);
			float y = GetGame().SurfaceY(x, z);
			vector pos = Vector(x, y, z);

			// ✅ Check slope (keep ship level)
			vector normal = GetGame().SurfaceGetNormal(x, z);
			if (normal[1] < 0.95)
				continue;

			// ✅ Check water
			string surfType;
			GetGame().SurfaceGetType(x, z, surfType);
			surfType.ToLower();

			if (!GetGame().SurfaceIsSea(x, z))
				continue;

			// 🧊 Exclude ice sheets (Sakhal etc.)
			if (surfType.Contains("sakhal_ice_sea") || surfType.Contains("ice"))
			{
				Print("[ShipWreck] Skipping ice surface: " + surfType);
				continue;
			}

			// ✅ Check for nearby ice within 40m
			bool nearIce = false;
			for (float angle = 0; angle < 360; angle += 45)
			{
				vector checkPos = pos + Vector(Math.Sin(angle) * 40.0, 0, Math.Cos(angle) * 40.0);
				string nearbySurf;
				GetGame().SurfaceGetType(checkPos[0], checkPos[2], nearbySurf);
				nearbySurf.ToLower();

				if (nearbySurf.Contains("sakhal_ice_sea") || nearbySurf.Contains("ice"))
				{
					Print("[ShipWreck] Skipping — ice nearby at: " + checkPos);
					nearIce = true;
					break;
				}
			}
			if (nearIce)
				continue;

			// ✅ Check nearby objects to avoid overlap
			array<Object> objects = {};
			array<CargoBase> dummy = {};
			GetGame().GetObjectsAtPosition(pos, 40.0, objects, dummy);

			bool blocked = false;
			foreach (Object obj : objects)
			{
				if (!obj) continue;
				string type = obj.GetType();
				if (type.Contains("House") || type.Contains("Land_Container") || type.Contains("Wreck") || type.Contains("Fence") || type.Contains("Wall") || type.Contains("Rail") || type.Contains("Roadblock") || type.Contains("Barrier"))
				{
					blocked = true;
					break;
				}
			}

			if (blocked)
				continue;

			// ✅ Valid position found
			return pos;

		}

		// ❌ Failed to find valid position
		return vector.Zero;
	}

	static void SpawnSite()
	{
		vector crashPos = FindValidCrashSite();

		// Prevent duplicate spawn
		array<Object> nearby = {};
		array<CargoBase> dummy = {};
		GetGame().GetObjectsAtPosition(crashPos, 100.0, nearby, dummy);
		foreach (Object obj : nearby)
		{
			if (!obj || obj.GetType() == "ShipWreck" || obj.GetType().IndexOf("Land_ContainerLocked") != -1)
			{
				Print("⚠️ Crash or container already nearby, skipping spawn.");
				return;
			}
		}

		// --- Spawn wreck ---
		ShipWreck wreck = ShipWreck.Cast(GetGame().CreateObject("ShipWreck", crashPos));
		if (!wreck) return;

		wreck.PlaceOnSurface();
		wreck.SetAffectPathgraph(true, true);
		wreck.SetSynchDirty();
		GetGame().UpdatePathgraphRegionByObject(wreck);   
		
		Print("[ShipWreck] Wreck placed and navmesh updated.");

		// --- Send notification if enabled ---
		if (ShipWreckSettings.Get().EnableCrashNotification)
		{
			SendCrashNotification(wreck.GetPosition());
		}

		// --- Play sound ---
		#ifdef SERVER
			Param3<bool, vector, int> playSound = new Param3<bool, vector, int>(true, wreck.GetPosition(), "HeliCrash_Distant_SoundSet".Hash());
			GetGame().RPCSingleParam(null, ERPCs.RPC_SOUND_HELICRASH, playSound, true);
		#endif

		// --- Select container type and matching key ---
		ref array<string> containerTypes = { "ContainerRed", "ContainerBlue", "ContainerYellow", "ContainerOrange" };
		string selectedType = containerTypes.GetRandomElement();

		string keyName = "";
		switch (selectedType)
		{
			case "ContainerBlue": keyName = "ShippingContainerKeys_Blue"; break;
			case "ContainerRed": keyName = "ShippingContainerKeys_Red"; break;
			case "ContainerYellow": keyName = "ShippingContainerKeys_Yellow"; break;
			case "ContainerOrange": keyName = "ShippingContainerKeys_Orange"; break;
		}

		// --- Place container on ShipWreck deck (10m back) ---
		vector dir = wreck.GetDirection();
		vector cargoPos = wreck.GetPosition() + (dir * 10.0);

		// Place container independently of the wreck
		EntityAI container = EntityAI.Cast(GetGame().CreateObject(selectedType, cargoPos));
		if (container)
		{
			container.PlaceOnSurface();
			vector adjustedPos = container.GetPosition();
			adjustedPos = Vector(adjustedPos[0], adjustedPos[1] + 0.2, adjustedPos[2]); // Raise slightly
			container.SetPosition(adjustedPos);

			// Navmesh + sync
			container.SetAffectPathgraph(true, true);
			container.SetSynchDirty();
			GetGame().UpdatePathgraphRegionByObject(container);

			// Start container cleanup timer
			m_ContainerTimers.Insert(container, 0);
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(CheckContainerLifetime, CONTAINER_CHECK_INTERVAL, true, container);

			PrintFormat("[ShipWreck] Container %1 placed on wreck deck (independent).", selectedType);

			// Spawn loot
			FillContainerWithRandomLoot(container);
		}

		// --- Spawn zombies with key ---
		if (keyName != "")
		{
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(SpawnZombiesOnDeck, 5000, false, wreck, keyName);
		}

		// --- Add wreck to container timer system (NEW) ---
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
			// ✅ Reset timer if players are nearby
			m_ContainerTimers.Set(obj, 0);
		}
		else
		{
			int elapsed = m_ContainerTimers.Get(obj) + CONTAINER_CHECK_INTERVAL;

			if (elapsed >= MAX_CONTAINER_LIFETIME)
			{
				
				m_ContainerTimers.Remove(obj);

				if (obj.IsInherited(ItemBase))
				{
					if (obj.GetHierarchyParent())
					{
						PrintFormat("[Cleanup] Stopped tracking loot: %1 (moved out of wreck site)", obj);
						return;
					}

					GetGame().ObjectDelete(obj);
					PrintFormat("[Cleanup] Deleted loose loot: %1", obj);
				}
				else if (obj.GetType().Contains("Land_ContainerLocked") || obj.GetType().Contains("Container"))
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

	static void SpawnZombiesOnDeck(EntityAI shipWreck, string keyName)
	{
		auto settings = ShipWreckSettings.Get();

		int zombieCount = settings.ZombieCount;
		if (zombieCount > 40) zombieCount = 40;
		if (zombieCount < 1) zombieCount = 1;

		array<string> zombieTypes;

		if (settings.EnableCustomZombieTypes && settings.CustomZombieTypes.Count() > 0)
		{
			zombieTypes = settings.CustomZombieTypes;
			Print("[ShipWreck] Using custom zombie types from config.");
		}
		else
		{
			zombieTypes = {
				"ZmbM_PatrolNormal_Summer",
				"ZmbM_SoldierNormal",
				"ZmbM_usSoldier_Officer_Woodland",
				"ZmbM_usSoldier_Heavy_Woodland"
			};
			Print("[ShipWreck] Using default zombie types.");
		}

		ref array<DayZInfected> spawnedZombies = new array<DayZInfected>();
		vector wreckPos = shipWreck.GetPosition();
		vector wreckDir = shipWreck.GetDirection();
		
		for (int i = 0; i < zombieCount; ++i)
		{
			// 🎲 Random deck height and offset
			float deckHeight = 3.0 * Math.RandomInt(1, 4); // Random deck level (3m increments)
			vector offset = wreckDir * Math.RandomFloat(-6, 6); // Forward/backward offset
			offset[1] = deckHeight;                            
			offset += Vector(Math.RandomFloat(-2, 2), 0, Math.RandomFloat(-2, 2)); // Random sideways

			vector zombiePos = wreckPos + offset;

			DayZInfected zmb = DayZInfected.Cast(GetGame().CreateObject(zombieTypes.GetRandomElement(), zombiePos, false, true, true));
			if (zmb)
			{
				zmb.PlaceOnSurface();                // ✅ snap to wreck surface
				zmb.SetDirection(wreckDir);          // align with wreck
				zmb.SetAffectPathgraph(true, true);  // navmesh
				zmb.SetSynchDirty();
				spawnedZombies.Insert(zmb);          // track for key assignment
			}
		}

		// 🗝️ Assign key to one random zombie
		if (keyName != "" && spawnedZombies.Count() > 0)
		{
			DayZInfected keyZombie = spawnedZombies.GetRandomElement();
			ItemBase keyItem = ItemBase.Cast(keyZombie.GetInventory().CreateInInventory(keyName));
			if (keyItem)
			{
				keyItem.SetHealth01("", "", 0.10);
				PrintFormat("[ShipWreck] Spawned key '%1' on zombie: %2", keyName, keyZombie);
			}
			else
			{
				PrintFormat("[ShipWreck] ERROR: Failed to create key '%1' on zombie: %2", keyName, keyZombie);
			}
		}
	}

	static void SendCrashNotification(vector pos)
	{
		if (!ShipWreckSettings.Get().EnableCrashNotification)
			return;  // 🚫 don't send anything at all

		string msg = string.Format("Wreck spotted at coordinates x(%1) z(%2)",
			pos[0].ToString(), pos[2].ToString());

		array<Man> players = new array<Man>;
		GetGame().GetPlayers(players);

		foreach (Man player : players)
		{
			PlayerBase pb = PlayerBase.Cast(player);
			if (pb && pb.IsAlive())
			{
				#ifdef EXPANSIONMOD
				ExpansionNotification("Ship Wreck", msg, "set:dayz_inventory image:explosive", COLOR_EXPANSION_NOTIFICATION_MISSION, 15).Create();
				#else
				pb.MessageStatus(msg);  // vanilla chat message
				NotificationSystem.SendNotificationToPlayerExtended(pb, 15, "Ship Wreck", msg, "set:dayz_inventory image:explosive");
				#endif
			}	
		}
	}
	
	static void MessageToPlayer(PlayerBase player, string msg)
	{
		if (!ShipWreckSettings.Get().EnableCrashNotification)
			return;

		if (player)
			player.MessageStatus(msg);  // vanilla chat message
	}

	static void FillContainerWithRandomLoot(EntityAI container)
	{
		ref set<string> spawnedWeapons = new set<string>();
		ref array<string> lootPool;

		auto settings = ShipWreckSettings.Get();
		int maxLoot = settings.MaxLootItems;
		if (maxLoot > 30) maxLoot = 30;
		if (maxLoot < 1) maxLoot = 1;

		if (settings.EnableCustomLootItems && settings.CustomLootItems && settings.CustomLootItems.Count() > 0)
		{
			lootPool = settings.CustomLootItems;
			Print("🧰 Using custom loot items from config");
		}
		else
		{
			lootPool = new array<string>;
			lootPool.InsertAll({
				// Weapons
				"FNX45","VSS","ASVAL","Vikhr","SV98","Winchester70","Mosin9130","SKS","AKM","AK74",
				"AKS74U","AK101","M4A1","M16A2","FAMAS","Aug","AugShort","FAL","SVD","SVD_Wooden",
				"Engraved1911","B95","Saiga","Deagle","Deagle_Gold","Scout","CZ550","R12","M14","M79",
				// Vests / clothing
				"PlateCarrierVest","PlateCarrierVest_Black","PlateCarrierVest_Green","PlateCarrierVest_Camo","PlateCarrierVest_Winter",
				"GorkaHelmet","GorkaHelmet_Black","Mich2001Helmet","AliceBag_Green","AliceBag_Black","AliceBag_Camo",
				"OMKPants_Navy","OMKJacket_Navy","MilitaryBoots_Black","MilitaryBelt",
				// Magazines
				"Mag_SV98_10rnd","Mag_M14_10Rnd","Mag_M14_20Rnd","Mag_AK74_30Rnd","Mag_AK74_45Rnd","Mag_AK101_30Rnd","Mag_AKM_30Rnd",
				"Mag_AKM_Palm30Rnd","Mag_AKM_Drum75Rnd","Mag_Aug_30Rnd","Mag_CZ550_10rnd","Mag_FAL_20Rnd","Mag_FAMAS_25Rnd",
				"Mag_STANAG_30Rnd","Mag_CMAG_30Rnd","Mag_CMAG_40Rnd","Mag_STANAGCoupled_30Rnd","Mag_STANAG_60Rnd","Mag_SVD_10Rnd",
				"Mag_VSS_10Rnd","Mag_VAL_20Rnd","Mag_Vikhr_30Rnd",
				// Ammo / Explosives
				"RemoteDetonator","Plastic_Explosive","Ammo_762x54","Ammo_762x54Tracer","Ammo_308Win","Ammo_308WinTracer","Ammo_545x39","Ammo_545x39Tracer","Ammo_556x45",
				"Ammo_556x45Tracer","Ammo_762x39","Ammo_762x39Tracer","Ammo_9x39","Ammo_9x39AP","Ammo_40mm_Explosive","Ammo_40mm_ChemGas",
				// Medical
				"SalineBagIV","BandageDressing","DisinfectantSpray","DisinfectantAlcohol","PurificationTablets","CharcoalTablets",
				"PainkillerTablets","VitaminBottle","IodineTincture","TetracyclineAntibiotics","Epinephrine","Morphine",
				"AntiChemInjector","SalineBag","StartKitIV","BloodBagEmpty","BloodTestKit",
				// Food / drink
				"Canteen","WaterBottle","TacticalBaconCan","TunaCan","Lunchmeat","BrisketSpread","Crackers",
				// Lights / NV
				"NVGoggles","NVGHeadstrap","Headtorch_Grey","Headtorch_Black","UniversalLight",
				// Suppressors
				"M4_Suppressor","AK_Suppressor","PistolSuppressor"
			});
		}

		vector containerPos = container.GetPosition();
		vector containerDir = container.GetDirection();

		for (int i = 0; i < maxLoot; ++i)
		{
			string itemName = lootPool.GetRandomElement();

			if (IsWeapon(itemName))
			{
				if (spawnedWeapons.Find(itemName) != -1)
				{
					--i; // skip duplicate weapon
					continue;
				}
				spawnedWeapons.Insert(itemName);

				// 🟢 Spawn weapon with attachments
				vector wPos = containerPos + Vector(Math.RandomFloat(-1.0, 1.0), 0.0, Math.RandomFloat(-2.5, 2.5));
				SpawnWeaponWithAttachments(itemName, wPos);

				// 🟢 Snap spawned objects on top of container deck
				array<Object> nearby = {};
				GetGame().GetObjectsAtPosition(wPos, 1.0, nearby, null);

				foreach (Object obj : nearby)
				{
					if (IsWeapon(obj.GetType()))
					{
						obj.PlaceOnSurface(); // force snap to container surface

						// ✅ Track weapon for cleanup
						EntityAI weapon = EntityAI.Cast(obj);
						if (weapon)
						{
							m_ContainerTimers.Insert(weapon, 0);
							GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(CheckContainerLifetime, CONTAINER_CHECK_INTERVAL, true, weapon);
						}
					}
				}

				continue;
			}

			// 🔥 Non-weapon items
			vector pos = containerPos + Vector(Math.RandomFloat(-1.0, 1.0), 0.0, Math.RandomFloat(-2.5, 2.5));

			ItemBase item = ItemBase.Cast(GetGame().CreateObject(itemName, pos, false, true));
			if (!item) continue;

			item.SetHealth01("", "", Math.RandomFloat(0.30, 1.0));
			item.SetOrientation(containerDir);
			item.PlaceOnSurface(); // Snap to container surface

			// ✅ Track loose loot for cleanup
			m_ContainerTimers.Insert(item, 0);
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(CheckContainerLifetime, CONTAINER_CHECK_INTERVAL, true, item);
		}
	}	

	/* --------------------------------------------------------------------- */
	/*  Weapon attachments                                                   */
	/* --------------------------------------------------------------------- */

	static void SpawnWeaponWithAttachments(string weaponName, vector pos)
	{
		ItemBase loot;  // will hold the newly spawned weapon (if any)

		switch (weaponName)
		{
			/* ------------------------------------------------------------- */
			/*  Pistols                                                      */
			/* ------------------------------------------------------------- */
			case "FNX45":
			{
				loot = ItemBase.Cast(GetGame().CreateObject("FNX45", pos));
				if (!loot) break;
				loot.SetHealth01("", "", Math.RandomFloat(0.3, 1.0));

				if (Math.RandomFloat01() <= 0.10) loot.GetInventory().CreateAttachment("Mag_FNX45_15Rnd");
				if (Math.RandomFloat01() <= 0.20) loot.GetInventory().CreateAttachment("PistolSuppressor");
				if (Math.RandomFloat01() <= 0.10) loot.GetInventory().CreateAttachment("TLRLight");
				if (Math.RandomFloat01() <= 0.15) loot.GetInventory().CreateAttachment("FNP45_MRDSOptic");
				break;
			}

			case "Engraved1911":
			{
				loot = ItemBase.Cast(GetGame().CreateObject("Engraved1911", pos));
				if (!loot) break;

				if (Math.RandomFloat01() <= 0.05) loot.GetInventory().CreateAttachment("PistolSuppressor");
				if (Math.RandomFloat01() <= 0.60) loot.GetInventory().CreateAttachment("Mag_1911_7Rnd");
				break;
			}

			case "Deagle":
			{
				loot = ItemBase.Cast(GetGame().CreateObject("Deagle", pos));
				if (!loot) break;

				if (Math.RandomFloat01() <= 0.10) loot.GetInventory().CreateAttachment("Mag_Deagle_9rnd");
				break;
			}

			case "Deagle_Gold":
			{
				loot = ItemBase.Cast(GetGame().CreateObject("Deagle_Gold", pos));
				if (!loot) break;

				if (Math.RandomFloat01() <= 0.25) loot.GetInventory().CreateAttachment("Mag_Deagle_9rnd");
				break;
			}

			/* ------------------------------------------------------------- */
			/*  9×39 mm family (VSS / VAL / Vikhr)                           */
			/* ------------------------------------------------------------- */
			case "VSS":
			{
				loot = ItemBase.Cast(GetGame().CreateObject("VSS", pos));
				if (!loot) break;
				loot.SetHealth01("", "", Math.RandomFloat(0.3, 1.0));

				loot.GetInventory().CreateAttachment("PSO11Optic");

				if (Math.RandomFloat01() <= 0.35)
				{
					float r = Math.RandomFloat01();
					if (r < 0.50)      loot.GetInventory().CreateAttachment("Mag_VSS_10Rnd");
					else if (r < 0.85) loot.GetInventory().CreateAttachment("Mag_VAL_20Rnd");
					else               loot.GetInventory().CreateAttachment("Mag_Vikhr_30Rnd");
				}
				break;
			}

			case "ASVAL":
			{
				loot = ItemBase.Cast(GetGame().CreateObject("ASVAL", pos));
				if (!loot) break;
				loot.SetHealth01("", "", Math.RandomFloat(0.3, 1.0));

				if (Math.RandomFloat01() <= 0.35)
				{
					float r1 = Math.RandomFloat01();
					if (r1 < 0.50)      loot.GetInventory().CreateAttachment("Mag_VSS_10Rnd");
					else if (r1 < 0.85) loot.GetInventory().CreateAttachment("Mag_VAL_20Rnd");
					else               loot.GetInventory().CreateAttachment("Mag_Vikhr_30Rnd");
				}

				if (Math.RandomFloat01() <= 0.30)
				{
					float r2 = Math.RandomFloat01();
					if (r2 < 0.25)      loot.GetInventory().CreateAttachment("BUISOptic");
					else if (r2 < 0.50) loot.GetInventory().CreateAttachment("M4_T3NRDSOptic");
					else if (r2 < 0.75) loot.GetInventory().CreateAttachment("ReflexOptic");
					else               loot.GetInventory().CreateAttachment("ACOGOptic");
				}

				if (Math.RandomFloat01() <= 0.10) loot.GetInventory().CreateAttachment("TLRLight");
				break;
			}

			case "Vikhr":
			{
				loot = ItemBase.Cast(GetGame().CreateObject("Vikhr", pos));
				if (!loot) break;
				loot.SetHealth01("", "", Math.RandomFloat(0.3, 1.0));

				if (Math.RandomFloat01() <= 0.25)
				{
					if (Math.RandomFloat01() < 0.5) loot.GetInventory().CreateAttachment("KashtanOptic");
					else                            loot.GetInventory().CreateAttachment("PSO1Optic");
				}

				if (Math.RandomFloat01() <= 0.35)
				{
					float r3 = Math.RandomFloat01();
					if (r3 < 0.50)      loot.GetInventory().CreateAttachment("Mag_VSS_10Rnd");
					else if (r3 < 0.85) loot.GetInventory().CreateAttachment("Mag_VAL_20Rnd");
					else               loot.GetInventory().CreateAttachment("Mag_Vikhr_30Rnd");
				}
				break;
			}

			/* ------------------------------------------------------------- */
			/*  Bolt actions / snipers                                       */
			/* ------------------------------------------------------------- */
			case "SV98":
			{
				loot = ItemBase.Cast(GetGame().CreateObject("SV98", pos));
				if (!loot) break;
				loot.SetHealth01("", "", Math.RandomFloat(0.3, 1.0));

				if (Math.RandomFloat01() <= 0.25)
				{
					float r4 = Math.RandomFloat01();
					if (r4 < 0.30)      loot.GetInventory().CreateAttachment("M4_T3NRDSOptic");
					else if (r4 < 0.60) loot.GetInventory().CreateAttachment("ReflexOptic");
					else if (r4 < 0.85) loot.GetInventory().CreateAttachment("ACOGOptic");
					else               loot.GetInventory().CreateAttachment("ACOGOptic_6x");
				}

				if (Math.RandomFloat01() <= 0.45) loot.GetInventory().CreateAttachment("Mag_SV98_10Rnd");
				break;
			}

			case "Winchester70":
			{
				loot = ItemBase.Cast(GetGame().CreateObject("Winchester70", pos));
				if (!loot) break;
				loot.SetHealth01("", "", Math.RandomFloat(0.3, 0.7));

				if (Math.RandomFloat01() <= 0.20)
				{
					if (Math.RandomFloat01() < 0.90) loot.GetInventory().CreateAttachment("SportingOptic");
					else                              loot.GetInventory().CreateAttachment("HuntingOptic");
				}
				break;
			}

			case "Mosin9130":
			{
				loot = ItemBase.Cast(GetGame().CreateObject("Mosin9130", pos));
				if (!loot) break;
				loot.SetHealth01("", "", Math.RandomFloat(0.3, 0.7));

				if (Math.RandomFloat01() <= 0.10) loot.GetInventory().CreateAttachment("Mosin_Compensator");
				if (Math.RandomFloat01() <= 0.05) loot.GetInventory().CreateAttachment("PUScopeOptic");
				break;
			}

			case "SKS":
			{
				loot = ItemBase.Cast(GetGame().CreateObject("SKS", pos));
				if (!loot) break;
				loot.SetHealth01("", "", Math.RandomFloat(0.3, 0.7));

				if (Math.RandomFloat01() <= 0.10) loot.GetInventory().CreateAttachment("PUScopeOptic");
				break;
			}

			/* ------------------------------------------------------------- */
			/*  AK family                                                    */
			/* ------------------------------------------------------------- */
			case "AKM":
			{
				loot = ItemBase.Cast(GetGame().CreateObject("AKM", pos));
				if (!loot) break;
				loot.SetHealth01("", "", Math.RandomFloat(0.45, 0.85));

				loot.GetInventory().CreateAttachment("AK_PlasticBttstck");
				loot.GetInventory().CreateAttachment("AK_PlasticHndgrd");

				if (Math.RandomFloat01() <= 0.50)
				{
					float r5 = Math.RandomFloat01();
					if (r5 <= 0.30)      loot.GetInventory().CreateAttachment("KashtanOptic");
					else if (r5 <= 0.50) loot.GetInventory().CreateAttachment("PSO11Optic");
				}

				if (Math.RandomFloat01() <= 0.05) loot.GetInventory().CreateAttachment("AK_Suppressor");
				if (Math.RandomFloat01() <= 0.30) loot.GetInventory().CreateAttachment("Mag_AKM_30Rnd");
				break;
			}

			case "AK74":
			{
				loot = ItemBase.Cast(GetGame().CreateObject("AK74", pos));
				if (!loot) break;

				loot.GetInventory().CreateAttachment("AK74_WoodBttstck");
				loot.GetInventory().CreateAttachment("AK74_Hndgrd");

				if (Math.RandomFloat01() <= 0.30)
				{
					float r6 = Math.RandomFloat01();
					if (r6 <= 0.50)      loot.GetInventory().CreateAttachment("KashtanOptic");
					else if (r6 <= 0.80) loot.GetInventory().CreateAttachment("PSO11Optic");
				}

				if (Math.RandomFloat01() <= 0.30)
				{
					if (Math.RandomFloat01() <= 0.15) loot.GetInventory().CreateAttachment("Mag_AK74_45Rnd");
					else                               loot.GetInventory().CreateAttachment("Mag_AK74_30Rnd");
				}
				break;
			}

			case "AKS74U":
			{
				loot = ItemBase.Cast(GetGame().CreateObject("AKS74U", pos));
				if (!loot) break;

				loot.GetInventory().CreateAttachment("AKS74U_Bttstck");

				if (Math.RandomFloat01() <= 0.30) loot.GetInventory().CreateAttachment("Mag_AK74_30Rnd");
				break;
			}

			case "AK101":
			{
				loot = ItemBase.Cast(GetGame().CreateObject("AK101", pos));
				if (!loot) break;

				loot.GetInventory().CreateAttachment("AK_PlasticBttstck");
				loot.GetInventory().CreateAttachment("AK_PlasticHndgrd");

				if (Math.RandomFloat01() <= 0.30)
				{
					float r7 = Math.RandomFloat01();
					if (r7 <= 0.50)      loot.GetInventory().CreateAttachment("KashtanOptic");
					else if (r7 <= 0.80) loot.GetInventory().CreateAttachment("PSO11Optic");
				}

				if (Math.RandomFloat01() <= 0.30) loot.GetInventory().CreateAttachment("Mag_AK101_30Rnd");
				break;
			}

			/* ------------------------------------------------------------- */
			/*  5.56 mm AR platform                                          */
			/* ------------------------------------------------------------- */
			case "M4A1":
			{
				loot = ItemBase.Cast(GetGame().CreateObject("M4A1", pos));
				if (!loot) break;

				loot.GetInventory().CreateAttachment("M4_OEBttstck");
				loot.GetInventory().CreateAttachment("M4_PlasticHndgrd");

				if (Math.RandomFloat01() <= 1.00)
				{
					if (Math.RandomFloat01() <= 0.50) loot.GetInventory().CreateAttachment("BUISOptic");
					else                              loot.GetInventory().CreateAttachment("M4_CarryHandleOptic");
				}

				if (Math.RandomFloat01() <= 0.30)
				{
					float r8 = Math.RandomFloat01();
					if (r8 <= 0.15)      loot.GetInventory().CreateAttachment("Mag_CMAG_40Rnd");
					else if (r8 <= 0.65) loot.GetInventory().CreateAttachment("Mag_CMAG_10Rnd");
					else if (r8 <= 0.90) loot.GetInventory().CreateAttachment("Mag_CMAG_20Rnd");
					else                loot.GetInventory().CreateAttachment("Mag_CMAG_30Rnd");
				}
				break;
			}

			case "M16A2":
			{
				loot = ItemBase.Cast(GetGame().CreateObject("M16A2", pos));
				if (!loot) break;
				loot.SetHealth01("", "", Math.RandomFloat(0.3, 0.7));

				if (Math.RandomFloat01() <= 0.30)
				{
					float r9 = Math.RandomFloat01();
					if (r9 <= 0.15)      loot.GetInventory().CreateAttachment("Mag_CMAG_40Rnd");
					else if (r9 <= 0.65) loot.GetInventory().CreateAttachment("Mag_CMAG_10Rnd");
					else if (r9 <= 0.90) loot.GetInventory().CreateAttachment("Mag_CMAG_20Rnd");
					else                loot.GetInventory().CreateAttachment("Mag_CMAG_30Rnd");
				}
				break;
			}

			case "FAMAS":
			{
				loot = ItemBase.Cast(GetGame().CreateObject("FAMAS", pos));
				if (!loot) break;
				loot.SetHealth01("", "", Math.RandomFloat(0.3, 0.7));

				if (Math.RandomFloat01() <= 0.75) loot.GetInventory().CreateAttachment("Mag_FAMAS_25Rnd");
				break;
			}

			case "Aug":
			{
				loot = ItemBase.Cast(GetGame().CreateObject("Aug", pos));
				if (!loot) break;
				loot.SetHealth01("", "", Math.RandomFloat(0.3, 1.0));

				if (Math.RandomFloat01() <= 0.25) loot.GetInventory().CreateAttachment("Mag_Aug_30Rnd");

				if (Math.RandomFloat01() <= 0.30)
				{
					float r10 = Math.RandomFloat01();
					if (r10 < 0.25)      loot.GetInventory().CreateAttachment("BUISOptic");
					else if (r10 < 0.50) loot.GetInventory().CreateAttachment("M4_T3NRDSOptic");
					else if (r10 < 0.75) loot.GetInventory().CreateAttachment("ReflexOptic");
					else               loot.GetInventory().CreateAttachment("ACOGOptic");
				}

				if (Math.RandomFloat01() <= 0.10) loot.GetInventory().CreateAttachment("TLRLight");
				break;
			}

			case "AugShort":
			{
				loot = ItemBase.Cast(GetGame().CreateObject("AugShort", pos));
				if (!loot) break;
				loot.SetHealth01("", "", Math.RandomFloat(0.3, 0.7));

				if (Math.RandomFloat01() <= 0.25) loot.GetInventory().CreateAttachment("Mag_Aug_30Rnd");
				break;
			}

			/* ------------------------------------------------------------- */
			/*  Battle rifle / DMR                                           */
			/* ------------------------------------------------------------- */
			case "FAL":
			{
				loot = ItemBase.Cast(GetGame().CreateObject("FAL", pos));
				if (!loot) break;
				loot.SetHealth01("", "", Math.RandomFloat(0.45, 0.85));

				if (Math.RandomFloat01() <= 1.00)
				{
					if (Math.RandomFloat01() <= 0.33) loot.GetInventory().CreateAttachment("Fal_FoldingBttstck");
					else                              loot.GetInventory().CreateAttachment("Fal_OeBttstck");
				}

				if (Math.RandomFloat01() <= 0.20)
				{
					float r11 = Math.RandomFloat01();
					if (r11 < 0.20)      loot.GetInventory().CreateAttachment("BUISOptic");
					else if (r11 < 0.40) loot.GetInventory().CreateAttachment("M68Optic");
					else if (r11 < 0.60) loot.GetInventory().CreateAttachment("M4_T3NRDSOptic");
					else if (r11 < 0.80) loot.GetInventory().CreateAttachment("ReflexOptic");
					else               loot.GetInventory().CreateAttachment("ACOGOptic");
				}

				if (Math.RandomFloat01() <= 0.10) loot.GetInventory().CreateAttachment("Mag_FAL_20Rnd");
				break;
			}

			case "SVD":
            case "SVD_Wooden":
            {
                string baseName;
                if (weaponName == "SVD")
                    baseName = "SVD";
                else
                    baseName = "SVD_Wooden";

                loot = ItemBase.Cast(GetGame().CreateObject(baseName, pos));
                if (!loot) break;
                loot.SetHealth01("", "", Math.RandomFloat(0.3, 0.7));

                if (Math.RandomFloat01() <= 0.10)
                    loot.GetInventory().CreateAttachment("Mag_SVD_10Rnd");

                if (Math.RandomFloat01() <= 0.50)
                {
                    if (Math.RandomFloat01() <= 0.50)
                        loot.GetInventory().CreateAttachment("KashtanOptic");
                    else
                        loot.GetInventory().CreateAttachment("PSO11Optic");
                }
                break;
            }

			case "Scout":
			{
				loot = ItemBase.Cast(GetGame().CreateObject("Scout", pos));
				if (!loot) break;

				if (Math.RandomFloat01() <= 0.75) loot.GetInventory().CreateAttachment("Mag_Scout_5Rnd");

				if (Math.RandomFloat01() <= 0.25)
				{
					float r12 = Math.RandomFloat01();
					if (r12 < 0.20)      loot.GetInventory().CreateAttachment("M68Optic");
					else if (r12 < 0.40) loot.GetInventory().CreateAttachment("ACOGOptic");
					else if (r12 < 0.60) loot.GetInventory().CreateAttachment("ACOGOptic_6x");
					else if (r12 < 0.80) loot.GetInventory().CreateAttachment("MK4Optic_Black");
					else               loot.GetInventory().CreateAttachment("M4_Suppressor");
				}
				break;
			}

			case "CZ550":
			{
				loot = ItemBase.Cast(GetGame().CreateObject("CZ550", pos));
				if (!loot) break;
				loot.SetHealth01("", "", Math.RandomFloat(0.3, 0.7));

				if (Math.RandomFloat01() <= 0.20)
				{
					if (Math.RandomFloat01() <= 0.90) loot.GetInventory().CreateAttachment("SportingOptic");
					else                              loot.GetInventory().CreateAttachment("HuntingOptic");
				}

				if (Math.RandomFloat01() <= 0.30) loot.GetInventory().CreateAttachment("Mag_CZ550_10rnd");
				break;
			}

			case "R12":
			{
				loot = ItemBase.Cast(GetGame().CreateObject("R12", pos));
				if (!loot) break;

				if (Math.RandomFloat01() <= 0.30) loot.GetInventory().CreateAttachment("UniversalLight");
				if (Math.RandomFloat01() <= 0.30) loot.GetInventory().CreateAttachment("ReflexOptic");
				break;
			}

			case "M14":
			{
				loot = ItemBase.Cast(GetGame().CreateObject("M14", pos));
				if (!loot) break;

				if (Math.RandomFloat01() <= 0.25)
				{
					if (Math.RandomFloat01() < 0.70) loot.GetInventory().CreateAttachment("Mag_M14_10Rnd");
					else                              loot.GetInventory().CreateAttachment("Mag_M14_20Rnd");
				}

				if (Math.RandomFloat01() <= 0.30)
				{
					float r13 = Math.RandomFloat01();
					if (r13 < 0.30)      loot.GetInventory().CreateAttachment("M4_T3NRDSOptic");
					else if (r13 < 0.60) loot.GetInventory().CreateAttachment("ReflexOptic");
					else if (r13 < 0.90) loot.GetInventory().CreateAttachment("ACOGOptic");
					else               loot.GetInventory().CreateAttachment("ACOGOptic_6x");
				}
				break;
			}

			/* ------------------------------------------------------------- */
			/*  Misc (M79 GL, Saiga, B95…)                                   */
			/* ------------------------------------------------------------- */
			case "M79":
			{
				loot = ItemBase.Cast(GetGame().CreateObject("M79", pos));
				if (!loot) break;
				loot.SetHealth01("", "", Math.RandomFloat(0.45, 1.0));
				break;
			}

			case "Saiga":
			{
				loot = ItemBase.Cast(GetGame().CreateObject("Saiga", pos));
				if (!loot) break;

				loot.GetInventory().CreateAttachment("Saiga_Bttstck");

				if (Math.RandomFloat01() <= 0.10)
				{
					if (Math.RandomFloat01() <= 0.60) loot.GetInventory().CreateAttachment("Mag_Saiga_5Rnd");
					else                              loot.GetInventory().CreateAttachment("Mag_Saiga_8Rnd");
				}
				break;
			}

			case "B95":
			{
				loot = ItemBase.Cast(GetGame().CreateObject("B95", pos));
				if (!loot) break;
				loot.SetHealth01("", "", Math.RandomFloat(0.3, 0.7));

				if (Math.RandomFloat01() <= 0.20)
				{
					if (Math.RandomFloat01() < 0.90) loot.GetInventory().CreateAttachment("SportingOptic");
					else                              loot.GetInventory().CreateAttachment("HuntingOptic");
				}
				break;
			}

			/* ------------------------------------------------------------- */
			/*  Default – non-weapon items                                   */
			/* ------------------------------------------------------------- */
			default:
				//! nothing: item already spawned by FillContainerWithRandomLoot()
				break;
		}
	}
	
	static ref set<string> m_WeaponNames;

    static void InitWeaponNames()
    {
	    if (!m_WeaponNames)
	    {
		    m_WeaponNames = new set<string>;
		    m_WeaponNames.Insert("FNX45");
	    	m_WeaponNames.Insert("VSS");
	    	m_WeaponNames.Insert("ASVAL");
	    	m_WeaponNames.Insert("Vikhr");
		    m_WeaponNames.Insert("SV98");
		    m_WeaponNames.Insert("Winchester70");
		    m_WeaponNames.Insert("Mosin9130");
		    m_WeaponNames.Insert("SKS");
	    	m_WeaponNames.Insert("AK74");
		    m_WeaponNames.Insert("AKS74U");
		    m_WeaponNames.Insert("AK101");
		    m_WeaponNames.Insert("M4A1");
		    m_WeaponNames.Insert("M16A2");
	    	m_WeaponNames.Insert("FAMAS");
		    m_WeaponNames.Insert("AUG");
		    m_WeaponNames.Insert("AUGShort");
		    m_WeaponNames.Insert("FAL");
		    m_WeaponNames.Insert("SVD");
		    m_WeaponNames.Insert("SVD_Wooden");
		    m_WeaponNames.Insert("B95");
		    m_WeaponNames.Insert("Saiga");
		    m_WeaponNames.Insert("Scout");
		    m_WeaponNames.Insert("CZ550");
		    m_WeaponNames.Insert("M14");
		    m_WeaponNames.Insert("Engraved1911");
		    m_WeaponNames.Insert("Deagle");
	    	m_WeaponNames.Insert("Deagle_Gold");
		    m_WeaponNames.Insert("R12");
	    }
    }

    static bool IsWeapon(string name)
    {
	    InitWeaponNames();
	    return m_WeaponNames.Find(name) != -1;
    }
	
};
