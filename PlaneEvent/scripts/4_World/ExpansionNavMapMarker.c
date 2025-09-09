#ifdef EXPANSIONMODNAVIGATION
class RuckPlaneExpansionMarkerService
{
	static void ServerCreateMarkerForWreck(string wreckType, EntityAI obj)
	{
		if (s_UIDByObject && s_UIDByObject.Contains(obj)) return;

		if (!GetGame().IsServer() || !obj) return;
		
		if (!PlaneCrashSettings.Get() || !PlaneCrashSettings.Get().EnableExpansionMarkers) return;

		ExpansionMarkerModule mod = ExpansionMarkerModule.GetModuleInstance();
		if (!mod) return;

		string uid   = UidFor(obj);
		string label = "Plane Crash";
		int color    = ColorForContainer(wreckType);
		vector pos   = obj.GetPosition();
		bool is3D    = true;
		string icon  = IconForContainer(wreckType);

		mod.RemoveServerMarker(uid);

		ExpansionMarkerData marker = mod.CreateServerMarker(label, icon, pos, color, is3D, uid);
		if (!marker) return;

		if (!s_UIDByObject)   s_UIDByObject   = new map<EntityAI, string>();
		if (!s_LabelByObject) s_LabelByObject = new map<EntityAI, string>();
		s_UIDByObject.Set(obj, uid);
		s_LabelByObject.Set(obj, label);
	}

	static void ServerRemoveMarkerFor(EntityAI obj)
	{
		if (!GetGame().IsServer() || !obj) return;
		if (!s_UIDByObject) return;

		string uid;
		if (!s_UIDByObject.Find(obj, uid)) return;

		ExpansionMarkerModule mod = ExpansionMarkerModule.GetModuleInstance();
		if (mod && uid != "")
			mod.RemoveServerMarker(uid);

		s_UIDByObject.Remove(obj);
		if (s_LabelByObject) s_LabelByObject.Remove(obj);
	}

	static void ServerRecreateAfterLoad(EntityAI obj)
	{
		if (!GetGame().IsServer() || !obj) return;
		ServerCreateMarkerForWreck(obj.GetType(), obj);
	}

	protected static int ColorForContainer(string t)
	{
		if (t.Contains("Red"))    return ARGB(255, 255,  64,  64);
		if (t.Contains("Blue"))   return ARGB(255,  64, 128, 255);
		if (t.Contains("Yellow")) return ARGB(255, 255, 220,  64);
		if (t.Contains("Orange")) return ARGB(255, 255, 160,  64);
		return ARGB(255, 255, 255, 255);
	}

	protected static ref map<EntityAI, string> s_UIDByObject;
	protected static ref map<EntityAI, string> s_LabelByObject;

	protected static string MakeId()
	{
		return string.Format("%1-%2", GetGame().GetTime(), Math.RandomInt(1000, 9999));
	}

	protected static string UidFor(EntityAI obj)
	{
		if (!obj) return MakeId();
		vector p = obj.GetPosition();
		int px = Math.Round(p[0]);
		int py = Math.Round(p[1]);
		int pz = Math.Round(p[2]);
		return string.Format("%1_%2_%3_%4", obj.GetType(), px, py, pz);
	}

	protected static string IconForContainer(string t)
	{
		return "Marker";
	}
}
#endif
