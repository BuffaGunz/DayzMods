class CfgPatches
{
	class RuckSkin_Bones
	{
		units[] = 
		{
			"BoneSkull",
			
		};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = 
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
class CfgVehicles
{
    class MeatStageTransitions;
	class FoodAnimationSources;
	class DZ_LightAI;
	class DayZInfected: DZ_LightAI
	{
	};
	class ZombieBase: DayZInfected
	{
		class Skinning
		{
			class Steaks
			{
				item="HumanSteakMeat";
				count=2;
				quantityMinMaxCoef[]={0.2,0.8};
			};
			class Skeleton
			{
				item="Skeleton";
				count=1;
				quantityMinMaxCoef[]={0.5,1};
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
	class Inventory_Base;
	class Edible_Base: Inventory_Base
	{
		ContinuousActions[]={101,105};
		InteractActions[]={};
		varTemperatureMax=100;
	};
	class HumanSteakMeat: Edible_Base
	{
		scope=2;
		displayName="Tasty Steak";
		descriptionShort="You Hungry Survivor?";
		inventorySlot[]=
		{
			"Ingredient",
			"DirectCookingA",
			"DirectCookingB",
			"DirectCookingC",
			"SmokingA",
			"SmokingB",
			"SmokingC",
			"SmokingD",
			"Trap_Bait_2",
			"Bait"
		};
	};
	class AllVehicles;
	class Man: AllVehicles
	{
	};
	class SurvivorBase: Man
	{
		class Skinning
		{
			class Steaks
			{
				item="HumanSteakMeat";
				count=10;
				quantityMinMaxCoef[]={0.5,1};
			};
			class Skull
			{
				item="BoneSkull";
				count=1;
				quantityMinMaxCoef[]={0.5,1};
			};
			class Arm
			{
				item="BoneArm";
				count=1;
				quantityMinMaxCoef[]={0.5,1};
			};
			class Leg
			{
				item="BoneLeg";
				count=1;
				quantityMinMaxCoef[]={0.5,1};
			};
			class Guts
			{
				item="Guts";
				count=1;
				quantityMinMaxCoef[]={0.5,0.80000001};
			};
			class Lard
			{
				item="Lard";
				count=1;
				quantityMinMaxCoef[]={0.5,1};
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
	class AnimalBase;
	class Animal_CervusElaphus: AnimalBase
	{	
		class Skinning
		{
			class Skull
			{
				item="DeerSkeleton";
				count=1;
				quantityMinMaxCoef[]={0.5,1};
			};
			class ObtainedSteaks
			{
				item="DeerSteakMeat";
				count=17;
				itemZones[]=
				{
					"Zone_Chest",
					"Zone_Belly",
					"Zone_Pelvis"
				};
				countByZone[]={7,5,6};
				quantityMinMaxCoef[]={0.75,1};
			};
			class ObtainedGuts
			{
				item="Guts";
				count=3;
				quantityMinMaxCoef[]={0.5,0.80000001};
			};
			class ObtainedPelt
			{
				item="DeerPelt";
				count=1;
				itemZones[]=
				{
					"Zone_Chest",
					"Zone_Belly"
				};
				quantityCoef=1;
				transferToolDamageCoef=1;
			};
			class ObtainedLard
			{
				item="Lard";
				count=3;
				quantityMinMaxCoef[]={0.5,1};
			};
			class ObtainedBones
			{
				item="Bone";
				count=3;
				quantityMinMaxCoef[]={0.80000001,1};
				transferToolDamageCoef=1;
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
	class Animal_CervusElaphusF: AnimalBase
	{
		class Skinning
		{
			class Skull
			{
				item="FDeerSkeleton";
				count=1;
				quantityMinMaxCoef[]={0.5,1};
			};
			class ObtainedSteaks
			{
				item="DeerSteakMeat";
				count=17;
				itemZones[]=
				{
					"Zone_Chest",
					"Zone_Belly",
					"Zone_Pelvis"
				};
				countByZone[]={7,5,6};
				quantityMinMaxCoef[]={0.75,1};
			};
			class ObtainedGuts
			{
				item="Guts";
				count=3;
				quantityMinMaxCoef[]={0.5,0.80000001};
			};
			class ObtainedPelt
			{
				item="DeerPelt";
				count=1;
				itemZones[]=
				{
					"Zone_Chest",
					"Zone_Belly"
				};
				quantityCoef=1;
				transferToolDamageCoef=1;
			};
			class ObtainedLard
			{
				item="Lard";
				count=3;
				quantityMinMaxCoef[]={0.5,1};
			};
			class ObtainedBones
			{
				item="Bone";
				count=3;
				quantityMinMaxCoef[]={0.80000001,1};
				transferToolDamageCoef=1;
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
    class BoneSkull: Inventory_Base
	{
		scope=2;
		displayName="Human Skull";
		descriptionShort="Keep Your Head On.";
		model="\RuckModPack\Data\Bones\Skull.p3d";
		weight=1000;
		itemSize[]={2,3};
		inventorySlot[]=
		{
			"Ingredient"
		};
		hiddenSelectionsTextures[]=
		{
			"RuckModPack\Data\Bones\data\Skull_co.paa"
		};
		hiddenSelectionsMaterials[]=
		{
			"RuckModPack\Data\Bones\data\BoneSkull.rvmat"
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
								"RuckModPack\Data\Bones\data\BoneSkull.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"RuckModPack\Data\Bones\data\BoneSkull.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"RuckModPack\Data\Bones\data\BoneSkull.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"RuckModPack\Data\Bones\data\BoneSkull.rvmat"
							}
						},
						
						{
							0,
							
							{
								"RuckModPack\Data\Bones\data\BoneSkull.rvmat"
							}
						}
					};
				};
			};
		};
	};	
	class Skeleton: Inventory_Base
	{
		scope=2;
		displayName="Human Skeleton";
		descriptionShort="Old Lazy Bones.";
		model="\DZ\structures_bliss\specific\forest\forest_humanskeleton.p3d";
		weight=1000;
		itemSize[]={6,3};
		hiddenSelectionsTextures[]=
		{
			"\DZ\structures_bliss\specific\forest\data\humanskeleton_ca.paa"
		};
		hiddenSelectionsMaterials[]=
		{
			"\DZ\structures_bliss\specific\forest\data\humanskeleton.rvmat"
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
							1,
							
							{
								"\DZ\structures_bliss\specific\forest\data\humanskeleton.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"\DZ\structures_bliss\specific\forest\data\humanskeleton.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"\DZ\structures_bliss\specific\forest\data\humanskeleton.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"\DZ\structures_bliss\specific\forest\data\humanskeleton.rvmat"
							}
						},
						
						{
							0,
							
							{
								"\DZ\structures_bliss\specific\forest\data\humanskeleton.rvmat"
							}
						}
					};
				};
			};
		};
	};	
	class DeerSkeleton: Inventory_Base
	{
		scope=2;
		displayName="Deer Skeleton";
		descriptionShort="Leftovers from a recent skinning.";
		model="\DZ\structures_bliss\specific\forest\forest_deerskeleton_full.p3d";
		weight=8000;
		itemSize[]={8,4};
		hiddenSelectionsTextures[]=
		{
			"\DZ\structures_bliss\specific\forest\data\skeleton_deer_co.paa"
		};
		hiddenSelectionsMaterials[]=
		{
			"\DZ\structures_bliss\specific\forest\data\skeleton_deer.rvmat"
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
							1,
							
							{
								"\DZ\structures_bliss\specific\forest\data\skeleton_deer.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"\DZ\structures_bliss\specific\forest\data\skeleton_deer.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"\DZ\structures_bliss\specific\forest\data\skeleton_deer.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"\DZ\structures_bliss\specific\forest\data\skeleton_deer.rvmat"
							}
						},
						
						{
							0,
							
							{
								"\DZ\structures_bliss\specific\forest\data\skeleton_deer.rvmat"
							}
						}
					};
				};
			};
		};
	};	
	class FDeerSkeleton: Inventory_Base
	{
		scope=2;
		displayName="Female Deer Skeleton";
		descriptionShort="Leftovers from a recent skinning.";
		model="\DZ\structures_bliss\specific\forest\forest_deerskeleton_dam.p3d";
		weight=8000;
		itemSize[]={8,4};
		hiddenSelectionsTextures[]=
		{
			"\DZ\structures_bliss\specific\forest\data\skeleton_deer_co.paa"
		};
		hiddenSelectionsMaterials[]=
		{
			"\DZ\structures_bliss\specific\forest\data\skeleton_deer.rvmatt"
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
							1,
							
							{
								"\DZ\structures_bliss\specific\forest\data\skeleton_deer.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"\DZ\structures_bliss\specific\forest\data\skeleton_deer.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"\DZ\structures_bliss\specific\forest\data\skeleton_deer.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"\DZ\structures_bliss\specific\forest\data\skeleton_deer.rvmat"
							}
						},
						
						{
							0,
							
							{
								"\DZ\structures_bliss\specific\forest\data\skeleton_deer.rvmat"
							}
						}
					};
				};
			};
		};
	};	
};