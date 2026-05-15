modded class PPERequesterRegistrations
{
	void PPERequesterRegistrations()
	{
		PPERequesterBank.RegisterRequester(PPERequester_RuckSleepSpawn);
	}
}

class PPERequester_RuckSleepSpawn extends PPERequester_GameplayBase
{
	static const int ID = 77221;
	protected ref array<float> m_OverlayColor;

	void SetEffect(float strength)
	{
		if (!IsRequesterRunning())
			Start();

		m_OverlayColor = { 0.0, 0.0, 0.0, 1.0 };

		SetTargetValueFloat(PostProcessEffectType.GaussFilter, PPEGaussFilter.PARAM_INTENSITY, true, strength * 0.2, ID, PPOperators.ADD_RELATIVE);
		SetTargetValueFloat(PostProcessEffectType.Glow, PPEGlow.PARAM_VIGNETTE, false, strength, ID, PPOperators.ADD);
		SetTargetValueFloat(PostProcessEffectType.Glow, PPEGlow.PARAM_OVERLAYFACTOR, true, strength * 0.16, ID, PPOperators.HIGHEST);
		SetTargetValueColor(PostProcessEffectType.Glow, PPEGlow.PARAM_OVERLAYCOLOR, m_OverlayColor, ID, PPOperators.SET);
	}
}
