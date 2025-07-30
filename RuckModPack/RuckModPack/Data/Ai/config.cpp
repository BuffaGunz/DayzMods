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

class PathGraphFilters
{
	class ZombieCalm
	{
		class Flags
		{
			include[]=
			{
				"walk",
				"door",
				"inside"
			};
			exclude[]=
			{
				"disabled",
				"swim",
				"swimsea",
				"jump",
				"climb",
				"crawl",
				"crouch"
			};
		};
		class Costs
		{
			building=5;
		};
	};
	class ZombieAlerted
	{
		class Flags
		{
			include[]=
			{
				"walk",
				"door",
				"inside",
				"jump",
				"swimsea",
				"climb"
			};
			exclude[]=
			{
				"disabled",
				"crawl",
				"crouch"
			};
		};
		class Costs
		{
			jump0=3;
			jump1=0;
			jump2=0;
			jump3=0;
			jump4=0;
			water=5;
		};
	};
};	