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
	class Paper : Inventory_Base
	{
		canBeSplit = 1;
		varQuantityInit = 1;
		varQuantityMin = 0;
		varQuantityMax = 5;
		varStackMax = 5;
		varQuantityDestroyOnMin = 1;
	};
	class PunchedCard : Paper
	{
		canBeSplit = 0;
		varQuantityInit = 1;
		varQuantityMin = 0;
		varQuantityMax = 1;
		varStackMax = 1;
		varQuantityDestroyOnMin = 1;
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