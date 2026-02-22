class CfgPatches
{
	class RuckSkin
	{
		units[]= 
		{
			"RuckHumanSkull"
		};
		weapons[]={};
		requiredVersion=1.0;
		requiredAddons[]=
		{
			"DZ_Scripts",
			"DZ_Data",
			"DZ_Characters",
			"DZ_gear_food",
			"DZ_Animals",
			"DZ_Animals_cervus_elaphus"
		};
	};
};
class CfgMods
{
	class RuckSkin
	{
		dir="RuckSkin";
		picture="";
		action="";
		hideName=1;
		hidePicture=1;
		name="Ruck Skin Mod";
		credits="";
		author="BuffaGunz";
		authorID="0";
		version="1.0";
		extra=0;
		type="mod";
		inputs = "";
		dependencies[]=
		{
			"Game",
			"World",
			"Mission"
		};
		class defs
		{
			class gameScriptModule
			{
				value="";
				files[]=
				{
					"RuckSkin\scripts\3_Game"
				};
			};
			class worldScriptModule
			{
				value="";
				files[]=
				{
					"RuckSkin\scripts\4_World"
				};
			};
			class missionScriptModule
			{
				value="";
				files[]=
				{
					"RuckSkin\scripts\5_Mission"
				};
			};
		};
	};
};

class CfgVehicles
{
	class DayZInfected;
	class ZombieBase: DayZInfected
	{
		class Skinning
		{
			class Steaks
			{
				item="HumanSteakMeat";
				count=8;
				quantityMinMaxCoef[]={0.2,0.8};
			};
			class Guts
			{
				item="Guts";
				count=1;
				quantityMinMaxCoef[]={0.5,0.80000001};
			};
			class Bones
			{
				item="Bone";
				count=2;
				quantityMinMaxCoef[]={0.75,1};
			};
			class BloodInfectionSettings
			{
				class Salmonella
				{
					chance=0.40000001;
				};
			};
		};
	};

	class Edible_Base;
	class HumanSteakMeat: Edible_Base
	{
		displayName= "$STR_CfgVehicles_TastySteak0";
		descriptionShort= "$STR_CfgVehicles_TastySteak1";
		inventorySlot[]+=
		{
			"Ingredient",
			"Bait"
		};
	};
	
	class Inventory_Base;
	class RuckHumanSkull: Inventory_Base
	{
		scope = 2;
		displayName= "$STR_CfgVehicles_HumanSkull0";
		descriptionShort= "$STR_CfgVehicles_HumanSkull1";
		model= "RuckSkin\HumanSkull.p3d";
		isMeleeWeapon= 1;
		weight = 1000;
		itemSize[] = {2,3};
		inventorySlot[]+=
		{
			"Ingredient",
			"Backpack_1"
		};
		hiddenSelections[]= 
		{
			"Skull"
		};
		hiddenSelectionsTextures[]= 
		{
			"RuckSkin\Data\HumanSkull_co.paa"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=300;
					healthLevels[]=
					{
						
						{
							1.00,
							
							{
								"RuckSkin\Data\HumanSkull.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"RuckSkin\Data\HumanSkull.rvmat"
							}
						},
						
						{
							0.50,
							
							{
								"RuckSkin\Data\HumanSkull_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"RuckSkin\Data\HumanSkull_damage.rvmat"
							}
						},
						
						{
							0.00,
							
							{
								"RuckSkin\Data\HumanSkull_destruct.rvmat"
							}
						}
					};
				};
			};
		};
	};
};

