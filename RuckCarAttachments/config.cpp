class CfgPatches
{
	class RuckCarAttachments
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
	class RuckCarAttachments
	{
		dir="RuckCarAttachments";
		picture="";
		action="";
		hideName=1;
		hidePicture=1;
		name="Ruck Car Attachments";
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
					"RuckCarAttachments\GUI\ImageSet\RuckCarAttachments.imageset",
				};
			};
		};	
	};
};