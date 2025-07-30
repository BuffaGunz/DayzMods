class CfgPatches
{
	class RuckCarScripts
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]={
			"DZ_Data"
		};
	};
};

class CfgMods
{
	class RuckCarScripts
	{
		dir="RuckCarScripts";
		picture="";
		action="";
		hideName=1;
		hidePicture=1;
		name="Ruck Car Scripts";
		credits="";
		author="BuffaGunz";
		authorID="";
		version="0.1";
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
					"RuckCarScripts\GUI\ImageSet\RuckCarAttachments.imageset",
				};
			};
		};	
	};
};