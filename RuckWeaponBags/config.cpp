class CfgPatches
{
    class RuckWeaponBags
    {
        units[] = {""};
        weapons[] = {};
		requiredAddons[] = 
		{
			"DZ_Data",
			"DZ_Characters",
			"DZ_Characters_Vests",
			"DZ_Characters_Backpacks",
			"DZ_Weapons_Firearms",
			"DZ_Sounds_Weapons",
			"DZ_Weapons_Firearms_M4",
			"DZ_Weapons_Firearms_SKS",
			"DZ_Weapons_Firearms_M16A2",
			"DZ_Weapons_Firearms_Winchester70",
			"DZ_Weapons_Firearms_AK74",
			"DZ_Weapons_Firearms_AK101",
			"DZ_Weapons_Firearms_AKM",
			"DZ_Weapons_Firearms_aug",
			"DZ_Weapons_Firearms_B95",
			"DZ_Weapons_Firearms_cz61",
			"DZ_Weapons_Firearms_CZ527",
			"DZ_Weapons_Firearms_CZ550",
			"DZ_Weapons_Firearms_FAL",
			"DZ_Weapons_Firearms_Famas",
			"DZ_Weapons_Firearms_IZH18",
			"DZ_Weapons_Firearms_M14",
			"DZ_Weapons_Firearms_MosinNagant",
			"DZ_Weapons_Firearms_MP5",
			"DZ_Weapons_Firearms_PP19",
			"DZ_Weapons_Firearms_Repeater",
			"DZ_Weapons_Firearms_Ruger1022",
			"DZ_Weapons_Firearms_Scout",
			"DZ_Weapons_Firearms_SSG82",
			"DZ_Weapons_Firearms_SV98",
			"DZ_Weapons_Firearms_SVD",
			"DZ_Weapons_Firearms_UMP",
			"DZ_Weapons_Firearms_VSS",
			"DZ_Weapons_Shotguns_Izh18Shotgun",
			"DZ_Weapons_Shotguns_Izh43",
			"DZ_Weapons_Shotguns_MP133",
			"DZ_Weapons_Firearms_SaigaK",
			"DZ_Weapons_Melee_Blade",
			"DZ_Weapons_Melee_Blunt",
			"DZ_Weapons_Archery_Crossbow"
		};
    };
};

class CfgMods
{
    class RuckWeaponBags
    {
        dir = "RuckWeaponBags";
        name = " Ruck Weapon Bags";
		author="BuffaGunz";
        picture = "";
        action = "";
        hideName = 1;
        hidePicture = 1;
        version = "1.0";
        type = "mod";
    };
};

class cfgWeapons
{
	class RifleCore;
	class Rifle_Base: RifleCore
	{
		inventorySlot[]=
		{
			"Shoulder",
			"Melee",
			"Backpack_1"
		};
		class InventorySlotsOffsets
		{
			class Backpack_1
			{
				position[]={0,0.2,0};
				orientation[]={0,0,90};
			};
		};
	};	
	class Archery_Base;
	class Crossbow_Base: Archery_Base
	{
		inventorySlot[]=
		{
			"Shoulder",
			"Melee",
			"Backpack_1"
		};
		class InventorySlotsOffsets
		{
			class Backpack_1
			{
				position[]={0,0,-0.05};
				orientation[]={270,0,90};
			};
			class Shoulder
			{
				position[]={0,0.07,-0.050000001};
				orientation[]={0,-80,0};
			};
			class Melee
			{
				position[]={0,0.1,0.029999999};
				orientation[]={0,80,0};
			};
		};
	};	
	class M16A2_Base: Rifle_Base
	{
		class InventorySlotsOffsets
		{
			class Backpack_1
			{
				position[]={0,0.2,0};
				orientation[]={0,0,90};
			};
			class Shoulder
			{
				position[]={-0.1,0,0.02};
				orientation[]={0,0,0};
			};
			class Melee
			{
				position[]={-0.1,0,-0.050000001};
				orientation[]={0,0,0};
			};
		};
	};	
	class SKS_Base: Rifle_Base
	{
		class InventorySlotsOffsets
		{
			class Backpack_1
			{
				position[]={0,0.2,0};
				orientation[]={0,0,90};
			};
			class Shoulder
			{
				position[]={0,0,-0.050000001};
				orientation[]={0,-40,0};
			};
			class Melee
			{
				position[]={0,0,0.050000001};
				orientation[]={0,40,0};
			};
		};
	};	
	class M4A1_Base: Rifle_Base
	{
		class InventorySlotsOffsets
		{
			class Backpack_1
			{
				position[]={0,0.2,0};
				orientation[]={0,0,90};
			};
			class Shoulder
			{
				position[]={-0.1,0,0.029999999};
				orientation[]={0,0,0};
			};
			class Melee
			{
				position[]={-0.1,0,-0.039999999};
				orientation[]={0,0,0};
			};
		};
    };		
	class Winchester70_Base;
	class Winchester70: Winchester70_Base
	{
		class InventorySlotsOffsets
		{
			class Backpack_1
			{
				position[]={0,0.2,0};
				orientation[]={0,0,90};
			};
			class Shoulder
			{
				position[]={0,-0.02,-0.029999999};
				orientation[]={0,-30,0};
			};
			class Melee
			{
				position[]={0,-0.02,0.0099999998};
				orientation[]={0,30,0};
			};
		};
	};
	class AK101_Base: Rifle_Base
	{
		class InventorySlotsOffsets
		{
			class Backpack_1
			{
				position[]={0,0.2,0};
				orientation[]={0,0,90};
			};
			class Shoulder
			{
				position[]={0,-0.015,-0.0099999998};
				orientation[]={0,-20,0};
			};
			class Melee
			{
				position[]={0,0,0};
				orientation[]={0,10,0};
			};
		};
	};
    class AKM_Base: Rifle_Base
	{
		class InventorySlotsOffsets
		{
			class Backpack_1
			{
				position[]={0,0.2,0};
				orientation[]={0,0,90};
			};
			class Shoulder
			{
				position[]={0,0,0.1};
				orientation[]={0,45,0};
			};
			class Melee
			{
				position[]={0,0,-0.1};
				orientation[]={0,-45,0};
			};
		};
	};
	class Aug_Base: Rifle_Base
	{
		class InventorySlotsOffsets
		{
			class Backpack_1
			{
				position[]={0,0.2,0};
				orientation[]={0,0,90};
			};
			class Shoulder
			{
				position[]={-0.2,0,0};
				orientation[]={0,0,0};
			};
			class Melee
			{
				position[]={-0.15000001,0,-0.02};
				orientation[]={0,0,0};
			};
		};	
	};
	class B95_Base;
	class B95: B95_Base
	{
		class InventorySlotsOffsets
		{
			class Backpack_1
			{
				position[]={0,0.2,0};
				orientation[]={0,0,90};
			};
			class Shoulder
			{
				position[]={0,0.0099999998,-0.029999999};
				orientation[]={0,-30,0};
			};
			class Melee
			{
				position[]={0,0,0};
				orientation[]={0,30,0};
			};
		};	
	};
	class CZ61_Base: Rifle_Base
	{
		class InventorySlotsOffsets
		{
			class Backpack_1
			{
				position[]={0,0.2,0};
				orientation[]={0,0,90};
			};
			class Shoulder
			{
				position[]={-0.15000001,-0.02,0};
				orientation[]={0,0,-13};
			};
			class Melee
			{
				position[]={-0.15000001,0,-0.02};
				orientation[]={0,0,-13};
			};
		};	
	};	
	class BoltActionRifle_ExternalMagazine_Base;
	class CZ527_Base: BoltActionRifle_ExternalMagazine_Base
	{
		class InventorySlotsOffsets
		{
			class Backpack_1
			{
				position[]={0,0.2,0};
				orientation[]={0,0,90};
			};
			class Shoulder
			{
				position[]={-0.07,0,-0.07};
				orientation[]={-7,-55,5};
			};
			class Melee
			{
				position[]={-0.07,0,0.050000001};
				orientation[]={2,55,-5};
			};
		};	
	};
	class CZ550_Base: BoltActionRifle_ExternalMagazine_Base
	{
		class InventorySlotsOffsets
		{
			class Backpack_1
			{
				position[]={0,0.2,0};
				orientation[]={0,0,90};
			};
			class Shoulder
			{
				position[]={0,-0.02,-0.029999999};
				orientation[]={0,-30,0};
			};
			class Melee
			{
				position[]={0,-0.029999999,0.02};
				orientation[]={0,30,0};
			};
		};	
	};	
	class FAL_Base: Rifle_Base
	{
		class InventorySlotsOffsets
		{
			class Backpack_1
			{
				position[]={0,0.2,0};
				orientation[]={0,0,90};
			};
			class Shoulder
			{
				position[]={-0.050000001,0,0.02};
				orientation[]={0,0,0};
			};
			class Melee
			{
				position[]={-0.050000001,0,-0.050000001};
				orientation[]={0,0,0};
			};
		};
	};
	class Famas_Base: Rifle_Base
	{
		class InventorySlotsOffsets
		{
			class Backpack_1
			{
				position[]={0,0.2,0};
				orientation[]={0,0,90};
			};
			class Shoulder
			{
				position[]={-0.25,0.035,0};
				orientation[]={0,0,0};
			};
			class Melee
			{
				position[]={-0.25,0.035,-0.029999999};
				orientation[]={0,0,0};
			};
		};
	};
	class Izh18_Base;
	class Izh18: Izh18_Base
	{
		class InventorySlotsOffsets
		{
			class Backpack_1
			{
				position[]={0,0.2,0};
				orientation[]={0,0,90};
			};
			class Shoulder
			{
				position[]={-0.029999999,-0.02,0.015};
				orientation[]={0,0,0};
			};
			class Melee
			{
				position[]={-0.029999999,0,-0.039999999};
				orientation[]={0,0,0};
			};
		};
	};
	class M14_Base: Rifle_Base
	{
		class InventorySlotsOffsets
		{
			class Backpack_1
			{
				position[]={0,0.2,0};
				orientation[]={0,0,90};
			};
			class Shoulder
			{
				position[]={-0.1,0,0.029999999};
				orientation[]={0,0,0};
			};
			class Melee
			{
				position[]={-0.1,0,-0.039999999};
				orientation[]={0,0,0};
			};
		};
	};
	class BoltActionRifle_InnerMagazine_Base;
	class Mosin9130_Base: BoltActionRifle_InnerMagazine_Base
	{
		class InventorySlotsOffsets
		{
			class Backpack_1
			{
				position[]={0,0.2,0};
				orientation[]={0,0,90};
			};
			class Shoulder
			{
				position[]={0,0,-0.059999999};
				orientation[]={0,-40,0};
			};
			class Melee
			{
				position[]={0,0,0.039999999};
				orientation[]={0,40,0};
			};
		};
	};
	class MP5K_Base: Rifle_Base
	{
		class InventorySlotsOffsets
		{
			class Backpack_1
			{
				position[]={0,0.2,0};
				orientation[]={0,0,90};
			};
			class Shoulder
			{
				position[]={-0.1,0.0099999998,0};
				orientation[]={0,-8,0};
			};
			class Melee
			{
				position[]={-0.1,0.0099999998,-0.02};
				orientation[]={0,0,0};
			};
		};
	};	
	class PP19_Base: Rifle_Base
	{
		class InventorySlotsOffsets
		{
			class Backpack_1
			{
				position[]={0,0.2,0};
				orientation[]={0,0,90};
			};
			class Shoulder
			{
				position[]={-0.059999999,-0.02,0.029999999};
				orientation[]={0,15,0};
			};
			class Melee
			{
				position[]={-0.059999999,-0.02,-0.050000001};
				orientation[]={0,-15,0};
			};
		};
	};
	class Repeater_Base: Rifle_Base
	{
		class InventorySlotsOffsets
		{
			class Backpack_1
			{
				position[]={0,0.2,0};
				orientation[]={0,0,90};
			};
			class Shoulder
			{
				position[]={0,-0.029999999,0};
				orientation[]={0,0,0};
			};
			class Melee
			{
				position[]={0,-0.015,-0.02};
				orientation[]={0,0,0};
			};
		};
	};
	class Ruger1022_Base: Rifle_Base
	{
		class InventorySlotsOffsets
		{
			class Backpack_1
			{
				position[]={0,0.2,0};
				orientation[]={0,0,90};
			};
			class Shoulder
			{
				position[]={0,0,-0.035};
				orientation[]={0,-20,-4};
			};
			class Melee
			{
				position[]={0,0,0};
				orientation[]={0,20,0};
			};
		};
	};
	class Scout_Base: BoltActionRifle_ExternalMagazine_Base
	{
		class InventorySlotsOffsets
		{
			class Backpack_1
			{
				position[]={0,0.2,0};
				orientation[]={0,0,90};
			};
			class Shoulder
			{
				position[]={0,-0.02,-0.050000001};
				orientation[]={0,-30,0};
			};
			class Melee
			{
				position[]={0,0,0.050000001};
				orientation[]={0,30,0};
			};
		};
	};
	class SSG82_Base: BoltActionRifle_ExternalMagazine_Base
	{
		class InventorySlotsOffsets
		{
			class Backpack_1
			{
				position[]={0,0.2,0};
				orientation[]={0,0,90};
			};
			class Shoulder
			{
				position[]={0.02,-0.02,-0.02};
				orientation[]={0,-30,0};
			};
			class Melee
			{
				position[]={0.02,0,0.0099999998};
				orientation[]={0,30,0};
			};
		};
	};
	class SV98_Base: BoltActionRifle_ExternalMagazine_Base
	{
		class InventorySlotsOffsets
		{
			class Backpack_1
			{
				position[]={0,0.2,0};
				orientation[]={0,0,90};
			};
			class Shoulder
			{
				position[]={0.02,-0.02,-0.02};
				orientation[]={0,-30,0};
			};
			class Melee
			{
				position[]={0.02,0,0.0099999998};
				orientation[]={0,30,0};
			};
		};
	};
	class SVD_Base: Rifle_Base
	{
		class InventorySlotsOffsets
		{
			class Backpack_1
			{
				position[]={0,0.2,0};
				orientation[]={0,0,90};
			};
			class Shoulder
			{
				position[]={0,-0.02,-0.02};
				orientation[]={0,-30,0};
			};
			class Melee
			{
				position[]={0,-0.02,0};
				orientation[]={0,30,0};
			};
		};
	};
	class UMP45_Base: Rifle_Base
	{
		class InventorySlotsOffsets
		{
			class Backpack_1
			{
				position[]={0,0.2,0};
				orientation[]={0,0,90};
			};
			class Shoulder
			{
				position[]={-0.1,0.0099999998,0};
				orientation[]={0,-8,0};
			};
			class Melee
			{
				position[]={-0.1,0.0099999998,-0.050000001};
				orientation[]={0,0,0};
			};
		};
	};
	class VSS_Base: Rifle_Base
	{
		class InventorySlotsOffsets
		{
			class Backpack_1
			{
				position[]={0,0.2,0};
				orientation[]={0,0,90};
			};
			class Shoulder
			{
				position[]={-0.1,0,0};
				orientation[]={0,-17,0};
			};
			class Melee
			{
				position[]={-0.1,-0.0099999998,0};
				orientation[]={0,20,0};
			};
		};
	};
	class Shotgun_Base;
	class Izh43Shotgun_Base: Shotgun_Base
	{
		class InventorySlotsOffsets
		{
			class Backpack_1
			{
				position[]={0,0.2,0};
				orientation[]={0,0,90};
			};
			class Shoulder
			{
				position[]={-0.029999999,0,0.0099999998};
				orientation[]={0,0,0};
			};
			class Melee
			{
				position[]={-0.029999999,0,-0.029999999};
				orientation[]={0,0,0};
			};
		};
	};
	class Mp133Shotgun_Base: Shotgun_Base
	{
		class InventorySlotsOffsets
		{
			class Backpack_1
			{
				position[]={0,0.2,0};
				orientation[]={0,0,90};
			};
			class Shoulder
			{
				position[]={-0.029999999,-0.0099999998,0.0099999998};
				orientation[]={0,0,0};
			};
			class Melee
			{
				position[]={-0.029999999,0,-0.029999999};
				orientation[]={0,0,0};
			};
		};
	};	
	class R12_Base: Shotgun_Base
	{
		class InventorySlotsOffsets
		{
			class Backpack_1
			{
				position[]={0,0.2,0};
				orientation[]={0,0,90};
			};
			class Shoulder
			{
				position[]={-0.029999999,-0.0099999998,0.0099999998};
				orientation[]={0,0,0};
			};
			class Melee
			{
				position[]={-0.029999999,0,-0.029999999};
				orientation[]={0,0,0};
			};
		};
	};
	class Saiga_Base: Rifle_Base
	{
		class InventorySlotsOffsets
		{
			class Backpack_1
			{
				position[]={0,0.2,0};
				orientation[]={0,0,90};
			};
			class Shoulder
			{
				position[]={-0.02,0.029999999,0.1};
				orientation[]={0,60,0};
			};
			class Melee
			{
				position[]={-0.02,0.02,-0.12};
				orientation[]={0,-60,0};
			};
		};
	};		
};

class CfgVehicles
{
	class Clothing;
	class SlingBag_ColorBase: Clothing
	{
		attachments[]=
		{
			"WalkieTalkie",
		};
	};	
	class ChildBag_ColorBase: Clothing
	{
		attachments[]=
		{
			"Chemlight",
			"WalkieTalkie"
		};
	};	
	class LeatherSack_ColorBase: Clothing
	{
		attachments[]=
		{
			"Chemlight",
			"WalkieTalkie"
		};
	};	
	class ArmyPouch_ColorBase: Clothing
	{
		attachments[]=
		{
			"Chemlight",
			"WalkieTalkie"
		};
	};	
	class DuffelBagSmall_ColorBase: Clothing
	{
		attachments[]=
		{
			"Chemlight",
			"WalkieTalkie"
		};
	};	
	class CanvasBag_ColorBase: Clothing
	{
		attachments[]=
		{
			"Chemlight",
			"WalkieTalkie"
		};
	};	
	class Inventory_Base;
	class WoodAxe: Inventory_Base
	{
		inventorySlot[]=
		{
			"Shoulder",
			"Melee",
			"Backpack_1"
		};
		class InventorySlotsOffsets
		{
			class Backpack_1
			{
				position[]={0,0.5,0};
				orientation[]={90,0,180};
			};
		};	
	};
	class FirefighterAxe: Inventory_Base
	{
		inventorySlot[]=
		{
			"Shoulder",
			"Melee",
			"Backpack_1"
		};
		class InventorySlotsOffsets
		{
			class Backpack_1
			{
				position[]={0,0.5,0};
				orientation[]={90,0,180};
			};
		};	
	};
	class Pitchfork: Inventory_Base
	{
		inventorySlot[]=
		{
			"Shoulder",
			"Melee",
			"Backpack_1"
		};
		class InventorySlotsOffsets
		{
			class Backpack_1
			{
				position[]={0,0.5,0};
				orientation[]={90,0,180};
			};
		};	
	};	
	class Pickaxe: Inventory_Base
	{		
		inventorySlot[]=
		{
			"Shoulder",
			"Melee",
			"Backpack_1"
		};
		class InventorySlotsOffsets
		{
			class Backpack_1
			{
				position[]={0,0.5,0};
				orientation[]={90,0,180};
			};
		};	
	};	
	class Sword: Inventory_Base
	{
		inventorySlot[]=
		{
			"Shoulder",
			"Melee",
			"Backpack_1"
		};
		class InventorySlotsOffsets
		{
			class Backpack_1
			{
				position[]={0,0.5,0};
				orientation[]={90,0,180};
			};
		};	
	};	
	class BaseballBat: Inventory_Base
	{
		inventorySlot[]=
		{
			"Shoulder",
			"Melee",
			"Backpack_1"
		};
		class InventorySlotsOffsets
		{
			class Backpack_1
			{
				position[]={0,0.5,0};
				orientation[]={90,0,180};
			};
		};	
	};	
	class NailedBaseballBat: Inventory_Base
	{
		inventorySlot[]=
		{
			"Shoulder",
			"Melee",
			"Backpack_1"
		};
		class InventorySlotsOffsets
		{
			class Backpack_1
			{
				position[]={0,0.5,0};
				orientation[]={90,0,180};
			};
		};	
	};	
	class BarbedBaseballBat: Inventory_Base
	{
		inventorySlot[]=
		{
			"Shoulder",
			"Melee",
			"Backpack_1"
		};
		class InventorySlotsOffsets
		{
			class Backpack_1
			{
				position[]={0,0.5,0};
				orientation[]={90,0,180};
			};
		};	
	};	
	class XmasBaseballBat: Inventory_Base
	{
		inventorySlot[]=
		{
			"Shoulder",
			"Melee",
			"Backpack_1"
		};
		class InventorySlotsOffsets
		{
			class Backpack_1
			{
				position[]={0,0.5,0};
				orientation[]={90,0,180};
			};
		};	
	};	
	class TelescopicBaton: Inventory_Base
	{
		inventorySlot[]=
		{
			"Shoulder",
			"Melee",
			"Backpack_1"
		};
		class InventorySlotsOffsets
		{
			class Backpack_1
			{
				position[]={0,0.5,0};
				orientation[]={90,0,180};
			};
		};	
	};	
	class HockeyStick: Inventory_Base
	{
		inventorySlot[]=
		{
			"Shoulder",
			"Melee",
			"Backpack_1"
		};
		class InventorySlotsOffsets
		{
			class Backpack_1
			{
				position[]={0,0.5,0};
				orientation[]={90,0,180};
			};
		};	
	};	
	class NewHockeyStick: Inventory_Base
	{
		inventorySlot[]=
		{
			"Shoulder",
			"Melee",
			"Backpack_1"
		};
		class InventorySlotsOffsets
		{
			class Backpack_1
			{
				position[]={0,0.5,0};
				orientation[]={90,0,180};
			};
		};	
	};	
	class PoliceBaton: Inventory_Base
	{
		inventorySlot[]=
		{
			"Shoulder",
			"Melee",
			"Backpack_1"
		};
		class InventorySlotsOffsets
		{
			class Backpack_1
			{
				position[]={0,0.5,0};
				orientation[]={90,0,180};
			};
		};	
	};	
};	