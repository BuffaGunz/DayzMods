class CfgPatches
{
	class CarHit
	{
		units[] = {"InvisibleFireplace"};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Scripts",
			"DZ_Data",
			"DZ_Gear_Camping"
		};
	};
};

class CfgMods
{
	class CarHit
	{
		dir="CarHit";
		picture="";
		action="";
		hideName=1;
		hidePicture=1;
		name="Ruck Mod Pack";
		credits="";
		author="BuffaGunz";
		authorID="0";
		version="0.1";
		extra=0;
		type="mod";
		inputs = "";
		dependencies[] = {"World"};

		class defs
		{
			class worldScriptModule
			{
				files[] = {"CarHit/scripts/4_World"};
			};
		};
	};
};

class CfgVehicles
{
    class Bonfire;
	class InvisibleFireplace: Bonfire
	{
		scope = 2;
		displayName = "";
		descriptionShort = "";
		model = "\CarHit\data\CarFire.p3d";
		hiddenSelections[] = {};
		hiddenSelectionsTextures[] = {};
		hiddenSelectionsMaterials[] = {};
	};
};