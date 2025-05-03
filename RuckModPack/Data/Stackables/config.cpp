class CfgPatches
{
	class RuckModPack_Stackables
	{
		requiredAddons[]=
		{
			"DZ_Data",
			"DZ_Gear_Consumables",
			"DZ_Gear_Crafting",
			"DZ_Gear_Medical"
		};
	};
};

class CfgVehicles
{
	class Inventory_Base;
	class Paper: Inventory_Base
	{
		varStackMax=10;
		canBeSplit=1;
	};
	class Firewood: Inventory_Base
	{
		varStackMax=5;
		canBeSplit=1;
	};
	class WoodenStick: Inventory_Base
	{
		varStackMax=10;
		canBeSplit=1;
	};	
};