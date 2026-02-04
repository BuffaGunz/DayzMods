modded class MapMarkerTypes
{
    protected static ref map<int, string> m_MarkerTypes;
    protected static ref array<int> m_TypeIdsOrdered;

    static const string RUCK_FALLBACK_ICON = "RuckVanillaMap/Icons/Marker.paa";

    static void EnsureInit()
    {
        if (!m_MarkerTypes)
            Init();
    }

    override static void Init() // assign markers here as well if adding custom 
    {
        m_MarkerTypes = new map<int, string>;
        m_TypeIdsOrdered = new array<int>;
		
		RegisterMarkerType(RuckMapMarkerTypes.MARKERTYPE_MAP_MARKER, "RuckVanillaMap/Icons/Marker.paa");
		RegisterMarkerType(RuckMapMarkerTypes.MARKERTYPE_MAP_BASE, "RuckVanillaMap/Icons/Base.paa");
		RegisterMarkerType(RuckMapMarkerTypes.MARKERTYPE_MAP_LOOT, "RuckVanillaMap/Icons/Loot.paa");
		RegisterMarkerType(RuckMapMarkerTypes.MARKERTYPE_MAP_BOAT, "RuckVanillaMap/Icons/Boat.paa");
		RegisterMarkerType(RuckMapMarkerTypes.MARKERTYPE_MAP_CONTAINER, "RuckVanillaMap/Icons/Container.paa");
		RegisterMarkerType(RuckMapMarkerTypes.MARKERTYPE_MAP_HELI, "RuckVanillaMap/Icons/Heli.paa");
		RegisterMarkerType(RuckMapMarkerTypes.MARKERTYPE_MAP_CAR, "RuckVanillaMap/Icons/Car.paa");
		RegisterMarkerType(RuckMapMarkerTypes.MARKERTYPE_MAP_PLANE, "RuckVanillaMap/Icons/Plane.paa");
		RegisterMarkerType(RuckMapMarkerTypes.MARKERTYPE_MAP_SKULL, "RuckVanillaMap/Icons/Skull.paa");
		
		RegisterMarkerType(RuckMapMarkerTypes.MARKERTYPE_EVENT_PLANECRASH, "RuckVanillaMap/Icons/PlaneCrash.paa");
		RegisterMarkerType(RuckMapMarkerTypes.MARKERTYPE_EVENT_AIRDROP, "RuckVanillaMap/Icons/Airdrop.paa");
		RegisterMarkerType(RuckMapMarkerTypes.MARKERTYPE_EVENT_SHIPWRECK, "RuckVanillaMap/Icons/Shipwreck!.paa");
		
		RegisterMarkerType(RuckMapMarkerTypes.MARKERTYPE_SPAWN_BOAT, "RuckVanillaMap/Icons/Boat.paa");
		RegisterMarkerType(RuckMapMarkerTypes.MARKERTYPE_SPAWN_SEDAN,     "RuckVanillaMap/Icons/CivSedan.paa");
		RegisterMarkerType(RuckMapMarkerTypes.MARKERTYPE_SPAWN_SEDAN2,     "RuckVanillaMap/Icons/Sedan02.paa");
		RegisterMarkerType(RuckMapMarkerTypes.MARKERTYPE_SPAWN_HATCHBACK, "RuckVanillaMap/Icons/Hatchback02.paa");
		RegisterMarkerType(RuckMapMarkerTypes.MARKERTYPE_SPAWN_HATCHBACK2, "RuckVanillaMap/Icons/OffroadHatchback.paa");
		RegisterMarkerType(RuckMapMarkerTypes.MARKERTYPE_SPAWN_OFFROAD,   "RuckVanillaMap/Icons/OffRoad02.paa");
		RegisterMarkerType(RuckMapMarkerTypes.MARKERTYPE_SPAWN_TRUCK,     "RuckVanillaMap/Icons/Truck01.paa");
		RegisterMarkerType(RuckMapMarkerTypes.MARKERTYPE_SPAWN_SIDEBYSIDE,     "RuckVanillaMap/Icons/SidebySide.paa");
		
		RegisterMarkerType(RuckMapMarkerTypes.MARKERTYPE_SPAWN_FEEDSHACK,     "RuckVanillaMap/Icons/FeedShack.paa");
		RegisterMarkerType(RuckMapMarkerTypes.MARKERTYPE_SPAWN_DEERSTAND,     "RuckVanillaMap/Icons/HuntingStand.paa");


		RegisterMarkerType(RuckMapMarkerTypes.MARKERTYPE_SPAWN_BEAR,             "RuckVanillaMap/Icons/Bear.paa");
		RegisterMarkerType(RuckMapMarkerTypes.MARKERTYPE_SPAWN_CATTLE,           "RuckVanillaMap/Icons/Cattle.paa");
		RegisterMarkerType(RuckMapMarkerTypes.MARKERTYPE_SPAWN_FOX,              "RuckVanillaMap/Icons/Fox.paa");
		RegisterMarkerType(RuckMapMarkerTypes.MARKERTYPE_SPAWN_PIG,              "RuckVanillaMap/Icons/Pig.paa");
		RegisterMarkerType(RuckMapMarkerTypes.MARKERTYPE_SPAWN_HEN,              "RuckVanillaMap/Icons/Hen.paa");
		RegisterMarkerType(RuckMapMarkerTypes.MARKERTYPE_SPAWN_HARE,              "RuckVanillaMap/Icons/Hare.paa");
		RegisterMarkerType(RuckMapMarkerTypes.MARKERTYPE_SPAWN_RED_DEER,         "RuckVanillaMap/Icons/RedDeer.paa");
		RegisterMarkerType(RuckMapMarkerTypes.MARKERTYPE_SPAWN_ROE_DEER,         "RuckVanillaMap/Icons/RoeDeer.paa");
		RegisterMarkerType(RuckMapMarkerTypes.MARKERTYPE_SPAWN_SHEEP_GOAT,       "RuckVanillaMap/Icons/SheepGoat.paa");
		RegisterMarkerType(RuckMapMarkerTypes.MARKERTYPE_SPAWN_WILD_BOAR,        "RuckVanillaMap/Icons/WildBoar.paa");
		RegisterMarkerType(RuckMapMarkerTypes.MARKERTYPE_SPAWN_WOLF,             "RuckVanillaMap/Icons/Wolf.paa");
    }

    override static void RegisterMarkerType(int id, string path)
    {
        if (!m_MarkerTypes) m_MarkerTypes = new map<int, string>;
        if (!m_TypeIdsOrdered) m_TypeIdsOrdered = new array<int>;

        m_MarkerTypes.Set(id, path);

        if (m_TypeIdsOrdered.Find(id) == -1)
            m_TypeIdsOrdered.Insert(id);
    }

    static string GetMarkerIconPath(int id)
    {
        EnsureInit();

        string path;
        if (m_MarkerTypes && m_MarkerTypes.Find(id, path))
        {
            if (path && path != string.Empty)
                return path;
        }
        return RUCK_FALLBACK_ICON;
    }

    static array<int> GetAllTypeIds()
    {
        EnsureInit();
        return m_TypeIdsOrdered;
    }
};
