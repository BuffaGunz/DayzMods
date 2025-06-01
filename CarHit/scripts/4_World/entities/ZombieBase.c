modded class ZombieBase
{
	bool m_VehicleHitSuspended = false;

	void ResetVehicleHit()
	{
		m_VehicleHitSuspended = false;
	}

	// Helper to calculate percentage-based damage
	float CalculateZoneDamage(CarScript car, string zone, float percent)
	{
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
			return; // Ignore minor nudges

		vector impactPos = this.GetPosition();

		// Tiered percent damage
		float percent = 0.03; // = 3%
		if (speed >= 70)
			percent = 0.12; // = 12%
		else if (speed > 30)
			percent = 0.08; // = 8%

		// Apply percentage-based damage to core zones
		car.ProcessDirectDamage(DT_CUSTOM, car, "Front", "TransportHit", impactPos, CalculateZoneDamage(car, "Front", percent));
		car.ProcessDirectDamage(DT_CUSTOM, car, "Back", "TransportHit", impactPos, CalculateZoneDamage(car, "Back", percent));
		car.ProcessDirectDamage(DT_CUSTOM, car, "Roof", "TransportHit", impactPos, CalculateZoneDamage(car, "Roof", percent));
		car.ProcessDirectDamage(DT_CUSTOM, car, "Fender_1_1", "TransportHit", impactPos, CalculateZoneDamage(car, "Fender_1_1", percent));
		car.ProcessDirectDamage(DT_CUSTOM, car, "Fender_2_1", "TransportHit", impactPos, CalculateZoneDamage(car, "Fender_2_1", percent));
		car.ProcessDirectDamage(DT_CUSTOM, car, "Fender_2_2", "TransportHit", impactPos, CalculateZoneDamage(car, "Fender_2_2", percent));
		car.ProcessDirectDamage(DT_CUSTOM, car, "WindowFront", "TransportHit", impactPos, CalculateZoneDamage(car, "WindowFront", percent));
		car.ProcessDirectDamage(DT_CUSTOM, car, "WindowLR", "TransportHit", impactPos, CalculateZoneDamage(car, "WindowLR", percent));
		car.ProcessDirectDamage(DT_CUSTOM, car, "WindowRR", "TransportHit", impactPos, CalculateZoneDamage(car, "WindowRR", percent));
		car.ProcessDirectDamage(DT_CUSTOM, car, "Engine", "TransportHit", impactPos, CalculateZoneDamage(car, "Engine", percent));
		car.ProcessDirectDamage(DT_CUSTOM, car, "Reflector_1_1", "TransportHit", impactPos, CalculateZoneDamage(car, "Reflector_1_1", percent));
		car.ProcessDirectDamage(DT_CUSTOM, car, "Reflector_2_1", "TransportHit", impactPos, CalculateZoneDamage(car, "Reflector_2_1", percent));

		m_VehicleHitSuspended = true;
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(ResetVehicleHit, 1000, false);

		if (speed >= 70)
			car.SynchCrashHeavySound(true);
		else if (speed > 10)
			car.SynchCrashLightSound(true);
	}
}
