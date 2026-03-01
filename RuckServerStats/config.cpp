class CfgPatches
{
	class RuckServerStats
	{
		requiredVersion=1.0;
		requiredAddons[]=
		{
			"DZ_Data",
			"DZ_Scripts"
		};
	};
};

class CfgMods
{
	class RuckServerStats
	{
		dir="RuckServerStats";
		name="Server Stats";
		credits=""; 
		author="BuffaGunz";
		version="1.0";
		extra=0;
		type="Mod";
		inputs="";
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
                value = "";
                files[] = 
				{
					"RuckServerStats/Scripts/3_Game"
				};
            };
            class worldScriptModule
            {
                value = "";
                files[] = 
				{
					"RuckServerStats/Scripts/4_World"
				};
            };
			class missionScriptModule
            {
                value = "";
                files[] = 
				{
					"RuckServerStats/Scripts/5_Mission"
				};
            };
		};	
	};
};

