class CfgPatches
{
	class RuckCarryHeavy
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
	class RuckCarryHeavy
	{
		dir="RuckCarryHeavy";
		picture="";
		action="";
		hideName=1;
		hidePicture=1;
		name="Ruck Carry Test";
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
					"RuckCarryHeavy\scripts\4_World"
				};
			};
		};
	};
};
