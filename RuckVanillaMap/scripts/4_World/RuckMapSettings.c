class RuckServerMarker
{
    string Name;
    vector Pos;

    string Color = "White";

    void RuckServerMarker(string name = "", vector pos = "0 0 0", string color = "White")
    {
        Name = name;
        Pos = pos;
        Color = color;
    }

    int GetColorARGB()
    {
        return RuckMarkerColors.Resolve(Color);
    }
}

class RuckMarkerColors // Pre set colours so server onwer dont have convert to argb values including me chat gtp does this for me lol 
{
    static int Resolve(string name)
    {
        string n = name;
        n.ToLower();

        if (n == "white")   return ARGB(255, 255, 255, 255);
        if (n == "black")   return ARGB(255,   0,   0,   0);
        if (n == "red")     return ARGB(255, 255,   0,   0);
        if (n == "green")   return ARGB(255,   0, 255,   0);
        if (n == "blue")    return ARGB(255,   0,   0, 255);
        if (n == "yellow")  return ARGB(255, 255, 255,   0);
        if (n == "orange")  return ARGB(255, 255, 122,   0);
        if (n == "purple")  return ARGB(255, 170,   0, 255);
        if (n == "cyan")    return ARGB(255,   0, 255, 255);
        if (n == "pink")    return ARGB(255, 255,  45, 170);
		if (n == "grey")    return ARGB(160, 128, 128, 128);
		if (n == "brown")   return ARGB(255, 139,  94,  60);


        return ARGB(255, 255, 255, 255);
    }
}

class RuckMapSettings extends Managed
{
    protected static string ConfigPATH = "$profile:Ruckus\\RuckMapSettings.json";
	
	bool Enable3DMarkers = true;
    bool EnableServerMarkers = false;
    bool EnableSpawnCacheMarkers = true; //If you dont want animal/car/hunting stands spawns false
	
	int AnimalClusterRadiusMeters = 500; // Set the radius bigger if rendering is slow in mapmenu with larger maps the size of cherno this may need adjusting. This just pushes say 5 icons in the same area into one icon removing 100s of extra markers helping performence.

    string EventSpawnsXML = "$mission:cfgeventspawns.xml";

    autoptr array<string> TerritoryXMLs = { // Default possible event spwans for all animals remove or add custom ones you would need to add a custom icon and point to it. via ruckspawncache.c and mapmenu.c markerinfo.c
        "$mission:env\\bear_territories.xml",
        "$mission:env\\cattle_territories.xml",
        "$mission:env\\fox_territories.xml",
        "$mission:env\\pig_territories.xml",
		 "$mission:env\\fox_territories.xml",
        "$mission:env\\hen_territories.xml",
        "$mission:env\\hare_territories.xml",
        "$mission:env\\roe_deer_territories.xml",
        "$mission:env\\sheep_goat_territories.xml",
        "$mission:env\\wild_boar_territories.xml",
        "$mission:env\\wolf_territories.xml"
    };

    string SpawnVehiclesColor = "White";
    string SpawnBoatsColor    = "Orange";
    string SpawnAnimalsColor  = "Brown";
	string SpawnHuntingColor  = "Green"; 


    autoptr array<string> ColorPresets = {
        "White","Black","Red","Green","Blue","Yellow","Orange","Purple","Cyan","Pink","Grey","Brown"
    };

    autoptr array<autoptr RuckServerMarker> ServerMarkers = {
        new RuckServerMarker("Example Server",  Vector(3693.01, 341.01, 6010.01), "Red"),
        new RuckServerMarker("Server Marker 2", Vector(2693.01, 341.01, 3010.01), "Blue")
    };

    void Load()
    {
        if (FileExist(ConfigPATH))
            JsonFileLoader<RuckMapSettings>.JsonLoadFile(ConfigPATH, this);
        else
            Save();
    }

    void Save()
    {
        JsonFileLoader<RuckMapSettings>.JsonSaveFile(ConfigPATH, this);
    }
}


ref RuckMapSettings g_RuckMapSettings;

static RuckMapSettings GetRuckMapSettings()
{
    if (!g_RuckMapSettings)
    {
        g_RuckMapSettings = new RuckMapSettings;
        g_RuckMapSettings.Load();
    }
    return g_RuckMapSettings;
}
