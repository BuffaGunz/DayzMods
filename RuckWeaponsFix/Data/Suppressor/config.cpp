class CfgPatches
{
	class RuckWeaponsFix_Suppressor
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data",
		"DZ_Weapons_Muzzles"
		};
	};
};
class cfgVehicles
{
	class Inventory_Base;
	class ItemSuppressor: Inventory_Base
	{
		scope=0;
		debug_ItemCategory=3;
		inventorySlot[]=
		{
			"weaponMuzzle"
		};
		simulation="ItemSuppressor";
		itemSize[]={1,1};
		selectionFireAnim="zasleh";
		soundIndex=1;
		repairableWithKits[]={1};
		repairCosts[]={25};
		muzzlePos="usti hlavne";
		barrelArmor=3000;
		recoilModifier[]={1,1,1};
		swayModifier[]={1,1,1};
		isMeleeWeapon=1;
		soundImpactType="metal";
	};
	class M4_Suppressor: ItemSuppressor
	{
		inventorySlot[]=
		{
			"weaponMuzzleM4",
			"suppressorImpro"
		};
	};
	class AK_Suppressor: ItemSuppressor
	{
		inventorySlot[]=
		{
			"weaponMuzzleAK",
			"suppressorImpro"
		};
	};	
};	