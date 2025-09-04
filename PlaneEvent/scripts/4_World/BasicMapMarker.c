#ifdef BASICMAP
class RuckPlaneBasicMarkerService
{
	protected static ref map<EntityAI, string>           s_ObjToUID;
	protected static ref map<string, ref BasicMapMarker> s_UIDToMarker;
	protected static const string GROUP_NAME = "PlaneCrashes";

	static void ServerCreateMarkerForWreck(string wreckType, EntityAI obj)
	{
		if (!GetGame().IsServer() || !obj) return;
		if (PlaneCrashSettings.Get() && !PlaneCrashSettings.Get().EnableBasicMapMarkers) return;

		if (!s_ObjToUID)    s_ObjToUID    = new map<EntityAI, string>();
		if (!s_UIDToMarker) s_UIDToMarker = new map<string, ref BasicMapMarker>();

		string uid = s_ObjToUID.Get(obj);
		if (uid == "") uid = UidFor(obj);
		s_ObjToUID.Set(obj, uid);

		int argb = ColorForContainer(wreckType);
		int A; int R; int G; int B;
		ARGBToRGBAComponents(argb, A, R, G, B);
		autoptr array<int> rgb = new array<int>;
		rgb.Insert(R); rgb.Insert(G); rgb.Insert(B);

		string label = "Plane Crash";
		vector pos   = obj.GetPosition();
		string icon  = "BasicMap\\gui\\images\\marker.paa";
		bool   onHUD = true;

		BasicMapMarker mk = new BasicMapMarker(label, pos, icon, rgb, A, onHUD);
		mk.SetGroup(uid);
		mk.SetCanEdit(false);
		mk.SetHideOnPanel(false);
		mk.SetHideOnMap(false);

		s_UIDToMarker.Set(uid, mk);
		PushGroupToClients();
	}

	static void ServerRemoveMarkerFor(EntityAI obj)
	{
		if (!GetGame().IsServer() || !obj) return;
		if (!s_ObjToUID && !s_UIDToMarker) return;

		string uid;
		if (s_ObjToUID && s_ObjToUID.Find(obj, uid) && uid != "")
		{
			s_ObjToUID.Remove(obj);
			if (s_UIDToMarker && s_UIDToMarker.Contains(uid))
				s_UIDToMarker.Remove(uid);
			PushGroupToClients();
			return;
		}

		uid = UidFor(obj);
		if (s_UIDToMarker && s_UIDToMarker.Contains(uid))
		{
			s_UIDToMarker.Remove(uid);
			PushGroupToClients();
			return;
		}

		if (s_UIDToMarker)
		{
			vector p = obj.GetPosition();
			float bestDist = 999999.0;
			string bestKey;
			for (int i = 0; i < s_UIDToMarker.Count(); i++)
			{
				BasicMapMarker m = s_UIDToMarker.GetElement(i);
				if (!m) continue;
				float d = vector.Distance(m.GetPosition(), p);
				if (d < bestDist)
				{
					bestDist = d;
					bestKey  = s_UIDToMarker.GetKey(i);
				}
			}
			if (bestKey != "" && bestDist <= 5.0)
			{
				s_UIDToMarker.Remove(bestKey);
				PushGroupToClients();
			}
		}
	}

	protected static void PushGroupToClients()
	{
		array<ref BasicMapMarker> outArr = new array<ref BasicMapMarker>;
		if (s_UIDToMarker)
		{
			for (int i = 0; i < s_UIDToMarker.Count(); i++)
			{
				BasicMapMarker m = s_UIDToMarker.GetElement(i);
				if (m) outArr.Insert(m);
			}
		}
		BasicMap().SetMarkers(GROUP_NAME, outArr);
		BasicMap().UpdateGroupRemote(GROUP_NAME);
	}
	
	static void ServerRecreateAfterLoad(EntityAI obj)
	{
		if (!GetGame().IsServer() || !obj) return;
		ServerCreateMarkerForWreck(obj.GetType(), obj);
	}

	protected static void ARGBToRGBAComponents(int argb, out int a, out int r, out int g, out int b)
	{
		a = (argb >> 24) & 0xFF; r = (argb >> 16) & 0xFF; g = (argb >> 8) & 0xFF; b = argb & 0xFF;
	}

	protected static int ColorForContainer(string t)
	{
		if (t.Contains("Red"))    return ARGB(255,255, 64, 64);
		if (t.Contains("Blue"))   return ARGB(255, 64,128,255);
		if (t.Contains("Yellow")) return ARGB(255,255,220, 64);
		if (t.Contains("Orange")) return ARGB(255,255,160, 64);
		return ARGB(255,255,255,255);
	}

	protected static string UidFor(EntityAI obj)
	{
		if (!obj) return string.Format("%1-%2", GetGame().GetTime(), Math.RandomInt(1000, 9999));
		vector p = obj.GetPosition();
		return string.Format("%1_%2_%3_%4", obj.GetType(), Math.Round(p[0]), Math.Round(p[1]), Math.Round(p[2]));
	}
}
#endif
