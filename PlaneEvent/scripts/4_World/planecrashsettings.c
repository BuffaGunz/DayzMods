class PlaneCrashSiteData
{
    vector Position;
    string NotificationMessage;
    
    void PlaneCrashSiteData(vector pos, string msg)
    {
        Position = pos;
        NotificationMessage = msg;
    }
}

class PlaneCrashSettings
{
    int CrashIntervalMin = 1200000;
    int CrashIntervalMax = 1800000;

    bool EnableCustomCrashSites = false;
	bool EnableGasZones = false;
	int GasZoneChancePercent = 100;

	bool EnableExpansionMarkers = true;
	bool EnableBasicMapMarkers = true;
	bool EnableLBMasterMarkers = true;
	bool EnableRuckMapMarkers = true;
	
	bool PristineLoot = false;
	
	bool EnableContainerBlue   = true;
	bool EnableContainerRed    = true;
	bool EnableContainerYellow = true;
	bool EnableContainerOrange = true;
	
	bool EnableCustomLootItemsRed = false;
    bool EnableCustomLootItemsBlue = false;
    bool EnableCustomLootItemsYellow = false;
    bool EnableCustomLootItemsOrange = false;

    ref array<ref PlaneCrashSiteData> CustomCrashSites;
    ref array<string> CustomLootItemsRed;
    ref array<string> CustomLootItemsBlue;
    ref array<string> CustomLootItemsYellow;
    ref array<string> CustomLootItemsOrange;

    int ZombieCount = 15; 
    
    int MaxLootItemsRed = 15;
    int MaxLootItemsBlue = 30;
    int MaxLootItemsYellow = 30;
    int MaxLootItemsOrange = 20; 
	
    bool EnableCrashNotification = false;
	
	string NotificationTitle = "Plane Crash";
    bool ShowCoordinatesInNotification = true;


    bool EnableCustomZombieTypes = false;
    ref array<string> CustomZombieTypes;

    private static ref PlaneCrashSettings m_Instance;

    void PlaneCrashSettings()
    {
        CustomCrashSites = new array<ref PlaneCrashSiteData>();
        CustomLootItemsRed = new array<string>();
        CustomLootItemsBlue = new array<string>();
        CustomLootItemsYellow = new array<string>();
        CustomLootItemsOrange = new array<string>();
        CustomZombieTypes = new array<string>();
    }

    static PlaneCrashSettings Get()
    {
        if (!m_Instance)
            Load();
        return m_Instance;
    }

    private static void Load()
    {
        string folder = "$profile:Ruckus";
        string path = folder + "/PlaneCrashSettings.json";

        if (!FileExist(folder))
            MakeDirectory(folder);

        ref PlaneCrashSettings cfg = new PlaneCrashSettings();

        if (FileExist(path))
        {
            JsonFileLoader<PlaneCrashSettings>.JsonLoadFile(path, cfg);
            Print("[PlaneCrash] ✅ Config loaded from Ruckus folder.");
        }
        else
        {
            JsonFileLoader<PlaneCrashSettings>.JsonSaveFile(path, cfg);
            Print("[PlaneCrash] 📁 Config file created in Ruckus folder.");
        }

        m_Instance = cfg;
    }
}
