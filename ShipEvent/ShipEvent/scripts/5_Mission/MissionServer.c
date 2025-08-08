modded class MissionServer
{
   override void OnInit()
	{
		super.OnInit();

		Print("✅ MissionServer OnInit: Initializing repeating shipwreck event.");
		StartRepeatingShipWreckEvent();
	}
	
    void StartRepeatingShipWreckEvent()
    {
        auto settings = ShipWreckSettings.Get();
        int delay = Math.RandomInt(settings.CrashIntervalMin, settings.CrashIntervalMax);
        GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(this.TriggerShipWreckEvent, delay, false);
    }

    void TriggerShipWreckEvent()
    {
        Print("✈️ Cargo Plane Event Triggered");
        GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(ShipWreck.SpawnSite, 2500, false);

        // Schedule the next one
        StartRepeatingShipWreckEvent();
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
                Print("ShipEvent Triggered");
                ShipWreck.SpawnSite(); // ✅ Updated to use ShipWreck
            }
        }
    }
}
