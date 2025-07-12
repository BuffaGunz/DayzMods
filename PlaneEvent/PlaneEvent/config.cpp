class CfgPatches
{
    class PlaneEvent
    {
        units[] = {"FlyingCargoPlane"};
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
	class HouseNoDestruct;
	class PlaneCrash: HouseNoDestruct
	{
		scope=2;
		model="\DZ\structures\Wrecks\Aircraft\Wreck_C130J_Cargo.p3d";
		forceNavMesh=1;
	};
};
