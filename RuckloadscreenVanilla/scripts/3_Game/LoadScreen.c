modded class LoadingScreen
{
    void LoadingScreen(DayZGame game)
    {
        RuckusLoadingHintsConfig.Get();

        m_DayZGame = game;

        m_WidgetRoot = game.GetLoadingWorkspace().CreateWidgets("RuckloadscreenVanilla/gui/layouts/loading.layout");

        Class.CastTo(m_ImageLogoMid, m_WidgetRoot.FindAnyWidget("ImageLogoMid"));
        Class.CastTo(m_ImageLogoCorner, m_WidgetRoot.FindAnyWidget("ImageLogoCorner"));
        Class.CastTo(m_TextWidgetTitle, m_WidgetRoot.FindAnyWidget("TextWidget"));
        Class.CastTo(m_TextWidgetStatus, m_WidgetRoot.FindAnyWidget("StatusText"));
        Class.CastTo(m_ImageWidgetBackground, m_WidgetRoot.FindAnyWidget("ImageBackground"));
        Class.CastTo(m_ImageLoadingIcon, m_WidgetRoot.FindAnyWidget("ImageLoadingIcon"));
        Class.CastTo(m_ModdedWarning, m_WidgetRoot.FindAnyWidget("ModdedWarning"));
        m_ImageBackground = ImageWidget.Cast(m_WidgetRoot.FindAnyWidget("ImageBackground"));
        m_ProgressLoading = ProgressBarWidget.Cast(m_WidgetRoot.FindAnyWidget("LoadingBar"));
        m_ProgressText = TextWidget.Cast(m_WidgetRoot.FindAnyWidget("ProgressText"));

        if (GetGame())
        {
            string tmp;
            m_ProgressText.Show(GetGame().CommandlineGetParam("loadingTest", tmp));
        }

        if (m_ImageWidgetBackground)
        {
            string customPath = "RuckloadscreenVanilla/gui/data/Ruckloadscreen2.edds";
            m_ImageWidgetBackground.LoadMaskTexture("");
            m_ImageWidgetBackground.LoadImageFile(0, customPath);
            Print("[RuckLoadscreen] Applied custom ImageBackground in LoadingScreen()");
        }

        if (m_ModdedWarning) m_ModdedWarning.Show(false);

        m_ImageWidgetBackground.Show(true);
        m_Counter = 0;

        game.GetBacklit().LoadingAnim();

        ProgressAsync.SetProgressData(m_ProgressLoading);
        ProgressAsync.SetUserData(m_ImageBackground);
    }

    override void Show()
    {
        super.Show();

        if (m_ImageWidgetBackground)
        {
            string customPath = "RuckloadscreenVanilla/gui/data/Ruckloadscreen2.edds";
            m_ImageWidgetBackground.LoadImageFile(0, customPath);
        }

        if (m_ImageLogoMid) m_ImageLogoMid.Show(false);
        if (m_ImageLogoCorner) m_ImageLogoCorner.Show(false);
        if (m_ModdedWarning) m_ModdedWarning.Show(false);
    }
}

modded class LoginTimeBase extends UIScriptedMenu
{
	override Widget Init()
	{
        RuckusLoadingHintsConfig.Get();

		layoutRoot = GetGame().GetWorkspace().CreateWidgets("RuckloadscreenVanilla/gui/layouts/dialog_login_time.layout");

		m_txtDescription = TextWidget.Cast(layoutRoot.FindAnyWidget("txtDescription"));
		m_txtLabel = TextWidget.Cast(layoutRoot.FindAnyWidget("txtLabel"));
		m_btnLeave = ButtonWidget.Cast(layoutRoot.FindAnyWidget("btnLeave"));

		m_txtDescription.Show(true);
		layoutRoot.FindAnyWidget("notification_root").Show(false);

		return layoutRoot;
	};

    ref TStringArray LoadingScreenArray =
    {
        "RuckloadscreenVanilla/gui/data/Ruckloadscreen1.edds"
    };

    override void Show()
    {
        super.Show();
        if (layoutRoot)
        {
            string preel = LoadingScreenArray.GetRandomElement();
            ImageWidget background = ImageWidget.Cast(layoutRoot.FindAnyWidget("Background"));
            background.LoadImageFile(0, preel);
        }
    }
}

modded class LoginQueueBase extends UIScriptedMenu
{
	override Widget Init()
	{
        RuckusLoadingHintsConfig.Get();

		return super.Init();
	}

	ref TStringArray LoadingScreenArray =
	{
		"RuckloadscreenVanilla/gui/data/Ruckloadscreen2.edds"
	};

    override void Show()
    {
        super.Show();
        if (layoutRoot)
        {
            string preel = LoadingScreenArray.GetRandomElement();
            ImageWidget background = ImageWidget.Cast(layoutRoot.FindAnyWidget("Background"));
            background.LoadImageFile(0, preel);
        }
    }
}
