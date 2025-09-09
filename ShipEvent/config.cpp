class CfgPatches
{
    class ShipEvent
    {
        units[] = {"ShipCrash"};
        weapons[] = {};
        requiredAddons[] = {"DZ_Data"};
    };
};

class CfgMods
{
    class ShipEvent
    {
        dir = "ShipEvent";
        name = "Ship Event";
		author="BuffaGunz";
        picture = "";
        action = "";
        hideName = 1;
        hidePicture = 1;
        version = "1.0";
        type = "mod";
        dependencies[] = 
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
					"ShipEvent/scripts/Common"
				};
			};
			class gameLibScriptModule
			{
				files[]=
				{
					"ShipEvent/scripts/Common"
				};
			};
            class gameScriptModule
            {
                value = "";
                files[] = 
				{
					"ShipEvent/scripts/Common",
					"ShipEvent/scripts/3_Game"
				};
            };
            class worldScriptModule
            {
                value = "";
                files[] = 
				{
					"ShipEvent/scripts/Common",
					"ShipEvent/scripts/4_World"
				};
            };
			class missionScriptModule
            {
                value = "";
                files[] = 
				{
					"ShipEvent/scripts/Common",
					"ShipEvent/scripts/5_Mission"
				};
            };
        };
    };
};

class CfgVehicles
{
	class Land_Ship_Medium2;
	class Land_ContainerLocked_Red_DE;
	class Land_ContainerLocked_Blue_DE;
	class Land_ContainerLocked_Yellow_DE;
	class Land_ContainerLocked_Orange_DE;
	class Container_Base;
	class ShipWreck: Land_Ship_Medium2
	{
		scope=2;
		forceNavMesh=1;
		storageCategory=4;
	};
	class ShipContainerRed: Land_ContainerLocked_Red_DE
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
	class ShipContainerBlue: Land_ContainerLocked_Blue_DE
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
	class ShipContainerYellow: Land_ContainerLocked_Yellow_DE
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
	class ShipContainerOrange: Land_ContainerLocked_Orange_DE
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
	class RuckShipStorage: Container_Base
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

class CfgSoundshaders
{
	class HeliCrash_Distant_SoundShader;
	class ShipWreck_SoundShader: HeliCrash_Distant_SoundShader
	{
		samples[]=
		{
			
			{
				"\ShipEvent\Sound\ShipWreck",
				1
			}
		};
		volume=1.5;
		range=3500;
	};
};

class CfgSoundsets
{
	class HeliCrash_Distant_Base_SoundSet;
	class ShipWreck_SoundSet: HeliCrash_Distant_Base_SoundSet
	{
		soundShaders[]=
		{
			"ShipWreck_SoundShader"
		};
		sound3DProcessingType="ThunderNear3DProcessingType";
	};
};
