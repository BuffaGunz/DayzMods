class CfgPatches
{
	class RuckModPack_Melee
	{
		units[] = 
		{
			"SurvivalShovel"
		};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[]=
		{
			"DZ_Data",
			"DZ_Weapons_Melee",
			"DZ_Gear_Tools"
		};
	};
};
class CfgVehicles
{
	class Inventory_Base;
	class SurvivalShovel: Inventory_Base
	{
		scope=2;
		displayName="Survival Shovel";
		descriptionShort="Shovel & Axe all in one.";
		model="\RuckModPack\Data\Melee\SurvivalShovel.p3d";
		debug_ItemCategory=2;
		repairableWithKits[]={4};
		repairCosts[]={20};
		rotationFlags=17;
		inventorySlot[]=
		{
			"Backpack_1",
			"Shoulder",
			"Melee"
		};
		itemInfo[]=
		{
			"Axe"
		};
		isMeleeWeapon=1;
		suicideAnim="woodaxe";
		weight=1800;
		itemSize[]={2,5};
		build_action_type=4;
		dismantle_action_type=4;
		openItemSpillRange[]={30,60};
		soundImpactType="metal";
		hiddenSelectionsTextures[]=
		{
			"RuckModPack\Data\Melee\Data\SurvivalShovel_co.paa"
		};
		hiddenSelectionsMaterials[]=
		{
			"DZ\gear\tools\data\CSLA_Field_Shovel.rvmat"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=200;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\gear\tools\data\CSLA_Field_Shovel.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\gear\tools\data\CSLA_Field_Shovel.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\gear\tools\data\CSLA_Field_Shovel_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\gear\tools\data\CSLA_Field_Shovel_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\gear\tools\data\CSLA_Field_Shovel_destruct.rvmat"
							}
						}
					};
				};
			};
		};
		class MeleeModes
		{
			class Default
			{
				ammo="MeleeSharpLight_5";
				range=1.8;
			};
			class Heavy
			{
				ammo="MeleeSharpHeavy_5";
				range=1.8;
			};
			class Sprint
			{
				ammo="MeleeSharpHeavy_5";
				range=3.7;
			};
		};
		class InventorySlotsOffsets
		{
			class Shoulder
			{
				position[]={0,0.075000003,0};
				orientation[]={60,0,0};
			};
			class Melee
			{
				position[]={0,0.050000001,0.02};
				orientation[]={120,0,0};
			};
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class pickUpShovel_Light
				{
					soundSet="pickUpShovelLight_SoundSet";
					id=796;
				};
				class pickUpShovel
				{
					soundSet="pickUpShovel_SoundSet";
					id=797;
				};
				class drop
				{
					soundset="shovel_drop_SoundSet";
					id=898;
				};
				class FirefighterAxe_loop_SoundSet
				{
					soundSet="FirefighterAxe_loop_SoundSet";
					id=1121;
				};
				class FirefighterAxe_end_SoundSet
				{
					soundSet="FirefighterAxe_end_SoundSet";
					id=1122;
				};
				class ShoulderR_Hide
				{
					soundset="ShoulderR_Hide_SoundSet";
					id=1210;
				};
				class ShoulderR_Show
				{
					soundset="ShoulderR_Show_SoundSet";
					id=1211;
				};
				class animalSkinning_in
				{
					soundSet="animalSkinning_in_SoundSet";
					id=516;
				};
				class animalSkinning
				{
					soundSet="animalSkinning_SoundSet";
					id=517;
				};
				class animalSkinning_out
				{
					soundSet="animalSkinning_out_SoundSet";
					id=518;
				};
			};
			class Sound
			{
				class SurfaceDig
				{
					class DigPrimary
					{
						default=887;
						sakhal_snow=900;
						sakhal_snow_forest=900;
						sakhal_grass_brown=900;
						sakhal_ice_sea=905;
						sakhal_ice_lake=905;
					};
					class DigSecondary
					{
						default=888;
						sakhal_snow=901;
						sakhal_snow_forest=901;
						sakhal_grass_brown=901;
						sakhal_ice_sea=904;
						sakhal_ice_lake=904;
					};
				};
			};
		};	
		class Horticulture
		{
			ToolAnim="DIGGINGSHOVEL";
			DiggingTimeToComplete=5;
		};	
	};
    class KukriKnife: Inventory_Base
	{
		inventorySlot[]=
		{
			"Backpack_1"
		};
	};
	class Cleaver: Inventory_Base
	{
		inventorySlot[]=
		{
			"Backpack_1"
		};
	};
	class FishingRod_Base;
	class FishingRod_Base_New: FishingRod_Base
	{
	};
	class FishingRod: FishingRod_Base_New
	{
		inventorySlot[]=
		{
			"Shoulder",
			"Melee",
			"Backpack_1"
		};
	};	
};	
 