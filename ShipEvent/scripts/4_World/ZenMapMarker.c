#ifdef ZENMAP
class RuckShipZenMarkerService
{
	protected static ref map<EntityAI, string> s_ByObject;
	protected static ref map<EntityAI, string> s_IdByObject;

	static void ServerCreateMarkerForWreck(string wreckType, EntityAI obj)
	{
		if (s_ByObject && s_ByObject.Contains(obj)) return;

		if (!GetGame().IsServer() || !obj) return;
		if (!ShipWreckSettings.Get().EnableZenMarkers) return;

		PluginZenMapMarkers mapPlugin = PluginZenMapMarkers.Cast(GetPlugin(PluginZenMapMarkers));
		if (!mapPlugin) return;

		string id;
		if (!s_IdByObject || !s_IdByObject.Find(obj, id) || id == "")
			id = MakeId();
		
		string label = "Ship Wreck";
		int color   = ColorForContainer(wreckType);
		int iconIdx = IconIndexSafe("ZenMap/data/icons/marker.paa");

		mapPlugin.AddMarker(new MapMarker(obj.GetPosition(), label, color, iconIdx));

		if (!s_ByObject)   s_ByObject   = new map<EntityAI, string>();
		if (!s_IdByObject) s_IdByObject = new map<EntityAI, string>();
		s_ByObject.Set(obj, label);
		s_IdByObject.Set(obj, id);
	}

	static void ServerRemoveMarkerFor(EntityAI obj)
	{
		if (!GetGame().IsServer() || !obj) return;

		PluginZenMapMarkers mapPlugin = PluginZenMapMarkers.Cast(GetPlugin(PluginZenMapMarkers));
		if (mapPlugin)
			mapPlugin.RemoveMarkerByPosition(obj.GetPosition());

		if (s_ByObject)   s_ByObject.Remove(obj);
		if (s_IdByObject) s_IdByObject.Remove(obj);
	}

	static void ServerRecreateAfterLoad(EntityAI obj)
	{
		if (!GetGame().IsServer() || !obj) return;
		ServerCreateMarkerForWreck(obj.GetType(), obj);
	}

	// ---- helpers ----
	protected static string MakeId()
	{
		return string.Format("%1-%2", GetGame().GetTime(), Math.RandomInt(1000, 9999));
	}

	protected static int ColorForContainer(string wreckType)
	{
		if (t.Contains("Red"))    return ARGB(255,255, 64, 64);
		if (t.Contains("Blue"))   return ARGB(255, 64,128,255);
		if (t.Contains("Yellow")) return ARGB(255,255,220, 64);
		if (t.Contains("Orange")) return ARGB(255,255,160, 64);
		return ARGB(255,255,255,255);
	}

	protected static int IconIndexSafe(string filePath)
	{
		int idx = GetZenMapConfig().FileToArrayIndex(filePath);
		if (idx >= 0) return idx;

		idx = GetZenMapConfig().FileToArrayIndex("ZenMap/data/icons/pin.paa");
		if (idx >= 0) return idx;

		return 0;
	}
}
#endif
