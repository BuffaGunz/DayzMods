modded class PlayerBase
{
	bool m_VehicleHitSuspended = false;

	void ResetVehicleHit()
	{
		m_VehicleHitSuspended = false;
	}

	float CalculateZoneDamage(CarScript car, string zone, float percent)
	{
		// Check if zone exists before calculating
		if (car.GetHealth01(zone, "Health") == -1)
			return 0;

		float maxHealth = car.GetMaxHealth(zone, "Health");
		if (maxHealth <= 0)
			return 0;

		return (maxHealth * percent);
	}

	override void EEHitBy(TotalDamageResult damageResult, int damageType, EntityAI source, int component, string dmgZone, string ammo, vector modelPos, float speedCoef)
	{
		super.EEHitBy(damageResult, damageType, source, component, dmgZone, ammo, modelPos, speedCoef);

		if (ammo != "TransportHit" || !source || !source.IsInherited(CarScript) || m_VehicleHitSuspended)
			return;

		CarScript car = CarScript.Cast(source);
		if (!car) return;

		float speed = car.GetSpeedometer();
		if (speed < 15)
			return;

		vector impactPos = this.GetPosition();

		auto cfg = CarHitConfig.Get().DamageSettings;
		if (cfg && cfg.EnablePlayerDamage)
		{
			float percent = 0.03;
			if (speed >= 70)
				percent = 0.12;
			else if (speed > 30)
				percent = 0.08;

			percent *= cfg.PlayerTransportHitDamageMul;

			// Apply damage only if the zone exists
			if (car.GetHealth01("Front", "Health") != -1)
				car.ProcessDirectDamage(DT_CUSTOM, car, "Front", "TransportHit", impactPos, CalculateZoneDamage(car, "Front", percent));

			if (car.GetHealth01("Back", "Health") != -1)
				car.ProcessDirectDamage(DT_CUSTOM, car, "Back", "TransportHit", impactPos, CalculateZoneDamage(car, "Back", percent));

			if (car.GetHealth01("Roof", "Health") != -1)
				car.ProcessDirectDamage(DT_CUSTOM, car, "Roof", "TransportHit", impactPos, CalculateZoneDamage(car, "Roof", percent));

			if (car.GetHealth01("Fender_1_1", "Health") != -1)
				car.ProcessDirectDamage(DT_CUSTOM, car, "Fender_1_1", "TransportHit", impactPos, CalculateZoneDamage(car, "Fender_1_1", percent));

			if (car.GetHealth01("Fender_2_1", "Health") != -1)
				car.ProcessDirectDamage(DT_CUSTOM, car, "Fender_2_1", "TransportHit", impactPos, CalculateZoneDamage(car, "Fender_2_1", percent));

			if (car.GetHealth01("Fender_2_2", "Health") != -1)
				car.ProcessDirectDamage(DT_CUSTOM, car, "Fender_2_2", "TransportHit", impactPos, CalculateZoneDamage(car, "Fender_2_2", percent));

			if (car.GetHealth01("WindowFront", "Health") != -1)
				car.ProcessDirectDamage(DT_CUSTOM, car, "WindowFront", "TransportHit", impactPos, CalculateZoneDamage(car, "WindowFront", percent));

			if (car.GetHealth01("WindowLR", "Health") != -1)
				car.ProcessDirectDamage(DT_CUSTOM, car, "WindowLR", "TransportHit", impactPos, CalculateZoneDamage(car, "WindowLR", percent));

			if (car.GetHealth01("WindowRR", "Health") != -1)
				car.ProcessDirectDamage(DT_CUSTOM, car, "WindowRR", "TransportHit", impactPos, CalculateZoneDamage(car, "WindowRR", percent));

			if (car.GetHealth01("Engine", "Health") != -1)
				car.ProcessDirectDamage(DT_CUSTOM, car, "Engine", "TransportHit", impactPos, CalculateZoneDamage(car, "Engine", percent));

			if (car.GetHealth01("Reflector_1_1", "Health") != -1)
				car.ProcessDirectDamage(DT_CUSTOM, car, "Reflector_1_1", "TransportHit", impactPos, CalculateZoneDamage(car, "Reflector_1_1", percent));

			if (car.GetHealth01("Reflector_2_1", "Health") != -1)
				car.ProcessDirectDamage(DT_CUSTOM, car, "Reflector_2_1", "TransportHit", impactPos, CalculateZoneDamage(car, "Reflector_2_1", percent));
		}

		if (speed >= 70)
			car.SynchCrashHeavySound(true);
		else if (speed > 10)
			car.SynchCrashLightSound(true);

		m_VehicleHitSuspended = true;
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(ResetVehicleHit, 1000, false);
	}
}
