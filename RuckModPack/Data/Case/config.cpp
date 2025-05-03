class CfgPatches
{
	class RuckModPack_Case
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] =
		{
			"DZ_Data",
			"DZ_Gear_Containers",
			"DZ_Gear_Medical",
			"DZ_Gear_Drinks",
			"DZ_Gear_Camping"
		};
	};
};

class CfgSlots
{
	class Slot_Purifier
	{
		name="Purifier";
		displayName="Water Purification";
		ghostIcon="";
	};
};	
	
class CfgVehicles
{
    class Container_Base;
    class SmallProtectorCase: Container_Base
	{
		attachments[]=
		{
			"Body",
			"Gloves",
			"Headgear",
			"Mask",
			"Legs",
			"Feet"
		};
	};
	class FirstAidKit: Container_Base
	{
		itemsCargoSize[]={5,5};
		inventorySlot[]=
		{
			"Belt_Left",
			"Backpack_1"
		};
		attachments[]=
		{
			"MedicalBandage",
			"Disinfectant"
		};
	};	
	class WoodenCrate: Container_Base
	{
		attachments[]=
		{
			"Body",
			"Gloves",
			"Headgear",
			"Mask",
			"Legs",
			"Feet",
			"Shoulder",
			"Shoulder",
			"Back",
			"Vest"
		};
	};	
	class SeaChest: Container_Base
	{
		attachments[]=
		{
			"Body",
			"Gloves",
			"Headgear",
			"Mask",
			"Legs",
			"Feet",
			"Shoulder",
			"Shoulder",
			"Back",
			"Vest"
		};
	};	
	class Bottle_Base;
	class Canteen: Bottle_Base
	{
		attachments[]=
		{
			"Purifier"
		};
	};
	class Edible_Base;
	class PurificationTablets: Edible_Base
	{
		inventorySlot[]=
		{
			"Purifier"
		};
	};
	class ChelatingTablets: Edible_Base
	{
		inventorySlot[]=
		{
			"Purifier"
		};
	};
};	