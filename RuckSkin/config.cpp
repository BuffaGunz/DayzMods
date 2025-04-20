class CfgPatches
{
	class RuckSkin
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
	class RuckSkin
	{
		dir="RuckSkin";
		picture="";
		action="";
		hideName=1;
		hidePicture=1;
		name="Ruck Skin";
		credits="";
		author="BuffaGunz";
		authorID="0";
		version="0.1";
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
					"RuckLootSkinSplat\scripts\4_World"
				};
			};
		};
	};
};