class CH_DamageSettings {
	bool EnablePlayerDamage = true;
	bool EnableZombieDamage = true;
	bool EnableAnimalDamage = true;
	float PlayerTransportHitDamageMul = 1.0;
	float ZombieTransportHitDamageMul = 1.0;
	float AnimalTransportHitDamageMul = 1.0;
	bool AllowBrokenLegs = true;
	bool AllowBleeding = true;
	float BrokenLegSpeedThreshold = 50.0;
	float BleedingSpeedThreshold = 50.0;
	float StaticImpactStallChance = 0.3;  // ✅ new config value
};

class CH_TreeSettings {
	bool EnableTreeDestruction = true;
	int FirewoodSpawnMin = 2;
	int FirewoodSpawnMax = 6;
	int LongStickSpawnMin = 1;
	int LongStickSpawnMax = 3;
};

class CH_FireSettings {
	bool EnableFireOnCrash = true;
	int FireDurationSeconds = 300;
};

class CH_CarPartMultipliers {
	float Engine = 1.0;
	float Radiator = 0.8;
	float Battery = 0.5;
	float Hood = 1.2;
	float Wheels = 0.6;
	float Windows = 1.0;
};

class CarHitConfig {
	ref CH_DamageSettings DamageSettings;
	ref CH_TreeSettings TreeSettings;
	ref CH_FireSettings FireSettings;
	ref CH_CarPartMultipliers CarPartDamageMultipliers;

	private static ref CarHitConfig s_Instance;

	void CarHitConfig() {
		DamageSettings = new CH_DamageSettings();
		TreeSettings = new CH_TreeSettings();
		FireSettings = new CH_FireSettings();
		CarPartDamageMultipliers = new CH_CarPartMultipliers();
	}

	static CarHitConfig Get() {
		if (!s_Instance)
			Load();
		return s_Instance;
	}

	private static void Load() {
		string folder = "$profile:CarCrash";
		string path = folder + "/CarHitSettings.json";

		if (!FileExist(folder))
			MakeDirectory(folder);

		ref CarHitConfig cfg = new CarHitConfig();

		if (FileExist(path)) {
			JsonFileLoader<CarHitConfig>.JsonLoadFile(path, cfg);
			Print("[CarHit] Config loaded from file.");

			// Fallbacks for missing config fields
			if (!cfg.DamageSettings)
				cfg.DamageSettings = new CH_DamageSettings();
			if (!cfg.TreeSettings)
				cfg.TreeSettings = new CH_TreeSettings();
			if (!cfg.FireSettings)
				cfg.FireSettings = new CH_FireSettings();
			if (!cfg.CarPartDamageMultipliers)
				cfg.CarPartDamageMultipliers = new CH_CarPartMultipliers();

			// Debug output
			Print("[CarHit] Tree destruction enabled = " + cfg.TreeSettings.EnableTreeDestruction);
			Print("[CarHit] Firewood spawn range = " + cfg.TreeSettings.FirewoodSpawnMin + " to " + cfg.TreeSettings.FirewoodSpawnMax);
			Print("[CarHit] Fire on crash enabled = " + cfg.FireSettings.EnableFireOnCrash);
			Print("[CarHit] Player damage enabled = " + cfg.DamageSettings.EnablePlayerDamage);
		} else {
			JsonFileLoader<CarHitConfig>.JsonSaveFile(path, cfg);
			Print("[CarHit] No config found. Created default CarHitSettings.json.");
		}

		s_Instance = cfg;
	}
};
