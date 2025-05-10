class CfgPatches
{
	class RuckloadscreenBitterroot
	{
		units[]={};
		weapons[]={};
		requiredVersion=1;
		requiredAddons[]=
		{
			"DZ_Data",
			"DZ_Scripts",
			"BitterRootLoadingScreen"
		};
	};
};
class CfgMods
{
	class RuckloadscreenBitterroot
	{
		dir="RuckloadscreenBitterroot";
		picture="";
		action="";
		hideName=1;
		hidePicture=1;
		name="RuckloadscreenBitterroot";
		author="BuffaGunz";
		version="1.0";
		extra=0;
		type="mod";
		dependencies[]=
		{
			"Game"
		};
		class defs
		{
			class gameScriptModule
			{
				value="";
				files[]=
				{
					"RuckloadscreenBitterroot/scripts/3_Game"
				};
			};
			class missionScriptModule
			{
				value = "";
				files[] = 
				{
					"RuckloadscreenBitterroot/scripts/5_Mission" 
				};
			};
		};
	};
};
