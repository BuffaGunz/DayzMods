class CfgPatches
{
	class RuckCarScripts_Carscripts
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = 
		{
			"DZ_Data",
			"DZ_Vehicles_Wheeled",
			"DZ_Vehicles_Water",
			"DZ_Gear_Medical",
			"DZ_Weapons_Melee",
			"DZ_Gear_Tools"
		};
	};
};

class CfgSlots
{
	class Slot_SeaChest
	{
		name="SeaChest";
		displayName="$STR_CfgVehicles_SeaChest0";
		ghostIcon="set:RuckCarAttachments image:SeaChest";
	};
	class Slot_JerryCan
	{
		name="JerryCan";
		displayName="$STR_CfgVehicles_CanisterGasoline0";
		ghostIcon="set:RuckCarAttachments image:JerryCan";
	};
	class Slot_TireRepairKit
	{
		name = "TireRepairKit";
		displayName = "$STR_CfgVehicles_TireRepairKit0";
		ghostIcon="set:RuckCarAttachments image:TireRepairKit";
	};
	class Slot_TireIron
	{
		name = "TireIron";
		displayName = "$STR_CfgVehicles_LugWrench0";
		ghostIcon="set:RuckCarAttachments image:TireIron";
	};
	class Slot_FirstAidKit
	{
		name = "FirstAidKit";
		displayName = "$STR_CfgVehicles_FirstAidKit0";
		ghostIcon="set:RuckCarAttachments image:FirstAidKit";
	};
	class Slot_Map
	{
		name = "Map";
		displayName = "$STR_CfgVehicles_ChernarusMap0";
		ghostIcon="set:RuckCarAttachments image:Map";
	};
	class Slot_FishingRod
	{
		name = "FishingRod";
		displayName = "$STR_CfgVehicles_FishingRod0";
		ghostIcon="set:RuckCarAttachments image:FishingRod";
	};
};

class CfgVehicles
{
	class SimulationModule;
	class Bottle_Base;
	class CanisterGasoline: Bottle_Base
	{
		inventorySlot[]+=
		{
			"JerryCan"
		};
	};
	class Container_Base;
	class SeaChest: Container_Base
	{
		inventorySlot[]+=
		{
			"SeaChest"
		};
	};
	class Inventory_Base;
	class TireRepairKit: Inventory_Base
	{
		inventorySlot[]+=
		{
			"TireRepairKit"
		};
	};
	class LugWrench: Inventory_Base
	{
		inventorySlot[]+=
		{
			"TireIron"
		};
	};
	class FirstAidKit: Container_Base
	{
		inventorySlot[]+=
		{
			"FirstAidKit"
		};
	};	
	class ItemMap;
	class ChernarusMap: ItemMap
	{
		inventorySlot[]+=
		{
			"Map"
		};
	};	
	class FishingRod_Base_New;
	class ImprovisedFishingRod: FishingRod_Base_New
	{
		inventorySlot[]+=
		{
			"FishingRod"
		};
	};	
	class FishingRod: FishingRod_Base_New
	{
		inventorySlot[]+=
		{
			"FishingRod"
		};
	};	
    class CarScript;
    class OffroadHatchback: CarScript
	{
		scope=2;
		displayName="$STR_OffroadHatchback0";
		descriptionShort="$STR_OffroadHatchback1";
		model="\dz\vehicles\wheeled\OffroadHatchback\OffroadHatchback.p3d";
		fuelCapacity=60;
		fuelConsumption=8;
		attachments[]+=
		{
			"Shoulder",
			"Back",
		    "Truck_01_WoodenCrate1",
		    "Truck_01_WoodenLogs",
			"Truck_01_WoodenPlanks",
			"Truck_01_MetalSheets",
			"SeaChest",
			"JerryCan",
			"TireRepairKit",
			"Camonet",
			"Backpack_1",
			"FishingRod",
			"Map",
			"FirstAidKit",
			"TireIron"
		};
		class SimulationModule: SimulationModule
		{
			class Throttle
			{
				reactionTime=0.99;
				defaultThrust=0.99;
				gentleThrust=0.7;
				turboCoef=4;
				gentleCoef=0.75;
			};
			class Brake
			{
				pressureBySpeed[]={0,0.8,10,0.8,20,0.8,40,0.8,60,0.8,80,0.8,100,0.8,120,0.8,150,0.8,200,0.8};
				gentleCoef=0.7;
				minPressure=0.2;
				reactionTime=0.2;
				driverless=0.1;
			};
			drive="DRIVE_AWD";
			class Engine
			{
				torqueCurve[]={650,50,750,100,1400,150,3400,200,5400,155,8000,0};
				inertia=0.11;
				frictionTorque=100;
				rollingFriction=0.5;
				viscousFriction=0.5;
				rpmIdle=800;
				rpmMin=900;
				rpmClutch=1000;
				rpmRedline=6500;
			};
		};
	    class GUIInventoryAttachmentsProps
	    {
		
		    class Body
		    {
			    name="$STR_attachment_Body0";
			    description="";
			    icon="set:dayz_inventory image:cat_vehicle_body";
			    attachmentSlots[]+=
			    {
				    "Shoulder",
					"Back",
					"Truck_01_WoodenCrate1",
					"Truck_01_WoodenLogs",
					"Truck_01_WoodenPlanks",
					"Truck_01_MetalSheets",
					"SeaChest",
					"JerryCan",
					"TireRepairKit",
					"Camonet",
					"Backpack_1",
					"FishingRod",
					"Map",
					"FirstAidKit",
					"TireIron"
			    };
		    };
	    };
	};
	class CivilianSedan: CarScript
	{
		scope=2;
		displayName="$STR_CivilianSedan0";
		descriptionShort="$STR_CivilianSedan1";
		model="\DZ\vehicles\wheeled\civiliansedan\CivilianSedan.p3d";
		fuelCapacity=60;
		fuelConsumption=8;
		attachments[]+=
		{
			"Shoulder",
			"Back",
		    "Truck_01_WoodenCrate1",
		    "Truck_01_WoodenLogs",
			"Truck_01_WoodenPlanks",
			"Truck_01_MetalSheets",
			"SeaChest",
			"JerryCan",
			"TireRepairKit",
			"Camonet",
			"Backpack_1",
			"FishingRod",
			"Map",
			"FirstAidKit",
			"TireIron"
		};
		class SimulationModule: SimulationModule
		{
			class Throttle
			{
				reactionTime=0.99;
				defaultThrust=0.99;
				gentleThrust=0.7;
				turboCoef=6;
				gentleCoef=0.7;
			};
			class Brake
			{
				pressureBySpeed[]={0,0.8,10,0.8,20,0.8,40,0.8,60,0.8,80,0.8,100,0.8,120,0.8,150,0.8,200,0.8};
				gentleCoef=0.7;
				minPressure=0.2;
				reactionTime=0.2;
				driverless=0.1;
			};
			drive="DRIVE_RWD";
			class Engine
			{
				torqueCurve[]={400,40,1000,197,1700,223,2500,227,4500,187,7000,0};
				inertia=0.44999999;
				frictionTorque=130;
				rollingFriction=1.5;
				viscousFriction=0.5;
				rpmIdle=850;
				rpmMin=900;
				rpmClutch=1000;
				rpmRedline=6000;
			};
		};
	    class GUIInventoryAttachmentsProps
	    {
		    class Body
		    {
			    name="$STR_attachment_Body0";
			    description="";
			    icon="set:dayz_inventory image:cat_vehicle_body";
			    attachmentSlots[]+=
			    {
				    "Shoulder",
					"Back",
					"Truck_01_WoodenCrate1",
					"Truck_01_WoodenLogs",
					"Truck_01_WoodenPlanks",
					"Truck_01_MetalSheets",
					"SeaChest",
					"JerryCan",
					"TireRepairKit",
					"Camonet",
					"Backpack_1",
					"FishingRod",
					"Map",
					"FirstAidKit",
					"TireIron"
			    };
		    };
	    };
	};
	class Hatchback_02: CarScript
	{
		scope=2;
		displayName="$STR_CivHatchback0";
		descriptionShort="$STR_CivHatchback1";
		model="\dz\vehicles\wheeled\Hatchback_02\Hatchback_02.p3d";
		fuelCapacity=60;
		fuelConsumption=8;
		attachments[]+=
		{
			"Shoulder",
			"Back",
		    "Truck_01_WoodenCrate1",
		    "Truck_01_WoodenLogs",
			"Truck_01_WoodenPlanks",
			"Truck_01_MetalSheets",
			"SeaChest",
			"JerryCan",
			"TireRepairKit",
			"Camonet",
			"Backpack_1",
			"FishingRod",
			"Map",
			"FirstAidKit",
			"TireIron"
		};
		class SimulationModule: SimulationModule
		{
			class Throttle
			{
				reactionTime=0.99;
				defaultThrust=0.99;
				gentleThrust=0.7;
				turboCoef=4;
				gentleCoef=0.75;
			};
			class Brake
			{
				pressureBySpeed[]={0,0.8,10,0.8,20,0.8,40,0.8,60,0.8,80,0.8,100,0.8,120,0.8,150,0.8,200,0.8};
				gentleCoef=0.7;
				minPressure=0.2;
				reactionTime=0.2;
				driverless=0.1;
			};
			drive="DRIVE_FWD";
			class Engine
			{
				torqueCurve[]={850,40,1150,130,2000,170,4400,226,5800,205,7500,0};
				inertia=0.20999999;
				frictionTorque=150;
				rollingFriction=0.2;
				viscousFriction=0.5;
				rpmIdle=850;
				rpmMin=900;
				rpmClutch=1000;
				rpmRedline=6000;
			};
		};
	    class GUIInventoryAttachmentsProps
	    {
		    class Body
		    {   
			    name="$STR_attachment_Body0";
			    description="";
			    icon="set:dayz_inventory image:cat_vehicle_body";
			    attachmentSlots[]+=
			    {
				    "Shoulder",
					"Back",
					"Truck_01_WoodenCrate1",
					"Truck_01_WoodenLogs",
					"Truck_01_WoodenPlanks",
					"Truck_01_MetalSheets",
					"SeaChest",
					"JerryCan",
					"TireRepairKit",
					"Camonet",
					"Backpack_1",
					"FishingRod",
					"Map",
					"FirstAidKit",
					"TireIron"
			    };
		    };
	    };
	};	
	class Sedan_02: CarScript
	{
		scope=2;
		displayName="$STR_Sedan_020";
		model="\DZ\vehicles\wheeled\Sedan_02\Sedan_02.p3d";
		fuelCapacity=60;
		fuelConsumption=8;
		attachments[]+=
		{
			"Shoulder",
			"Back",
		    "Truck_01_WoodenCrate1",
		    "Truck_01_WoodenLogs",
			"Truck_01_WoodenPlanks",
			"Truck_01_MetalSheets",
			"SeaChest",
			"JerryCan",
			"TireRepairKit",
			"Camonet",
			"Backpack_1",
			"FishingRod",
			"Map",
			"FirstAidKit",
			"TireIron"
		};
		class SimulationModule: SimulationModule
		{
			class Throttle
			{
				reactionTime=0.99;
				defaultThrust=0.99;
				gentleThrust=0.7;
				turboCoef=4;
				gentleCoef=0.75;
			};
			class Brake
			{
				pressureBySpeed[]={0,0.8,10,0.8,20,0.8,40,0.8,60,0.8,80,0.8,100,0.8,120,0.8,150,0.8,200,0.8};
				gentleCoef=0.7;
				minPressure=0.2;
				reactionTime=0.2;
				driverless=0.1;
			};
			drive="DRIVE_RWD";
			class Engine
			{
				torqueCurve[]={600,40,990,90,1800,115,3000,122,5000,111,7000,0};
				inertia=0.2;
				frictionTorque=80;
				rollingFriction=0.5;
				viscousFriction=0;
				rpmIdle=900;
				rpmMin=1000;
				rpmClutch=1000;
				rpmRedline=5500;
			};
		};
	    class GUIInventoryAttachmentsProps
	    {
		    class Body
		    {
			    name="$STR_attachment_Body0";
			    description="";
			    icon="set:dayz_inventory image:cat_vehicle_body";
			    attachmentSlots[]+=
			    {
				    "Shoulder",
					"Back",
					"Truck_01_WoodenCrate1",
					"Truck_01_WoodenLogs",
					"Truck_01_WoodenPlanks",
					"Truck_01_MetalSheets",
					"SeaChest",
					"JerryCan",
					"TireRepairKit",
					"Camonet",
					"Backpack_1",
					"FishingRod",
					"Map",
					"FirstAidKit",
					"TireIron"
			    };
		    };
	    };	
    };
	class Offroad_02: CarScript
	{
		attachments[]+=
		{
			"Shoulder",
			"Back",
		    "Truck_01_WoodenCrate1",
		    "Truck_01_WoodenLogs",
			"Truck_01_WoodenPlanks",
			"Truck_01_MetalSheets",
			"SeaChest",
			"JerryCan",
			"TireRepairKit",
			"Camonet",
			"Backpack_1",
			"FishingRod",
			"Map",
			"FirstAidKit",
			"TireIron"
		};
		class GUIInventoryAttachmentsProps
		{
			class Body
			{
				name="$STR_attachment_Body0";
				description="";
				icon="set:dayz_inventory image:cat_vehicle_body";
				attachmentSlots[]+=
				{
					"Shoulder",
					"Back",
					"Truck_01_WoodenCrate1",
					"Truck_01_WoodenLogs",
					"Truck_01_WoodenPlanks",
					"Truck_01_MetalSheets",
					"SeaChest",
					"JerryCan",
					"TireRepairKit",
					"Camonet",
					"Backpack_1",
					"FishingRod",
					"Map",
					"FirstAidKit",
					"TireIron"
				};
			};
		};
	};	
	class Boat;
	class BoatScript: Boat
	{
		debug_ItemCategory=8;
		storageCategory=4;
		class Crew
		{
			class Driver
			{
				actionSel="seat_driver";
				proxyPos="crewDriver";
				getInPos="pos_driver";
				getInDir="pos_driver_dir";
				isDriver=1;
			};
		};
		class Buoyancy
		{
			linearDampeningCoefficient=0;
			angularDampeningCoefficient=0;
			linearDragCoefficient=0.2;
			quadraticDragCoefficient=0.2;
			falloffPower=0.80000001;
			sinkRate=0.050000001;
		};
	};
	class Boat_01_ColorBase: BoatScript
	{
		fuelCapacity=40;
		fuelConsumption=2.0;
		attachments[]+=
		{
			"Shoulder",
			"Back",
			"SeaChest",
			"JerryCan",
			"SparkPlug",
			"TireRepairKit",
			"Backpack_1",
			"FishingRod",
			"Map",
			"FirstAidKit"
		};
		class SimulationModule
		{
			class Engine
			{
				torqueCurve[]={500,110,1000,150,1500,190,2500,280,3500,370,4800,280,6500,110,7000,0};
				inertia=1.1;
				frictionTorque=200;
				rollingFriction=1.5;
				viscousFriction=0.80000001;
				rpmIdle=850;
				rpmMin=900;
				rpmClutch=1000;
				rpmRedline=6500;
			};
			class Throttle
			{
				defaultThrust=0.99;
				turboIncrease=4;
				regularIncrease=2;
				slowIncrease=1.12;
				turboDecrease=1.5;
				regularDecrease=1.5;
				slowDecrease=1;
				autoDecrease=1;
			};
		}; 
		class Cargo
		{
			itemsCargoSize[]={10,30};
			allowOwnedCargoManipulation=1;
			openable=0;
		};
		class GUIInventoryAttachmentsProps
		{
			class Chassis
			{
				attachmentSlots[]+=
				{
					"Shoulder",
			        "Back",
					"SeaChest",
			        "JerryCan",
					"TireRepairKit",
					"Backpack_1",
					"FishingRod",
					"Map",
					"FirstAidKit"
				};
			};
		};
	};	
	class CarWheel: Inventory_Base
	{
	};
	class Offroad_02_Wheel: CarWheel
	{
		inventorySlot[]+=
		{
			"Truck_01_Wheel_1_1",
			"Truck_01_Wheel_2_1",
			"Truck_01_Wheel_Spare_1",
			"Truck_01_Wheel_Spare_2",
			"Truck_01_Wheel_1_2",
			"Truck_01_Wheel_1_3",
			"Truck_01_Wheel_2_2",
			"Truck_01_Wheel_2_3"
		};
		tyreOffroadResistance=1;
		tyreGrip=0.94999999;
		tyreRollResistance=0.017999999;
	};
	class HatchbackWheel: CarWheel
	{
		inventorySlot[]+=
		{
			"Hatchback_02_Wheel_1_1",
			"Hatchback_02_Wheel_1_2",
			"Hatchback_02_Wheel_2_1",
			"Hatchback_02_Wheel_2_2",
			"Hatchback_02_Wheel_Spare_1",
			"NivaWheel_Spare_1",
			"CivSedanWheel_1_1",
			"CivSedanWheel_1_2",
			"CivSedanWheel_2_1",
			"CivSedanWheel_2_2",
			"CivSedanWheel_Spare_1",
			"Sedan_02_Wheel_1_1",
			"Sedan_02_Wheel_1_2",
			"Sedan_02_Wheel_2_1",
			"Sedan_02_Wheel_2_2",
			"Sedan_02_Wheel_Spare_1"
		};
		tyreOffroadResistance=1;
		tyreGrip=0.94999999;
		tyreRollResistance=0.017999999;
	};
	class CivSedanWheel: CarWheel
	{
		inventorySlot[]+=
		{
			"NivaWheel_1_1",
			"NivaWheel_1_2",
			"NivaWheel_2_1",
			"NivaWheel_2_2",
			"NivaWheel_Spare_1",
			"Hatchback_02_Wheel_1_1",
			"Hatchback_02_Wheel_1_2",
			"Hatchback_02_Wheel_2_1",
			"Hatchback_02_Wheel_2_2",
			"Hatchback_02_Wheel_Spare_1",
			"Sedan_02_Wheel_1_1",
			"Sedan_02_Wheel_1_2",
			"Sedan_02_Wheel_2_1",
			"Sedan_02_Wheel_2_2",
			"Sedan_02_Wheel_Spare_1"
		};
		tyreOffroadResistance=1;
		tyreGrip=0.94999999;
		tyreRollResistance=0.017999999;
	};
	class Hatchback_02_Wheel: CarWheel
	{
		inventorySlot[]+=
		{
			"NivaWheel_1_1",
			"NivaWheel_1_2",
			"NivaWheel_2_1",
			"NivaWheel_2_2",
			"NivaWheel_Spare_1",
			"CivSedanWheel_1_1",
			"CivSedanWheel_1_2",
			"CivSedanWheel_2_1",
			"CivSedanWheel_2_2",
			"CivSedanWheel_Spare_1",
			"Sedan_02_Wheel_1_1",
			"Sedan_02_Wheel_1_2",
			"Sedan_02_Wheel_2_1",
			"Sedan_02_Wheel_2_2",
			"Sedan_02_Wheel_Spare_1"
		};
		tyreOffroadResistance=1;
		tyreGrip=0.94999999;
		tyreRollResistance=0.017999999;
	};
	class Sedan_02_Wheel: CarWheel
	{
		inventorySlot[]+=
		{
			"NivaWheel_1_1",
			"NivaWheel_1_2",
			"NivaWheel_2_1",
			"NivaWheel_2_2",
			"NivaWheel_Spare_1",
			"CivSedanWheel_1_1",
			"CivSedanWheel_1_2",
			"CivSedanWheel_2_1",
			"CivSedanWheel_2_2",
			"CivSedanWheel_Spare_1",
			"Hatchback_02_Wheel_1_1",
			"Hatchback_02_Wheel_1_2",
			"Hatchback_02_Wheel_2_1",
			"Hatchback_02_Wheel_2_2",
			"Hatchback_02_Wheel_Spare_1"
		};
		tyreOffroadResistance=1;
		tyreGrip=0.94999999;
		tyreRollResistance=0.017999999;
	};
	class Truck_01_Wheel: CarWheel
	{
		inventorySlot[]+=
		{
			"Offroad_02_Wheel_1_1",
			"Offroad_02_Wheel_1_2",
			"Offroad_02_Wheel_2_1",
			"Offroad_02_Wheel_2_2",
			"Offroad_02_Wheel_Spare_1"
		};
	};
	class Truck_01_WheelDouble: Truck_01_Wheel
	{
		inventorySlot[]+=
		{
			"Offroad_02_Wheel_1_1",
			"Offroad_02_Wheel_1_2",
			"Offroad_02_Wheel_2_1",
			"Offroad_02_Wheel_2_2",
			"Offroad_02_Wheel_Spare_1",
		};
	};
};	