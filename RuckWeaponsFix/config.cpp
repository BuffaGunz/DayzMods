class CfgPatches
{
	class RuckWeaponsFix
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]={
			"DZ_Data"
		};
	};
};

class CfgMods
{
	class RuckWeaponsFix
	{
		dir="RuckWeaponsFix";
		picture="";
		action="";
		hideName=1;
		hidePicture=1;
		name="Ruck Weapons Fix";
		credits="";
		author="BuffaGunz";
		authorID="";
		version="0.3";
		extra=0;
		type="mod";
		dependencies[]=
		{
			"World"
		};
		class defs
		{
			class worldScriptModule
			{
				value="";
				files[]=
				{
					"RuckWeaponsFix\scripts\4_World"
				};
			};
		};
	};
};