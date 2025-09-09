modded class MissionServer
{
	#ifdef BASICMAP
	override void OnClientReadyEvent(PlayerIdentity identity, PlayerBase player)
    {
        super.OnClientReadyEvent(identity, player);

        RuckBasicMarkerService.PushGroupTo(identity);
    }
	#endif
	
    override void OnInit()
    {
        super.OnInit();
        Print("✅ MissionServer OnInit: Initializing repeating RuckPlane event.");
        StartRepeatingRuckPlaneEvent();
    }

    void StartRepeatingRuckPlaneEvent()
    {
        AirDropSettings settings = AirDropSettings.Get();
        int delay = Math.RandomInt(settings.DropIntervalMin, settings.DropIntervalMax);
        GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.TriggerRuckPlaneEvent, delay, false);
    }

    void TriggerRuckPlaneEvent()
    {
        Print("✈️ RuckPlane Event Triggered");
        GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(RuckPlane.SpawnSite, 2500, false);
        StartRepeatingRuckPlaneEvent();
    }

    override void OnEvent(EventType eventTypeId, Param params)
    {
        super.OnEvent(eventTypeId, params);

        if (eventTypeId == ChatMessageEventTypeID)
        {
            Param3<string, string, int> chatParams = Param3<string, string, int>.Cast(params);
            if (!chatParams) return;

            string senderName = chatParams.param1;
            string message    = chatParams.param2;
            int channel       = chatParams.param3;

            if (message == "/ruckplane")
            {
                Print("🛬 [RuckPlane] Chat trigger received — spawning manually");
                RuckPlane.SpawnSite();
            }
        }
    }

}
