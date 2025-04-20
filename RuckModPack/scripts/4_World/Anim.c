modded class ModItemRegisterCallbacks
{
	override void RegisterOneHanded(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior)
	{	
		super.RegisterOneHanded( pType, pBehavior);
		pType.AddItemInHandsProfileIK("SurvivalShovel", "dz/anims/workspaces/player/player_main/player_main_1h.asi", pBehavior, "dz/anims/anm/player/ik/gear/hatchet.anm");
	}
};