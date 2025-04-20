class CfgPatches
{
	class RuckLoot
	{
		units[]=
		{
		};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Scripts",
			"DZ_Data"
		};
	};
};
class CfgMods
{
	class RuckLoot
	{
		dir="RuckLoot";
		picture="";
		action="";
		hideName=1;
		hidePicture=1;
		name="Ruck Loot";
		credits="";
		author="BuffaGunz";
		authorID="0";
		version="0.1";
		extra=0;
		type="mod";
		dependencies[]=
		{
			"World",
			"Mission"
		};
		class defs
		{
			class worldScriptModule
			{
				value="";
				files[]=
				{
					"RuckLoot\scripts\4_World"
				};
			};
			class missionScriptModule
			{
				value="";
				files[]=
				{
					"RuckLoot\scripts\5_Mission"
				};
			};
		};
	};
};