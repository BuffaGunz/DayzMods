class CfgPatches
{
    class PlaneEvent
    {
        units[] = {};
        weapons[] = {};
        requiredAddons[] = {"DZ_Data"};
    };
};

class CfgMods
{
    class PlaneEvent
    {
        dir = "PlaneEvent";
        name = "Plane Event";
		author="BuffaGunz";
        picture = "";
        action = "";
        hideName = 1;
        hidePicture = 1;
        version = "1.0";
        type = "mod";
        dependencies[] = {"Game", "World", "Mission"};

        class defs
        {
            class gameScriptModule
            {
                value = "";
                files[] = {"PlaneEvent/scripts/3_Game"};
            };
            class worldScriptModule
            {
                value = "";
                files[] = {"PlaneEvent/scripts/4_World"};
            };
			class missionScriptModule
            {
                value = "";
                files[] = {"PlaneEvent/scripts/5_Mission"};
            };
        };
    };
};

class CfgVehicles
{
	class Land_Wreck_C130J_Cargo;
	class Land_ContainerLocked_Red_DE;
	class Land_ContainerLocked_Blue_DE;
	class Land_ContainerLocked_Yellow_DE;
	class Land_ContainerLocked_Orange_DE;
	class Container_Base;
	class PlaneCrash: Land_Wreck_C130J_Cargo
	{
		scope=2;
		forceNavMesh=1;
	};
	class WreckContainerRed: Land_ContainerLocked_Red_DE
	{
		scope=2;
		forceNavMesh=1;
		attachments[]=
		{
		    "Truck_01_WoodenCrate1"
		};
		class GUIInventoryAttachmentsProps
		{
			class Cargo
			{
				name="Cargo";
				attachmentSlots[]=
				{
					"Truck_01_WoodenCrate1"
				};
			};
			
		};
	};
	class WreckContainerBlue: Land_ContainerLocked_Blue_DE
	{
		scope=2;
		forceNavMesh=1;
		attachments[]=
		{
		    "Truck_01_WoodenCrate1"
		};
		class GUIInventoryAttachmentsProps
		{
			class Cargo
			{
				name="Cargo";
				attachmentSlots[]=
				{
					"Truck_01_WoodenCrate1"
				};
			};
			
		};
	};
	class WreckContainerYellow: Land_ContainerLocked_Yellow_DE
	{
		scope=2;
		forceNavMesh=1;
		attachments[]=
		{
		    "Truck_01_WoodenCrate1"
		};
		class GUIInventoryAttachmentsProps
		{
			class Cargo
			{
				name="Cargo";
				attachmentSlots[]=
				{
					"Truck_01_WoodenCrate1"
				};
			};
			
		};
	};
	class WreckContainerOrange: Land_ContainerLocked_Orange_DE
	{
		scope=2;
		forceNavMesh=1;
		attachments[]=
		{
		    "Truck_01_WoodenCrate1"
		};
		class GUIInventoryAttachmentsProps
		{
			class Cargo
			{
				name="Cargo";
				attachmentSlots[]=
				{
					"Truck_01_WoodenCrate1"
				};
			};
			
		};
	};
	class RuckCrashStorage: Container_Base
	{
		scope=2;
		model="DZ\structures\Military\Misc\Misc_SupplyBox2.p3d";
		displayName="";
		descriptionShort="";
		inventorySlot[]=
		{
			"Truck_01_WoodenCrate1"
		};
		class Cargo
		{
			itemsCargoSize[]={10,100};
			openable=0;
			allowOwnedCargoManipulation=1;
		};
	};
};
