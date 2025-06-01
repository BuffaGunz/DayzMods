class InvisibleFireplace : Bonfire
{
    protected ref UniversalTemperatureSourceLambdaConstant m_CustomUTSLambda;
    protected ref UniversalTemperatureSource m_CustomUTSource;
    protected ref UniversalTemperatureSourceSettings m_CustomUTSSettings;
    protected ref Timer m_DeleteTimer;

    override void EEInit()
    {
        vector localPos = "0 0 -0.2";

        // Scaled-down flame particle
        if (!m_ParticleFire)
        {
            m_ParticleFire = ParticleManager.GetInstance().PlayOnObject(ParticleList.BONFIRE_FIRE, this, localPos, Vector(0, 0, 0), true);
            m_ParticleFire.ScaleParticleParamFromOriginal(EmitorParam.SIZE, 0.3);
        }

        #ifndef SERVER
        // Fire sound (client-only)
        PlaySoundSetLoop(m_SoundFireLoop, "HeavyFire_SoundSet", 1.0, 2.0);
        #endif

        if (GetGame().IsServer() || !GetGame().IsMultiplayer())
        {
            // Heat emission
            m_CustomUTSSettings = new UniversalTemperatureSourceSettings();
            m_CustomUTSSettings.m_UpdateInterval = 2;
            m_CustomUTSSettings.m_Updateable = true;
            m_CustomUTSSettings.m_TemperatureItemCap = GameConstants.ITEM_TEMPERATURE_NEUTRAL_ZONE_MIDDLE;
            m_CustomUTSSettings.m_TemperatureCap = 25;
            m_CustomUTSSettings.m_RangeFull = 6;
            m_CustomUTSSettings.m_RangeMax = 18;

            m_CustomUTSLambda = new UniversalTemperatureSourceLambdaConstant();
            m_CustomUTSource = new UniversalTemperatureSource(this, m_CustomUTSSettings, m_CustomUTSLambda);
            m_CustomUTSource.SetActive(true);

            // Auto-delete after 5 minutes
            m_DeleteTimer = new Timer(CALL_CATEGORY_SYSTEM);
            m_DeleteTimer.Run(300, this, "DeleteSelf");
        }
    }

    void DeleteSelf()
    {
        GetGame().ObjectDelete(this);
    }

    override void EEDelete(EntityAI parent)
    {
        super.EEDelete(parent);

        if (m_ParticleFire)
        {
            m_ParticleFire.Stop();
            m_ParticleFire = null;
        }

        #ifndef SERVER
        if (m_SoundFireLoop)
        {
            m_SoundFireLoop.SoundStop();
            m_SoundFireLoop = null;
        }
        #endif

        if (m_CustomUTSource)
        {
            m_CustomUTSource.SetActive(false);
            m_CustomUTSource = null;
        }

        if (m_DeleteTimer)
        {
            m_DeleteTimer.Stop();
            m_DeleteTimer = null;
        }
    }
}
