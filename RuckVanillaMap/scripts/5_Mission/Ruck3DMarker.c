class Ruck3DMarker
{
	static const string LAYOUT = "RuckVanillaMap/Layouts/Marker3D.layout";

	protected Widget m_Root;
	protected ImageWidget m_Icon;
	protected TextWidget m_Name;
	protected TextWidget m_Distance;
	protected Widget m_TextBG;

	protected ref RuckMapMarkerData m_Data;

	protected vector m_WorldPos;
	protected bool m_WorldPosValid;

	static const float TERRAIN_LIFT = 0.35;

	static const float POS_CHANGE_EPS = 0.25;
	static const float POS_CHANGE_EPS_SQ = POS_CHANGE_EPS * POS_CHANGE_EPS;

	void Ruck3DMarker(RuckMapMarkerData data)
	{
		m_Data = data;

		m_Root = GetGame().GetWorkspace().CreateWidgets(LAYOUT);
		m_Root.SetFlags(WidgetFlags.IGNOREPOINTER);
		m_Root.Show(false);

		m_Icon     = ImageWidget.Cast(m_Root.FindAnyWidget("Icon"));
		m_Name     = TextWidget.Cast(m_Root.FindAnyWidget("Name"));
		m_Distance = TextWidget.Cast(m_Root.FindAnyWidget("Distance"));
		m_TextBG   = m_Root.FindAnyWidget("TextBG");

		CacheWorldPos();
		RefreshStatic();
	}

	void ~Ruck3DMarker()
	{
		Destroy();
	}

	void Destroy()
	{
		if (m_Root)
		{
			m_Root.Show(false);
			m_Root.Unlink();
		}
	}

	int GetId()
	{
		if (!m_Data) return -999999;
		return m_Data.Id;
	}

	void SetData(RuckMapMarkerData data)
	{
		if (!data)
			return;

		bool needCache = false;

		if (!m_Data)
		{
			needCache = true;
		}
		else
		{
			if (vector.DistanceSq(m_Data.Pos, data.Pos) > POS_CHANGE_EPS_SQ)
				needCache = true;
		}

		m_Data = data;

		if (needCache)
			CacheWorldPos();

		RefreshStatic();
	}

	protected void CacheWorldPos()
	{
		m_WorldPosValid = false;

		if (!m_Data)
			return;

		vector p = m_Data.Pos;
		float y = GetGame().SurfaceY(p[0], p[2]);
		p[1] = y + TERRAIN_LIFT;

		m_WorldPos = p;
		m_WorldPosValid = true;
	}

	protected void RefreshStatic()
	{
		if (!m_Data) return;

		if (m_Icon)
		{
			string tex = MapMarkerTypes.GetMarkerIconPath(m_Data.TypeId);
			m_Icon.LoadImageFile(0, tex);
			m_Icon.SetImage(0);
		}

		if (m_Name)
		{
			string n = m_Data.Name;
			if (!n || n == string.Empty)
				n = "Marker";
			m_Name.SetText(n);
		}
	}

	bool Update(PlayerBase player)
	{
		if (!m_Root || !m_Data || !player)
			return false;

		RuckMapSettings s = GetRuckMapSettings();
		if (!s || !s.Enable3DMarkers)
		{
			m_Root.Show(false);
			return true;
		}

		if (GetGame().GetUIManager().GetMenu())
		{
			m_Root.Show(false);
			return true;
		}

		vector worldPos;
		if (m_WorldPosValid) worldPos = m_WorldPos;
		else worldPos = m_Data.Pos;

		vector screen = GetGame().GetScreenPosRelative(worldPos);

		if (screen[2] <= 0 || screen[0] <= 0 || screen[0] >= 1 || screen[1] <= 0 || screen[1] >= 1)
		{
			m_Root.Show(false);
			return true;
		}

		float sw, sh;
		GetGame().GetWorkspace().GetScreenSize(sw, sh);

		float px = screen[0] * sw;
		float py = screen[1] * sh;

		float ix = 0, iy = 0, iw = 0, ih = 0;
		if (m_Icon)
		{
			m_Icon.GetPos(ix, iy);
			m_Icon.GetSize(iw, ih);
		}

		px -= (ix + (iw * 0.5));
		py -= (iy + (ih * 0.5));

		m_Root.SetPos(px, py);
		m_Root.Show(true);

		vector camPos = GetGame().GetCurrentCameraPosition();
		float dist = vector.Distance(camPos, worldPos);

		if (m_Distance)
			m_Distance.SetText(Math.Round(dist).ToString() + "m");

		float alphaF = 255.0;

		float fadeStart = 600.0;
		float fadeEnd   = 4000.0;
		float minAlpha  = 40.0;

		if (dist > fadeStart)
		{
			float t = (dist - fadeStart) / (fadeEnd - fadeStart);
			t = Math.Clamp(t, 0.0, 1.0);
			alphaF = Math.Lerp(255.0, minAlpha, t);
		}

		int argb = m_Data.ColorARGB;
		int a = (argb >> 24) & 255;
		int r = (argb >> 16) & 255;
		int g = (argb >> 8)  & 255;
		int b =  argb        & 255;

		int col = ARGB(alphaF, r, g, b);

		if (m_Icon)     m_Icon.SetColor(col);
		if (m_Name)     m_Name.SetColor(col);
		if (m_Distance) m_Distance.SetColor(col);

		if (m_TextBG)
			m_TextBG.Show(false);

		return true;
	}
}
