modded class ModItemRegisterCallbacks
{
	override void RegisterHeavy(DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior)
    {
		super.RegisterHeavy( pType, pBehavior );
		
		//Attach
		pType.AddItemInHandsProfileIK("truck_02_wheel", "dz/anims/workspaces/player/player_main/player_main_heavy.asi", pBehavior, "dz/anims/anm/player/ik/vehicles/hatchback_02/Hatchback_02_wheel.anm");
		pType.AddItemInHandsProfileIK("truck_02_wheel_ruined", "dz/anims/workspaces/player/player_main/player_main_heavy.asi", pBehavior, "dz/anims/anm/player/ik/vehicles/hatchback_02/Hatchback_02_wheel.anm");
		pType.AddItemInHandsProfileIK("truck_02_door_1_1", "dz/anims/workspaces/player/player_main/player_main_heavy.asi", pBehavior, "dz/anims/anm/player/ik/vehicles/hatchback/hatchback_driverdoor.anm");
		pType.AddItemInHandsProfileIK("truck_02_door_2_1", "dz/anims/workspaces/player/player_main/player_main_heavy.asi", pBehavior, "dz/anims/anm/player/ik/vehicles/hatchback/hatchback_driverdoor.anm");
		pType.AddItemInHandsProfileIK("truck_02_hull", "dz/anims/workspaces/player/player_main/player_main_heavy.asi", pBehavior, "dz/anims/anm/player/ik/vehicles/hatchback/hatchback_driverdoor.anm");
	};
}