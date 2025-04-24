class CfgPatches
{
	class RuckModPack
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
	class RuckModPack
	{
		dir="RuckModPack";
		picture="";
		action="";
		hideName=1;
		hidePicture=1;
		name="Ruck Mod Pack";
		credits="";
		author="BuffaGunz";
		authorID="0";
		version="0.3";
		extra=0;
		type="mod";
		dependencies[]=
		{
			"Game",
			"World",
			"Mission"
		};
		inputs="RuckModPack\Data\RuckBudz\data\inputs.xml";
		class defs
		{
			class gameScriptModule
			{
				value="";
				files[]=
				{
					"RuckModPack\scripts\3_Game"
				};
			};
			class worldScriptModule
			{
				value="";
				files[]=
				{
					"RuckModPack\scripts\4_World"
				};
			};
			class missionScriptModule
			{
				value="";
				files[]=
				{
					"RuckModPack\scripts\5_Mission"
				};
			};
		};
	};
};
