class CfgPatches
{
	class RuckMelee
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]={
			"DZ_Data",
			"DZ_Scripts"
		};
	};
};

class CfgMods
{
	class RuckMelee
	{
		dir="RuckMelee";
		picture="";
		action="";
		hideName=1;
		hidePicture=1;
		name="Ruck Melee";
		credits="";
		author="BuffaGunz";
		authorID="";
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
					"RuckMelee\scripts\4_World"
				};
			};
		};	
	};
};