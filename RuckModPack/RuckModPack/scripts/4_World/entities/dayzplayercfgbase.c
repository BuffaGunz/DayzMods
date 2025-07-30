modded class DayzPlayerItemBehaviorCfg extends HumanItemBehaviorCfg
{
	
	void	SetHeavyItems()
	{
		m_iType = ItemBehaviorType.HEAVY;

		m_iStanceMask = DayZPlayerConstants.STANCEMASK_ERECT;
		m_StanceMovements[DayZPlayerConstants.STANCEIDX_ERECT] = DayZPlayerConstants.MOVEMENT_IDLE | DayZPlayerConstants.MOVEMENT_WALK | DayZPlayerConstants.MOVEMENT_RUN;
		m_iPerItemCameraUserData = DayZPlayerCameras.PERITEMUD_TWOHANDED;
	  
		SetIKAll(false, true, true);
		
		m_bAttackLean = true;
		m_bJumpAllowed = true;
	}

}