#ifdef BASICMAP
class RuckPlaneBasicMarkerService
{
    protected static ref map<string, ref BasicMapMarker> s_MarkersByUID;
    protected static const string GROUP_NAME = "PlaneCrash";
	
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

    static void ServerCreateMarkerForWreck(string wreckType, EntityAI obj)
    {
        if (!GetGame().IsServer() || !obj) return;
        if (PlaneCrashSettings.Get() && !PlaneCrashSettings.Get().EnableBasicMapMarkers) return;

        string uid = UidFor(obj);

        string label = "Plane Crash";
        vector pos   = obj.GetPosition();
        string icon  = "PlaneEvent\\Icon\\PlaneCrash.paa";
        bool   onHUD = true;

        int A = 255;
        autoptr array<int> rgb = new array<int>;
        rgb.Insert(255); rgb.Insert(255); rgb.Insert(255); // white

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
            Print(string.Format("[PlaneCrashMarkers] REMOVED uid=%1", uid));
        } else {
            Print(string.Format("[PlaneCrashMarkers] WARN remove miss uid=%1", uid));
        }

        PushGroupToClients();
    }

    static void ServerRecreateAfterLoad(EntityAI obj)
    {
        if (!GetGame().IsServer() || !obj) return;
        ServerCreateMarkerForWreck(obj.GetType(), obj);
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

    protected static string UidFor(EntityAI obj)
    {
        if (!obj) return string.Format("nil-%1", Math.RandomInt(1000, 9999));
        int low; int high;
        obj.GetNetworkID(low, high);
        return string.Format("%1_%2", low, high);
    }
}
#endif
