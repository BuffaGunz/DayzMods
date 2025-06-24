class PlaneCrash extends CrashBase
{
	static ref array<EntityAI> m_PreviousWrecks = new array<EntityAI>();
	static ref map<EntityAI, int> m_ContainerTimers = new map<EntityAI, int>();
	static const int MAX_CONTAINER_LIFETIME = 3600000; // 1 hour
	static const int CONTAINER_CHECK_INTERVAL = 300000; // 5 minutes

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

        // ✅ Use custom site if enabled
        if (settings.EnableCustomCrashSites && settings.CustomCrashSites && settings.CustomCrashSites.Count() > 0)
        {
            vector site = settings.CustomCrashSites.GetRandomElement();
            site[1] = GetGame().SurfaceY(site[0], site[2]);
            Print("📍 Using custom crash site: " + site);
            return site;
        }

        // ✅ Try zone A (0–7500)
        vector zoneA = GenerateCrashSiteInRange(1000, 7500);
        if (zoneA != vector.Zero)
        {
            Print("📍 Using zone A crash site: " + zoneA);
            return zoneA;
        }

        // ✅ Try zone B (7500–15000)
        vector zoneB = GenerateCrashSiteInRange(7500, 14000);
        if (zoneB != vector.Zero)
        {
            Print("📍 Using zone B crash site: " + zoneB);
            return zoneB;
        }

        // ❌ Fallback to hardcoded default
        vector fallback = Vector(4264.498535, GetGame().SurfaceY(4264.498535, 4429.974121), 4429.974121);
        Print("⚠️ No valid site found — using fallback: " + fallback);
        return fallback;
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

            // Check slope
            vector normal = GetGame().SurfaceGetNormal(x, z);
            if (normal[1] < 0.95)
                continue;

            // Check water
            string surfType;
            GetGame().SurfaceGetType(x, z, surfType);
            surfType.ToLower();

            if (GetGame().SurfaceIsSea(x, z) || surfType.Contains("pond") || surfType.Contains("lake") || surfType.Contains("river") || surfType.Contains("swamp") || surfType.Contains("water"))
                continue;

            // Check objects
            array<Object> objects = {};
            array<CargoBase> dummy = {};
            GetGame().GetObjectsAtPosition(pos, 20.0, objects, dummy);

            bool blocked = false;
            foreach (Object obj : objects)
            {
                if (!obj) continue;
                string type = obj.GetType();
                if (type.Contains("House") || type.Contains("Land_Container") || type.Contains("Wreck"))
                {
                    blocked = true;
                    break;
                }
            }

            if (blocked)
                continue;

            return pos;
        }

        return vector.Zero;
    }

	static void SpawnSite()
	{
		vector crashPos = FindValidCrashSite();
        crashPos[1] = crashPos[1] + 5.0;

		array<Object> nearby = {};
		array<CargoBase> dummy = {};
		GetGame().GetObjectsAtPosition(crashPos, 100.0, nearby, dummy);

		foreach (Object obj : nearby)
		{
			if (!obj || obj.GetType() == "PlaneCrash" || obj.GetType().IndexOf("Land_ContainerLocked") != -1)
			{
				Print("⚠️ Crash or container already nearby, skipping spawn.");
				return;
			}
		}

		EntityAI wreck = EntityAI.Cast(GetGame().CreateObject("PlaneCrash", crashPos));
		wreck.SetAffectPathgraph(true, true);
		if (!wreck) return;

		vector up = GetGame().SurfaceGetNormal(crashPos[0], crashPos[2]);
		vector forward = Vector(0, 0, -1);
		vector right = vector.Direction(up, forward).Normalized();
		forward = vector.Direction(right, up).Normalized();

		float yaw = Math.Atan2(forward[0], forward[2]) * Math.RAD2DEG;
		float pitch = (-Math.Asin(forward[1]) * Math.RAD2DEG) + 70.0;
		vector orientation = Vector(pitch, yaw, 0);
		wreck.SetOrientation(orientation);

		#ifdef SERVER
		Param3<bool, vector, int> playSound = new Param3<bool, vector, int>(true, wreck.GetPosition(), "HeliCrash_Distant_SoundSet".Hash());
		GetGame().RPCSingleParam(null, ERPCs.RPC_SOUND_HELICRASH, playSound, true);
		#endif

		vector updatedDir = wreck.GetDirection();
		vector backOffset = updatedDir * 17.0;
		vector cargoPos = wreck.GetPosition() + backOffset;
		cargoPos[1] = GetGame().SurfaceY(cargoPos[0], cargoPos[2]) + 1.05;

		ref array<string> containerTypes = {
			"Land_ContainerLocked_Blue_DE",
			"Land_ContainerLocked_Red_DE",
			"Land_ContainerLocked_Yellow_DE",
			"Land_ContainerLocked_Orange_DE"
		};
		string selectedType = containerTypes.GetRandomElement();

		EntityAI container = GetGame().CreateObject(selectedType, cargoPos);
		container.SetAffectPathgraph(true, true);
		if (container)
		{
			container.SetFlags(EntityFlags.STATIC, false);
			container.SetLifetime(0); // Persistent object

			m_ContainerTimers.Insert(container, 0);
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(CheckContainerLifetime, CONTAINER_CHECK_INTERVAL, true, container);

			FillContainerWithRandomLoot(cargoPos);
		}

		string keyName;
        switch (selectedType)
        {
	        case "Land_ContainerLocked_Blue_DE":
		        keyName = "ShippingContainerKeys_Blue";
		        break;
	        case "Land_ContainerLocked_Red_DE":
		        keyName = "ShippingContainerKeys_Red";
		        break;
	        case "Land_ContainerLocked_Yellow_DE":
		        keyName = "ShippingContainerKeys_Yellow";
		        break;
	        case "Land_ContainerLocked_Orange_DE":
		        keyName = "ShippingContainerKeys_Orange";
		        break;
        }
        SpawnZombiesWithKey(crashPos, keyName);
		
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
	    	m_ContainerTimers.Set(obj, 0); // Reset timer if players are near
	    }
    	else
	    {
	    	int elapsed = m_ContainerTimers.Get(obj) + CONTAINER_CHECK_INTERVAL;
		    if (elapsed >= MAX_CONTAINER_LIFETIME)
		    {
		    	m_ContainerTimers.Remove(obj);
		    	GetGame().ObjectDelete(obj);
		    }
		    else
		    {
		    	m_ContainerTimers.Set(obj, elapsed);
		    }
	    }
    }


	static void CleanupWreck(EntityAI wreck)
	{
		if (wreck)
			m_PreviousWrecks.RemoveItem(wreck);
	}

	static void SpawnZombiesWithKey(vector center, string keyName)
    {
	    const int ZOMBIE_COUNT = 15;
	    array<string> zombieTypes = {
		     "ZmbM_PatrolNormal_Summer",
             "ZmbM_PatrolNormal_Autumn",
			 "ZmbM_SoldierNormal",
			 "ZmbM_eastSoldier_Heavy_Navy",
			 "ZmbM_eastSoldier_normal_Navy",
			 "ZmbM_usSoldier_Heavy_Woodland",
			 "ZmbM_usSoldier_Officer_Desert"
	    };

	    int keyZombieIndex = Math.RandomInt(0, ZOMBIE_COUNT);

	    for (int i = 0; i < ZOMBIE_COUNT; ++i)
	    {
		    vector pos = center + Vector(Math.RandomFloat(-10, 10), 0, Math.RandomFloat(-10, 10));
		    pos[1] = GetGame().SurfaceY(pos[0], pos[2]);
		    string zombieType = zombieTypes.GetRandomElement();

		    DayZInfected z = DayZInfected.Cast(GetGame().CreateObject(zombieType, pos, false, true));
		    if (z)
		    {
			    z.SetAffectPathgraph(true, true);

			    if (i == keyZombieIndex)
			    {
				    ItemBase keyItem = ItemBase.Cast(z.GetInventory().CreateInInventory(keyName));
				    if (keyItem)
					    keyItem.SetHealth01("", "", 0.10);
			    }
		    }
	    }
    }

	static void FillContainerWithRandomLoot(vector centerPos)
    {
        ref set<string> spawnedWeapons = new set<string>();
        ref array<string> lootPool;

        auto settings = PlaneCrashSettings.Get();
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
		
		for (int i = 0; i < 15; ++i)
	    {
		    string itemName = lootPool.GetRandomElement();

		    /* -------- Prevent duplicate weapons -------- */
		    if (IsWeapon(itemName))
		    {
			    if (spawnedWeapons.Find(itemName) != -1)
			    {
				    --i;                     // pick another item this iteration
				    continue;
			    }

			    //! mark weapon as spawned & create it with attachments
			    spawnedWeapons.Insert(itemName);

			    vector wPos = centerPos + Vector(Math.RandomFloat(-1, 1), 0, Math.RandomFloat(-1, 1));
			    wPos[1] = GetGame().SurfaceY(wPos[0], wPos[2]);

			    SpawnWeaponWithAttachments(itemName, wPos);   // this creates the weapon
			    continue;  // skip the non-weapon spawn below
		    }

		    /* -------- Non-weapon items (allow duplicates) -------- */
		    vector pos = centerPos + Vector(Math.RandomFloat(-1, 1), 0, Math.RandomFloat(-1, 1));
		    pos[1] = GetGame().SurfaceY(pos[0], pos[2]);

		    ItemBase item = ItemBase.Cast(GetGame().CreateObject(itemName, pos, false, false));
		    if (!item) continue;

		    item.SetHealth01("", "", Math.RandomFloat(0.30, 1.0));
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
