class PlaneCrashSettings
{
    int CrashIntervalMin = 1200000;
    int CrashIntervalMax = 1800000;

    bool EnableCustomCrashSites = false;
    bool EnableCustomLootItems = false;

    ref array<vector> CustomCrashSites;
    ref array<string> CustomLootItems;

    private static ref PlaneCrashSettings m_Instance;

    void PlaneCrashSettings()
    {
        CustomCrashSites = new array<vector>();
        CustomLootItems = new array<string>();
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
            Print("[PlaneCrash] Config loaded from file.");

            if (!cfg.CustomCrashSites)
                cfg.CustomCrashSites = new array<vector>();
            if (!cfg.CustomLootItems)
                cfg.CustomLootItems = new array<string>();
        }
        else
        {
            JsonFileLoader<PlaneCrashSettings>.JsonSaveFile(path, cfg);
            Print("[PlaneCrash] No config found. Created default PlaneCrashSettings.json.");
        }

        m_Instance = cfg;
    }
}
