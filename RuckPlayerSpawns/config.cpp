class CfgPatches
{
	class RuckPlayerSpawns
	{
		units[]=
		{
		};
		weapons[]={};
		requiredVersion=1.0;
		requiredAddons[]=
		{
			"DZ_Scripts",
			"DZ_Data"
		};
	};
};
class CfgMods
{
	class RuckPlayerSpawns
	{
		dir="RuckPlayerSpawns";
		picture="";
		action="";
		hideName=1;
		hidePicture=1;
		name="Ruck Mod Pack";
		credits="";
		author="BuffaGunz";
		authorID="0";
		version="1.0";
		extra=0;
		type="mod";
		inputs = "";
		dependencies[]=
		{
			"Game",
			"World",
			"Mission"
		};
		class defs
		{
			class gameScriptModule
			{
				value="";
				files[]=
				{
					"RuckPlayerSpawns\scripts\3_Game"
				};
			};
			class worldScriptModule
			{
				value="";
				files[]=
				{
					"RuckPlayerSpawns\scripts\4_World"
				};
			};
			class missionScriptModule
			{
				value="";
				files[]=
				{
					"RuckPlayerSpawns\scripts\5_Mission"
				};
			};
		};
	};
};
