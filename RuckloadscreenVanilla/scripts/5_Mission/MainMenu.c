modded class MainMenu extends UIScriptedMenu
{
	protected ref MainMenuStats		m_Stats;
	protected ref MainMenuVideo		m_Video;
	
	protected MissionMainMenu		m_Mission;
	protected DayZIntroScenePC 		m_ScenePC;
	
	protected TextWidget			m_PlayerName;
	
	protected Widget				m_CharacterRotationFrame;
	
	protected Widget				m_Play;
	protected Widget		 		m_ChooseServer;
	protected Widget				m_CustomizeCharacter;
	protected Widget				m_PlayVideo;
	protected Widget				m_Discord;
	protected Widget				m_Tutorials;
	protected Widget				m_TutorialButton;
	protected Widget				m_MessageButton;
	protected Widget				m_SettingsButton;
	protected Widget				m_Exit;
	protected Widget				m_NewsMain;
	protected Widget				m_NewsSec1;
	protected Widget				m_NewsSec2;
	protected Widget				m_PrevCharacter;
	protected Widget				m_NextCharacter;
	
	protected Widget				m_LastPlayedTooltip;
	protected Widget				m_LastPlayedTooltipLabel;
	protected TextWidget 			m_LastPlayedTooltipName;
	protected TextWidget			m_LastPlayedTooltipIP;
	protected TextWidget			m_LastPlayedTooltipPort;
	
	protected ref WidgetFadeTimer	m_LastPlayedTooltipTimer;
	protected ref Widget			m_LastFocusedButton;
	
	protected ref ModsMenuSimple	m_ModsSimple;
	protected ref ModsMenuDetailed	m_ModsDetailed;
	protected ref ModsMenuTooltip	m_ModsTooltip;
	
	

	override Widget Init()
	{
		layoutRoot = GetGame().GetWorkspace().CreateWidgets("RuckloadscreenVanilla/gui/layouts/main_menu.layout");
		
		m_Play						= layoutRoot.FindAnyWidget("play");
		m_ChooseServer				= layoutRoot.FindAnyWidget("choose_server");
		m_CustomizeCharacter		= layoutRoot.FindAnyWidget("customize_character");
		m_PlayVideo					= layoutRoot.FindAnyWidget("play_video");
		m_Discord					= layoutRoot.FindAnyWidget("Discord_button");
		m_Tutorials					= layoutRoot.FindAnyWidget("tutorials");
		m_TutorialButton			= layoutRoot.FindAnyWidget("tutorial_button");
		m_MessageButton				= layoutRoot.FindAnyWidget("message_button");
		m_SettingsButton			= layoutRoot.FindAnyWidget("settings_button");
		m_Exit						= layoutRoot.FindAnyWidget("exit_button");
		m_PrevCharacter				= layoutRoot.FindAnyWidget("prev_character");
		m_NextCharacter				= layoutRoot.FindAnyWidget("next_character");

		m_CharacterRotationFrame	= layoutRoot.FindAnyWidget("character_rotation_frame");
		
		m_LastPlayedTooltip			= layoutRoot.FindAnyWidget("last_server_info");
		m_LastPlayedTooltip.Show(false);
		m_LastPlayedTooltipLabel	= m_LastPlayedTooltip.FindAnyWidget("last_server_info_label");
		m_LastPlayedTooltipName 	= TextWidget.Cast(m_LastPlayedTooltip.FindAnyWidget("last_server_info_name"));
		m_LastPlayedTooltipIP		= TextWidget.Cast(m_LastPlayedTooltip.FindAnyWidget("last_server_info_ip"));
		m_LastPlayedTooltipPort		= TextWidget.Cast(m_LastPlayedTooltip.FindAnyWidget("last_server_info_port"));
		
		m_LastPlayedTooltipTimer	= new WidgetFadeTimer();
		
		m_Stats						= new MainMenuStats(layoutRoot.FindAnyWidget("character_stats_root"));
		
		m_Mission					= MissionMainMenu.Cast(GetGame().GetMission());
		
		m_LastFocusedButton 		= m_Play;

		m_ScenePC					= m_Mission.GetIntroScenePC();
		
		if (m_ScenePC)
		{
			m_ScenePC.ResetIntroCamera();
		}
		
		
		m_PlayerName				= TextWidget.Cast(layoutRoot.FindAnyWidget("character_name_text"));
		
		
		GetGame().GetUIManager().ScreenFadeOut(0);

		SetFocus(null);
		
		Refresh();
		
		LoadMods();
		
		GetDayZGame().GetBacklit().MainMenu_OnShow();
	
		g_Game.SetLoadState(DayZLoadState.MAIN_MENU_CONTROLLER_SELECT);
		
		return layoutRoot;
	}
	
	override bool OnClick(Widget w, int x, int y, int button)
	{
		if (button == MouseState.LEFT)
		{
			if (w == m_Play)
			{
				m_LastFocusedButton = m_Play;
				Play();
				return true;
			}
			else if (w == m_ChooseServer)
			{
				m_LastFocusedButton = m_ChooseServer;
				OpenMenuServerBrowser();
				return true;
			}
			else if (w == m_CustomizeCharacter)
			{
				OpenMenuCustomizeCharacter();
				return true;
			}
			else if (w == m_TutorialButton)
			{
				OpenTutorials();
				return true;
			}
			else if (w == m_MessageButton)
			{
				OpenCredits();
				return true;
			}
			else if (w == m_SettingsButton)
			{
				OpenSettings();
				return true;
			}
			else if (w == m_Exit)
			{
				Exit();
				return true;
			}
			else if (w == m_PrevCharacter)
			{
				PreviousCharacter();
				return true;
			}
			else if (w == m_NextCharacter)
			{
				NextCharacter();
				return true;
			}
			else if (w == m_PlayVideo)
			{
				m_LastFocusedButton = m_PlayVideo;
				PlayVideo();
				return true;
			}
			else if (w == m_Tutorials)
			{
				m_LastFocusedButton = m_Tutorials;
				OpenTutorials();
				return true;
			}
			else if (w == m_Discord)
			{
				m_LastFocusedButton = m_Discord;
				OpenDiscord();
			}
		}
		return false;
	}
	
	bool IsFocusable(Widget w)
	{
		if (w)
		{
			if (w == m_Play || w == m_ChooseServer || w == m_CustomizeCharacter || w == m_TutorialButton || w == m_MessageButton || w == m_SettingsButton)
			{
				return true;
			}
			
			if (w == m_Exit || w == m_PlayVideo || w == m_Discord)
			{
				return true;
			}
			
			if (w == m_NewsMain || w == m_NewsSec1 || w == m_NewsSec2 || w == m_PrevCharacter || w == m_NextCharacter)
			{
				return true;
			}
		}
		return false;
	}
	
	void OpenDiscord()
	{
		string url = RuckusLoadingHintsConfig.Get().discord_invite;
		if (url && url != "")
			GetGame().OpenURL(url);
	}

}

