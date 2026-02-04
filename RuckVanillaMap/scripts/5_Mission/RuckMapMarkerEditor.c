class RuckMapMarkerEditor extends ScriptedWidgetEventHandler // i assume i will get hounded for 3d style marker which i personall dont like but feel free to.
{
	protected Widget m_Root;
	protected TextWidget m_Title;
	protected EditBoxWidget m_NameEdit;

	protected ImageWidget m_IconPreview;
	protected ButtonWidget m_PrevIcon;
	protected ButtonWidget m_NextIcon;

	protected ButtonWidget m_PrevColor;
	protected ButtonWidget m_NextColor;
	protected Widget m_ColorSwatch;

	protected ButtonWidget m_Save;
	protected ButtonWidget m_Cancel;

	protected ref array<int> m_ColorPresets;
	protected int m_ColorIndex;

	protected MapMenu m_MapMenu;
	protected ref RuckMapMarkerData m_Target;

	protected ref array<int> m_IconTypeIds;
	protected int m_IconIndex;
	protected int m_OrigTypeId;
	protected int m_OrigColorARGB;
	protected string m_OrigName;
	protected bool m_IsOpen;

	void RuckMapMarkerEditor(Widget parent, MapMenu menu)
	{
		m_MapMenu = menu;

		m_Root = Widget.Cast(GetGame().GetWorkspace().CreateWidgets("RuckVanillaMap/Layouts/MarkerEditor.layout", parent));
		m_Root.SetHandler(this);
		m_Root.Show(false);

		m_Title    = TextWidget.Cast(m_Root.FindAnyWidget("TitleText"));
		m_NameEdit = EditBoxWidget.Cast(m_Root.FindAnyWidget("NameEdit"));

		m_IconPreview = ImageWidget.Cast(m_Root.FindAnyWidget("IconPreview"));
		m_PrevIcon    = ButtonWidget.Cast(m_Root.FindAnyWidget("PrevIcon"));
		m_NextIcon    = ButtonWidget.Cast(m_Root.FindAnyWidget("NextIcon"));

		m_PrevColor   = ButtonWidget.Cast(m_Root.FindAnyWidget("PrevColor"));
		m_NextColor   = ButtonWidget.Cast(m_Root.FindAnyWidget("NextColor"));
		m_ColorSwatch = Widget.Cast(m_Root.FindAnyWidget("ColorSwatch"));

		m_Save   = ButtonWidget.Cast(m_Root.FindAnyWidget("Save"));
		m_Cancel = ButtonWidget.Cast(m_Root.FindAnyWidget("Cancel"));

		MapMarkerTypes.EnsureInit();

		m_IconTypeIds = new array<int>;
		BuildDefaultIconList();

		m_ColorPresets = new array<int>;
		m_ColorPresets.Insert(ARGB(255, 255, 255, 255)); 
		m_ColorPresets.Insert(ARGB(255, 255,   0,   0)); 
		m_ColorPresets.Insert(ARGB(255,   0, 255,   0)); 
		m_ColorPresets.Insert(ARGB(255,   0,   0, 255));
		m_ColorPresets.Insert(ARGB(255, 255, 128,   0)); 
		m_ColorPresets.Insert(ARGB(255, 255,   0, 255)); 
		m_ColorPresets.Insert(ARGB(255,   0, 255, 255)); 

		m_ColorIndex = 0;
		m_IconIndex = 0;
		m_IsOpen = false;
	}

	void SetAvailableIconTypeIds(array<int> ids)
	{
		m_IconTypeIds.Clear();

		foreach (int t : ids)
		{
			if (IsAllowedEditorType(t))
				m_IconTypeIds.Insert(t);
		}

		if (m_IconTypeIds.Count() == 0)
			BuildDefaultIconList();

		m_IconIndex = 0;
		UpdateIconPreview();
	}

	protected bool IsAllowedEditorType(int typeId)
	{
		switch (typeId)
		{
			case RuckMapMarkerTypes.MARKERTYPE_MAP_MARKER:
			case RuckMapMarkerTypes.MARKERTYPE_MAP_BASE:
			case RuckMapMarkerTypes.MARKERTYPE_MAP_LOOT:
			case RuckMapMarkerTypes.MARKERTYPE_MAP_BOAT:
			case RuckMapMarkerTypes.MARKERTYPE_MAP_CONTAINER:
			case RuckMapMarkerTypes.MARKERTYPE_MAP_HELI:
			case RuckMapMarkerTypes.MARKERTYPE_MAP_CAR:
			case RuckMapMarkerTypes.MARKERTYPE_MAP_PLANE:
			case RuckMapMarkerTypes.MARKERTYPE_MAP_SKULL:
				return true;
		}

		return false;
	}

	protected void BuildDefaultIconList()
	{
		m_IconTypeIds.Clear();

		array<int> all = MapMarkerTypes.GetAllTypeIds();
		if (all)
		{
			foreach (int t : all)
			{
				if (IsAllowedEditorType(t))
					m_IconTypeIds.Insert(t);
			}
		}

		if (m_IconTypeIds.Count() == 0)
			m_IconTypeIds.Insert(RuckMapMarkerTypes.MARKERTYPE_MAP_MARKER);
	}


	bool IsOpen()
	{
		return m_IsOpen && m_Root && m_Root.IsVisible();
	}

	void Open(RuckMapMarkerData marker)
	{
		if (!m_Root || !marker)
			return;

		m_Target = marker;
		m_OrigTypeId = m_Target.TypeId;
		m_OrigColorARGB = m_Target.ColorARGB;
		m_OrigName = m_Target.Name;

		if (m_Title)
			m_Title.SetText("Edit Marker");

		if (m_NameEdit)
			m_NameEdit.SetText(m_Target.Name);

		m_IconIndex  = FindIconIndex(m_Target.TypeId);
		m_ColorIndex = FindColorIndex(m_Target.ColorARGB);

		UpdateIconPreview();
		ApplyPreviewColor();

		m_Root.Show(true);
		m_IsOpen = true;
	}

	void Close()
	{
		m_IsOpen = false;
		m_Target = null;

		if (m_Root)
			m_Root.Show(false);
	}
	
	protected void ApplyLivePreview()
	{
		if (!m_Target || !m_MapMenu)
			return;

		string newName;
		if (m_NameEdit)
			newName = m_NameEdit.GetText();
		else
			newName = m_Target.Name;

		int newTypeId = m_Target.TypeId;
		if (m_IconTypeIds && m_IconTypeIds.Count() > 0)
			newTypeId = m_IconTypeIds[m_IconIndex];

		int newColor = m_Target.ColorARGB;
		if (m_ColorPresets && m_ColorPresets.Count() > 0)
			newColor = m_ColorPresets[m_ColorIndex];

		m_MapMenu.ApplyLocalMarkerEdit(m_Target.Id, newTypeId, newName, newColor);
	}

	override bool OnChange(Widget w, int x, int y, bool finished)
	{
		if (!IsOpen())
			return super.OnChange(w, x, y, finished);

		if (w == m_NameEdit)
		{
			ApplyLivePreview();
			return true;
		}

		return super.OnChange(w, x, y, finished);
	}

	protected int FindIconIndex(int typeId)
	{
		for (int i = 0; i < m_IconTypeIds.Count(); i++)
		{
			if (m_IconTypeIds[i] == typeId)
				return i;
		}
		return 0;
	}

	protected int FindColorIndex(int argb)
	{
		if (!m_ColorPresets)
			return 0;

		for (int i = 0; i < m_ColorPresets.Count(); i++)
		{
			if (m_ColorPresets[i] == argb)
				return i;
		}
		return 0;
	}

	protected void ApplyPreviewColor()
	{
		if (!m_ColorPresets || m_ColorPresets.Count() == 0)
			return;

		int c = m_ColorPresets[m_ColorIndex];

		if (m_ColorSwatch)
			m_ColorSwatch.SetColor(c);

		if (m_IconPreview)
			m_IconPreview.SetColor(c);

		if (m_NameEdit)
			m_NameEdit.SetTextColor(c);
	}

	protected void UpdateIconPreview()
	{
		if (!m_IconPreview || m_IconTypeIds.Count() == 0)
			return;

		int typeId = m_IconTypeIds[m_IconIndex];
		string tex = MapMarkerTypes.GetMarkerIconPath(typeId);

		m_IconPreview.LoadImageFile(0, tex);
		m_IconPreview.SetImage(0);
		m_IconPreview.Show(true);
	}

	protected void StepIcon(int delta)
	{
		if (m_IconTypeIds.Count() == 0)
			return;

		m_IconIndex += delta;

		if (m_IconIndex < 0)
			m_IconIndex = m_IconTypeIds.Count() - 1;
		else if (m_IconIndex >= m_IconTypeIds.Count())
			m_IconIndex = 0;

		UpdateIconPreview();
		ApplyPreviewColor();
		ApplyLivePreview();
	}

	protected void StepColor(int delta)
	{
		if (!m_ColorPresets || m_ColorPresets.Count() == 0)
			return;

		m_ColorIndex += delta;

		if (m_ColorIndex < 0)
			m_ColorIndex = m_ColorPresets.Count() - 1;
		else if (m_ColorIndex >= m_ColorPresets.Count())
			m_ColorIndex = 0;

		ApplyPreviewColor();
		ApplyLivePreview();
	}

	override bool OnClick(Widget w, int x, int y, int button)
	{
		if (!IsOpen())
			return super.OnClick(w, x, y, button);

		if (w == m_PrevIcon)
		{
			StepIcon(-1);
			return true;
		}

		if (w == m_NextIcon)
		{
			StepIcon(1);
			return true;
		}

		if (w == m_PrevColor)
		{
			StepColor(-1);
			return true;
		}

		if (w == m_NextColor)
		{
			StepColor(1);
			return true;
		}

		if (w == m_Cancel)
		{
			if (m_Target && m_MapMenu)
				m_MapMenu.ApplyLocalMarkerEdit(m_Target.Id, m_OrigTypeId, m_OrigName, m_OrigColorARGB);

			Close();
			return true;
		}

		if (w == m_Save)
		{
			if (!m_Target)
			{
				Close();
				return true;
			}

			string newName;

			if (m_NameEdit)
				newName = m_NameEdit.GetText();
			else
				newName = m_Target.Name;

			if (!newName) newName = "";
			if (newName.Length() > 32) newName = newName.Substring(0, 32);

			int newTypeId;
			if (m_IconTypeIds.Count() > 0)
				newTypeId = m_IconTypeIds[m_IconIndex];
			else
				newTypeId = m_Target.TypeId;

			int newColor = ARGB(255, 255, 255, 255);
			if (m_ColorPresets && m_ColorPresets.Count() > 0)
				newColor = m_ColorPresets[m_ColorIndex];

			m_MapMenu.RequestEditMarker(m_Target.Id, newTypeId, newName, newColor);

			Close();
			return true;
		}

		return super.OnClick(w, x, y, button);
	}
};
