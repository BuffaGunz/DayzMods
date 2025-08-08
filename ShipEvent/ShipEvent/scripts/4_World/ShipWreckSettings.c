class ShipWreckSettings
{
    int CrashIntervalMin = 1200000;
    int CrashIntervalMax = 1800000;

    bool EnableCustomCrashSites = false;
    bool EnableCustomLootItems = false;

    ref array<vector> CustomCrashSites;
    ref array<string> CustomLootItems;

    int ZombieCount = 8; // Max 40
    int MaxLootItems = 15; // Max 30
    bool EnableCrashNotification = false;

    bool EnableCustomZombieTypes = false;
    ref array<string> CustomZombieTypes;

    private static ref ShipWreckSettings m_Instance;

    void ShipWreckSettings()
    {
        CustomCrashSites = new array<vector>();
        CustomLootItems = new array<string>();
        CustomZombieTypes = new array<string>();
    }

    static ShipWreckSettings Get()
    {
        if (!m_Instance)
            Load();
        return m_Instance;
    }

    private static void Load()
    {
        string folder = "$profile:Ruckus";
        string path = folder + "/ShipWreckSettings.json";

        if (!FileExist(folder))
            MakeDirectory(folder);

        ref ShipWreckSettings cfg = new ShipWreckSettings();

        if (FileExist(path))
        {
            JsonFileLoader<ShipWreckSettings>.JsonLoadFile(path, cfg);
            Print("[ShipWreck] Config loaded from Ruckus folder.");
        }
        else
        {
            JsonFileLoader<ShipWreckSettings>.JsonSaveFile(path, cfg);
            Print("[ShipWreck] Config file created in Ruckus folder.");
        }

        m_Instance = cfg;
    }
}
