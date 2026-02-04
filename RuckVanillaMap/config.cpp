class CfgPatches
{
	class RuckVanillaMap
	{
		requiredVersion=1.0;
		requiredAddons[]=
		{
			"DZ_Worlds_Chernarusplus_World",
			"DZ_Worlds_Sakhal",
			"DZ_Data_Sakhal",
			"DZ_Data_Bliss",
			"DZ_Gear_Navigation",
			"DZ_Data",
			"DZ_Scripts"
		};
	};
};
class CfgMods
{
	class RuckVanillaMap
	{
		dir="RuckVanillaMap";
		name="Ruck Map Menu";
		credits="DaemonForge"; // Looked at his basic map code for ideas of how to create markers and .layout creations etc.
		author="BuffaGunz";
		version="1.0";
		extra=0;
		type="Mod";
		inputs="RuckVanillaMap/data/Inputs.xml";
		dependencies[]=
		{
			"Game",
			"World",
			"Mission"
		};
		class defs
        {
			class engineScriptModule
			{
				files[]=
				{
					"RuckVanillaMap/Scripts/Common"
				};
			};
			class gameLibScriptModule
			{
				files[]=
				{
					"RuckVanillaMap/Scripts/Common"
				};
			};
            class gameScriptModule
            {
                value = "";
                files[] = 
				{
					"RuckVanillaMap/Scripts/Common",
					"RuckVanillaMap/Scripts/3_Game"
				};
            };
            class worldScriptModule
            {
                value = "";
                files[] = 
				{
					"RuckVanillaMap/Scripts/Common",
					"RuckVanillaMap/Scripts/4_World"
				};
            };
			class missionScriptModule
            {
                value = "";
                files[] = 
				{
					"RuckVanillaMap/Scripts/Common",
					"RuckVanillaMap/Scripts/5_Mission"
				};
            };
		};	
	};
};

class MapDefaults
{
	maxSatelliteAlpha=1;
	maxUserMapAlpha=0;
	alphaFadeStartScale = 2;
	alphaFadeEndScale = 2;
	alphaUserMapFadeStartScale=1;
	alphaUserMapFadeEndScale=1;
	ptsPerSquareObj = 8; // Makes icons appear when further zoomed out the 1 is basically always show i think vanilla was 15 
	colorSea[]={0.18, 0.37, 0.36, 1}; // More of a green to match isurvive style sat map
	colorForest[]={0,0,0,0};     
	colorForestBorder[]={0,0,0,0};    
	colorCountlines[]={0,0,0,0};
	colorMainCountlines[]={0,0,0,0};
	colorTracks[]={0.6, 0.35, 0.15, 1};
	colorRoads[]={0.5, 0.5, 0.5, 1};
	colorMainRoads[]={0.2, 0.2, 0.2, 1};
	colorTracksFill[]={0.8, 0.5, 0.25, 1]};
	colorRoadsFill[]={0.6, 0.6, 0.6, 1};
	colorMainRoadsFill[]={0.3, 0.3, 0.3, 1};
	class Bush
	{
		icon="\dz\gear\navigation\data\map_bush_ca.paa";
		color[]={0,0,0,0};
		size=14;
		importance="6 * 20 * 0.05";    
		coefMin = 1;                 
		coefMax = 2;
	};
	class SmallTree
	{
		icon="\dz\gear\navigation\data\map_smalltree_ca.paa";
		color[]={0,0,0,0};
		size=12;
		importance="6 * 20 * 0.05";    
		coefMin = 1;                 
		coefMax = 2;
	};
	class Tree
	{
		icon="\dz\gear\navigation\data\map_tree_ca.paa";
		color[]={0,0,0,0};
		size=12;
		importance="6 * 20 * 0.05";    
		coefMin = 1;                 
		coefMax = 2;
	};
	class BusStop
	{
		icon="\RuckVanillaMap\Icons\Bus.paa";
		color[]={0.15000001,0.25999999,0.87,1};
		size=10;
		importance="6 * 20 * 0.05";    
		coefMin = 1;                 
		coefMax = 2;
	};
	class Fountain
	{
		icon="\RuckVanillaMap\Icons\Fountain.paa";
		color[]={0.2,0.44999999,0.69999999,1};
		size=20;
		importance="6 * 20 * 0.05";    
		coefMin = 1;                 
		coefMax = 2;
	};
	class Tourism
	{
		icon="\RuckVanillaMap\Icons\Beer.paa";
		color[]={1,1,1,1};
		size=20;
		importance="6 * 20 * 0.05";    
		coefMin = 1;                 
		coefMax = 2;
	};
	class Fuelstation
	{
		icon="\RuckVanillaMap\Icons\Fuel.paa";
		color[] = {1, 1, 1, 1};
		size=20;
		importance="6 * 20 * 0.05";    
		coefMin = 1;                 
		coefMax = 2;
	};
	class Lighthouse
	{
		icon="\RuckVanillaMap\Icons\Lighthouse.paa";
		color[] = {1, 0.3, 0.6, 1};
		size=20;
		importance="6 * 20 * 0.05";    
		coefMin = 1;                 
		coefMax = 4;
	};
	class Waterpump
	{
		icon="\RuckVanillaMap\Icons\Well.paa";
		color[] = {0, 0.4, 1, 1};
		size=20;
		importance="6 * 20 * 0.05";    
		coefMin = 1;                 
		coefMax = 1;
	};
	class Hospital
	{
		icon="\RuckVanillaMap\Icons\Hospital.paa";
		color[] = {0, 0.8, 0.2, 1};
		size=20;
		importance="6 * 20 * 0.05";    
		coefMin = 1;                 
		coefMax = 2;
	};
	class Police
	{
		icon="\RuckVanillaMap\Icons\Police.paa";
		color[] = {1, 0.75, 0.2, 1};
		size=20;
		importance="6 * 20 * 0.05";    
		coefMin = 1;                 
		coefMax = 2;
	};
	class FireDep
	{
		icon="\RuckVanillaMap\Icons\Firefighter.paa";
		color[] = {1, 0, 0, 1};
		size=20;
		importance="6 * 20 * 0.05";    
		coefMin = 1;                 
		coefMax = 2;
	};
	class TouristSign
	{
		icon="\RuckVanillaMap\Icons\Map.paa";
		color[] = {0.0, 0.35, 0.1, 1};
		size=20;
		importance="6 * 20 * 0.05";    
		coefMin = 1;                 
		coefMax = 2;
	};
	class Church
	{
		icon = "\RuckVanillaMap\Icons\Church.paa";
		color[] = {1, 0.75, 0.2, 1};
		size=20;
		importance="6 * 20 * 0.05";    
		coefMin = 1;                 
		coefMax = 2;
	};
	class Stack
	{
		icon="\RuckVanillaMap\Icons\SmokeTower.paa";
		size=20;
		color[]={0,0,0,1};
		importance="6 * 20 * 0.05";    
		coefMin = 0.4;      
		coefMax=2;
	};
	class Transmitter
	{
		icon="\RuckVanillaMap\Icons\RadioTower.paa";
		color[]={0.85, 0.2, 0.2, 1};
		size=20;
		importance="6 * 20 * 0.05";    
		coefMin = 1;          
		coefMax=2;
	};
	class Watertower
	{
		icon="\RuckVanillaMap\Icons\WaterTower.paa";
		color[]={0.05, 0.4, 0.6, 1};
		size=20;
		importance="6 * 20 * 0.05";    
		coefMin = 1;          
		coefMax=2;
	};
	class Shipwreck
	{
		icon="\RuckVanillaMap\Icons\ShipWreck.paa";
		color[]={1.0, 0.5, 0.0, 1};
		size=20;
		importance="6 * 20 * 0.05";    
		coefMin = 1;          
		coefMax=2;
	};
	class Monument
	{
		icon="\RuckVanillaMap\Icons\Statue.paa";
		color[]={0.25, 0.25, 0.25, 1};
		size=20;
		importance="6 * 20 * 0.05";    
		coefMin = 1;          
		coefMax=2;
	};
	class Waterspring
	{
		icon="\RuckVanillaMap\Icons\Water.paa";
		color[]={0.1,0.30000001,0.55000001,1};
		size=20;
		importance="6 * 20 * 0.05";    
		coefMin = 1;          
		coefMax=2;
	};
	class Store
	{
		icon="\RuckVanillaMap\Icons\Shop.paa";
		color[]={0.0, 0.35, 0.55, 1};
		size=20;
		importance="6 * 20 * 0.05";    
		coefMin = 1;          
		coefMax=4;
	};
	class Chapel
	{
		icon="\RuckVanillaMap\Icons\Cross.paa";
		color[]={0,0,0,1};
		size=10;
		importance="6 * 20 * 0.05";    
		coefMin = 1;          
		coefMax=2;
	};
	class TouristShelter
	{
		icon="\RuckVanillaMap\Icons\TShelter.paa";
		color[]={0.05, 0.25, 0.12, 1};
		size=20;
		importance="6 * 20 * 0.05";    
		coefMin = 1;          
		coefMax=2;
	};
	class Quay
	{
		icon="\RuckVanillaMap\Icons\Port.paa";
		size=20;
		color[]={1,1,1,1};
		importance="6 * 20 * 0.05";    
		coefMin = 1;          
		coefMax=2;
	};
	class Bunker
	{
		icon="\RuckVanillaMap\Icons\Bunker.paa";
		color[]={0.25, 0.25, 0.25, 1};
		size=20;
		importance="6 * 20 * 0.05";    
		coefMin = 1;          
		coefMax=2;
	};
	class Fortress
	{
		icon="\RuckVanillaMap\Icons\Castle.paa";
		size=20;
		color[]={1,1,1,1};
		importance="6 * 20 * 0.05";    
		coefMin = 1;          
		coefMax=2;
	};
	class Ruin
	{
		icon="\RuckVanillaMap\Icons\Ruin.paa";
		size=20;
		color[]={0,0,0,1};
		importance="6 * 20 * 0.05";    
		coefMin = 1;          
		coefMax=2;
	};
	class ViewTower
	{
		icon="\RuckVanillaMap\Icons\ViewTower.paa";
		color[]={1,1,1,1};
		size=12;
		importance="6 * 20 * 0.05";    
		coefMin = 1;          
		coefMax=2;
	};
};

class RscMapControl: MapDefaults // Was doing this in Mapdefaults but some admintools override Rsc making my settings fail. This is just a fail safe hopefully. 
{
	maxSatelliteAlpha=1;
	maxUserMapAlpha=0;
	alphaFadeStartScale = 2;
	alphaFadeEndScale = 2;
	alphaUserMapFadeStartScale=1;
	alphaUserMapFadeEndScale=1;
	ptsPerSquareObj = 8; // Makes icons appear when further zoomed out the 1 is basically always show i think vanilla was 15 
	colorSea[]={0.18, 0.37, 0.36, 1}; // More of a green to match isurvive style sat map
	colorForest[]={0,0,0,0};     
	colorForestBorder[]={0,0,0,0};    
	colorCountlines[]={0,0,0,0};
	colorMainCountlines[]={0,0,0,0};
	colorTracks[]={0.6, 0.35, 0.15, 1};
	colorRoads[]={0.5, 0.5, 0.5, 1};
	colorMainRoads[]={0.2, 0.2, 0.2, 1};
	colorTracksFill[]={0.8, 0.5, 0.25, 1]};
	colorRoadsFill[]={0.6, 0.6, 0.6, 1};
	colorMainRoadsFill[]={0.3, 0.3, 0.3, 1};
	class Bush
	{
		icon="\dz\gear\navigation\data\map_bush_ca.paa";
		color[]={0,0,0,0};
		size=14;
		importance="6 * 20 * 0.05";    
		coefMin = 1;                 
		coefMax = 2;
	};
	class SmallTree
	{
		icon="\dz\gear\navigation\data\map_smalltree_ca.paa";
		color[]={0,0,0,0};
		size=12;
		importance="6 * 20 * 0.05";    
		coefMin = 1;                 
		coefMax = 2;
	};
	class Tree
	{
		icon="\dz\gear\navigation\data\map_tree_ca.paa";
		color[]={0,0,0,0};
		size=12;
		importance="6 * 20 * 0.05";    
		coefMin = 1;                 
		coefMax = 2;
	};
	class BusStop
	{
		icon="\RuckVanillaMap\Icons\Bus.paa";
		color[]={0.15000001,0.25999999,0.87,1};
		size=10;
		importance="6 * 20 * 0.05";    
		coefMin = 1;                 
		coefMax = 2;
	};
	class Fountain
	{
		icon="\RuckVanillaMap\Icons\Fountain.paa";
		color[]={0.2,0.44999999,0.69999999,1};
		size=20;
		importance="6 * 20 * 0.05";    
		coefMin = 1;                 
		coefMax = 2;
	};
	class Tourism
	{
		icon="\RuckVanillaMap\Icons\Beer.paa";
		color[]={1,1,1,1};
		size=20;
		importance="6 * 20 * 0.05";    
		coefMin = 1;                 
		coefMax = 2;
	};
	class Fuelstation
	{
		icon="\RuckVanillaMap\Icons\Fuel.paa";
		color[] = {1, 1, 1, 1};
		size=20;
		importance="6 * 20 * 0.05";    
		coefMin = 1;                 
		coefMax = 2;
	};
	class Lighthouse
	{
		icon="\RuckVanillaMap\Icons\Lighthouse.paa";
		color[] = {1, 0.3, 0.6, 1};
		size=20;
		importance="6 * 20 * 0.05";    
		coefMin = 1;                 
		coefMax = 4;
	};
	class Waterpump
	{
		icon="\RuckVanillaMap\Icons\Well.paa";
		color[] = {0, 0.4, 1, 1};
		size=20;
		importance="6 * 20 * 0.05";    
		coefMin = 1;                 
		coefMax = 1;
	};
	class Hospital
	{
		icon="\RuckVanillaMap\Icons\Hospital.paa";
		color[] = {0, 0.8, 0.2, 1};
		size=20;
		importance="6 * 20 * 0.05";    
		coefMin = 1;                 
		coefMax = 2;
	};
	class Police
	{
		icon="\RuckVanillaMap\Icons\Police.paa";
		color[] = {1, 0.75, 0.2, 1};
		size=20;
		importance="6 * 20 * 0.05";    
		coefMin = 1;                 
		coefMax = 2;
	};
	class FireDep
	{
		icon="\RuckVanillaMap\Icons\Firefighter.paa";
		color[] = {1, 0, 0, 1};
		size=20;
		importance="6 * 20 * 0.05";    
		coefMin = 1;                 
		coefMax = 2;
	};
	class TouristSign
	{
		icon="\RuckVanillaMap\Icons\Map.paa";
		color[] = {0.0, 0.35, 0.1, 1};
		size=20;
		importance="6 * 20 * 0.05";    
		coefMin = 1;                 
		coefMax = 2;
	};
	class Church
	{
		icon = "\RuckVanillaMap\Icons\Church.paa";
		color[] = {1, 0.75, 0.2, 1};
		size=20;
		importance="6 * 20 * 0.05";    
		coefMin = 1;                 
		coefMax = 2;
	};
	class Stack
	{
		icon="\RuckVanillaMap\Icons\SmokeTower.paa";
		size=20;
		color[]={0,0,0,1};
		importance="6 * 20 * 0.05";    
		coefMin = 0.4;      
		coefMax=2;
	};
	class Transmitter
	{
		icon="\RuckVanillaMap\Icons\RadioTower.paa";
		color[]={0.85, 0.2, 0.2, 1};
		size=20;
		importance="6 * 20 * 0.05";    
		coefMin = 1;          
		coefMax=2;
	};
	class Watertower
	{
		icon="\RuckVanillaMap\Icons\WaterTower.paa";
		color[]={0.05, 0.4, 0.6, 1};
		size=20;
		importance="6 * 20 * 0.05";    
		coefMin = 1;          
		coefMax=2;
	};
	class Shipwreck
	{
		icon="\RuckVanillaMap\Icons\ShipWreck.paa";
		color[]={1.0, 0.5, 0.0, 1};
		size=20;
		importance="6 * 20 * 0.05";    
		coefMin = 1;          
		coefMax=2;
	};
	class Monument
	{
		icon="\RuckVanillaMap\Icons\Statue.paa";
		color[]={0.25, 0.25, 0.25, 1};
		size=20;
		importance="6 * 20 * 0.05";    
		coefMin = 1;          
		coefMax=2;
	};
	class Waterspring
	{
		icon="\RuckVanillaMap\Icons\Water.paa";
		color[]={0.1,0.30000001,0.55000001,1};
		size=20;
		importance="6 * 20 * 0.05";    
		coefMin = 1;          
		coefMax=2;
	};
	class Store
	{
		icon="\RuckVanillaMap\Icons\Shop.paa";
		color[]={0.0, 0.35, 0.55, 1};
		size=20;
		importance="6 * 20 * 0.05";    
		coefMin = 1;          
		coefMax=4;
	};
	class Chapel
	{
		icon="\RuckVanillaMap\Icons\Cross.paa";
		color[]={0,0,0,1};
		size=10;
		importance="6 * 20 * 0.05";    
		coefMin = 1;          
		coefMax=2;
	};
	class TouristShelter
	{
		icon="\RuckVanillaMap\Icons\TShelter.paa";
		color[]={0.05, 0.25, 0.12, 1};
		size=20;
		importance="6 * 20 * 0.05";    
		coefMin = 1;          
		coefMax=2;
	};
	class Quay
	{
		icon="\RuckVanillaMap\Icons\Port.paa";
		size=20;
		color[]={1,1,1,1};
		importance="6 * 20 * 0.05";    
		coefMin = 1;          
		coefMax=2;
	};
	class Bunker
	{
		icon="\RuckVanillaMap\Icons\Bunker.paa";
		color[]={0.25, 0.25, 0.25, 1};
		size=20;
		importance="6 * 20 * 0.05";    
		coefMin = 1;          
		coefMax=2;
	};
	class Fortress
	{
		icon="\RuckVanillaMap\Icons\Castle.paa";
		size=20;
		color[]={1,1,1,1};
		importance="6 * 20 * 0.05";    
		coefMin = 1;          
		coefMax=2;
	};
	class Ruin
	{
		icon="\RuckVanillaMap\Icons\Ruin.paa";
		size=20;
		color[]={0,0,0,1};
		importance="6 * 20 * 0.05";    
		coefMin = 1;          
		coefMax=2;
	};
	class ViewTower
	{
		icon="\RuckVanillaMap\Icons\ViewTower.paa";
		color[]={1,1,1,1};
		size=12;
		importance="6 * 20 * 0.05";    
		coefMin = 1;          
		coefMax=2;
	};
};

class CfgVehicles
{
	
	class ItemMap;
	class ChernarusMap: ItemMap
	{
		class MapProperties: MapDefaults
		{
			scaleMin=0.03;
			scaleMax=0.8;
		};
	};
};	

class CfgLocationTypes
{
	class Name
	{
		name="keypoint";
		drawStyle="name";
		texture="#(argb,1,1,1)color(1,1,1,1)";
		color[]={1,1,1,1};
		size=0;
		font="gui/fonts/metronbook-bold28";
		textSize=0.03;
		shadow=0.1;
		importance=1;
	};
	class NameIcon
	{
		name="keypoint";
		drawStyle="icon";
		texture="#(argb,1,1,1)color(1,1,1,1)";
		color[]={1,1,1,1};
		size=0;
		font="gui/fonts/metronbook-bold28";
		textSize=0.03;
		shadow=0;
		importance=1;
	};
	class Capital: Name
	{
		color[]={1,1,1,1};
		textSize=0.059999999;
		importance=7;
	};
	class City: Name
	{
		textSize=0.050000001;
		importance=6;
	};
	class Village: Name
	{
		color[] = {0.6, 0.1, 0.1, 1};
		textSize=0.039999999;
		importance=5;
	};
	class Local: Name
	{
		color[] = {0.6, 0.1, 0.1, 1};
		textSize=0.03;
		importance=5;
	};
	class Marine: Name
	{
		color[]={0.05,0.4,0.8,0.8};
		textSize=0.03;
		importance=3;
	};
	class Ruin: NameIcon
	{
		texture="\DZ\gear\navigation\data\map_ruin_ca.paa";
		textSize=0.03;
		importance=2;
		size=7;
	};
	class Camp: NameIcon
	{
		color[] = {0.6, 0.1, 0.1, 1};
		texture="\DZ\gear\navigation\data\map_camp_ca.paa";
		textSize=0.02;
		size=5;
	};
	class Hill: NameIcon
	{
		color[] = {0.6, 0.1, 0.1, 1};
		texture="\DZ\gear\navigation\data\map_hill_ca.paa";
		textSize=0.02;
		size=3;
	};
	class ViewPoint: NameIcon
	{
		color[]={0,0,0.0,0};
		texture="\DZ\gear\navigation\data\map_viewpoint_ca.paa";
		size=9;
	};
	class RockArea: NameIcon
	{
		color[]={0,0,0,1};
		texture="\DZ\gear\navigation\data\map_rock_ca.paa";
		size=9;
	};
	class RailroadStation: NameIcon
	{
		color[] = {0.95, 0.45, 0.1, 1};
		texture="\DZ\gear\navigation\data\map_station_ca.paa";
		size=9;
	};
	class IndustrialSite: NameIcon
	{
		color[] = {0.95, 0.45, 0.1, 1};
		texture="\DZ\gear\navigation\data\map_factory_ca.paa";
		size=9;
	};
	class LocalOffice: NameIcon
	{
		color[] = {0, 0, 0, 0};
		texture="\DZ\gear\navigation\data\map_govoffice_ca.paa";
		size=10;
	};
	class BorderCrossing: NameIcon
	{
		color[]={0.78,0,0.05,1};
		texture="\DZ\gear\navigation\data\map_border_cross_ca.paa";
		size=9;
	};
};

class CfgWorlds
{
	class CAWorld;
	class ChernarusPlus: CAWorld
	{
		class Names
		{
			class Settlement_Chernogorsk
			{
				name="Chernogorsk";
				position[]={6778.6191,2321.7739};
				type="Capital";
			};

			class Settlement_Novodmitrovsk
			{
				name="Novodmitrovsk";
				position[]={11339.77,14391.05};
				type="Capital";
			};

			class Settlement_Novoselki
			{
				name="Novoselki";
				position[]={6115.9102,3256.3601};
				type="City";
			};

			class Settlement_Dubovo
			{
				name="Dubovo";
				position[]={6754.5098,3595.2571};
				type="City";
			};

			class Settlement_Vysotovo
			{
				name="Vysotovo";
				position[]={5701.2402,2556.1101};
				type="City";
			};

			class Settlement_Zelenogorsk
			{
				name="Zelenogorsk";
				position[]={2796,5166};
				type="City";
			};

			class Settlement_Berezino
			{
				name="Berezino";
				position[]={12372.383,9760.9814};
				type="City";
			};

			class Settlement_Elektrozavodsk
			{
				name="Elektrozavodsk";
				position[]={10286.68,1992.77};
				type="City";
			};

			class Settlement_NovayaPetrovka
			{
				name="Novaya Petrovka";
				position[]={3477.1689,12931.243};
				type="City";
			};

			class Settlement_Gorka
			{
				name="Gorka";
				position[]={9524,8945};
				type="City";
			};

			class Settlement_Solnechny
			{
				name="Solnechny";
				position[]={13487.724,6225.8838};
				type="City";
			};

			class Settlement_StarySobor
			{
				name="Stary Sobor";
				position[]={6114,7849};
				type="City";
			};

			class Settlement_Vybor
			{
				name="Vybor";
				position[]={3909.8311,9019.6143};
				type="City";
			};

			class Settlement_Severograd
			{
				name="Severograd";
				position[]={8168.4839,12573.602};
				type="City";
			};

			class Settlement_Bor
			{
				name="Bor";
				position[]={3316.406,4070.9661};
				type="Village";
			};

			class Settlement_Svetloyarsk
			{
				name="Svetloyarsk";
				position[]={13989.74,13263.78};
				type="City";
			};

			class Settlement_Krasnostav
			{
				name="Krasnostav";
				position[]={11203.167,12340.808};
				type="City";
			};

			class Settlement_ChernayaPolyana
			{
				name="Chernaya Polyana";
				position[]={12158.54,13770.22};
				type="City";
			};

			class Settlement_Polyana
			{
				name="Polyana";
				position[]={10794,8160};
				type="City";
			};

			class Settlement_Tulga
			{
				name="Tulga";
				position[]={12768,4384};
				type="Village";
			};

			class Settlement_Msta
			{
				name="Msta";
				position[]={11333.79,5421.3999};
				type="Village";
			};

			class Settlement_Staroye
			{
				name="Staroye";
				position[]={10212.52,5385.0498};
				type="Village";
			};

			class Settlement_Shakhovka
			{
				name="Shakhovka";
				position[]={9728.6396,6567.2998};
				type="Village";
			};

			class Settlement_Dolina
			{
				name="Dolina";
				position[]={11285.17,6633.5801};
				type="Village";
			};

			class Settlement_Orlovets
			{
				name="Orlovets";
				position[]={12250,7253};
				type="Village";
			};

			class Settlement_NovySobor
			{
				name="Novy Sobor";
				position[]={7123.6299,7774.6299};
				type="Village";
			};

			class Settlement_Kabanino
			{
				name="Kabanino";
				position[]={5300.71,8645.9004};
				type="Village";
			};

			class Settlement_Mogilevka
			{
				name="Mogilevka";
				position[]={7650.4102,5096.46};
				type="Village";
			};

			class Settlement_Nadezhdino
			{
				name="Nadezhdino";
				position[]={5894,4780};
				type="Village";
			};

			class Settlement_Guglovo
			{
				name="Guglovo";
				position[]={8445,6579};
				type="Village";
			};

			class Settlement_Kamyshovo
			{
				name="Kamyshovo";
				position[]={12170,3458};
				type="Village";
			};

			class Settlement_Pusta
			{
				name="Pusta";
				position[]={9197,3873};
				type="Village";
			};

			class Settlement_Dubrovka
			{
				name="Dubrovka";
				position[]={10324.299,9888.2373};
				type="Village";
			};

			class Settlement_VyshnayaDubrovka
			{
				name="Vyshnaya Dubrovka";
				position[]={9926.8232,10468.919};
				type="Village";
			};

			class Settlement_Khelm
			{
				name="Khelm";
				position[]={12329.27,10771.01};
				type="Village";
			};

			class Settlement_Olsha
			{
				name="Olsha";
				position[]={13402,12898};
				type="Village";
			};

			class Settlement_Gvozdno
			{
				name="Gvozdno";
				position[]={8644.751,11934.115};
				type="Village";
			};

			class Settlement_Grishino
			{
				name="Grishino";
				position[]={5980,10257};
				type="Village";
			};

			class Settlement_Rogovo
			{
				name="Rogovo";
				position[]={4802,6748};
				type="Village";
			};

			class Settlement_Pogorevka
			{
				name="Pogorevka";
				position[]={4445,6322};
				type="Village";
			};

			class Settlement_Pustoshka
			{
				name="Pustoshka";
				position[]={3137.9441,7890.9248};
				type="Village";
			};

			class Settlement_Kozlovka
			{
				name="Kozlovka";
				position[]={4402,4736};
				type="Village";
			};

			class Settlement_Karmanovka
			{
				name="Karmanovka";
				position[]={12700.628,14691.312};
				type="Village";
			};

			class Settlement_Balota
			{
				name="Balota";
				position[]={4527.5801,2465.3201};
				type="Village";
			};

			class Settlement_Komarovo
			{
				name="Komarovo";
				position[]={3702,2440};
				type="Village";
			};

			class Settlement_Kamenka
			{
				name="Kamenka";
				position[]={1981,2207};
				type="Village";
			};

			class Settlement_Myshkino
			{
				name="Myshkino";
				position[]={2048,7258};
				type="Village";
			};

			class Settlement_Pavlovo
			{
				name="Pavlovo";
				position[]={1693.98,3858.6499};
				type="Village";
			};

			class Settlement_Lopatino
			{
				name="Lopatino";
				position[]={2801,10029};
				type="Village";
			};

			class Settlement_Vyshnoye
			{
				name="Vyshnoye";
				position[]={6629,6051};
				type="Village";
			};

			class Settlement_Prigorodki
			{
				name="Prigorodki";
				position[]={7760,3336};
				type="Village";
			};

			class Settlement_Drozhino
			{
				name="Drozhino";
				position[]={3374,4861};
				type="Village";
			};

			class Settlement_Sosnovka
			{
				name="Sosnovka";
				position[]={2556,6307};
				type="Village";
			};

			class Settlement_Nizhneye
			{
				name="Nizhneye";
				position[]={12824.88,8097.7002};
				type="Village";
			};

			class Settlement_Pulkovo
			{
				name="Pulkovo";
				position[]={5015,5607};
				type="Village";
			};

			class Settlement_Berezhki
			{
				name="Berezhki";
				position[]={15020,13905};
				type="Village";
			};

			class Settlement_Turovo
			{
				name="Turovo";
				position[]={13630,14146};
				type="Village";
			};

			class Settlement_BelayaPolyana
			{
				name="Belaya Polyana";
				position[]={14166,14968};
				type="Village";
			};

			class Settlement_Dobroye
			{
				name="Dobroye";
				position[]={12996,15066};
				type="Village";
			};

			class Settlement_Nagornoye
			{
				name="Nagornoye";
				position[]={9286,14677};
				type="Village";
			};

			class Settlement_Svergino
			{
				name="Svergino";
				position[]={9493.5195,13875.27};
				type="Village";
			};

			class Settlement_Ratnoye
			{
				name="Ratnoye";
				position[]={6195.8779,12761.802};
				type="Village";
			};

			class Settlement_Kamensk
			{
				name="Kamensk";
				position[]={6748.7412,14430.046};
				type="Village";
			};

			class Settlement_Krasnoye
			{
				name="Krasnoye";
				position[]={6411.374,15029.961};
				type="Village";
			};

			class Settlement_StaryYar
			{
				name="Stary Yar";
				position[]={4987.8599,14992.976};
				type="Village";
			};

			class Settlement_Polesovo
			{
				name="Polesovo";
				position[]={5955.7368,13558.046};
				type="Village";
			};

			class Settlement_Tisy
			{
				name="Tisy";
				position[]={3441.6499,14799.55};
				type="Village";
			};

			class Settlement_Topolniki
			{
				name="Topolniki";
				position[]={2913.7451,12366.357};
				type="Village";
			};

			class Settlement_Zaprudnoye
			{
				name="Zaprudnoye";
				position[]={5214,12792};
				type="Village";
			};

			class Settlement_Sinystok
			{
				name="Sinystok";
				position[]={1538.278,11904.578};
				type="Village";
			};

			class Settlement_Vavilovo
			{
				name="Vavilovo";
				position[]={2263,11103};
				type="Village";
			};

			class Settlement_Kumyrna
			{
				name="Kumyrna";
				position[]={8300,6054};
				type="Village";
			};

			class Settlement_Kalinovka
			{
				name="Kalinovka";
				position[]={7448,13406};
				type="Village";
			};

			class Settlement_Bogatyrka
			{
				name="Bogatyrka";
				position[]={1453.62,8870.9199};
				type="Village";
			};

			class Settlement_SvyatoyRomanSkiResort
			{
				name="Svyatoy Roman Ski Resort";
				position[]={638,11667};
				type="Local";
			};

			class Settlement_SKVSChBiathlonArena
			{
				name="SKVSCh Biathlon Arena";
				position[]={357,11142};
				type="Local";
			};

			class Settlement_Zvir
			{
				name="Zvir";
				position[]={577.33002,5317.4199};
				type="Village";
			};

			class Settlement_Zabolotye
			{
				name="Zabolotye";
				position[]={1256.859,9993.2598};
				type="Village";
			};

			class Settlement_Galkino
			{
				name="Galkino";
				position[]={1102.6801,8798.2695};
				type="Local";
			};

			class Camp_Arsenovo
			{
				name="Arsenovo";
				position[]={8509.6611,13918.628};
				type="Camp";
			};

			class Camp_Stroytel
			{
				name="Stroytel";
				position[]={7017.6299,4365.21};
				type="Camp";
			};

			class Camp_Romashka
			{
				name="Romashka";
				position[]={8177.6021,10980.289};
				type="Camp";
			};

			class Camp_Kometa
			{
				name="Kometa";
				position[]={10271.697,3558.228};
				type="Camp";
			};

			class Camp_Druzhba
			{
				name="Druzhba";
				position[]={11437,10695};
				type="Camp";
			};

			class Camp_Nadezhda
			{
				name="Nadezhda";
				position[]={7279.9678,7014.3501};
				type="Camp";
			};

			class Camp_YouthPioneer
			{
				name="Youth Pioneer";
				position[]={11155.825,7074.1431};
				type="Camp";
			};

			class Camp_ProudChernarus
			{
				name="Proud Chernarus";
				position[]={3199.6169,6174.9321};
				type="Camp";
			};

			class Camp_Shkolnik
			{
				name="Shkolnik";
				position[]={14856.503,14571.028};
				type="Camp";
			};

			class Camp_Pobeda
			{
				name="Pobeda";
				position[]={3703.3821,14876.384};
				type="Camp";
			};

			class Camp_Metalurg
			{
				name="Metalurg";
				position[]={1035.406,6677.3828};
				type="Camp";
			};

			class Hill_Zelenayagora
			{
				name="Zelenayagora";
				position[]={3767.1699,6010.54};
				type="Hill";
			};

			class Local_Dichina
			{
				name="Dichina";
				position[]={4618,7821};
				type="Local";
			};

			class Local_Novylug
			{
				name="Novylug";
				position[]={9251,11360};
				type="Local";
			};

			class Local_Staryeluga
			{
				name="Staryeluga";
				position[]={6919,8995};
				type="Local";
			};

			class Hill_Vysota
			{
				name="Vysota";
				position[]={6591.6299,3400};
				type="Hill";
			};

			class Hill_Kopyto
			{
				name="Kopyto";
				position[]={7871.479,3869.1021};
				type="Hill";
			};

			class Local_Grubyeskaly
			{
				name="Grubyeskaly";
				position[]={13115.06,11900};
				type="Local";
			};

			class Local_Chernyles
			{
				name="Chernyles";
				position[]={9031,7803};
				type="Local";
			};

			class Hill_Altar
			{
				name="Altar";
				position[]={8143.3999,9159.6797};
				type="Hill";
			};

			class Local_RadioZenit
			{
				name="Radio Zenit";
				position[]={8080.0098,9341.6797};
				type="Local";
			};

			class Hill_PikKozlova
			{
				name="Pik Kozlova";
				position[]={8850.1699,2880.53};
				type="Hill";
			};

			class Local_Pustoykhrebet
			{
				name="Pustoykhrebet";
				position[]={10890,5665};
				type="Local";
			};

			class Hill_Bashnya
			{
				name="Bashnya";
				position[]={4178.27,11771.22};
				type="Hill";
			};

			class Hill_Veresnik
			{
				name="Veresnik";
				position[]={4440.1699,8070.54};
				type="Hill";
			};

			class Hill_Kurgan
			{
				name="Kurgan";
				position[]={3368.52,5296.8701};
				type="Hill";
			};

			class Hill_Kustryk
			{
				name="Kustryk";
				position[]={4912.8799,5063.4502};
				type="Hill";
			};

			class Hill_Vetryanayagora
			{
				name="Vetryanayagora";
				position[]={3892.74,4200.5898};
				type="Hill";
			};

			class Hill_Kalmyk
			{
				name="Kalmyk";
				position[]={6903.7798,4919.6602};
				type="Hill";
			};

			class Hill_PopIvan
			{
				name="Pop Ivan";
				position[]={6420.2598,6570.6602};
				type="Hill";
			};

			class Hill_Erbenka
			{
				name="Erbenka";
				position[]={2842.916,4014.811};
				type="Hill";
			};

			class Local_Lesnoykhrebet
			{
				name="Lesnoykhrebet";
				position[]={8122.77,7815.54};
				type="Local";
			};

			class Hill_Vysokiykamen
			{
				name="Vysokiykamen";
				position[]={8940.1904,4380.52};
				type="Hill";
			};

			class Hill_Dobry
			{
				name="Dobry";
				position[]={10552.9,3061.03};
				type="Hill";
			};

			class Hill_Baranchik
			{
				name="Baranchik";
				position[]={10153.147,6208.521};
				type="Hill";
			};

			class Hill_Malinovka
			{
				name="Malinovka";
				position[]={10897.7,7575.5898};
				type="Hill";
			};

			class Hill_Dubina
			{
				name="Dubina";
				position[]={11107.9,8474.8301};
				type="Hill";
			};

			class Hill_Klen
			{
				name="Klen";
				position[]={11473.511,11315.393};
				type="Hill";
			};

			class Hill_Chernayagora
			{
				name="Chernayagora";
				position[]={10280.816,12053.928};
				type="Hill";
			};

			class Ruin_Zolotar
			{
				name="Zolotar";
				position[]={10179,11998};
				type="Ruin";
			};

			class Hill_Ostry
			{
				name="Ostry";
				position[]={10792.747,12829.504};
				type="Hill";
			};

			class Hill_Olsha
			{
				name="Olsha";
				position[]={12975.7,12775.2};
				type="Hill";
			};

			class Marine_Tikhiyzaliv
			{
				name="Tikhiyzaliv";
				position[]={1221.49,2111.8899};
				type="Marine";
			};

			class Marine_Mutnyizaliv
			{
				name="Mutnyizaliv";
				position[]={5735.479,1918.92};
				type="Marine";
			};

			class Marine_Chernyzaliv
			{
				name="Chernyzaliv";
				position[]={7599.0688,2486.5859};
				type="Marine";
			};

			class Marine_Zelenyzaliv
			{
				name="Zelenyzaliv";
				position[]={11227.019,2989.8379};
				type="Marine";
			};

			class Marine_Skalistyproliv
			{
				name="Skalistyproliv";
				position[]={13385.92,3613.9399};
				type="Marine";
			};

			class Marine_Nizhniyzaliv
			{
				name="Nizhniyzaliv";
				position[]={12989.3,8515.7598};
				type="Marine";
			};

			class Marine_ZalivGuba
			{
				name="Zaliv Guba";
				position[]={14328.374,13136.732};
				type="Marine";
			};

			class Marine_Rify
			{
				name="Rify";
				position[]={13931.73,11288.61};
				type="Local";
			};

			class Marine_Ivovoyeozero
			{
				name="Ivovoyeozero";
				position[]={13248,11572};
				type="Marine";
			};

			class Marine_Chernoyeozero
			{
				name="Chernoyeozero";
				position[]={13381,12002};
				type="Marine";
			};

			class Marine_PlotinaTopolka
			{
				name="Plotina Topolka";
				position[]={10231.33,3691.1499};
				type="Marine";
			};

			class Marine_PlotinaPobeda
			{
				name="Plotina Pobeda";
				position[]={9928.2939,13874.643};
				type="Marine";
			};

			class Marine_PlotinaTishina
			{
				name="Plotina Tishina";
				position[]={1150.8199,6432.4541};
				type="Marine";
			};

			class Marine_Ozerko
			{
				name="Ozerko";
				position[]={6777.6299,4492.4199};
				type="Marine";
			};

			class Marine_Prud
			{
				name="Prud";
				position[]={6610.98,9308.5703};
				type="Marine";
			};

			class Ruin_Chortovzamok
			{
				name="Chortovzamok";
				position[]={6883.2388,11501.288};
				type="Ruin";
			};

			class Ruin_Zub
			{
				name="Zub";
				position[]={6574.2798,5573.8501};
				type="Ruin";
			};

			class Ruin_Rog
			{
				name="Rog";
				position[]={11267.206,4293.0361};
				type="Ruin";
			};

			class Local_Grozovypereval
			{
				name="Grozovypereval";
				position[]={3318.1201,15250.55};
				type="Local";
			};

			class Local_Sosnovypereval
			{
				name="Sosnovypereval";
				position[]={2687.3999,6590.2798};
				type="Local";
			};

			class Local_PerevalOreshka
			{
				name="Pereval Oreshka";
				position[]={9822.1914,6088.793};
				type="Local";
			};

			class Local_Turovskiypereval
			{
				name="Turovskiypereval";
				position[]={14674.241,14089.306};
				type="Local";
			};

			class Local_Tridoliny
			{
				name="Tridoliny";
				position[]={12764.47,5412.21};
				type="Local";
			};

			class Local_Grozovyedoly
			{
				name="Grozovyedoly";
				position[]={10403.982,14793.168};
				type="Local";
			};

			class Ruin_Klyuch
			{
				name="Klyuch";
				position[]={9282.5703,13476.67};
				type="Ruin";
			};

			class Hill_Lysayagora
			{
				name="Lysayagora";
				position[]={6722.459,14050.42};
				type="Hill";
			};

			class Marine_Glubokoyeozero
			{
				name="Glubokoyeozero";
				position[]={1692.5551,14821.565};
				type="Marine";
			};

			class Local_Skalka
			{
				name="Skalka";
				position[]={5758,14486};
				type="Local";
			};

			class Local_Vidy
			{
				name="Vidy";
				position[]={785.05402,14398.815};
				type="Local";
			};

			class Hill_Tumannyverkh
			{
				name="Tumannyverkh";
				position[]={331.224,12982.99};
				type="Hill";
			};

			class Local_Adamovka
			{
				name="Adamovka";
				position[]={5340.6602,11380.01};
				type="Local";
			};

			class Hill_Shishok
			{
				name="Shishok";
				position[]={3559.313,9422.2695};
				type="Hill";
			};

			class Settlement_Skalisty
			{
				name="Skalisty";
				position[]={13715.454,3118.78};
				type="Village";
			};

			class Ruin_Storozh
			{
				name="Storozh";
				position[]={2816.6011,1277.96};
				type="Ruin";
			};

			class Local_MysGolova
			{
				name="Mys Golova";
				position[]={8286.0527,2405.5979};
				type="Local";
			};

			class Local_Drakon
			{
				name="Drakon";
				position[]={11191,2443};
				type="Local";
			};

			class Local_Otmel
			{
				name="Otmel";
				position[]={11581.25,3213.24};
				type="Local";
			};

			class Local_MysKrutoy
			{
				name="Mys Krutoy";
				position[]={13578.19,3976.8201};
				type="Local";
			};

			class Hill_Tokarnya
			{
				name="Tokarnya";
				position[]={8890.4775,5672.5532};
				type="Hill";
			};

			class Hill_Ostrog
			{
				name="Ostrog";
				position[]={2655.7339,2264.6321};
				type="Hill";
			};

			class Local_Maryanka
			{
				name="Maryanka";
				position[]={2789,3386};
				type="Local";
			};

			class Local_Polonina
			{
				name="Polonina";
				position[]={1004.486,4242.8691};
				type="Local";
			};

			class Local_Kalinka
			{
				name="Kalinka";
				position[]={3346.5,11292.097};
				type="Local";
			};

			class Hill_Kikimora
			{
				name="Kikimora";
				position[]={1812,6200};
				type="Hill";
			};

			class Hill_BolshoyKotel
			{
				name="Bolshoy Kotel";
				position[]={714.64899,6520.4312};
				type="Hill";
			};

			class Hill_Simurg
			{
				name="Simurg";
				position[]={134,7569.9902};
				type="Hill";
			};

			class Hill_Volchiypik
			{
				name="Volchiypik";
				position[]={320.254,2719.269};
				type="Hill";
			};

			class Ruin_Krona
			{
				name="Krona";
				position[]={1493,9270.3398};
				type="Ruin";
			};

			class Local_TriKresta
			{
				name="Tri Kresta";
				position[]={301,9478};
				type="Local";
			};

			class Local_Rostoki
			{
				name="Rostoki";
				position[]={744.45001,8647.8604};
				type="Local";
			};

			class Marine_OrlyeOzero
			{
				name="Orlye Ozero";
				position[]={597,5990};
				type="Marine";
			};

			class Local_Makosh
			{
				name="Makosh";
				position[]={7849.7202,6480.1899};
				type="Local";
			};

			class Local_Klenovyipereval
			{
				name="Klenovyipereval";
				position[]={10862.702,11585.512};
				type="Local";
			};

			class Local_Zmeinykhrebet
			{
				name="Zmeinykhrebet";
				position[]={11446.17,13606.92};
				type="Local";
			};

			class Hill_Sokol
			{
				name="Sokol";
				position[]={12001,14813};
				type="Hill";
			};

			class Local_Krutyeskaly
			{
				name="Krutyeskaly";
				position[]={14880.63,13671.76};
				type="Local";
			};

			class Local_Bogat
			{
				name="Bogat";
				position[]={7058.0112,12023.571};
				type="Local";
			};

			class Local_Dubnik
			{
				name="Dubnik";
				position[]={3298.29,10330.89};
				type="Local";
			};

			class Hill_Viselitsa
			{
				name="Viselitsa";
				position[]={12722.157,7504.0498};
				type="Hill";
			};

			class Local_Dazhbog
			{
				name="Dazhbog";
				position[]={6581,8590};
				type="Hill";
			};

			class Marine_Verbnik
			{
				name="Verbnik";
				position[]={4414.8789,9103.002};
				type="Marine";
			};

			class Local_Medvezhilugi
			{
				name="Medvezhilugi";
				position[]={9641,13236};
				type="Local";
			};

			class Ruin_Voron
			{
				name="Voron";
				position[]={13517.93,3311.2451};
				type="Ruin";
			};

			class Ruin_Gnomovzamok
			{
				name="Gnomovzamok";
				position[]={7446.915,9097.1699};
				type="Ruin";
			};

			class Marine_Glaza
			{
				name="Glaza";
				position[]={7383,9320};
				type="Marine";
			};

			class Local_KarerKrasnayaZarya
			{
				name="Karer Krasnaya Zarya";
				position[]={8565.3486,13418.684};
				type="Local";
			};

			class Local_Matveyevo
			{
				name="Matveyevo";
				position[]={4281,7380};
				type="Local";
			};

			class Local_Kotka
			{
				name="Kotka";
				position[]={5873.7002,6883.2402};
				type="Local";
			};

			class Local_Chernyeskaly
			{
				name="Chernyeskaly";
				position[]={3932.572,14599.496};
				type="Local";
			};

			class Hill_SvyatoyRoman
			{
				name="Svyatoy Roman";
				position[]={84.832001,11901.246};
				type="Hill";
			};

			class Hill_Koman
			{
				name="Koman";
				position[]={1660.652,7415.6611};
				type="Hill";
			};

			class Hill_Mayak
			{
				name="Mayak";
				position[]={12323.813,4553.1069};
				type="Hill";
			};

			class Local_MB_VMC
			{
				name="VMC Military";
				position[]={4497,8291};
				type="Local";
			};

			class Local_MB_Tisy
			{
				name="Tisy Military";
				position[]={1570,14069};
				type="Local";
			};

			class Local_MB_Kamensk
			{
				name="Kamensk Military";
				position[]={7838.812,14704.823};
				type="Local";
			};

			class Local_MB_Zeleno
			{
				name="Zeleno Military";
				position[]={2410.375,5133.6812};
				type="Local";
			};

			class Local_MB_Pavlovo
			{
				name="Pavlovo Military";
				position[]={2016,3408};
				type="Local";
			};

			class Local_AF_Balota
			{
				name="Balota Airfield";
				position[]={5082.0308,2376.3279};
				type="Local";
			};

			class Local_AF_Krasno
			{
				name="Krasno Airfield";
				position[]={12100.681,12573.896};
				type="Local";
			};

			class Local_AF_Vybor
			{
				name="Vybor Airfield";
				position[]={4428,10179};
				type="Local";
			};

			class RailroadStation_Elektro
			{
				name="Elektro Train Station";
				position[]={10309.912,2092.2029};
				type="RailroadStation";
			};

			class RailroadStation_Prigorodki
			{
				name="Prigorodki Train Station";
				position[]={8056.0342,3264.908};
				type="RailroadStation";
			};

			class RailroadStation_Cherno
			{
				name="Cherno Train Station";
				position[]={6540.626,2638.7749};
				type="RailroadStation";
			};

			class RailroadStation_Balota
			{
				name="Balota Train Station";
				position[]={4399.2588,2309.397};
				type="RailroadStation";
			};

			class RailroadStation_Komarovo
			{
				name="Komarovo Train Station";
				position[]={3670.667,2397.5249};
				type="RailroadStation";
			};

			class RailroadStation_Kamenka
			{
				name="Kamenka Train Station";
				position[]={1877.9351,2168.5591};
				type="RailroadStation";
			};

			class RailroadStation_Zeleno
			{
				name="Zeleno Train Station";
				position[]={2485.2661,5214.6641};
				type="RailroadStation";
			};

			class RailroadStation_Vavilovo
			{
				name="Vavilovo Train Station";
				position[]={1991.5031,11289.488};
				type="RailroadStation";
			};

			class RailroadStation_Novaya
			{
				name="Novaya Train Station";
				position[]={3534.425,12537.095};
				type="RailroadStation";
			};

			class RailroadStation_Severograd
			{
				name="Severograd Train Station";
				position[]={7846.5811,12401.488};
				type="RailroadStation";
			};

			class RailroadStation_Novo
			{
				name="Novo Train Station";
				position[]={11610.908,14133.702};
				type="RailroadStation";
			};

			class RailroadStation_Svetlo
			{
				name="Svetlo Train Station";
				position[]={13970.473,13486.344};
				type="RailroadStation";
			};

			class RailroadStation_Berezino
			{
				name="Berezino Train Station";
				position[]={12989.844,10200.673};
				type="RailroadStation";
			};

			class RailroadStation_Solnich
			{
				name="Solnich Train Station";
				position[]={13146.109,7094.4722};
				type="RailroadStation";
			};

			class RailroadStation_Solnich2
			{
				name="Solnich2 Train Station";
				position[]={13356.109,6154.4722};
				type="RailroadStation";
			};

			class RailroadStation_Kamyshovo
			{
				name="Kamyshovo Train Station";
				position[]={11970.969,3548.7229};
				type="RailroadStation";
			};

			class RailroadStation_Dobroye
			{
				name="Dobroye Train Station";
				position[]={12860.658,15050.221};
				type="RailroadStation";
			};

			class LocalOffice_Novaya
			{
				name="Novaya";
				position[]={3469.1721,13135.165};
				type="LocalOffice";
			};

			class LocalOffice_Vybor
			{
				name="Vybor";
				position[]={3857.656,8946.1396};
				type="LocalOffice";
			};

			class LocalOffice_Sinys
			{
				name="Sinys";
				position[]={1439.08,12011.26};
				type="LocalOffice";
			};

			class LocalOffice_Vavil
			{
				name="Vavil";
				position[]={2220.8401,11075.83};
				type="LocalOffice";
			};

			class LocalOffice_Lopat
			{
				name="Lopat";
				position[]={2720.72,9978.1396};
				type="LocalOffice";
			};

			class LocalOffice_Pustosh
			{
				name="Pustosh";
				position[]={3051.4399,7804.6802};
				type="LocalOffice";
			};

			class LocalOffice_Pogorev
			{
				name="Pogorev";
				position[]={4480.71,6462};
				type="LocalOffice";
			};

			class LocalOffice_Kabanin
			{
				name="Kabanin";
				position[]={5382,8589};
				type="LocalOffice";
			};

			class LocalOffice_Stary
			{
				name="Stary";
				position[]={6056.0801,7715.3501};
				type="LocalOffice";
			};

			class LocalOffice_Novy
			{
				name="Novy";
				position[]={7166.96,7526.0098};
				type="LocalOffice";
			};

			class LocalOffice_Grishino
			{
				name="Grishino";
				position[]={5983,10305};
				type="LocalOffice";
			};

			class LocalOffice_Severo
			{
				name="Severo";
				position[]={7986,12732};
				type="LocalOffice";
			};

			class LocalOffice_Gorka
			{
				name="Gorka";
				position[]={9503,8805};
				type="LocalOffice";
			};

			class LocalOffice_Mogi
			{
				name="Mogi";
				position[]={7562,5149};
				type="LocalOffice";
			};

			class LocalOffice_Nadez
			{
				name="Nadez";
				position[]={5906,4844};
				type="LocalOffice";
			};

			class LocalOffice_Cherno
			{
				name="Cherno";
				position[]={6607,2418};
				type="LocalOffice";
			};

			class LocalOffice_Kozlov
			{
				name="Kozlov";
				position[]={4394,4629};
				type="LocalOffice";
			};

			class LocalOffice_Komar
			{
				name="Komar";
				position[]={3676,2501};
				type="LocalOffice";
			};

			class LocalOffice_Pavlovo
			{
				name="Pavlovo";
				position[]={1655,3851};
				type="LocalOffice";
			};

			class LocalOffice_Zeleno
			{
				name="Zeleno";
				position[]={2854,5282};
				type="LocalOffice";
			};

			class LocalOffice_Elektro
			{
				name="Elektro";
				position[]={10212,2295};
				type="LocalOffice";
			};

			class LocalOffice_Kamys
			{
				name="Kamys";
				position[]={12155,3514};
				type="LocalOffice";
			};

			class LocalOffice_Staroye
			{
				name="Staroye";
				position[]={10106,5457};
				type="LocalOffice";
			};

			class LocalOffice_Dolina
			{
				name="Dolina";
				position[]={11217,6564};
				type="LocalOffice";
			};

			class LocalOffice_Solnich
			{
				name="Solnich";
				position[]={13383,6225};
				type="LocalOffice";
			};

			class LocalOffice_Polana
			{
				name="Polana";
				position[]={10676,7989};
				type="LocalOffice";
			};

			class LocalOffice_Berezino
			{
				name="Berezino";
				position[]={12272,9474};
				type="LocalOffice";
			};

			class LocalOffice_Krasno
			{
				name="Krasno";
				position[]={11257,12211};
				type="LocalOffice";
			};

			class LocalOffice_Svetlo
			{
				name="Svetlo";
				position[]={14013,13335};
				type="LocalOffice";
			};

			class LocalOffice_Cpol
			{
				name="Cpol";
				position[]={12110,13779};
				type="LocalOffice";
			};

			class LocalOffice_Novo
			{
				name="Novo";
				position[]={11564,14742};
				type="LocalOffice";
			};

			class ViewPoint_1
			{
				name="1";
				position[]={567,6997};
				type="ViewPoint";
			};

			class ViewPoint_2
			{
				name="2";
				position[]={687,6874};
				type="ViewPoint";
			};

			class ViewPoint_3
			{
				name="3";
				position[]={724,6510};
				type="ViewPoint";
			};

			class ViewPoint_4
			{
				name="4";
				position[]={298,3460};
				type="ViewPoint";
			};

			class ViewPoint_5
			{
				name="5";
				position[]={172,3412};
				type="ViewPoint";
			};

			class ViewPoint_6
			{
				name="6";
				position[]={258,3283};
				type="ViewPoint";
			};

			class ViewPoint_7
			{
				name="7";
				position[]={322,2697};
				type="ViewPoint";
			};

			class ViewPoint_8
			{
				name="8";
				position[]={1671,2211};
				type="ViewPoint";
			};

			class ViewPoint_9
			{
				name="9";
				position[]={2915,3995};
				type="ViewPoint";
			};

			class ViewPoint_10
			{
				name="10";
				position[]={3371,4551};
				type="ViewPoint";
			};

			class ViewPoint_11
			{
				name="11";
				position[]={414,9574};
				type="ViewPoint";
			};

			class ViewPoint_12
			{
				name="12";
				position[]={241,11867};
				type="ViewPoint";
			};

			class ViewPoint_13
			{
				name="13";
				position[]={1153,12411};
				type="ViewPoint";
			};

			class ViewPoint_14
			{
				name="14";
				position[]={2320,13650};
				type="ViewPoint";
			};

			class ViewPoint_15
			{
				name="15";
				position[]={4084,14570};
				type="ViewPoint";
			};

			class ViewPoint_16
			{
				name="16";
				position[]={4445,15045};
				type="ViewPoint";
			};

			class ViewPoint_17
			{
				name="17";
				position[]={4926,14820};
				type="ViewPoint";
			};

			class ViewPoint_18
			{
				name="18";
				position[]={5172,14841};
				type="ViewPoint";
			};

			class ViewPoint_19
			{
				name="19";
				position[]={5345,14873};
				type="ViewPoint";
			};

			class ViewPoint_20
			{
				name="20";
				position[]={5480,14822};
				type="ViewPoint";
			};

			class ViewPoint_21
			{
				name="21";
				position[]={5692,14771};
				type="ViewPoint";
			};

			class ViewPoint_22
			{
				name="22";
				position[]={5896,14747};
				type="ViewPoint";
			};

			class ViewPoint_23
			{
				name="23";
				position[]={6246,14707};
				type="ViewPoint";
			};

			class ViewPoint_24
			{
				name="24";
				position[]={6434,14816};
				type="ViewPoint";
			};

			class ViewPoint_25
			{
				name="25";
				position[]={6707,13961};
				type="ViewPoint";
			};

			class ViewPoint_26
			{
				name="26";
				position[]={6861,14115};
				type="ViewPoint";
			};

			class ViewPoint_27
			{
				name="27";
				position[]={8710,14200};
				type="ViewPoint";
			};

			class ViewPoint_28
			{
				name="28";
				position[]={10822,14651};
				type="ViewPoint";
			};

			class ViewPoint_29
			{
				name="29";
				position[]={11369,15037};
				type="ViewPoint";
			};

			class ViewPoint_30
			{
				name="30";
				position[]={13604,14632};
				type="ViewPoint";
			};

			class ViewPoint_31
			{
				name="31";
				position[]={13877,14703};
				type="ViewPoint";
			};

			class ViewPoint_32
			{
				name="32";
				position[]={14140,15244};
				type="ViewPoint";
			};

			class ViewPoint_33
			{
				name="33";
				position[]={13840,13833};
				type="ViewPoint";
			};

			class ViewPoint_34
			{
				name="34";
				position[]={14075,13889};
				type="ViewPoint";
			};

			class ViewPoint_35
			{
				name="35";
				position[]={14895,13611};
				type="ViewPoint";
			};

			class ViewPoint_36
			{
				name="36";
				position[]={14828,13759};
				type="ViewPoint";
			};

			class ViewPoint_37
			{
				name="37";
				position[]={11982,13388};
				type="ViewPoint";
			};

			class ViewPoint_38
			{
				name="38";
				position[]={11690,13511};
				type="ViewPoint";
			};

			class ViewPoint_39
			{
				name="39";
				position[]={11473,13580};
				type="ViewPoint";
			};

			class ViewPoint_40
			{
				name="40";
				position[]={11376,13661};
				type="ViewPoint";
			};

			class ViewPoint_41
			{
				name="41";
				position[]={13937,11250};
				type="ViewPoint";
			};

			class ViewPoint_42
			{
				name="42";
				position[]={11481,8429};
				type="ViewPoint";
			};
			class ViewPoint_43
			{
				name="";
				position[]={11574,7743};
				type="ViewPoint";
			};
			class ViewPoint_44
			{
				name="";
				position[]={12123,6997};
				type="ViewPoint";
			};
			class ViewPoint_45
			{
				name="";
				position[]={12980,5967};
				type="ViewPoint";
			};
			class ViewPoint_46
			{
				name="";
				position[]={12352,4519};
				type="ViewPoint";
			};
			class ViewPoint_47
			{
				name="";
				position[]={12304,3976};
				type="ViewPoint";
			};
			class ViewPoint_48
			{
				name="";
				position[]={10584,2867};
				type="ViewPoint";
			};
			class ViewPoint_49
			{
				name="";
				position[]={8767,2959};
				type="ViewPoint";
			};
			class ViewPoint_50
			{
				name="";
				position[]={8811,2850};
				type="ViewPoint";
			};
			class ViewPoint_51
			{
				name="";
				position[]={8547,3872};
				type="ViewPoint";
			};
			class ViewPoint_52
			{
				name="";
				position[]={9029,4380};
				type="ViewPoint";
			};
			class ViewPoint_53
			{
				name="";
				position[]={10741,4180};
				type="ViewPoint";
			};
			class ViewPoint_54
			{
				name="";
				position[]={6897,11648};
				type="ViewPoint";
			};
			class ViewPoint_55
			{
				name="";
				position[]={5633,6885};
				type="ViewPoint";
			};
			class ViewPoint_56
			{
				name="";
				position[]={1456,9611};
				type="ViewPoint";
			};
			class ViewPoint_57
			{
				name="";
				position[]={1941,6768};
				type="ViewPoint";
			};
		};
	};
	class Sakhal: CAWorld // Credit to JG27_Catsy for the names here not sure where you found these class names as i struggled but cheers!
	{
		class Names
		{
			class Settlement_Capital
			{
				name="Petropavlovsk-Sakhalsky";
				position[]={4749,10695};
				type="Capital";
			};
			class Settlement_CityNorth
			{
				name="Severomorsk";
				position[]={9544,13656};
				type="City";
			};
			class Settlement_CitySouthEast
			{
				name="Aniva";
				position[]={12895,7273};
				type="City";
			};
			class Settlement_CityAirfield
			{
				name="Nogovo";
				position[]={7814,7949};
				type="City";
			};
			class Settlement_VillageSW1
			{
				name="Bolotnoye";
				position[]={5040,8667};
				type="Village";
			};
			class Settlement_VillageSW2
			{
				name="Dudino";
				position[]={6233,7245};
				type="Village";
			};
			class Settlement_VillageSW3
			{
				name="Tikhoye";
				position[]={6260,8669};
				type="Local";
			};
			class Settlement_VillageS1
			{
				name="Taranay";
				position[]={9706,6584};
				type="Local";
			};
			class Settlement_VillageS2
			{
				name="Yuzhnoye";
				position[]={10972,6323};
				type="Village";
			};
			class Settlement_VillageS3
			{
				name="Dolinovka";
				position[]={9831,9835};
				type="Local";
			};
			class Settlement_VillageM1
			{
				name="Goryachevo";
				position[]={8774,10059};
				type="Local";
			};
			class Settlement_VillageM2
			{
				name="Yasnaya Polyana";
				position[]={8116,9191};
				type="Local";
			};
			class Settlement_VillageM3
			{
				name="Lesogorovka";
				position[]={10969,9695};
				type="Village";
			};
			class Settlement_VillageM4
			{
				name="Sakhalag";
				position[]={12163,9698};
				type="Village";
			};
			class Settlement_VillageM5
			{
				name="Iturup";
				position[]={10371,10700};
				type="Local";
			};
			class Settlement_VillageSouthEast
			{
				name="Vostok";
				position[]={13910,8337};
				type="Village";
			};
			class Settlement_VillageEast1
			{
				name="Shumnoye";
				position[]={14383,8842};
				type="Village";
			};
			class Settlement_VillageEast2
			{
				name="Baykovo";
				position[]={14571,9794};
				type="Village";
			};
			class Settlement_VillageNorthEast1
			{
				name="Matrosovo";
				position[]={14233,11586};
				type="Village";
			};
			class Settlement_OreHarbor
			{
				name="Rudnogorsk";
				position[]={13587,12152};
				type="City";
			};
			class Settlement_VillageNorthEast2
			{
				name="Rybnoye";
				position[]={12471,12667};
				type="Village";
			};
			class Settlement_VillageNorth1
			{
				name="Podgornoye";
				position[]={10985,13209};
				type="Village";
			};
			class Settlement_VillageNorth2
			{
				name="Orlovo";
				position[]={10373,13348};
				type="Village";
			};
			class Settlement_VillageNorth3
			{
				name="Tumanovo";
				position[]={8417,13646};
				type="Village";
			};
			class Settlement_VillageNorth4
			{
				name="Evay";
				position[]={7954,13512};
				type="Village";
			};
			class Settlement_VillageNorthWest1
			{
				name="Yasnomorsk";
				position[]={6951,13331};
				type="Village";
			};
			class Settlement_VillageNorthWest2
			{
				name="Sovetskoye";
				position[]={6413,12783};
				type="Village";
			};
			class Settlement_VillageNorthWest3
			{
				name="Zhupanovo";
				position[]={5741,12516};
				type="Village";
			};
			class Settlement_VillageIcyRidge
			{
				name="Vysokoye";
				position[]={11186.201,7965.8384};
				type="Village";
			};
			class Hill_NW1
			{
				name="Pik Volchy";
				position[]={8196,11668};
				type="Hill";
			};
			class Hill_NW2
			{
				name="Storozh";
				position[]={8776,12791};
				type="Hill";
			};
			class Hill_Volcano
			{
				name="Odinoky Vulkan";
				position[]={10029,12087};
				type="Hill";
			};
			class Hill_N1
			{
				name="Ostry";
				position[]={11546,11669};
				type="Hill";
			};
			class Hill_N2
			{
				name="Tupoy";
				position[]={11898,11267};
				type="Hill";
			};
			class Hill_M1
			{
				name="Ledyanoy Greben";
				position[]={10756,8669};
				type="Hill";
			};
			class Hill_M2
			{
				name="Troyka";
				position[]={9016,9268};
				type="Hill";
			};
			class Hill_E
			{
				name="Pik Vostochny";
				position[]={12835,9418};
				type="Hill";
			};
			class Industrial_Quarry
			{
				name="Zvezdny Nikel";
				position[]={12033,10323};
				type="Local";
			};
			class Industrial_Geoplant
			{
				name="Sakhalskaya GeoES";
				position[]={8407,10204};
				type="Local";
			};
			class Island_1
			{
				name="Tungar";
				position[]={12630,14135};
				type="Local";
			};
			class Island_2
			{
				name="Ushki";
				position[]={10817,14631};
				type="Local";
			};
			class Island_3
			{
				name="Sputnik";
				position[]={7786,14802};
				type="Local";
			};
			class Island_4
			{
				name="Utyos";
				position[]={5453,14535};
				type="Local";
			};
			class Island_5
			{
				name="Tochka";
				position[]={3755,14402};
				type="Local";
			};
			class Island_6
			{
				name="Cherepakha";
				position[]={835,11285};
				type="Local";
			};
			class Island_7
			{
				name="Urup";
				position[]={1537,891};
				type="Local";
			};
			class Island_8
			{
				name="Mrak";
				position[]={8443,1328};
				type="Local";
			};
			class Island_9
			{
				name="Solisko";
				position[]={12653,2121};
				type="Local";
			};
			class Island_10
			{
				name="Yelizarovo";
				position[]={13492,5178};
				type="Local";
			};
			class Island_11
			{
				name="Slomanny";
				position[]={6313,6454};
				type="Local";
			};
			class Island_12
			{
				name="Utichy";
				position[]={8628,5146};
				type="Local";
			};
			class Island_13
			{
				name="Ketoy";
				position[]={5755,2066};
				type="Local";
			};
			class RocketBay
			{
				name="Raketnaya Bukhta";
				position[]={4396,7269};
				type="Marine";
			};
			class Burukan
			{
				name="Burukan";
				position[]={2706,6540};
				type="City";
			};
			class Shantar
			{
				name="Shantar";
				position[]={2278,3413};
				type="Village";
			};
			class Burukan_village1
			{
				name="Tugur";
				position[]={1738,6131};
				type="Local";
			};
			class Burukan_village2
			{
				name="Neran";
				position[]={2666,9297};
				type="Local";
			};
			class Burukan_village3
			{
				name="Kekra";
				position[]={7188,4235};
				type="Local";
			};
			class Burukan_village4
			{
				name="Ayan";
				position[]={1243,3022};
				type="Local";
			};
			class Burukan_Mys
			{
				name="Cherny Mys";
				position[]={5084,3592};
				type="Local";
			};
		};
	};	
};	