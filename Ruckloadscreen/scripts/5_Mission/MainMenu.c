modded class MainMenu
{
    override void OnShow()
    {
        super.OnShow();

        if (layoutRoot)
        {
            m_ModdedWarning.SetText("DayZ a Day Keeps The Doctor Away"); //Change this text to what you want to be dispalyed.

            WrapSpacerWidget mods = WrapSpacerWidget.Cast(layoutRoot.FindAnyWidget("ModsSimple"));
            if (mods)
                mods.Show(false);
        }
    }
}