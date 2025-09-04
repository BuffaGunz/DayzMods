#ifdef LBmaster_Groups
class RuckLBMasterMarkerService
{
	protected static ref map<EntityAI, int>                s_UIDByObject;
	protected static ref map<EntityAI, ref LBServerMarker> s_MarkerByObject;

	static void ServerCreateMarkerForContainer(string containerType, EntityAI obj)
	{
		if (!GetGame().IsServer() || !obj) return;
		if (s_UIDByObject && s_UIDByObject.Contains(obj)) return;

		if (AirDropSettings.Get() && !AirDropSettings.Get().EnableLBMasterMarkers) return;

		vector pos   = obj.GetPosition();
		string label = "Supply Drop";
		int color    = ColorForContainer(containerType);
		string icon  = "LBmaster_Groups\\data\\icons\\marker.paa";

		bool toSurface = true;
		bool display3D = true;
		bool displayMap = true;
		bool displayGPS = true;

		LBServerMarker marker = LBStaticMarkerManager.Get.AddTempServerMarker(label, pos, icon, color, toSurface, display3D, displayMap, displayGPS);

		if (!s_MarkerByObject) s_MarkerByObject = new map<EntityAI, ref LBServerMarker>();
		if (!s_UIDByObject)    s_UIDByObject    = new map<EntityAI, int>();

		s_MarkerByObject.Set(obj, marker);
		s_UIDByObject.Set(obj, marker.uid);
	}

	static void ServerRemoveMarkerFor(EntityAI obj)
	{
		if (!GetGame().IsServer() || !obj) return;

		int uid;
		if (s_UIDByObject && s_UIDByObject.Find(obj, uid))
		{
			LBStaticMarkerManager.Get.RemoveServerMarker(uid);
			s_UIDByObject.Remove(obj);
		}
		else if (s_MarkerByObject)
		{
			LBServerMarker m;
			if (s_MarkerByObject.Find(obj, m))
			{
				LBStaticMarkerManager.Get.RemoveServerMarker(m);
				s_MarkerByObject.Remove(obj);
			}
		}
	}

	static void ServerRecreateAfterLoad(EntityAI obj)
	{
		if (!GetGame().IsServer() || !obj) return;
		ServerCreateMarkerForContainer(obj.GetType(), obj);
	}

	protected static int ColorForContainer(string t)
	{
		if (t.Contains("Red"))    return ARGB(255, 255,  64,  64);
		if (t.Contains("Blue"))   return ARGB(255,  64, 128, 255);
		if (t.Contains("Yellow")) return ARGB(255, 255, 220,  64);
		if (t.Contains("Orange")) return ARGB(255, 255, 160,  64);
		return ARGB(255, 255, 255, 255);
	}
}
#endif
