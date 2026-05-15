modded class PlayerBase
{
	private static const float RUCK_SLEEP_FX_TICKS = 350;
	private float m_RuckSleepFxT;

	private ref PPERequester_RuckSleepSpawn m_RuckSleepPPE;

	private bool m_RuckSleepLaydownDone;

	override void OnPlayerLoaded()
	{
		super.OnPlayerLoaded();

		if (!GetGame().IsClient())
			return;

		RuckSleepEffect();

		m_RuckSleepLaydownDone = false;
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(RuckTrySleep, 50, false);

		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(RuckWakeUp, 4500, false);
	}

	protected void RuckTrySleep()
	{
		if (m_RuckSleepLaydownDone)
			return;

		EmoteManager em = GetEmoteManager();
		if (em && em.IsEmotePlaying())
		{
			m_RuckSleepLaydownDone = true;
			return;
		}

		RuckSleepLayDown();

		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(RuckTrySleep, 50, false);
	}

	protected void RuckSleepEffect()
	{
		m_RuckSleepFxT = RUCK_SLEEP_FX_TICKS;
		m_RuckSleepPPE = PPERequester_RuckSleepSpawn.Cast(PPERequesterBank.GetRequester(PPERequester_RuckSleepSpawn));
		if (m_RuckSleepPPE)
		{
			m_RuckSleepPPE.SetEffect(2.0);
			GetGame().GetSoundScene().SetSoundVolume(0, 0);
		}
	}

	protected void RuckSleepLayDown()
	{
		if (!IsControlledPlayer())
			return;

		if (IsRestrained() || IsUnconscious() || IsFalling() || !IsAlive() || IsSwimming())
			return;

		if (GetEmoteManager() && !GetEmoteManager().IsEmotePlaying())
		{
			if (GetEmoteManager().CanPlayEmote(EmoteConstants.ID_EMOTE_LYINGDOWN))
			{
				GetEmoteManager().CreateEmoteCBFromMenu(EmoteConstants.ID_EMOTE_LYINGDOWN, true);
			}
			else if (GetEmoteManager().CanPlayEmote(EmoteConstants.ID_EMOTE_SITA))
			{
				GetEmoteManager().CreateEmoteCBFromMenu(EmoteConstants.ID_EMOTE_SITA, true);
			}
		}
	}

	protected void RuckWakeUp()
	{
		GetGame().GetSoundScene().SetSoundVolume(g_Game.m_volume_sound, 4);
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(RuckSleepSpawnFxTick, 1, false);
	}

	protected void RuckSleepSpawnFxTick()
	{
		if (!m_RuckSleepPPE)
			return;

		float t = 1.0 - ((RUCK_SLEEP_FX_TICKS - m_RuckSleepFxT) / RUCK_SLEEP_FX_TICKS);
		float strength = Math.Lerp(0.0, 2.0, t);

		m_RuckSleepFxT -= 1;
		m_RuckSleepPPE.SetEffect(strength);

		if (strength <= 0.0 || m_RuckSleepFxT <= 0)
		{
			m_RuckSleepPPE.SetEffect(0.0);
			m_RuckSleepPPE.Stop();
			m_RuckSleepPPE = null;
			return;
		}

		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(RuckSleepSpawnFxTick, 1, false);
	}
}
