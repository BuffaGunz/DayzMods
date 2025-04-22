modded class PlayerBase extends ManBase
{
    override void Init()
    {
        if ( !GetGame().IsServer() || !GetGame().IsMultiplayer() ) {
			DayzPlayerItemBehaviorCfg heavyItemBehaviour = new DayzPlayerItemBehaviorCfg;
			heavyItemBehaviour.SetHeavyItems();
 
			GetDayZPlayerType().AddItemInHandsProfileIK("IkarusWheel", "dz/anims/workspaces/player/player_main/player_main_heavy.asi", heavyItemBehaviour,					 "dz/anims/anm/player/ik/vehicles/hatchback_02/Hatchback_02_wheel.anm");
			GetDayZPlayerType().AddItemInHandsProfileIK("ikaruswheel_rear", "dz/anims/workspaces/player/player_main/player_main_heavy.asi", heavyItemBehaviour,					"dz/anims/anm/player/ik/vehicles/hatchback_02/Hatchback_02_wheel.anm");
			GetDayZPlayerType().AddItemInHandsProfileIK("IkarusWheel_destroyed", "dz/anims/workspaces/player/player_main/player_main_heavy.asi", heavyItemBehaviour,					 "dz/anims/anm/player/ik/vehicles/hatchback_02/Hatchback_02_wheel.anm");
			GetDayZPlayerType().AddItemInHandsProfileIK("ikaruswheel_rear_destroyed", "dz/anims/workspaces/player/player_main/player_main_heavy.asi", heavyItemBehaviour,					"dz/anims/anm/player/ik/vehicles/hatchback_02/Hatchback_02_wheel.anm");
            GetDayZPlayerType().AddItemInHandsProfileIK("BusLeftDoors_1", "dz/anims/workspaces/player/player_main/player_main_heavy.asi", heavyItemBehaviour,					 "dz/anims/anm/player/ik/vehicles/hatchback_02/Hatchback_02_wheel.anm");
			GetDayZPlayerType().AddItemInHandsProfileIK("BusLeftDoors_2", "dz/anims/workspaces/player/player_main/player_main_heavy.asi", heavyItemBehaviour,					"dz/anims/anm/player/ik/vehicles/hatchback_02/Hatchback_02_wheel.anm");
            GetDayZPlayerType().AddItemInHandsProfileIK("BusLeftDoors_3", "dz/anims/workspaces/player/player_main/player_main_heavy.asi", heavyItemBehaviour,					"dz/anims/anm/player/ik/vehicles/hatchback_02/Hatchback_02_wheel.anm");
			GetDayZPlayerType().AddItemInHandsProfileIK("BusRightDoors_1", "dz/anims/workspaces/player/player_main/player_main_heavy.asi", heavyItemBehaviour,					"dz/anims/anm/player/ik/vehicles/hatchback_02/Hatchback_02_wheel.anm");
			GetDayZPlayerType().AddItemInHandsProfileIK("BusRightDoors_2", "dz/anims/workspaces/player/player_main/player_main_heavy.asi", heavyItemBehaviour,					"dz/anims/anm/player/ik/vehicles/hatchback_02/Hatchback_02_wheel.anm");
			GetDayZPlayerType().AddItemInHandsProfileIK("BusRightDoors_3", "dz/anims/workspaces/player/player_main/player_main_heavy.asi", heavyItemBehaviour,					"dz/anims/anm/player/ik/vehicles/hatchback_02/Hatchback_02_wheel.anm");
            GetDayZPlayerType().AddItemInHandsProfileIK("BusHood", "dz/anims/workspaces/player/player_main/player_main_heavy.asi", heavyItemBehaviour,					"dz/anims/anm/player/ik/vehicles/hatchback_02/Hatchback_02_wheel.anm");

			
			}
        super.Init();
    }
}
