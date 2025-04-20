modded class MainMenu
{
    override void OnShow()
    {
        super.OnShow();

        if (layoutRoot)
        {
            m_ModdedWarning.SetText("DayZ a Day Keeps The Doctor Away");

            WrapSpacerWidget mods = WrapSpacerWidget.Cast(layoutRoot.FindAnyWidget("ModsSimple"));
            if (mods)
                mods.Show(false);
        }
    }
}