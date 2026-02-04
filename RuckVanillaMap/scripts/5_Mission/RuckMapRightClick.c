class RuckMapRightClick extends ScriptedWidgetEventHandler
{
	protected bool m_IsOpen;

	protected vector m_ClickWorldPos;

	protected Widget m_Root;
	protected Widget m_Menu;
	protected Widget m_CreateBox;
	protected Widget m_EditBox;

	protected ButtonWidget m_Create;
	protected ButtonWidget m_Edit;
	protected ButtonWidget m_Delete;

	protected MapMenu m_MapMenu;
	protected ref RuckMapMarkerData m_SelectedMarker;

	void RuckMapRightClick(Widget parent, MapMenu menu)
	{
		m_MapMenu = menu;

		m_Root = Widget.Cast(GetGame().GetWorkspace().CreateWidgets("RuckVanillaMap/Layouts/RightClickMenu.layout", parent));
		m_Menu = m_Root.FindAnyWidget("RightClickMenu");
		
		m_CreateBox = m_Root.FindAnyWidget("CreateBox");
		m_EditBox   = m_Root.FindAnyWidget("EditBox");

		m_Create = ButtonWidget.Cast(m_Root.FindAnyWidget("Create"));
		m_Edit   = ButtonWidget.Cast(m_Root.FindAnyWidget("Edit"));
		m_Delete = ButtonWidget.Cast(m_Root.FindAnyWidget("Delete"));

		m_Root.SetHandler(this);

		m_Root.Show(false);
		if (m_Menu) m_Menu.Show(false);

		m_IsOpen = false;
		m_SelectedMarker = null;
	}

	bool IsOpen()
	{
		return m_IsOpen && m_Root && m_Root.IsVisible();
	}

	void Open(RuckMapMarkerData marker, int screenX, int screenY, bool createMode)
	{
		if (!m_Root) return;

		m_IsOpen = true;
		m_SelectedMarker = marker;
		bool isServer = (marker && marker.Id < 0);
		if (m_Edit) m_Edit.Show(!isServer);
		if (m_Delete) m_Delete.Show(!isServer);

		m_ClickWorldPos = m_MapMenu.MapClickPosition(screenX, screenY);

		if (m_CreateBox) m_CreateBox.Show(createMode);
		if (m_EditBox)   m_EditBox.Show(!createMode);

		float rootW, rootH;
		m_Root.GetSize(rootW, rootH);

		float scrW, scrH;
		GetGame().GetWorkspace().GetScreenSize(scrW, scrH);

		float px = screenX;
		float py = screenY;

		if (px + rootW > scrW) px = scrW - rootW;
		if (py + rootH > scrH) py = scrH - rootH;
		if (px < 0) px = 0;
		if (py < 0) py = 0;

		m_Root.SetPos(px, py);

		m_Root.Show(true);
		if (m_Menu) m_Menu.Show(true);
	}


	void Close()
	{
		m_IsOpen = false;
		m_SelectedMarker = null;

		if (m_Root) m_Root.Show(false);
		if (m_Menu) m_Menu.Show(false);
	}
	
	bool IsWidgetInMenu(Widget w)
	{
		if (!w || !m_Root) return false;

		Widget cur = w;
		while (cur)
		{
			if (cur == m_Root)
				return true;
			cur = cur.GetParent();
		}
		return false;
	}

	override bool OnClick(Widget w, int x, int y, int button)
	{
		if (w == m_Create)
		{
			string name = "Marker";
			int typeId = eMapMarkerTypes.MARKERTYPE_MAP_CAMP;

			vector createPos = m_ClickWorldPos;

			y = GetGame().SurfaceY(createPos[0], createPos[2]);
			createPos[1] = y + 0.35;

			m_MapMenu.SetPendingEditAfterCreate(createPos);
			m_MapMenu.RequestCreateMarker(createPos, typeId, name);

			Close();
			return true;
		}

		if (w == m_Edit && m_SelectedMarker)
		{
			m_MapMenu.OpenMarkerEditor(m_SelectedMarker);
			Close();
			return true;
		}

		if (w == m_Delete && m_SelectedMarker)
		{
			m_MapMenu.RequestDeleteMarker(m_SelectedMarker);
			Close();
			return true;
		}

		return super.OnClick(w, x, y, button);
	}
};
