class CfgPatches
{
	class AussieBeers
	{
		units[]=
		{
			"XXXXCan",
			"VBCan",
			"CCDryCan",
			"HahnCan",
			"BundyCan",
			"NorthernCan",
			"FostersCan"
		};
		weapons[]={};
		requiredVersion=1.0;
		requiredAddons[]=
		{
			"DZ_Data",
			"DZ_Gear_Drinks"
		};
	};
};

class CfgMods
{
	class AussieBeers
	{
		dir="AussieBeers";
		name="Aussie Beers";
		credits=""; 
		author="BuffaGunz";
		version="1.0";
		extra=0;
		type="Mod";
		inputs="";
		dependencies[]={};
		class defs {};	
	};
};

class cfgVehicles
{
	class SodaCan_ColorBase;
	class NorthernCan: SodaCan_ColorBase
	{
		scope=2;
		displayName="Great Northern";
		descriptionShort="A light, refreshing lager brewed for easy drinking in Australia’s hot northern climate.";
		hiddenSelectionsTextures[]=
		{
			"AussieBeers\Data\GreatNorthern.paa"
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class SodaCan_in_B
				{
					soundSet="SodaCan_in_B_SoundSet";
					id=202;
				};
				class PondBottle_loop
				{
					soundSet="PondBottle_loop_SoundSet";
					id=209;
				};
				class WellBottle_loop
				{
					soundSet="WellBottle_loop_SoundSet";
					id=210;
				};
				class pickup
				{
					soundSet="SodaCan_pickup_SoundSet";
					id=797;
				};
				class drop
				{
					soundset="SodaCan_drop_SoundSet";
					id=898;
				};
			};
		};
	};
	class CCDryCan: SodaCan_ColorBase
	{
		scope=2;
		displayName="Canadian Club & Dry";
		descriptionShort="A smooth blend of Canadian Club whisky and dry ginger ale in a refreshing premix.";
		hiddenSelectionsTextures[]=
		{
			"AussieBeers\Data\CC&Dry.paa"
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class SodaCan_in_B
				{
					soundSet="SodaCan_in_B_SoundSet";
					id=202;
				};
				class PondBottle_loop
				{
					soundSet="PondBottle_loop_SoundSet";
					id=209;
				};
				class WellBottle_loop
				{
					soundSet="WellBottle_loop_SoundSet";
					id=210;
				};
				class pickup
				{
					soundSet="SodaCan_pickup_SoundSet";
					id=797;
				};
				class drop
				{
					soundset="SodaCan_drop_SoundSet";
					id=898;
				};
			};
		};
	};
	class BundyCan: SodaCan_ColorBase
	{
		scope=2;
		displayName="Bundaberg Rum";
		descriptionShort="Bundy – The Spirit of Queensland.";
		hiddenSelectionsTextures[]=
		{
			"AussieBeers\Data\Bundy.paa"
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class SodaCan_in_B
				{
					soundSet="SodaCan_in_B_SoundSet";
					id=202;
				};
				class PondBottle_loop
				{
					soundSet="PondBottle_loop_SoundSet";
					id=209;
				};
				class WellBottle_loop
				{
					soundSet="WellBottle_loop_SoundSet";
					id=210;
				};
				class pickup
				{
					soundSet="SodaCan_pickup_SoundSet";
					id=797;
				};
				class drop
				{
					soundset="SodaCan_drop_SoundSet";
					id=898;
				};
			};
		};
	};
	class HahnCan: SodaCan_ColorBase
	{
		scope=2;
		displayName="Hahn SuperDry";
		descriptionShort="A clean, super crisp Australian lager brewed longer to create a dry finish and lower carb content";
		hiddenSelectionsTextures[]=
		{
			"AussieBeers\Data\Hahn.paa"
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class SodaCan_in_B
				{
					soundSet="SodaCan_in_B_SoundSet";
					id=202;
				};
				class PondBottle_loop
				{
					soundSet="PondBottle_loop_SoundSet";
					id=209;
				};
				class WellBottle_loop
				{
					soundSet="WellBottle_loop_SoundSet";
					id=210;
				};
				class pickup
				{
					soundSet="SodaCan_pickup_SoundSet";
					id=797;
				};
				class drop
				{
					soundset="SodaCan_drop_SoundSet";
					id=898;
				};
			};
		};
	};
	class FostersCan: SodaCan_ColorBase
	{
		scope=2;
		displayName="Fosters Lager";
		descriptionShort="Foster’s – Australian for Beer";
		hiddenSelectionsTextures[]=
		{
			"AussieBeers\Data\Fosters.paa"
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class SodaCan_in_B
				{
					soundSet="SodaCan_in_B_SoundSet";
					id=202;
				};
				class PondBottle_loop
				{
					soundSet="PondBottle_loop_SoundSet";
					id=209;
				};
				class WellBottle_loop
				{
					soundSet="WellBottle_loop_SoundSet";
					id=210;
				};
				class pickup
				{
					soundSet="SodaCan_pickup_SoundSet";
					id=797;
				};
				class drop
				{
					soundset="SodaCan_drop_SoundSet";
					id=898;
				};
			};
		};
	};
	class XXXXCan: SodaCan_ColorBase
	{
		scope=2;
		displayName="XXXX";
		descriptionShort="A crisp mid-strength Queensland lager brewed for easy drinking in the Australian heat";
		hiddenSelectionsTextures[]=
		{
			"AussieBeers\Data\XXXX.paa"
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class SodaCan_in_B
				{
					soundSet="SodaCan_in_B_SoundSet";
					id=202;
				};
				class PondBottle_loop
				{
					soundSet="PondBottle_loop_SoundSet";
					id=209;
				};
				class WellBottle_loop
				{
					soundSet="WellBottle_loop_SoundSet";
					id=210;
				};
				class pickup
				{
					soundSet="SodaCan_pickup_SoundSet";
					id=797;
				};
				class drop
				{
					soundset="SodaCan_drop_SoundSet";
					id=898;
				};
			};
		};
	};		
	class VBCan: SodaCan_ColorBase
	{
		scope=2;
		displayName="Vic Bitter";
		descriptionShort="A hard earned thirst needs a big cold beer, and the best cold beer is Vic Vicoria Bitter!";
		hiddenSelectionsTextures[]=
		{
			"AussieBeers\Data\VB.paa"
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class SodaCan_in_B
				{
					soundSet="SodaCan_in_B_SoundSet";
					id=202;
				};
				class PondBottle_loop
				{
					soundSet="PondBottle_loop_SoundSet";
					id=209;
				};
				class WellBottle_loop
				{
					soundSet="WellBottle_loop_SoundSet";
					id=210;
				};
				class pickup
				{
					soundSet="SodaCan_pickup_SoundSet";
					id=797;
				};
				class drop
				{
					soundset="SodaCan_drop_SoundSet";
					id=898;
				};
			};
		};
	};
};
