class CfgPatches
{
	class RuckSheath_backpacks
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Characters","DZ_Characters_Belts"};
	};
};
class cfgVehicles
{
	class Clothing_Base;
	class Clothing: Clothing_Base
	{
	};
	class LeatherKnifeSheath: Clothing
	{
		scope=2;
		displayName="$STR_CfgVehicles_LeatherKnifeSheath0";
		descriptionShort="$STR_CfgVehicles_LeatherKnifeSheath1";
		model="\DZ\characters\belts\knife_holster_g.p3d";
		inventorySlot[]=
		{
			"Belt_Back",
			"Chemlight",
			"WalkieTalkie"
		};
		vehicleClass="Clothing";
		itemInfo[]=
		{
			"Clothing",
			"Belt"
		};
		weight=110;
		itemSize[]={1,3};
		attachments[]=
		{
			"Knife"
		};
		absorbency=0.1;
		heatIsolation=0;
		repairableWithKits[]={3};
		repairCosts[]={25};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\characters\belts\data\knife_holster.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\characters\belts\data\knife_holster.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\characters\belts\data\knife_holster_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\characters\belts\data\knife_holster_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\characters\belts\data\knife_holster_destruct.rvmat"
							}
						}
					};
				};
			};
		};
		class ClothingTypes
		{
			male="\DZ\characters\belts\knife_holster_m.p3d";
			female="\DZ\characters\belts\knife_holster_f.p3d";
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class pickUpItem
				{
					soundSet="WorkingGloves_pickup_SoundSet";
					id=797;
				};
				class drop
				{
					soundset="WorkingGloves_drop_SoundSet";
					id=898;
				};
			};
		};
	};
};