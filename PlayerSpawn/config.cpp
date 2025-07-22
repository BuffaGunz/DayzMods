class CfgPatches
{
	class PlayerSpawn
	{
		units[]={};
		weapons[]={};
		requiredVersion=1;
		requiredAddons[]=
		{
			"DZ_Data",
			"DZ_Scripts"
		};
	};
};
class CfgMods
{
	class PlayerSpawn
	{
		dir="PlayerSpawn";
		picture="";
		action="";
		hideName=1;
		hidePicture=1;
		name="PlayerSpawn";
		author="BuffaGunz";
		version="1.0";
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
				value = "";
				files[] = 
				{
					"PlayerSpawn/scripts/4_World" 
				};
			};
		};
	};
};
