class DropSiteData
{
    vector Position;
    string NotificationMessage;
    
    void DropSiteData(vector pos, string msg)
    {
        Position = pos;
        NotificationMessage = msg;
    }
}

class AirDropSettings
{
    int DropIntervalMin = 1200000;
    int DropIntervalMax = 1800000;

    bool EnableCustomDropSites = false;
	 bool EnableGasZones = false;
    int GasZoneChancePercent = 100;
	
	bool EnableExpansionMarkers = true;
	bool EnableBasicMapMarkers = true;
	bool EnableLBMasterMarkers = true;
	bool EnableRuckMapMarkers = true;
	
	bool EnableContainerBlue = true;
    bool EnableContainerRed = true;
    bool EnableContainerYellow = true;
    bool EnableContainerOrange = true;
	
	bool PristineLoot = false;

    bool EnableCustomLootItemsRed = false;
    bool EnableCustomLootItemsBlue = false;
    bool EnableCustomLootItemsYellow = false;
    bool EnableCustomLootItemsOrange = false;

    ref array<ref DropSiteData> CustomDropSites;

    ref array<string> CustomLootItemsRed;
    ref array<string> CustomLootItemsBlue;
    ref array<string> CustomLootItemsYellow;
    ref array<string> CustomLootItemsOrange;

    int MaxLootItemsRed = 15;
    int MaxLootItemsBlue = 30;
    int MaxLootItemsYellow = 30;
    int MaxLootItemsOrange = 20;

    int ZombieCount = 15;
    bool EnableDropNotification = false;
    
    string NotificationTitle = "Supply Drop";
    bool ShowCoordinatesInNotification = true;

    bool EnableCustomZombieTypes = false;
    ref array<string> CustomZombieTypes;

    private static ref AirDropSettings m_Instance;

    void AirDropSettings()
    {
        CustomDropSites = new array<ref DropSiteData>();
        CustomLootItemsRed = new array<string>();
        CustomLootItemsBlue = new array<string>();
        CustomLootItemsYellow = new array<string>();
        CustomLootItemsOrange = new array<string>();
        CustomZombieTypes = new array<string>();
    }

    static AirDropSettings Get()
    {
        if (!m_Instance)
            Load();
        return m_Instance;
    }

    private static void Load()
    {
        string folder = "$profile:Ruckus";
        string path = folder + "/AirDropSettings.json";

        if (!FileExist(folder))
            MakeDirectory(folder);

        ref AirDropSettings cfg = new AirDropSettings();

        if (FileExist(path))
        {
            JsonFileLoader<AirDropSettings>.JsonLoadFile(path, cfg);
            Print("[AirDrop] ✅ Config loaded from Ruckus folder.");
        }
        else
        {
            JsonFileLoader<AirDropSettings>.JsonSaveFile(path, cfg);
            Print("[AirDrop] 📝 Config created in Ruckus folder.");
        }
		
		 cfg.GasZoneChancePercent = Math.Clamp(cfg.GasZoneChancePercent, 0, 100);
		 
        m_Instance = cfg;
    }
}