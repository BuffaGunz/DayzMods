class CfgPatches
{
    class RuckAirDrop
    {
        units[] = {""};
        weapons[] = {};
        requiredAddons[] = {"DZ_Data", "DZ_Sounds_Effects"};
    };
};

class CfgMods
{
    class RuckAirDrop
    {
        dir = "RuckAirDrop";
        name = " Ruck Air Drop";
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
                files[] = {"RuckAirDrop/Scripts/3_Game"};
            };
            class worldScriptModule
            {
                value = "";
                files[] = {"RuckAirDrop/Scripts/4_World"};
            };
			class missionScriptModule
            {
                value = "";
                files[] = {"RuckAirDrop/Scripts/5_Mission"};
            };
        };
    };
};

class CfgVehicles
{
	class Land_Wreck_C130J_2;
	class Land_ContainerLocked_Red_DE;
	class Land_ContainerLocked_Blue_DE;
	class Land_ContainerLocked_Yellow_DE;
	class Land_ContainerLocked_Orange_DE;
	class Container_Base;
	class RuckPlane: Land_Wreck_C130J_2
	{
		scope=2;
		forceNavMesh=1;
	};
	class AirdropContainerRed: Land_ContainerLocked_Red_DE
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
	class AirdropContainerBlue: Land_ContainerLocked_Blue_DE
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
	class AirdropContainerYellow: Land_ContainerLocked_Yellow_DE
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
	class AirdropContainerOrange: Land_ContainerLocked_Orange_DE
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
	class RuckStorageRed: Container_Base
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
	class RuckStorageBlue: Container_Base
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
	class RuckStorageYellow: Container_Base
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
	class RuckStorageOrange: Container_Base
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

class CfgSoundShaders
{
	class baseCharacter_SoundShader;  // from DZ_Sounds_Effects

	class RuckPlane_Engine_SoundShader: baseCharacter_SoundShader
	{
		range = 3000;
	};

	class RuckPlane_Loop_SoundShader: RuckPlane_Engine_SoundShader
	{
		samples[] =
		{
			{ "\RuckAirDrop\Sound\RuckPlane", 1 }
		};
		volume = 1;
	};
};

class CfgSoundSets
{
	class baseCharacter_SoundSet; 

	class RuckPlane_Engine_SoundSet: baseCharacter_SoundSet
	{
		sound3DProcessingType = "Vehicle_Ext_3DProcessingType";
		distanceFilter = "softVehiclesDistanceFreqAttenuationFilter";
		volumeCurve = "vehicleEngineAttenuationCurve";
		volumeFactor = 1;
		spatial = 1;
		loop = 0; 
	};

	class RuckPlane_Loop_SoundSet: RuckPlane_Engine_SoundSet
	{
		soundShaders[] =
		{
			"RuckPlane_Loop_SoundShader"
		};
		volumeFactor = 1;
	};
};

class CfgSounds
{
	class default
	{
		name = "";
		titles[] = {};
	};

	class RuckPlane_Loop_Sound: default
	{
		sound[] =
		{
			"\RuckAirDrop\Sound\RuckPlane",
			1,
			1,
			1000
		};
	};
};