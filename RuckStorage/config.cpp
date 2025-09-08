class CfgPatches
{
	class RuckStorage
	{
		units[] = { "RuckChest" };
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = { "DZ_Data", "DZ_Gear_Camping" };
	};
};

class CfgMods
{
	class RuckStorage
	{
		dir = "RuckStorage";
		name = "Ruck Storage";
		author = "BuffaGunz";
		hideName = 1;
		hidePicture = 1;
		version = "1.0";
		type = "mod";
		dependencies[] = { "World" };
		class defs
		{
			class worldScriptModule
			{
				value = "";
				files[] = { "RuckStorage/Scripts/4_World" };
			};
		};
	};
};

class CfgVehicles
{
	class Container_Base;
	class RuckChest: Container_Base
	{
		scope=2;
		displayName="Storage Chest";
		descriptionShort="A place to store all your loot.";
		model="\DZ\gear\camping\sea_chest_anniversary.p3d";
		hologramMaterial="sea_chest";
		hologramMaterialPath="dz\gear\camping\data";
		slopeTolerance=0.40000001;
		yawPitchRollLimit[]={45,45,45};
		weight=10000;
		itemBehaviour=2;
		physLayer="item_large";
		itemSize[]={10,10};
		overrideDrawArea="3.0";
		bounding="BSphere";
		forceFarBubble="true";
		carveNavmesh=1;
		canBeDigged=1;
		rotationFlags=2;
		class Cargo
		{
			itemsCargoSize[]={10,40};
			openable=0;
			allowOwnedCargoManipulation=1;
		};
		soundImpactType="wood";
		class AnimEvents
		{
			class SoundWeapon
			{
				class movement
				{
					soundSet="seachest_movement_SoundSet";
					id=1;
				};
				class pickUpItem_Light
				{
					soundSet="pickUpSeaChest_SoundSet";
					id=796;
				};
				class pickUpItem
				{
					soundSet="pickUpSeaChest_SoundSet";
					id=797;
				};
				class drop
				{
					soundset="seachest_drop_SoundSet";
					id=898;
				};
			};
		};
		class AnimationSources
		{
			class lidclosing
			{
				source="user";
				animPeriod=0.5;
				initPhase=1;
			};
			class rayshiding
			{
				source="user";
				animPeriod=0.5;
				initPhase=1;
			};
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=800;
					transferToAttachmentsCoef=0.059999999;
					healthLevels[]=
					{
						 {
                            1.01,
                            
                            {
                                "dz\gear\camping\data\sea_chest_e_co.paa",
                                "dz\gear\camping\data\sea_chest_e.rvmat",
                                "DZ\gear\camping\data\gradientgold_e_ca.paa"
                                
                            }
                        },
                        {
                            1,
                        
                            {
                                "dz\gear\camping\data\sea_chest_co.paa",
                                "dz\gear\camping\data\sea_chest.rvmat",
                                "dz\gear\camping\data\party_tent_cloth_brown_co.paa"
                            }
                        },
						{
							0.69999999,
							
							{
								"dz\gear\camping\data\sea_chest_co.paa",
                                "dz\gear\camping\data\sea_chest.rvmat",
                                "dz\gear\camping\data\party_tent_cloth_brown_co.paa"
							}
						},
						
						{
							0.5,
							
							{
								"dz\gear\camping\data\sea_chest_co.paa",
                                "dz\gear\camping\data\sea_chest_damage.rvmat",
                                "dz\gear\camping\data\party_tent_cloth_brown_co.paa"
							}
						},
						
						{
							0.30000001,
							
							{
								"dz\gear\camping\data\sea_chest_co.paa",
                                "dz\gear\camping\data\sea_chest_damage.rvmat",
                                "dz\gear\camping\data\party_tent_cloth_brown_co.paa"
							}
						},
						
						{
							0,
							
							{
								"dz\gear\camping\data\sea_chest_co.paa",
                                "dz\gear\camping\data\sea_chest_destruct.rvmat",
                                "dz\gear\camping\data\party_tent_cloth_brown_co.paa"
							}
						}
					};
				};
			};
			class GlobalArmor
			{
				class Projectile
				{
					class Health
					{
						damage=0;
					};
					class Blood
					{
						damage=0;
					};
					class Shock
					{
						damage=0;
					};
				};
				class Melee
				{
					class Health
					{
						damage=0;
					};
					class Blood
					{
						damage=0;
					};
					class Shock
					{
						damage=0;
					};
				};
				class FragGrenade
				{
					class Health
					{
						damage=0;
					};
					class Blood
					{
						damage=0;
					};
					class Shock
					{
						damage=0;
					};
				};
			};
		};
	};
};	