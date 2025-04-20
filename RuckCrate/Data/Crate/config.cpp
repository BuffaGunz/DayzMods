class CfgPatches
{
	class RuckCrate_Crate
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data","DZ_Gear_Camping"};
	};
};
class CfgVehicles
{
class Container_Base;
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
};	