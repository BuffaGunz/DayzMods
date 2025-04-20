class CfgPatches
{
	class RuckModPack_FirstAidKit
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data","DZ_Gear_Containers"};
	};
};
class CfgVehicles
{
class Container_Base;
class FirstAidKit: Container_Base
	{
		scope=2;
		displayName="$STR_CfgVehicles_FirstAidKit0";
		descriptionShort="$STR_CfgVehicles_FirstAidKit1";
		model="\dz\gear\containers\FirstAidKit.p3d";
		inventorySlot[]=
		{
			"Belt_Left",
			"Backpack_1"
		};
		rotationFlags=17;
		weight=140;
		itemSize[]={3,3};
		itemsCargoSize[]={3,3};
		allowOwnedCargoManipulation=1;
		randomQuantity=2;
		canBeDigged=1;
		repairableWithKits[]={2};
		repairCosts[]={25};
		isMeleeWeapon=1;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=80;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\gear\containers\data\FirsAidKit.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\gear\containers\data\FirsAidKit.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\gear\containers\data\FirsAidKit_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\gear\containers\data\FirsAidKit_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\gear\containers\data\FirsAidKit_destruct.rvmat"
							}
						}
					};
				};
			};
		};
		soundImpactType="textile";
		class AnimEvents
		{
			class SoundWeapon
			{
				class pickUpItem_Light
				{
					soundSet="pickUpCourierBag_Light_SoundSet";
					id=796;
				};
				class pickUpItem
				{
					soundSet="pickUpCourierBag_SoundSet";
					id=797;
				};
			};
		};
	};
};	