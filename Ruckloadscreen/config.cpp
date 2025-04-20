class CfgPatches
{
	class Loadingscreen
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
	class Loadingscreen
	{
		dir="Loadingscreen";
		picture="";
		action="";
		hideName=1;
		hidePicture=1;
		name="Loadingscreen";
		credits="BuffaGunz";
		author="BuffaGunz";
		authorID="0";
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
					"Ruckloadscreen/scripts/3_Game"
				};
			};
			class missionScriptModule
			{
				value = "";
				files[] = 
				{
					"Ruckloadscreen/scripts/5_Mission" 
				};
			};
		};
	};
};
