modded class LoadingScreen
{
	ref TStringArray BitterRootLoadingScreenArray = 
	{
		"Ruckloadscreen/gui/data/Ruckloadscreen.edds",
		"Ruckloadscreen/gui/data/Summer.edds",
		"Ruckloadscreen/gui/data/Deer.edds"
	};

	override void Show()
	{		
		string preel = BitterRootLoadingScreenArray.GetRandomElement();
		m_ImageWidgetBackground.LoadMaskTexture("");
		m_ImageWidgetBackground.LoadImageFile(0, preel);   
        m_ImageLogoMid.Show(false);
		m_ImageLogoCorner.Show(false);	    	
		m_ModdedWarning.Show(false); 
		super.Show();
	}
}


modded class LoginTimeBase extends UIScriptedMenu
{
	ref TStringArray BitterRootLoadingScreenArray = 
	{
		"Ruckloadscreen/gui/data/Ruckloadscreen.edds",
		"Ruckloadscreen/gui/data/Summer.edds",
		"Ruckloadscreen/gui/data/Deer.edds"
	};

    override void Show()
    {
        super.Show();
        if (layoutRoot)
        {
            string preel = BitterRootLoadingScreenArray.GetRandomElement();
            ImageWidget background = ImageWidget.Cast( layoutRoot.FindAnyWidget("Background"));
            background.LoadImageFile(0, preel);  
        }
    }
}


modded class LoginQueueBase extends UIScriptedMenu
{
	ref TStringArray BitterRootLoadingScreenArray = 
	{
		"Ruckloadscreen/gui/data/Ruckloadscreen.edds",
		"Ruckloadscreen/gui/data/Summer.edds",
		"Ruckloadscreen/gui/data/Deer.edds"
	};

    override void Show()
    {
        super.Show();
        if (layoutRoot)
        {
            string preel = BitterRootLoadingScreenArray.GetRandomElement();
            ImageWidget background = ImageWidget.Cast( layoutRoot.FindAnyWidget("Background"));
            background.LoadImageFile(0, preel);  
        }
    }
}