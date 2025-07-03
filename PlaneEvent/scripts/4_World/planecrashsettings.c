class PlaneCrashSettings
{
    int CrashIntervalMin = 1200000;
    int CrashIntervalMax = 1800000;

    bool EnableCustomCrashSites = false;
    bool EnableCustomLootItems = false;

    ref array<vector> CustomCrashSites;
    ref array<string> CustomLootItems;

    int ZombieCount = 15; // Max 40
    int MaxLootItems = 15; //Max30
    bool EnableCrashNotification = false;

    bool EnableCustomZombieTypes = false;
    ref array<string> CustomZombieTypes;

    private static ref PlaneCrashSettings m_Instance;

    void PlaneCrashSettings()
    {
        CustomCrashSites = new array<vector>();
        CustomLootItems = new array<string>();

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
        string folder = "$profile:PlaneCrash";
        string path = folder + "/PlaneCrashSettings.json";

        if (!FileExist(folder))
            MakeDirectory(folder);

        ref PlaneCrashSettings cfg = new PlaneCrashSettings();

        if (FileExist(path))
        {
            JsonFileLoader<PlaneCrashSettings>.JsonLoadFile(path, cfg);
            Print("[PlaneCrash] Config loaded.");
        }
        else
        {
            JsonFileLoader<PlaneCrashSettings>.JsonSaveFile(path, cfg);
            Print("[PlaneCrash] Config file created.");
        }

        m_Instance = cfg;
    }
}
