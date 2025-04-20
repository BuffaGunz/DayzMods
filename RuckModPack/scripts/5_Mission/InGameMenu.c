modded class InGameMenu 
{
	
	override void OnShow()
    {
        super.OnShow();

        if (layoutRoot)
        {
            m_ModdedWarning.SetText("Dayz a Day Keeps The Doctor Away");

            WrapSpacerWidget mods = WrapSpacerWidget.Cast(layoutRoot.FindAnyWidget("ModsSimple"));
            if (mods)
                mods.Show(false);
        }
    }	

}
