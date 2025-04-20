modded class ModItemRegisterCallbacks
{
   override void RegisterHeavy(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior)
    {
        super.RegisterHeavy(pType, pBehavior);
			pType.AddItemInHandsProfileIK("van_01_door_1_1", "dz/anims/workspaces/player/player_main/player_main_heavy.asi", pBehavior,					"dz/anims/anm/player/ik/vehicles/hatchback_02/Hatchback_02_Door_driver.anm");
			pType.AddItemInHandsProfileIK("van_01_door_2_1", "dz/anims/workspaces/player/player_main/player_main_heavy.asi", pBehavior,			"dz/anims/anm/player/ik/vehicles/hatchback_02/Hatchback_02_Door_driver.anm");
			pType.AddItemInHandsProfileIK("van_01_door_2_2", "dz/anims/workspaces/player/player_main/player_main_heavy.asi", pBehavior,			"dz/anims/anm/player/ik/vehicles/hatchback_02/Hatchback_02_Door_driver.anm");
			pType.AddItemInHandsProfileIK("van_01_trunk_1", "dz/anims/workspaces/player/player_main/player_main_heavy.asi", pBehavior,			"dz/anims/anm/player/ik/vehicles/hatchback_02/Hatchback_02_Door_driver.anm");
			pType.AddItemInHandsProfileIK("van_01_trunk_2", "dz/anims/workspaces/player/player_main/player_main_heavy.asi", pBehavior,			"dz/anims/anm/player/ik/vehicles/hatchback/hatchback_hood.anm");
	};
}