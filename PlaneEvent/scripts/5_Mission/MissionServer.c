modded class MissionServer
{
	#ifdef BASICMAP
	override void OnClientReadyEvent(PlayerIdentity identity, PlayerBase player)
    {
        super.OnClientReadyEvent(identity, player);

        RuckPlaneBasicMarkerService.PushGroupTo(identity);
    }
	#endif
	
    override void OnInit()
    {
        super.OnInit();

        Print("✅ MissionServer OnInit: Initializing repeating cargo plane event.");
        StartRepeatingCargoPlaneEvent();
    }

    void StartRepeatingCargoPlaneEvent()
    {
        auto settings = PlaneCrashSettings.Get();
        int delay = Math.RandomInt(settings.CrashIntervalMin, settings.CrashIntervalMax);
        GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.TriggerCargoPlaneEvent, delay, false);
    }

    void TriggerCargoPlaneEvent()
    {
        Print("✈️ Cargo Plane Event Triggered");
        GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(PlaneCrash.SpawnSite, 2500, false);

        // Schedule the next one
        StartRepeatingCargoPlaneEvent();
    }

    override void OnEvent(EventType eventTypeId, Param params)
    {
        super.OnEvent(eventTypeId, params);

        if (eventTypeId == ChatMessageEventTypeID)
        {
            Param3<string, string, int> chatParams = Param3<string, string, int>.Cast(params);
            if (!chatParams)
                return;

            string senderName = chatParams.param1;
            string message = chatParams.param2;
            int channel = chatParams.param3;

            if (message == "/crash")
            {
                Print("🛬 [PlaneEvent] Chat trigger received — Spawning crash site");
                PlaneCrash.SpawnSite(); // ✅ Updated to use PlaneCrash
            }
        }
    }
}
