class AirDropSettings
{
    int DropIntervalMin = 1200000;
    int DropIntervalMax = 1800000;

    bool EnableCustomDropSites = false;
	
	bool EnableExpansionMarkers = true;
	bool EnableBasicMapMarkers = true;
	bool EnableLBMasterMarkers    = true;
	
	bool EnableContainerBlue   = true;
    bool EnableContainerRed    = true;
    bool EnableContainerYellow = true;
    bool EnableContainerOrange = true;

    bool EnableCustomLootItemsRed = false;
    bool EnableCustomLootItemsBlue = false;
    bool EnableCustomLootItemsYellow = false;
    bool EnableCustomLootItemsOrange = false;

    ref array<vector> CustomDropSites;

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

    bool EnableCustomZombieTypes = false;
    ref array<string> CustomZombieTypes;

    private static ref AirDropSettings m_Instance;

    void AirDropSettings()
    {
        CustomDropSites = new array<vector>();
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
            Print("[AirDrop] 📁 Config created in Ruckus folder.");
        }

        m_Instance = cfg;
    }
}
