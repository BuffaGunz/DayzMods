#ifdef BASICMAP
class RuckBasicMarkerService
{
    protected static ref map<string, ref BasicMapMarker> s_MarkersByUID;
    protected static const string GROUP_NAME = "RuckAirDrop";
	
	static void PushGroupTo(PlayerIdentity toPlayer)
    {
        if (!GetGame().IsServer() || !toPlayer) return;

        array<autoptr BasicMapMarker> markersOut = new array<autoptr BasicMapMarker>;
        if (s_MarkersByUID) {
            for (int i = 0; i < s_MarkersByUID.Count(); i++) {
                BasicMapMarker m = s_MarkersByUID.GetElement(i);
                if (m) markersOut.Insert(m);
            }
        }
        BasicMap().SetMarkersRemote(GROUP_NAME, markersOut, toPlayer);
    }

    static void ServerCreateMarkerForContainer(string containerType, EntityAI obj)
    {
        if (!GetGame().IsServer() || !obj) return;
        if (!AirDropSettings.Get().EnableBasicMapMarkers) return;

        string uid = UidFor(obj);

        int A, R, G, B;
        int argb = ColorForContainer(containerType);
        ARGBToRGBAComponents(argb, A, R, G, B);

        autoptr array<int> rgb = new array<int>;
        rgb.Insert(R); rgb.Insert(G); rgb.Insert(B);

        string label = "Supply Drop";
        vector pos   = obj.GetPosition();
        string icon  = "RuckAirDrop\\Data\\SupplyDrop.paa";
        bool   onHUD = true;

        BasicMapMarker mk = new BasicMapMarker(label, pos, icon, rgb, A, onHUD);
        mk.SetGroup(GROUP_NAME);
        mk.SetCanEdit(false);
        mk.SetHideOnPanel(false);
        mk.SetHideOnMap(false);

        if (!s_MarkersByUID) s_MarkersByUID = new map<string, ref BasicMapMarker>();
        s_MarkersByUID.Set(uid, mk);

        PushGroupToClients();
    }

    static void ServerRemoveMarkerFor(EntityAI obj)
    {
        if (!GetGame().IsServer() || !obj) return;
        if (!s_MarkersByUID) return;

        string uid = UidFor(obj);
        if (s_MarkersByUID.Contains(uid)) {
            s_MarkersByUID.Remove(uid);
            Print(string.Format("[SupplyDrops] REMOVED uid=%1", uid));
        } else {
            Print(string.Format("[SupplyDrops] WARN remove miss uid=%1", uid));
        }

        PushGroupToClients();
    }

    static void ServerRecreateAfterLoad(EntityAI obj)
    {
        if (!GetGame().IsServer() || !obj) return;
        ServerCreateMarkerForContainer(obj.GetType(), obj);
    }

    static void PushGroupToClients()
    {
        array<autoptr BasicMapMarker> markersOut = new array<autoptr BasicMapMarker>;
        if (s_MarkersByUID) {
            for (int i = 0; i < s_MarkersByUID.Count(); i++) {
                BasicMapMarker m = s_MarkersByUID.GetElement(i);
                if (m) markersOut.Insert(m);
            }
        }
        BasicMap().SetMarkersRemote(GROUP_NAME, markersOut, NULL);
    }

    protected static int ColorForContainer(string t)
    {
        if (t.Contains("Red"))    return ARGB(255, 255,  64,  64);
        if (t.Contains("Blue"))   return ARGB(255,  64, 128, 255);
        if (t.Contains("Yellow")) return ARGB(255, 255, 220,  64);
        if (t.Contains("Orange")) return ARGB(255, 255, 160,  64);
        return ARGB(255, 255, 255, 255);
    }

    protected static void ARGBToRGBAComponents(int argb, out int a, out int r, out int g, out int b)
    {
        a = (argb >> 24) & 0xFF;
        r = (argb >> 16) & 0xFF;
        g = (argb >> 8)  & 0xFF;
        b =  argb        & 0xFF;
    }

    protected static string UidFor(EntityAI obj)
    {
        if (!obj) return string.Format("nil-%1", Math.RandomInt(1000, 9999));
        int low; int high;
        obj.GetNetworkID(low, high);
        return string.Format("%1_%2", low, high);
    }
}
#endif
