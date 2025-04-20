class CfgPatches
{
	class RuckVan
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
	class RuckVan
	{
		dir="RuckVan";
		picture="";
		action="";
		hideName=1;
		hidePicture=1;
		name="Ruck Van";
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
					"RuckVan\scripts\4_World"
				};
			};
		};
	};
};