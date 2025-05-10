modded class InGameMenu extends UIScriptedMenu
{

    protected Widget m_DiscordButton;
	protected ImageWidget m_Logo;
	DayZGame m_DayZGame;
	override Widget Init()
	{
		layoutRoot = GetGame().GetWorkspace().CreateWidgets("RuckLoadScreen/gui/layouts/day_z_ingamemenu.layout");
		m_DayZGame = DayZGame.Cast(GetGame());		
		m_ContinueButton			= layoutRoot.FindAnyWidget("continuebtn");
		m_SeparatorPanel			= layoutRoot.FindAnyWidget("separator_red");
		m_ExitButton				= layoutRoot.FindAnyWidget("exitbtn");
		m_RestartButton				= layoutRoot.FindAnyWidget("restartbtn");
		m_RespawnButton 			= layoutRoot.FindAnyWidget("respawn_button");
		m_RestartDeadRandomButton	= layoutRoot.FindAnyWidget("respawn_button_random");
		m_RestartDeadCustomButton	= layoutRoot.FindAnyWidget("respawn_button_custom");
		m_OptionsButton				= layoutRoot.FindAnyWidget("optionsbtn");
		m_Logo						= ImageWidget.Cast(layoutRoot.FindAnyWidget("dayz_logo"));
        m_DiscordButton             = layoutRoot.FindAnyWidget("discordbtn");

		m_ModdedWarning				= TextWidget.Cast(layoutRoot.FindAnyWidget("ModdedWarning"));
		m_HintPanel					= new UiHintPanel(layoutRoot.FindAnyWidget("hint_frame"));
		m_ServerInfoPanel 			= layoutRoot.FindAnyWidget("server_info");
		m_ServerIP 					= TextWidget.Cast(layoutRoot.FindAnyWidget("server_ip"));
		m_ServerPort 				= TextWidget.Cast(layoutRoot.FindAnyWidget("server_port"));
		m_ServerName 				= TextWidget.Cast(layoutRoot.FindAnyWidget("server_name"));
		m_FavoriteImage 			= layoutRoot.FindAnyWidget("favorite_image");
		m_UnfavoriteImage 			= layoutRoot.FindAnyWidget("unfavorite_image");
		m_CopyInfoButton 			= layoutRoot.FindAnyWidget("copy_button");

		
		if (GetGame().IsMultiplayer())
		{
			ButtonSetText(m_RestartButton, "#main_menu_respawn");
		}
		else
		{
			ButtonSetText(m_RestartButton, "#main_menu_restart");
		}

		HudShow(false);
		SetGameVersion();
		SetServerInfoVisibility(SetServerInfo() && g_Game.GetProfileOption(EDayZProfilesOptions.SERVERINFO_DISPLAY));
    	m_ModdedWarning.Show(g_Game.ReportModded());
		
		Mission mission = g_Game.GetMission();
		if (mission)
			mission.Pause();
		
		return layoutRoot;
	}
	
	override bool OnClick(Widget w, int x, int y, int button)
	{
		bool ret = super.OnClick(w, x, y, button);
		
        if ( m_DiscordButton != null && w == m_DiscordButton )
        {
            GetGame().OpenURL( "https://discord.gg/W35b8TKDU3" );
            ret = true;
        }
        return ret;
	}
	
}