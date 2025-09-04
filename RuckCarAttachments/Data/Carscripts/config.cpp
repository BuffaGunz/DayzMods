class CfgPatches
{
	class RuckCarAttachments_Carscripts
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
			"Backpack_1",
			"TireIron"
		};
	};
	class FirstAidKit: Container_Base
	{
		inventorySlot[]+=
		{
			"Backpack_1",
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
			"Shoulder",
			"Melee",
			"FishingRod"
		};
	};	
	class FishingRod: FishingRod_Base_New
	{
		inventorySlot[]+=
		{
			"Backpack_1",
			"FishingRod"
		};
	};	
    class CarScript;
    class OffroadHatchback: CarScript
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
	class CivilianSedan: CarScript
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
	class Hatchback_02: CarScript
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
	class Sedan_02: CarScript
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
	class BoatScript;
	class Boat_01_ColorBase: BoatScript
	{
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
		class Cargo
		{
			itemsCargoSize[]={10,30};
			allowOwnedCargoManipulation=1;
			openable=0;
		};
	};	
};	