#ifdef BASICMAP
class RuckBasicMarkerService
{
	protected static ref map<string, ref BasicMapMarker> s_MarkersByUID;
	protected static const string GROUP_NAME = "SupplyDrops"; 

	static void ServerCreateMarkerForContainer(string containerType, EntityAI obj)
	{
		if (!GetGame().IsServer() || !obj) return;
		if (!AirDropSettings.Get().EnableBasicMapMarkers) return;

		string uid = UidFor(obj);

		int argb = ColorForContainer(containerType);
		int A; int R; int G; int B;
		ARGBToRGBAComponents(argb, A, R, G, B);
		autoptr array<int> rgb = new array<int>;
		rgb.Insert(R); rgb.Insert(G); rgb.Insert(B);

		string label = "Supply Drop";
		vector pos   = obj.GetPosition();
		string icon  = "BasicMap\\gui\\images\\marker.paa"; 
		bool   onHUD = true;

		BasicMapMarker mk = new BasicMapMarker(label, pos, icon, rgb, A, onHUD);
		mk.SetGroup(uid);       
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
		if (s_MarkersByUID.Contains(uid))
		{
			s_MarkersByUID.Remove(uid);
			PushGroupToClients();
		}
	}

	static void ServerRecreateAfterLoad(EntityAI obj)
	{
		if (!GetGame().IsServer() || !obj) return;
		ServerCreateMarkerForContainer(obj.GetType(), obj);
	}

	protected static void PushGroupToClients()
	{
		array<ref BasicMapMarker> markers = new array<ref BasicMapMarker>;
		if (s_MarkersByUID)
		{
			for (int i = 0; i < s_MarkersByUID.Count(); i++)
			{
				BasicMapMarker m = s_MarkersByUID.GetElement(i);
				if (m) markers.Insert(m);
			}
		}
		BasicMap().SetMarkers(GROUP_NAME, markers);
		BasicMap().UpdateGroupRemote(GROUP_NAME);
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
		if (!obj) return string.Format("%1-%2", GetGame().GetTime(), Math.RandomInt(1000, 9999));
		vector p = obj.GetPosition();
		int px = Math.Round(p[0]);
		int py = Math.Round(p[1]);
		int pz = Math.Round(p[2]);
		return string.Format("%1_%2_%3_%4", obj.GetType(), px, py, pz);
	}
}
#endif
