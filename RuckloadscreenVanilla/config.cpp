class CfgPatches
{
	class RuckloadscreenVanilla
	{
		units[]={};
		weapons[]={};
		requiredVersion=1;
		requiredAddons[]=
		{
			"DZ_Data",
			"DZ_Scripts",
			"DZ_Gear_Consumables",
			"DZ_Vehicles_Wheeled",
			"DZ_Structures_Residential",
			"DZ_Sounds_Effects",
			"DZ_Sounds_Weapons"
		};
	};
};
class CfgMods
{
	class RuckloadscreenVanilla
	{
		dir="RuckloadscreenVanilla";
		picture="";
		action="";
		hideName=1;
		hidePicture=1;
		name="RuckloadscreenVanilla";
		author="BuffaGunz";
		version="1.0";
		extra=0;
		type="mod";
		dependencies[]=
		{
			"Game",
			"World",
			"Mission"
		};
		class defs
		{
			class imageSets
			{
				files[]=
				{
					"RuckloadscreenVanilla\gui\data\RuckLogo.imageset"
				};
			};
			class gameScriptModule
			{
				value="";
				files[]=
				{
					"RuckloadscreenVanilla/scripts/3_Game"
				};
			};
			class worldScriptModule
			{
				value = "";
				files[] = 
				{
					"RuckloadscreenVanilla/scripts/4_World" 
				};
			};
			class missionScriptModule
			{
				value = "";
				files[] = 
				{
					"RuckloadscreenVanilla/scripts/5_Mission" 
				};
			};
		};
	};
};
