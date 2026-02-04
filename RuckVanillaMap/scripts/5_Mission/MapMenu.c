modded class MapMenu extends UIScriptedMenu
{
	protected TextWidget					m_ToolsGPSText;
	protected Widget 						m_GPSNamePanel;
	protected TextWidget  					m_GPSMarkerText;
	protected ref RuckMapRightClick			m_RightClick;
	protected ref RuckMapMarkerEditor		m_MarkerEditor;
	protected ChernarusMap 					m_RuckMapItem;
	protected Widget						m_RuckMarkerLayer;
	protected ref map<int, Widget>			m_RuckMarkerWidgets;
	protected bool							m_RuckMarkersDirty;
	protected float							m_RuckLastScale = -999.0;
	protected vector						m_RuckLastMapPos = "0 0 0";
	protected int							m_RuckLastRevision = -1;
	protected bool   						m_RuckPendingEditAfterCreate;
	protected vector 						m_RuckPendingCreatePos;
	protected int    						m_RuckPendingCreateRevision;
	protected TextWidget 					m_ToolsGPSPosLineText;
	protected TextWidget 		 			m_ToolsGPSTimeText;
	protected TextWidget 					m_ToolsGPSDateText;



	static const int 						RUCK_RPC_MARKER_ADD_REQUEST    = 77801; 
	static const int 						RUCK_RPC_MARKER_EDIT_REQUEST   = 77802; 
	static const int 						RUCK_RPC_MARKER_DELETE_REQUEST = 77803; 
	static const int 						RUCK_RPC_MARKER_SYNC_REQUEST   = 77804; 
	
	static const float RUCK_SPAWN_MAX_SCALE = 0.30; 

	override Widget Init()
	{
		layoutRoot 			= GetGame().GetWorkspace().CreateWidgets("RuckVanillaMap/Layouts/RuckMap.layout");
		m_Hud 				= IngameHud.Cast(GetGame().GetMission().GetHud());
		m_IsOpenning		= true;

		m_MapToolsContainer = layoutRoot.FindAnyWidget("Map_Tools_Container");
		if (m_MapToolsContainer)
			m_MapToolsContainer.Show(false);

		m_MapToolsContainer.GetScript(m_LegendResizer);
		m_MapWidgetInstance			= MapWidget.Cast(layoutRoot.FindAnyWidget("Map"));
		m_GPSMarker        = ImageWidget.Cast(layoutRoot.FindAnyWidget("PlayerPostion"));
		m_GPSMarkerArrow   = ImageWidget.Cast(layoutRoot.FindAnyWidget("PlayerDirection"));

		m_GPSNamePanel 				= layoutRoot.FindAnyWidget("PlayerNamePanel");
		m_GPSMarkerText 			= TextWidget.Cast(layoutRoot.FindAnyWidget("PlayerNameText"));

		if (m_GPSNamePanel)
			m_GPSNamePanel.Show(false);

		m_UpperLegendContainer		= layoutRoot.FindAnyWidget("Tools_Extra");
		layoutRoot.Update();
		m_ToolsCompassBase			= layoutRoot.FindAnyWidget("Tools_Compass_Base");
		m_ToolsCompassArrow			= ImageWidget.Cast(layoutRoot.FindAnyWidget("Tools_Compass_Arrow"));

		m_ToolsGPSText				= TextWidget.Cast(layoutRoot.FindAnyWidget("Tools_GPS_PlayerName"));
		m_ToolsGPSPosLineText   = TextWidget.Cast(layoutRoot.FindAnyWidget("Tools_GPS_PosLine_Value"));
		m_ToolsGPSTimeText = TextWidget.Cast(layoutRoot.FindAnyWidget("Tools_GPS_Time_Value"));
		m_ToolsGPSDateText = TextWidget.Cast(layoutRoot.FindAnyWidget("Tools_GPS_Date_Value"));

		m_ToolsScaleContourText		= TextWidget.Cast(layoutRoot.FindAnyWidget("Tools_Scale_Contour_Value"));
		m_ToolsScaleCellSizeText	= TextWidget.Cast(layoutRoot.FindAnyWidget("Tools_Scale_CellSize_Value"));
		m_ToolsScaleCellSizeCanvas	= CanvasWidget.Cast(layoutRoot.FindAnyWidget("Tools_Scale_CellSize_Canvas"));
		m_ToolbarPanel				= layoutRoot.FindAnyWidget("toolbar_bg");
		
		MapMarkerTypes.EnsureInit();

		if (!m_RuckMarkerWidgets)
			m_RuckMarkerWidgets = new map<int, Widget>;

		if (!m_RightClick)
			m_RightClick = new RuckMapRightClick(layoutRoot, this);

		if (!m_MarkerEditor)
			m_MarkerEditor = new RuckMapMarkerEditor(layoutRoot, this);

		m_RuckMarkersDirty = true;

		if (m_MapWidgetInstance && !m_RuckMarkerLayer)
		{
			m_RuckMarkerLayer = GetGame().GetWorkspace().CreateWidgets("", m_MapWidgetInstance);
			if (m_RuckMarkerLayer)
			{
				m_RuckMarkerLayer.SetName("RuckMarkerLayer");
				m_RuckMarkerLayer.SetFlags(WidgetFlags.IGNOREPOINTER);
				m_RuckMarkerLayer.Show(true);
			}
		}

		m_RuckMapItem = FindPlayerMapItem();

		if (m_RuckMapItem)
		{
			GetGame().RPCSingleParam(m_RuckMapItem, RUCK_RPC_MARKER_SYNC_REQUEST, new Param1<int>(0), true);
			m_RuckMarkersDirty = true;
		}

		float canvasHeight = 0;
		m_ToolsScaleCellSizeCanvas.GetSize(m_ToolScaleCellSizeCanvasWidth, canvasHeight);

		if (m_MapWidgetInstance)
		{
			float scale;
			vector mapPosition;
			PlayerBase player = PlayerBase.Cast(g_Game.GetPlayer());
			if (player && !player.GetLastMapInfo(scale, mapPosition))
			{
				vector tempPosition = GetGame().ConfigGetVector(string.Format("CfgWorlds %1 centerPosition", GetGame().GetWorldName()));
				scale = 0.33;
				mapPosition = Vector(tempPosition[0], tempPosition[1], tempPosition[2]);
			}

			m_MapWidgetInstance.SetScale(scale);
			m_MapWidgetInstance.SetMapPos(mapPosition);

			m_HasCompass 	= false;
			m_HasGPS 		= false;

			SetGPSMarkerVisibility(false);
			SetGPSDirectionVisibility(false);
			SetCompassUIVisibility(false);
			SetUpperLegendVisibility(true);

			if (player)
			{
				m_MapNavigationBehaviour = player.GetMapNavigationBehaviour();
				if (m_MapNavigationBehaviour)
				{
					m_HasGPS = (m_MapNavigationBehaviour.GetNavigationType() & EMapNavigationType.GPS|EMapNavigationType.ALL == 0);				
					m_HasCompass = (m_MapNavigationBehaviour.GetNavigationType() & EMapNavigationType.COMPASS|EMapNavigationType.ALL == 0);
					
					m_HasGPS 		= m_HasGPS;
					m_HasCompass 	= m_HasCompass;

					if (m_HasGPS)
					{
						if (m_MapToolsContainer)
                            m_MapToolsContainer.Show(true);

						SetUpperLegendVisibility(true);

						SetGPSMarkerVisibility(true);
						if (m_GPSNamePanel)
							m_GPSNamePanel.Show(true);

						m_MapWidgetInstance.SetMapPos(m_MapNavigationBehaviour.GetPositionReal());
					}

					if (m_HasCompass)
					{
						SetCompassUIVisibility(true);
						SetUpperLegendVisibility(true);

						if (m_HasGPS)
							SetGPSDirectionVisibility(true);
					}

					if ((!m_HasGPS && !m_HasCompass))
					{
						if (m_MapToolsContainer)
							m_MapToolsContainer.Show(false);

						SetUpperLegendVisibility(false);
					}
				}
			}

			m_MapMenuHandler = new MapHandler(m_MapWidgetInstance);

			if (m_Hud)
			{
				m_Hud.ShowHudUI(false);
				m_Hud.ShowQuickbarUI(false);
			}
		}

		float x,y;
		m_MapToolsContainer.GetScreenPos(x,y);
		m_ToolsContainerPos0[0] = x;
		m_ToolsContainerPos0[1] = y;

		GetGame().GetMission().GetOnInputPresetChanged().Insert(OnInputPresetChanged);
		GetGame().GetMission().GetOnInputDeviceChanged().Insert(OnInputDeviceChanged);

		return layoutRoot;
	}

	override void Update(float timeslice)
	{
		super.Update(timeslice);
		m_ToolsScaleCellSizeCanvas.Clear();

		PlayerBase player = PlayerBase.Cast(g_Game.GetPlayer());

		if (m_MapWidgetInstance)
		{
			if (m_Images)
			{
				m_MapWidgetInstance.RemoveChild(m_Images);
			}

			if (!m_RuckMapItem)
			{
				m_RuckMapItem = FindPlayerMapItem();
				if (m_RuckMapItem)
				{
					GetGame().RPCSingleParam(m_RuckMapItem, RUCK_RPC_MARKER_SYNC_REQUEST, new Param1<int>(0), true);
					m_RuckMarkersDirty = true;
				}
			}

			UpdateRuckMarkers();

			if (player)
			{
				m_ToolsScaleContourText.SetText(string.Format("%1 m", m_MapWidgetInstance.GetContourInterval()));
				RenderScaleRuler();
				float rulerMaxDistance;
				string rulerUnits;
				ProcessDistanceAndUnits(m_MapWidgetInstance.GetCellSize(m_ToolScaleCellSizeCanvasWidth), rulerMaxDistance, rulerUnits);
				m_ToolsScaleCellSizeText.SetText(string.Format("%1%2", rulerMaxDistance, rulerUnits));

				if (m_MapNavigationBehaviour)
				{
					vector mapPos = m_MapWidgetInstance.MapToScreen(m_MapNavigationBehaviour.GetPositionReal());
					float scale = 1 - m_MapWidgetInstance.GetScale();

					if (m_HasCompass)
					{
						vector rot = player.GetYawPitchRoll();
						float angle = Math.Round(rot[0]);
						if (angle < 0)
						{
							angle = 360 + angle;
						}

						m_GPSMarkerArrow.SetRotation(0, 0, angle);
						m_ToolsCompassArrow.SetRotation(0, 0, angle);
					}

					array<int> coords = MapNavigationBehaviour.OrderedPositionNumbersFromGridCoords(player);
					if (m_HasGPS)
					{
						float markerW = scale * 26;
						float markerH = scale * 26;
						float arrowW  = scale * 26;
						float arrowH  = scale * 26;

						vector scr = m_MapWidgetInstance.MapToScreen(m_MapNavigationBehaviour.GetPositionReal());
						float cx = scr[0];
						float cy = scr[1];

						m_GPSMarker.SetSize(markerW, markerH);
						m_GPSMarkerArrow.SetSize(arrowW, arrowH);

						m_GPSMarker.SetPos(cx - (markerW * 0.5), cy - (markerH * 0.5));
						m_GPSMarkerArrow.SetPos(cx - (arrowW * 0.5), cy - (arrowH * 0.5));

						if (m_GPSNamePanel)
						{
							float markerX, markerY;
							float mW, mH;
							float pW, pH;
							float gap = 1;

							m_GPSMarker.GetPos(markerX, markerY);
							m_GPSMarker.GetSize(mW, mH);
							m_GPSNamePanel.GetSize(pW, pH);

							float panelX = markerX + (mW * 0.5) - (pW * 0.5);
							float panelY = markerY + mH + gap;

							m_GPSNamePanel.SetPos(panelX, panelY);
							m_GPSNamePanel.Show(true);
						}

						if (m_ToolsGPSTimeText)
							m_ToolsGPSTimeText.SetText(GetInGameTimeText());

						if (m_ToolsGPSDateText)
							m_ToolsGPSDateText.SetText(GetInGameDateText());

						if (m_GPSMarkerText)
							m_GPSMarkerText.SetText(GetPlayerDisplayName());

						if (m_ToolsGPSText)
							m_ToolsGPSText.SetText(GetPlayerDisplayName());

						string xStr = "-.--";
						string yStr = "-.--";
						string hStr = "---.--";

						if (coords.Count() == m_MapNavigationBehaviour.DISPLAY_GRID_POS_MAX_CHARS_COUNT * 2 && coords[0] >= 0)
						{
							xStr = string.Format(COORD_FORMAT, coords[0], coords[1], coords[2]);
							yStr = string.Format(COORD_FORMAT, coords[3], coords[4], coords[5]);
						}

						hStr = string.Format("%1", Math.Round(player.GetPosition()[1]));

						if (m_ToolsGPSPosLineText)
							m_ToolsGPSPosLineText.SetText(string.Format("X %1  Y %2  alt. %3", xStr, yStr, hStr));
					}
					else
					{
						if (m_GPSNamePanel)
							m_GPSNamePanel.Show(false);

						if (m_ToolsGPSPosLineText)
							m_ToolsGPSPosLineText.SetText("");

						if (m_ToolsGPSTimeText)
							m_ToolsGPSTimeText.SetText("");

						if (m_ToolsGPSDateText)
							m_ToolsGPSDateText.SetText("");
					}
				}
			}

			if (!m_IsOpenning && GetUApi().GetInputByID(UAUIBack).LocalPress())
			{
				if (player)
				{
					player.SetLastMapInfo(m_MapWidgetInstance.GetScale(), m_MapWidgetInstance.GetMapPos());
				}

				CloseMapMenu();
			}

			m_IsOpenning = false;
		}
	}

	void SetPendingEditAfterCreate(vector worldPos)
	{
		m_RuckPendingEditAfterCreate = true;
		m_RuckPendingCreatePos = worldPos;
		
		if (m_RuckMapItem)
		{
			m_RuckPendingCreateRevision = m_RuckMapItem.GetRuckMarkersRevision();
		}
		else
		{
			m_RuckPendingCreateRevision = 0;
		}

	}
	
	string GetInGameTimeText()
	{
		int y, mo, d, h, mi;
		GetGame().GetWorld().GetDate(y, mo, d, h, mi);

		string sh;
		if (h < 10) sh = "0" + h.ToString();
		else sh = h.ToString();

		string sm;
		if (mi < 10) sm = "0" + mi.ToString();
		else sm = mi.ToString();

		return string.Format("%1:%2", sh, sm);
	}

	string GetInGameDateText()
	{
		int y, mo, d, h, mi;
		GetGame().GetWorld().GetDate(y, mo, d, h, mi);

		int yy = y % 100;

		string syy;
		if (yy < 10) syy = "0" + yy.ToString();
		else syy = yy.ToString();

		string sdd;
		if (d < 10) sdd = "0" + d.ToString();
		else sdd = d.ToString();

		string smm;
		if (mo < 10) smm = "0" + mo.ToString();
		else smm = mo.ToString();

		return string.Format("%1/%2/%3", sdd, smm, syy);
	}

	string GetPlayerDisplayName()
	{
		DayZPlayer player = DayZPlayer.Cast(GetGame().GetPlayer());
		if (!player) return "PLAYER";

		PlayerIdentity identity = player.GetIdentity();
		if (identity)
			return identity.GetName();

		return "PLAYER";
	}
	
	override void CloseMapMenu()
	{
		if (m_WasChanged && m_Map)
		{
			m_Map.SyncMapMarkers();
			m_WasChanged = false;
		}

		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		if (player)
		{
			player.SetMapClosingSyncSet(false);
		}

		if (m_RightClick && m_RightClick.IsOpen())
			m_RightClick.Close();

		if (m_MarkerEditor && m_MarkerEditor.IsOpen())
			m_MarkerEditor.Close();

		if (m_Hud)
		{
			m_Hud.ShowHudUI(true);
			m_Hud.ShowQuickbarUI(true);
		}

		GetGame().GetMission().RemoveActiveInputExcludes({"map"});
		GetGame().GetMission().RemoveActiveInputRestriction(EInputRestrictors.MAP);

		Close();
	}

	override bool OnMouseButtonUp(Widget w, int x, int y, int button)
	{
		if (m_MarkerEditor && m_MarkerEditor.IsOpen())
			return super.OnMouseButtonUp(w, x, y, button);

		if (button == 0)
		{
			if (m_RightClick && m_RightClick.IsOpen())
			{
				if (IsWidgetOnMap(w))
				{
					m_RightClick.Close();
					return true;
				}

				return super.OnMouseButtonUp(w, x, y, button);
			}

			return super.OnMouseButtonUp(w, x, y, button);
		}

		if (button == 1)
		{
			if (m_RightClick && m_RightClick.IsOpen())
			{
				m_RightClick.Close();

				if (!IsWidgetOnMap(w))
					return true;
			}

			if (IsWidgetOnMap(w))
			{
				vector worldPos = MapClickPosition(x, y);
				RuckMapMarkerData hit = FindMarkerNear(worldPos, 15.0);
				bool createMode = (hit == null);

				if (m_RightClick)
					m_RightClick.Open(hit, x, y, createMode);

				return true;
			}

			return super.OnMouseButtonUp(w, x, y, button);
		}

		return super.OnMouseButtonUp(w, x, y, button);
	}

	vector MapClickPosition(int screenX, int screenY)
	{
		if (!m_MapWidgetInstance)
			return "0 0 0";

		return m_MapWidgetInstance.ScreenToMap(Vector(screenX, screenY, 0));
	}

	protected bool IsWidgetOnMap(Widget w)
	{
		if (!w || !m_MapWidgetInstance)
			return false;

		Widget cur = w;
		while (cur)
		{
			if (cur == m_MapWidgetInstance)
				return true;

			cur = cur.GetParent();
		}
		return false;
	}

	protected array<ref RuckMapMarkerData> GetActiveMarkers()
	{
		if (!m_RuckMapItem)
			return null;

		return m_RuckMapItem.GetRuckMarkers();
	}

	protected RuckMapMarkerData FindMarkerNear(vector worldPos, float radiusMeters)
	{
		array<ref RuckMapMarkerData> markers = GetActiveMarkers();
		if (!markers)
			return null;

		foreach (RuckMapMarkerData m : markers)
		{
			if (m && m.IsNear(worldPos, radiusMeters))
				return m;
		}
		return null;
	}

	void RequestCreateMarker(vector pos, int typeId, string name)
	{
		Print("[RuckMap] RequestCreateMarker: m_RuckMapItem=" + m_RuckMapItem);
		if (!m_RuckMapItem)
			return;

		float y = GetGame().SurfaceY(pos[0], pos[2]);
		pos[1] = y + 0.35;

		if (!name) name = "";
		if (name.Length() > 32) name = name.Substring(0, 32);

		int colorARGB = ARGB(255, 255, 255, 255);

		GetGame().RPCSingleParam(m_RuckMapItem, RUCK_RPC_MARKER_ADD_REQUEST, new Param4<vector, int, string, int>(pos, typeId, name, colorARGB), true);

		array<ref RuckMapMarkerData> markers = m_RuckMapItem.GetRuckMarkers();
		markers.Insert(new RuckMapMarkerData(-999, pos, typeId, name, colorARGB));

		m_RuckMarkersDirty = true;
		m_RuckLastRevision = -1;
	}

	void RequestDeleteMarker(RuckMapMarkerData marker)
	{
		if (!m_RuckMapItem || !marker)
			return;

		GetGame().RPCSingleParam(m_RuckMapItem, RUCK_RPC_MARKER_DELETE_REQUEST, new Param1<int>(marker.Id), true);
		m_RuckMarkersDirty = true;
	}

	void OpenMarkerEditor(RuckMapMarkerData marker)
	{
		if (!marker)
			return;

		if (m_MarkerEditor)
			m_MarkerEditor.Open(marker);
	}

	void RequestEditMarker(int markerId, int newTypeId, string newName, int colorARGB)
	{
		if (!m_RuckMapItem)
			return;

		if (!newName) newName = "";
		if (newName.Length() > 32) newName = newName.Substring(0, 32);

		if (colorARGB == 0)
			colorARGB = ARGB(255, 255, 255, 255);

		GetGame().RPCSingleParam(m_RuckMapItem, RUCK_RPC_MARKER_EDIT_REQUEST, new Param4<int, int, string, int>(markerId, newTypeId, newName, colorARGB), true);

		m_RuckMarkersDirty = true;
	}


	protected void UpdateRuckMarkers()
	{
		if (!m_MapWidgetInstance || !m_RuckMapItem)
			return;

		float scale = m_MapWidgetInstance.GetScale();
		vector mapPos = m_MapWidgetInstance.GetMapPos();

		bool mapChanged = (Math.AbsFloat(scale - m_RuckLastScale) > 0.0001) || (vector.Distance(mapPos, m_RuckLastMapPos) > 0.001);

		int rev = m_RuckMapItem.GetRuckMarkersRevision();
		bool markersChanged = (rev != m_RuckLastRevision);

		if (m_RuckMarkersDirty || mapChanged || markersChanged)
		{
			RenderRuckMarkers();

			if (m_RuckPendingEditAfterCreate && m_MarkerEditor && !m_MarkerEditor.IsOpen())
			{
				if (rev > m_RuckPendingCreateRevision)
				{
					RuckMapMarkerData created = FindMarkerNear(m_RuckPendingCreatePos, 5.0);
					if (created)
					{
						m_RuckPendingEditAfterCreate = false;
						OpenMarkerEditor(created);
					}
				}
			}

			m_RuckMarkersDirty = false;
			m_RuckLastScale = scale;
			m_RuckLastMapPos = mapPos;
			m_RuckLastRevision = rev;
		}
	}

	protected RuckMapMarkerData FindClosestMarker(vector worldPos, float maxMeters)
	{
		array<ref RuckMapMarkerData> markers = GetActiveMarkers();
		if (!markers)
			return null;

		RuckMapMarkerData best = null;
		float bestDist = 999999.0;

		foreach (RuckMapMarkerData m : markers)
		{
			if (!m) continue;

			vector a = m.Pos; a[1] = 0;
			vector b = worldPos; b[1] = 0;
			float d = vector.Distance(a, b);

			if (d < bestDist)
			{
				bestDist = d;
				best = m;
			}
		}

		if (best && bestDist <= maxMeters)
			return best;

		return null;
	}
	
	protected bool IsVehicleSpawnType(int typeId) // assign here in one of these blocks or create your own etc. 
	{
		switch (typeId)
		{
			case RuckMapMarkerTypes.MARKERTYPE_SPAWN_SEDAN:
			case RuckMapMarkerTypes.MARKERTYPE_SPAWN_SEDAN2:
			case RuckMapMarkerTypes.MARKERTYPE_SPAWN_HATCHBACK:
			case RuckMapMarkerTypes.MARKERTYPE_SPAWN_HATCHBACK2:
			case RuckMapMarkerTypes.MARKERTYPE_SPAWN_OFFROAD:
			case RuckMapMarkerTypes.MARKERTYPE_SPAWN_TRUCK:
			case RuckMapMarkerTypes.MARKERTYPE_SPAWN_BOAT:
			case RuckMapMarkerTypes.MARKERTYPE_SPAWN_SIDEBYSIDE:
				return true;
		}
		return false;
	}
	
	protected bool IsHuntingType(int typeId)
	{
		switch (typeId)
		{
			case RuckMapMarkerTypes.MARKERTYPE_SPAWN_FEEDSHACK:
			case RuckMapMarkerTypes.MARKERTYPE_SPAWN_DEERSTAND:
				return true;
		}
		return false;
	}
	
	protected bool IsAnimalSpawnType(int typeId)
	{
		switch (typeId)
		{
			case RuckMapMarkerTypes.MARKERTYPE_SPAWN_BEAR:
			case RuckMapMarkerTypes.MARKERTYPE_SPAWN_CATTLE:
			case RuckMapMarkerTypes.MARKERTYPE_SPAWN_DOMESTIC_ANIMALS:
			case RuckMapMarkerTypes.MARKERTYPE_SPAWN_FOX:
			case RuckMapMarkerTypes.MARKERTYPE_SPAWN_PIG:
			case RuckMapMarkerTypes.MARKERTYPE_SPAWN_HEN:
			case RuckMapMarkerTypes.MARKERTYPE_SPAWN_HARE:
			case RuckMapMarkerTypes.MARKERTYPE_SPAWN_RED_DEER:
			case RuckMapMarkerTypes.MARKERTYPE_SPAWN_ROE_DEER:
			case RuckMapMarkerTypes.MARKERTYPE_SPAWN_SHEEP_GOAT:
			case RuckMapMarkerTypes.MARKERTYPE_SPAWN_WILD_BOAR:
			case RuckMapMarkerTypes.MARKERTYPE_SPAWN_WOLF:
				return true;
		}
		return false;
	}

	protected void RenderRuckMarkers()
	{
		if (!m_RuckMarkerWidgets)
			m_RuckMarkerWidgets = new map<int, Widget>;

		array<ref RuckMapMarkerData> markers = GetActiveMarkers();
		if (!markers)
			return;

		for (int k = m_RuckMarkerWidgets.Count() - 1; k >= 0; k--)
		{
			int markerId = m_RuckMarkerWidgets.GetKey(k);
			if (!HasMarkerId(markers, markerId))
			{
				Widget w = m_RuckMarkerWidgets.Get(markerId);
				if (w) w.Unlink();
				m_RuckMarkerWidgets.Remove(markerId);
			}
		}

		float scaleNow = m_MapWidgetInstance.GetScale();

		foreach (RuckMapMarkerData m : markers)
		{
			if (!m) continue;

			bool isVehicleSpawn = IsVehicleSpawnType(m.TypeId);
			bool isHuntingSpawn = IsHuntingType(m.TypeId);
			bool isAnimalSpawn  = IsAnimalSpawnType(m.TypeId);
			bool isSpawn        = isVehicleSpawn || isHuntingSpawn || isAnimalSpawn;

			if (isSpawn && scaleNow > RUCK_SPAWN_MAX_SCALE)
			{
				Widget existing = m_RuckMarkerWidgets.Get(m.Id);
				if (existing)
					existing.Show(false);

				continue;
			}


			Widget markerRoot = m_RuckMarkerWidgets.Get(m.Id);
			if (!markerRoot)
			{
				Widget parent;

				if (m_RuckMarkerLayer)
					parent = m_RuckMarkerLayer;
				else
					parent = m_MapWidgetInstance;

				markerRoot = Widget.Cast(GetGame().GetWorkspace().CreateWidgets("RuckVanillaMap/Layouts/MarkerIcon.layout", parent));
				if (!markerRoot) continue;

				markerRoot.SetFlags(WidgetFlags.IGNOREPOINTER);
				markerRoot.Show(true);

				m_RuckMarkerWidgets.Set(m.Id, markerRoot);
			}

			markerRoot.Show(true);

			ImageWidget icon = ImageWidget.Cast(markerRoot.FindAnyWidget("Icon"));
			TextWidget label = TextWidget.Cast(markerRoot.FindAnyWidget("Label"));

			float baseSize;
			float coefMin;
			float coefMax;

			if (isAnimalSpawn)
			{
				baseSize = 8.0;
				coefMin  = 0.8;
				coefMax  = 3.0;
			}
			else if (isHuntingSpawn)
			{
				baseSize = 16.0;
				coefMin  = 0.8;
				coefMax  = 3.0;
			}
			else if (isVehicleSpawn)
			{
				baseSize = 14.0;
				coefMin  = 0.8;
				coefMax  = 3.0;
			}
			else
			{
				baseSize = 10.0;
				coefMin  = 0.8;
				coefMax  = 4.0;
			}

			float t = 1.0 - scaleNow;
			float coef = Math.Lerp(coefMin, coefMax, t);

			float size = baseSize * coef;
			float gap  = 1.0 * coef;

			float rootW = size;
			float rootH = size;

			float lw = 0, lh = 0;
			if (label)
			{
				if (isSpawn)
				{
					label.Show(false);
					lw = 0; lh = 0;
					rootW = size;
					rootH = size;
				}
				else
				{
					label.Show(true);
					label.SetText(m.Name);
					label.SetColor(m.ColorARGB);

					label.GetSize(lw, lh);

					rootW = Math.Max(size, lw);
					rootH = size + gap + lh;
				}
			}
			else
			{
				rootW = size;
				rootH = size;
			}

			markerRoot.SetSize(rootW, rootH);

			float iconX = (rootW * 0.5) - (size * 0.5);
			float iconY = 0;

			if (icon)
			{
				string tex;

				if (m.Id < 0 && m.TypeId == 0)
					tex = "RuckVanillaMap/Icons/Marker.paa";
				else
					tex = MapMarkerTypes.GetMarkerIconPath(m.TypeId);

				icon.LoadImageFile(0, tex);
				icon.SetImage(0);
				icon.SetColor(m.ColorARGB);
				icon.Show(true);

				icon.SetPos(iconX, iconY);
				icon.SetSize(size, size);
			}

			if (label && !isSpawn)
			{
				float labelX = (rootW * 0.5) - (lw * 0.5);
				float labelY = size + gap;

				label.SetPos(labelX, labelY);
			}

			vector screen = m_MapWidgetInstance.MapToScreen(m.Pos);

			float rootX = screen[0] - (iconX + (size * 0.5));
			float rootY = screen[1] - (iconY + (size * 0.5));

			markerRoot.SetPos(rootX, rootY);
		}
	}

	protected RuckMapMarkerData FindRuckMarkerById_Local(int markerId)
	{
		array<ref RuckMapMarkerData> markers = GetActiveMarkers();
		if (!markers)
			return null;

		foreach (RuckMapMarkerData m : markers)
		{
			if (m && m.Id == markerId)
				return m;
		}
		return null;
	}

	void ApplyLocalMarkerEdit(int markerId, int newTypeId, string newName, int colorARGB)
	{
		RuckMapMarkerData m = FindRuckMarkerById_Local(markerId);
		if (!m)
			return;

		if (!newName) newName = "";
		if (newName.Length() > 32) newName = newName.Substring(0, 32);

		if (colorARGB == 0)
			colorARGB = ARGB(255, 255, 255, 255);

		m.SetType(newTypeId);
		m.SetName(newName);
		m.SetColor(colorARGB);

		m_RuckMarkersDirty = true;
	}
	
	protected bool HasMarkerId(array<ref RuckMapMarkerData> markers, int id)
	{
		foreach (RuckMapMarkerData m : markers)
		{
			if (m && m.Id == id)
				return true;
		}
		return false;
	}

	protected ChernarusMap FindPlayerMapItem()
	{
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		if (!player) return null;

		EntityAI inHands = player.GetHumanInventory().GetEntityInHands();
		ChernarusMap mapInHands = ChernarusMap.Cast(inHands);
		if (mapInHands) return mapInHands;

		array<EntityAI> items = new array<EntityAI>();
		player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, items);
		foreach (EntityAI item : items)
		{
			ChernarusMap mapItem = ChernarusMap.Cast(item);
			if (mapItem) return mapItem;
		}

		return null;
	}
}
