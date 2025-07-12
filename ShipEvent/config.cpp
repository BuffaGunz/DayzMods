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
        dependencies[] = {"Game", "World", "Mission"};

        class defs
        {
            class gameScriptModule
            {
                value = "";
                files[] = {"ShipEvent/scripts/3_Game"};
            };
            class worldScriptModule
            {
                value = "";
                files[] = {"ShipEvent/scripts/4_World"};
            };
			class missionScriptModule
            {
                value = "";
                files[] = {"ShipEvent/scripts/5_Mission"};
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
	class ShipWreck: Land_Ship_Medium2
	{
		scope=2;
		forceNavMesh=1;
	};
	class ContainerRed: Land_ContainerLocked_Red_DE
	{
		scope=2;
		forceNavMesh=1;
	};
	class ContainerBlue: Land_ContainerLocked_Blue_DE
	{
		scope=2;
		forceNavMesh=1;
	};
	class ContainerYellow: Land_ContainerLocked_Yellow_DE
	{
		scope=2;
		forceNavMesh=1;
	};
	class ContainerOrange: Land_ContainerLocked_Orange_DE
	{
		scope=2;
		forceNavMesh=1;
	};
};
