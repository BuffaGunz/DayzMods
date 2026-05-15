modded class InGameMenu extends UIScriptedMenu
{
    protected Widget m_DiscordButton;
	protected ImageWidget m_RuckLogo;
	DayZGame m_DayZGame;

	override Widget Init()
	{
		layoutRoot = GetGame().GetWorkspace().CreateWidgets("RuckloadscreenVanilla/gui/layouts/day_z_ingamemenu.layout");
		m_DayZGame = DayZGame.Cast(GetGame());

		m_ContinueButton			= layoutRoot.FindAnyWidget("continuebtn");
		m_SeparatorPanel			= layoutRoot.FindAnyWidget("separator_red");
		m_ExitButton				= layoutRoot.FindAnyWidget("exitbtn");
		m_RestartButton				= layoutRoot.FindAnyWidget("restartbtn");
		m_RespawnButton 			= layoutRoot.FindAnyWidget("respawn_button");
		m_RestartDeadRandomButton	= layoutRoot.FindAnyWidget("respawn_button_random");
		m_RestartDeadCustomButton	= layoutRoot.FindAnyWidget("respawn_button_custom");
		m_OptionsButton				= layoutRoot.FindAnyWidget("optionsbtn");
		m_RuckLogo					= ImageWidget.Cast(layoutRoot.FindAnyWidget("Ruck_logo"));
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

		Mission mission = g_Game.GetMission();
		if (mission)
			mission.Pause();

		return layoutRoot;
	}

	protected void ColorHighlight(Widget w)
	{
		if (!w)
			return;

		ButtonSetColor(w, ARGB(0, 0, 0, 0));
		ButtonSetTextColor(w, ARGB(255, 0, 200, 0));
		if (m_DiscordButton) m_DiscordButton.SetColor(ARGB(255,128,0,128));
	}

	protected void ColorNormal(Widget w)
	{
		if (!w)
			return;

		ButtonSetColor(w, ARGB(0, 0, 0, 0));
		ButtonSetTextColor(w, ARGB(255, 200, 0, 0));
	}

	protected void ColorDisable(Widget w)
	{
		if (!w)
			return;

		ButtonSetColor(w, ARGB(0, 0, 0, 0));
		ButtonSetTextColor(w, ARGB(255, 120, 0, 0));
	}

	override bool OnClick(Widget w, int x, int y, int button)
	{
		bool ret = super.OnClick(w, x, y, button);

		if (button == MouseState.LEFT && m_DiscordButton != null && w == m_DiscordButton)
		{
			string url = RuckusLoadingHintsConfig.Get().discord_invite;

			// Fallback if config not yet received for some reason
			if (url == "")
				url = "https://discord.gg/W35b8TKDU3";

			Print("[Ruckus] InGameMenu opening Discord URL: " + url);
			GetGame().OpenURL(url);
			return true;
		}

		return ret;
	}
}
