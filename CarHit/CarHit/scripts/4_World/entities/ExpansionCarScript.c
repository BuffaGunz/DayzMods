#ifdef EXPANSION_VEHICLEBASE
modded class ExpansionVehicleBase
{
    protected InvisibleFireplace m_HoodFire;
    protected ref Timer m_FireDamageTimer;

    override void OnContact(string zoneName, vector localPos, IEntity other, Contact data)
    {
        super.OnContact(zoneName, localPos, other, data);

        float speedKmh = GetSpeedometer();
        Object obj = Object.Cast(other);

        // 🛑 Ignore weak impulses or non-solid objects
        if (!obj || data.Impulse < 2000)
            return;

        string objType = obj.GetType();
        if (!(obj.IsTree() || obj.IsBush() || obj.IsRock() || obj.IsInherited(ZombieBase) || obj.IsInherited(PlayerBase) || obj.IsInherited(AnimalBase) || objType.Contains("House") || objType.Contains("Fence") || objType.Contains("Wreck") || objType.Contains("Barrier") || objType.Contains("Gate") || objType.Contains("Wall") || objType.Contains("Roadblock")))
            return;

        bool isStatic = obj && (obj.IsBuilding() || obj.IsRock() || obj.IsTree() || obj.IsBush());

        auto damageCfg = CarHitConfig.Get().DamageSettings;

        if (other && (other.IsInherited(ZombieBase) || other.IsInherited(PlayerBase) || other.IsInherited(AnimalBase)))
        {
            if (Math.RandomFloatInclusive(0.0, 1.0) <= 0.2)
                EngineStop();
        }

        if (isStatic && speedKmh > 50)
        {
            if (Math.RandomFloatInclusive(0.0, 1.0) <= damageCfg.StaticImpactStallChance)
                EngineStop();
        }

        if (speedKmh > 25 && obj && obj.IsTree() && obj.IsCuttable())
        {
            if (obj.IsInherited(TreeHard) || obj.IsInherited(TreeSoft) || obj.IsInherited(BushHard))
            {
                auto treeCfg = CarHitConfig.Get().TreeSettings;
                if (treeCfg.EnableTreeDestruction)
                {
                    obj.DecreaseHealth("", "", 100, true);
                    obj.OnTreeCutDown(this);

                    vector treePos = obj.GetPosition();

                    int firewood = Math.RandomIntInclusive(treeCfg.FirewoodSpawnMin, treeCfg.FirewoodSpawnMax);
                    int sticks   = Math.RandomIntInclusive(treeCfg.LongStickSpawnMin, treeCfg.LongStickSpawnMax);

                    for (int i = 0; i < firewood; i++)
                        GetGame().CreateObjectEx("Firewood", treePos + Vector(Math.RandomFloat(-0.5, 0.5), 0, Math.RandomFloat(-0.5, 0.5)), ECE_PLACE_ON_SURFACE);

                    for (int j = 0; j < sticks; j++)
                        GetGame().CreateObjectEx("LongWoodenStick", treePos + Vector(Math.RandomFloat(-0.5, 0.5), 0, Math.RandomFloat(-0.5, 0.5)), ECE_PLACE_ON_SURFACE);

                    dBodyDestroy(obj);
                }
            }
        }

        for (int c = 0; c < CrewSize(); ++c)
        {
            Human crew = CrewMember(c);
            if (!crew) continue;

            PlayerBase player;
            if (Class.CastTo(player, crew) && player.IsAlive())
            {
                if (!damageCfg.EnablePlayerDamage)
                    continue;

                if (!damageCfg) return;

                if (damageCfg.AllowBrokenLegs && speedKmh > damageCfg.BrokenLegSpeedThreshold)
                    player.GetModifiersManager().ActivateModifier(eModifiers.MDF_BROKEN_LEGS);

                if (damageCfg.AllowBleeding && speedKmh > damageCfg.BleedingSpeedThreshold)
                {
                    player.GetBleedingManagerServer().AttemptAddBleedingSourceBySelection("LeftLeg");
                    if (speedKmh > 70)
                        player.GetBleedingManagerServer().AttemptAddBleedingSourceBySelection("RightLeg");
                }
            }
        }
    }

    override void EEKilled(Object killer)
    {
        if (!CarHitConfig.Get().FireSettings.EnableFireOnCrash)
            return;

        super.EEKilled(killer);

        if (m_HoodFire) return;

        vector flamePos;
        if (MemoryPointExists("engine"))
            flamePos = GetMemoryPointPos("engine");
        else
            flamePos = "0 0.8 1.5";

        m_HoodFire = InvisibleFireplace.Cast(GetGame().CreateObject("InvisibleFireplace", GetPosition(), false));
        if (!m_HoodFire) return;

        AddChild(m_HoodFire, -1);
        m_HoodFire.SetPosition(flamePos);

        int burnDuration = CarHitConfig.Get().FireSettings.FireDurationSeconds;
        m_HoodFire.SetLifetime(burnDuration);

        m_HoodFire.SetTakeable(false);
        m_HoodFire.SetViewIndex(-1);
        m_HoodFire.SetWet(false);

        if (GetGame().IsServer())
        {
            m_FireDamageTimer = new Timer(CALL_CATEGORY_SYSTEM);
            m_FireDamageTimer.Run(2.0, this, "ApplyFireDamageToNearby", NULL, true);
        }

        SetEventMask(EntityEvent.FRAME);
    }

    override void EEDelete(EntityAI parent)
    {
        super.EEDelete(parent);

        if (m_HoodFire)
        {
            m_HoodFire.Delete();
            m_HoodFire = null;
        }

        if (m_FireDamageTimer)
        {
            m_FireDamageTimer.Stop();
            m_FireDamageTimer = null;
        }
    }

    override void EOnFrame(IEntity other, float timeSlice)
    {
        super.EOnFrame(other, timeSlice);

        if (m_HoodFire && MemoryPointExists("engine"))
        {
            vector hoodPos = GetMemoryPointPos("engine");
            m_HoodFire.SetPosition(hoodPos);
        }
    }

    void ApplyFireDamageToNearby()
    {
        if (!m_HoodFire) return;

        vector flamePos;
        if (MemoryPointExists("engine"))
            flamePos = ModelToWorld(GetMemoryPointPos("engine"));
        else
            flamePos = ModelToWorld("0 0.8 1.5");

        array<Object> nearby = new array<Object>();
        array<CargoBase> proxy = new array<CargoBase>();

        GetGame().GetObjectsAtPosition(flamePos, 0.4, nearby, proxy);

        foreach (Object obj : nearby)
        {
            if (!obj || obj == this) continue;

            if (obj.IsInherited(PlayerBase) || obj.IsInherited(ZombieBase) || obj.IsInherited(AnimalBase))
            {
                EntityAI target = EntityAI.Cast(obj);
                if (!target) continue;

                target.ProcessDirectDamage(DT_CUSTOM, m_HoodFire, "", "FireDamage", flamePos, 2.0);
            }
        }
    }
};
#endif
