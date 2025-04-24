class CfgPatches
{
	class RuckModPack_Ai
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data",
			"DZ_data_aiconfigs"
		};
	};
};

class AIParams
{
	class AgentTeams
	{
		class Predator
		{
			friends[]=
			{
				"Predator"
			};
		};
		class Zombies
		{
			friends[]=
			{
				"Zombies"
			};
		};
	};
};
