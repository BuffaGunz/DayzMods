class CfgPatches
{
	class RuckTruck_Truck
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Scripts",
			"DZ_Data",
			"DZ_Sounds_Effects",
			"DZ_Vehicles_Wheeled",
			"DZ_Vehicles_Parts"
		};
	};
};

class cfgvehicles
{
	class Health;
	class Window;
	class CarDoor;
	class Doors;
	class CarScript;
	class Crew;
	class Driver;
	class CoDriver;
	class DamageSystem;
	class GlobalHealth;
	class DamageZones;
	class SimulationModule;
	class Axles;
	class Front;
	class Rear;
	class Wheels;
	class Left;
	class Right;
	class AnimationSources;
	class GUIInventoryAttachmentsProps;
	class Body;
    class Inventory_Base;
	class CarWheel;
	class AllDrive;
	class truck_02_wheel: CarWheel
	{
		scope=2;
		displayName="#STR_CfgWheel0";
		descriptionShort="Wheel Fits Hippy Van";
		model="\DZ\vehicles\wheeled\truck_02\proxy\truck_02_wheel.p3d";
		weight=15000;
		inventorySlot[]=
		{
			"truck_02_wheel_1_1",
			"truck_02_wheel_1_2",
			"truck_02_wheel_2_1",
			"truck_02_wheel_2_2",
			"truck_02_wheel_spare"
		};
		rotationFlags=4;
		repairableWithKits[]={6};
		repairCosts[]={30};
		radiusByDamage[]={0,0.36199999,0.30000001,0.30000001,0.99980003,0.25,0.99989998,0.2};
		radius=0.34999999;
		width=0.17;
		tyreOffroadResistance=0.99;
		tyreGrip=0.99;
		tyreRollResistance=0.015;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=200;
					healthLevels[]=
					{
						
						{
							1,
							{}
						},
						
						{
							0.69999999,
							{}
						},
						
						{
							0.5,
							{}
						},
						
						{
							0.30000001,
							{}
						},
						
						{
							0,
							{}
						}
					};
				};
			};
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class drop
				{
					soundset="hatchbackwheel_drop_SoundSet";
					id=898;
				};
			};
		};
	};
	class truck_02_wheel_ruined: truck_02_wheel
	{
		model="\DZ\vehicles\wheeled\truck_02\proxy\truck_02_wheel_ruined.p3d";
		radius=0.315;
		width=0.27000001;
		tyreOffroadResistance=0.1;
		tyreGrip=0.40000001;
		tyreRollResistance=0.31999999;
	};
	class truck_02_door_1_1: CarDoor
	{
		scope=2;
		displayName="#STR_CfgDoor0";
		descriptionShort="DriverDoor";
		model="\DZ\vehicles\wheeled\truck_02\proxy\truck_02_door_1_1.p3d";
		weight=15000;
		inventorySlot[]=
		{
			"truck_02_door_1_1"
		};
		rotationFlags=8;
		hiddenSelectionsMaterials[]=
		{
			"\DZ\vehicles\wheeled\truck_02\data\truck_02_door.rvmat"
		}; 

	};
	class truck_02_door_2_1: truck_02_door_1_1
	{
		displayName="#STR_CfgDoor0";
		descriptionShort="CoDriverDoor";
		model="\DZ\vehicles\wheeled\truck_02\proxy\truck_02_door_2_1.p3d";
		inventorySlot[]=
		{
			"truck_02_door_2_1"
		};
		rotationFlags=4;
	};
	class Truck_02_Base: Carscript
	{
		scope=0;
		InteractActions[]=
		{
			"AT_ANIMATE_SEATS",
			"AT_GETIN_TRANSPORT"
		};
		descriptionShort="Sweet Home Alabama";
		Model="\DZ\vehicles\wheeled\truck_02\truck_02.p3d";
		attachments[]=
		{
			"TruckBattery",
			"Reflector_1_1",
			"Reflector_2_1",
			"SparkPlug",
			"truck_02_door_1_1",
			"truck_02_door_2_1",
			"truck_02_wheel_1_1",
			"truck_02_wheel_1_2",
			"truck_02_wheel_2_1",
			"truck_02_wheel_2_2",
			"truck_02_wheel_spare"
		};
		hiddenSelections[]=
		{
			"light_1_1",
			"light_2_1", 
			"dmgZone_chassis",
			"dmgZone_front",
			"dmgZone_back",
			"dmgZone_roof",
			"dmgZone_fender_1_1",
			"dmgZone_fender_1_2",
			"dmgZone_fender_2_1",
			"dmgZone_fender_2_2"
		};
		hiddenSelectionsTextures[]=
		{
			"dz\vehicles\wheeled\offroadhatchback\data\headlights_glass.paa",
			"dz\vehicles\wheeled\offroadhatchback\data\headlights_glass.paa",
			"",
			"",
			"",
			"",
			"",
			"",
			"",
			"",
			"",
			""
		};
		hiddenSelectionsMaterials[]=
		{
			"dz\vehicles\wheeled\offroadhatchback\data\headlights_glass.rvmat",
			"dz\vehicles\wheeled\offroadhatchback\data\headlights_glass.rvmat",
			"DZ\vehicles\wheeled\truck_02\data\truck_02_base.rvmat",
			"DZ\vehicles\wheeled\truck_02\data\truck_02_base.rvmat",
			"DZ\vehicles\wheeled\truck_02\data\truck_02_base.rvmat",
			"DZ\vehicles\wheeled\truck_02\data\truck_02_base.rvmat",
			"DZ\vehicles\wheeled\truck_02\data\truck_02_base.rvmat",
			"DZ\vehicles\wheeled\truck_02\data\truck_02_base.rvmat",
			"DZ\vehicles\wheeled\truck_02\data\truck_02_base.rvmat",
			"DZ\vehicles\wheeled\truck_02\data\truck_02_base.rvmat",
			"DZ\vehicles\wheeled\truck_02\data\truck_02_base.rvmat",
			"DZ\vehicles\wheeled\truck_02\data\truck_02_base.rvmat"
		};
		dashboardMatOn="\DZ\vehicles\wheeled\truck_02\data\truck_02_interior.rvmat";
		dashboardMatOff="\DZ\vehicles\wheeled\truck_02\data\truck_02_interior.rvmat";
		frontReflectorMatOn="DZ\vehicles\wheeled\truck_02\data\truck_02_base.rvmat";
		frontReflectorMatOff="DZ\vehicles\wheeled\truck_02\data\truck_02_base.rvmat";
		brakeReflectorMatOn="DZ\vehicles\wheeled\truck_02\data\truck_02_base.rvmat";
		brakeReflectorMatOff="DZ\vehicles\wheeled\truck_02\data\truck_02_base.rvmat";
		ReverseReflectorMatOn="DZ\vehicles\wheeled\truck_02\data\truck_02_base.rvmat";
		ReverseReflectorMatOff="DZ\vehicles\wheeled\truck_02\data\truck_02_base.rvmat";
		TailReflectorMatOn="DZ\vehicles\wheeled\truck_02\data\truck_02_base.rvmat";
		TailReflectorMatOff="DZ\vehicles\wheeled\truck_02\data\truck_02_base.rvmat";
		fuelCapacity=42;
		fuelConsumption=11;
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
			class CoDriver
			{
				isDriver=0;
				actionSel="seat_codriver";
				proxyPos="crewCoDriver";
				getInPos="pos_codriver";
				getInDir="pos_codriver_dir";
			};
		};
		class SimulationModule: SimulationModule
		{
			class Steering
			{
				maxSteeringAngle=30;
				increaseSpeed[]={0,40,30,20,100,5};
				decreaseSpeed[]={0,80,60,40,90,20};
				centeringSpeed[]={0,0,15,25,60,40,100,60};
			};
			class Throttle
			{
				reactionTime=0.99;
				defaultThrust=0.99;
				gentleThrust=0.8;
				turboCoef=4;
				gentleCoef=0.75;
			};
			class Brake
			{
				pressureBySpeed[]={0,0.75,10,0.64999998,20,0.5,40,0.40000001,60,0.43000001,80,0.44999999,100,0.5,120,0.64999998};
				gentleCoef=0.64999998;
				minPressure=0.2;
				reactionTime=0.30000001;
				driverless=0.1;
			};
			class Aerodynamics
			{
				frontalArea=2.1800001;
				dragCoefficient=0.56;
			};
			drive="DRIVE_AWD";
			class Engine
			{
				torqueCurve[]={650,50,750,90,1400,130,3400,164,5400,145,8000,0};
				inertia=0.11;
				frictionTorque=100;
				rollingFriction=0.5;
				viscousFriction=0.5;
				rpmIdle=800;
				rpmMin=900;
				rpmClutch=1400;
				rpmRedline=6000;
			};
			class Clutch
			{
				maxTorqueTransfer=240;
				uncoupleTime=0.30000001;
				coupleTime=0.44999999;
			};
			class Gearbox
			{
				type="GEARBOX_MANUAL";
				reverse=3.526;
				ratios[]={3.6670001,2.0999999,1.3609999,1};
			};
			class CentralDifferential
			{
				ratio=1.5;
				type="DIFFERENTIAL_LOCKED";
			};
			class Axles: Axles
			{
				class Front: Front
				{
					maxBrakeTorque=950;
					maxHandbrakeTorque=2500;
					wheelHubMass=5;
					wheelHubRadius=0.15000001;
					class Differential
					{
						ratio=4.0999999;
						type="DIFFERENTIAL_OPEN";
					};
					class Suspension
					{
						stiffness=40000;
						compression=2100;
						damping=7500;
						travelMaxUp=0.088200003;
						travelMaxDown=0.083300002;
					};
					class Wheels: Wheels
					{
						class Left: Left
						{
							animDamper="damper_1_1";
							inventorySlot="truck_02_wheel_1_1";
						};
						class Right: Right
						{
							animDamper="damper_2_1";
							inventorySlot="truck_02_wheel_2_1";
						};
					};
				};
				class Rear: Rear
				{
					maxBrakeTorque=780;
					maxHandbrakeTorque=2500;
					wheelHubMass=5;
					wheelHubRadius=0.15000001;
					class Differential
					{
						ratio=4.0999999;
						type="DIFFERENTIAL_OPEN";
					};
					class Suspension
					{
						stiffness=40000;
						compression=2200;
						damping=7600;
						travelMaxUp=0.1587;
						travelMaxDown=0.1059;
					};
					class Wheels: Wheels
					{
						class Left: Left
						{
							animDamper="damper_1_2";
							inventorySlot="truck_02_wheel_1_2";
						};
						class Right: Right
						{
							animDamper="damper_2_2";
							inventorySlot="truck_02_wheel_2_2";
						};
					};
				};
			};
		};
		class Cargo
		{
			itemsCargoSize[]={10,30};
			allowOwnedCargoManipulation=1;
			openable=0;
		};
		class AnimationSources
		{
			class DoorsDriver
			{
				source="user";
				initPhase=0;
				animPeriod=0.5;
			};
			class DoorsCoDriver: DoorsDriver
			{
			};
			class DoorsHood: DoorsDriver
			{
			};
			class DoorsTrunk: DoorsDriver
			{
			};
			class HideDestroyed_1_1
			{
				source="user";
				initPhase=0;
				animPeriod=0.001;
			};
			class HideDestroyed_1_2
			{
				source="user";
				initPhase=0;
				animPeriod=0.001;
			};
			class HideDestroyed_2_1
			{
				source="user";
				initPhase=0;
				animPeriod=0.001;
			};
			class HideDestroyed_2_2
			{
				source="user";
				initPhase=0;
				animPeriod=0.001;
			};
			class AnimHitWheel_1_1
			{
				source="Hit";
				hitpoint="HitWheel_1_1";
				raw=1;
			};
			class AnimHitWheel_1_2: AnimHitWheel_1_1
			{
				hitpoint="HitWheel_1_2";
			};
			class AnimHitWheel_2_1: AnimHitWheel_1_1
			{
				hitpoint="HitWheel_2_1";
			};
			class AnimHitWheel_2_2: AnimHitWheel_1_1
			{
				hitpoint="HitWheel_2_2";
			};
			class HitDoorsHood: AnimHitWheel_1_1
			{
				hitpoint="HitDoorsHood";
			};
			class HitDoorsTrunk: AnimHitWheel_1_1
			{
				hitpoint="HitDoorsTrunk";
			};
			class HitDoorsDrivers: AnimHitWheel_1_1
			{
				hitpoint="HitDoorsDriver";
			};
			class HitDoorsCoDrivers: AnimHitWheel_1_1
			{
				hitpoint="HitDoorsCoDriver";
			};
			class HitDoorsCargo: AnimHitWheel_1_1
			{
				hitpoint="HitDoorsCargo";
			};
		};
		class NoiseCarHorn
		{
			strength=30;
			type="sound";
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=5000;
					healthLevels[]=
					{
						
						{
							1,
							{}
						},
						
						{
							0.69999999,
							{}
						},
						
						{
							0.5,
							{}
						},
						
						{
							0.30000001,
							{}
						},
						
						{
							0,
							{}
						}
					};
				};
			};
			class DamageZones
			{
				class Chassis
				{
					displayName="$STR_CfgVehicleDmg_Chassis0";
					fatalInjuryCoef=-1;
					componentNames[]=
					{
						"dmgZone_chassis"
					};
					class Health
					{
						hitpoints=3000;
						transferToGlobalCoef=0;
					};
					inventorySlots[]={};
				};
				class Front
				{
					displayName="$STR_CfgVehicleDmg_Bumper0";
					fatalInjuryCoef=-1;
					memoryPoints[]=
					{
						"dmgZone_front"
					};
					componentNames[]=
					{
						"dmgZone_front"
					};
					class Health
					{
						hitpoints=1200;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1,
								
								{
									"DZ\vehicles\wheeled\truck_02\data\truck_02_base.rvmat"
								}
							},
							
							{
								0.69999999,
								
								{
									"DZ\vehicles\wheeled\truck_02\data\truck_02_base.rvmat"
								}
							},
							
							{
								0.5,
								
								{
									"DZ\vehicles\wheeled\truck_02\data\truck_02_base.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									"DZ\vehicles\wheeled\truck_02\data\truck_02_base.rvmat"
								}
							},
							
							{
								0,
								
								{
									"DZ\vehicles\wheeled\truck_02\data\truck_02_base.rvmat"
								}
							}
						};
					};
					transferToZonesNames[]=
					{
						"Fender_1_1",
						"Fender_2_1",
						"Engine"
					};
					transferToZonesCoefs[]={0.1,0.1,0.15000001};
					inventorySlots[]=
					{
						"truck_02_wheel_1_1",
						"truck_02_wheel_2_1"
					};
					inventorySlotsCoefs[]={0.30000001,0.25,0.1,0.1};
				};
				class Reflector_1_1
				{
					displayName="$STR_CfgVehicleDmg_Reflector0";
					fatalInjuryCoef=-1;
					componentNames[]=
					{
						"dmgZone_lights_1_1"
					};
					memoryPoints[]=
					{
						"dmgZone_lights_1_1"
					};
					class Health
					{
						hitpoints=10;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1,
								
								{
									"DZ\vehicles\wheeled\truck_02\data\truck_02_windows.rvmat"
								}
							},
							
							{
								0.69999999,
								{}
							},
							
							{
								0.5,
								
								{
									"DZ\vehicles\wheeled\truck_02\data\truck_02_windows.rvmat"
								}
							},
							
							{
								0.30000001,
								{}
							},
							
							{
								0,
								
								{
									"DZ\vehicles\wheeled\truck_02\data\truck_02_windows.rvmat"
								}
							}
						};
					};
					transferToZonesNames[]=
					{
						"Front",
						"Fender_1_1"
					};
					transferToZonesCoefs[]={1,1};
					inventorySlots[]=
					{
						"Reflector_1_1",
						"truck_02_wheel_1_1"
					};
					inventorySlotsCoefs[]={1,0.1};
				};
				class Reflector_2_1: Reflector_1_1
				{
					memoryPoints[]=
					{
						"dmgZone_lights_2_1"
					};
					componentNames[]=
					{
						"dmgZone_lights_2_1"
					};
					transferToZonesNames[]=
					{
						"Front",
						"Fender_2_1"
					};
					inventorySlots[]=
					{
						"Reflector_2_1",
						"truck_02_wheel_2_1"
					};
				};
				class Back
				{
					displayName="$STR_CfgVehicleDmg_Bumper0";
					fatalInjuryCoef=-1;
					memoryPoints[]=
					{
						"dmgZone_back"
					};
					componentNames[]=
					{
						"dmgZone_back"
					};
					class Health
					{
						hitpoints=1500;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1,
								
								{
									"DZ\vehicles\wheeled\truck_02\data\truck_02_base.rvmat"
								}
							},
							
							{
								0.69999999,
								
								{
									"DZ\vehicles\wheeled\truck_02\data\truck_02_base.rvmat"
								}
							},
							
							{
								0.5,
								
								{
									"DZ\vehicles\wheeled\truck_02\data\truck_02_base.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									"DZ\vehicles\wheeled\truck_02\data\truck_02_base.rvmat"
								}
							},
							
							{
								0,
								
								{
									"DZ\vehicles\wheeled\truck_02\data\truck_02_base.rvmat"
								}
							}
						};
					};
					transferToZonesNames[]=
					{
						"Fender_1_2",
						"Fender_2_2",
						"WindowLR",
						"WindowRR"
					};
					transferToZonesCoefs[]={0.15000001,0.15000001,0.050000001,0.050000001};
					inventorySlots[]=
					{
						"truck_02_wheel_1_2",
						"truck_02_wheel_2_2"
					};
					inventorySlotsCoefs[]={0.40000001,0.1,0.1};
				};
				class Roof
				{
					displayName="$STR_CfgVehicleDmg_Roof0";
					fatalInjuryCoef=-1;
					componentNames[]=
					{
						"dmgZone_roof"
					};
					memoryPoints[]=
					{
						"dmgZone_roof"
					};
					class Health
					{
						hitpoints=700;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1,
								
								{
									"DZ\vehicles\wheeled\truck_02\data\truck_02_base.rvmat"
								}
							},
							
							{
								0.69999999,
								
								{
									"DZ\vehicles\wheeled\truck_02\data\truck_02_base.rvmat"
								}
							},
							
							{
								0.5,
								
								{
									"DZ\vehicles\wheeled\truck_02\data\truck_02_base.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									"DZ\vehicles\wheeled\truck_02\data\truck_02_base.rvmat"
								}
							},
							
							{
								0,
								
								{
									"DZ\vehicles\wheeled\truck_02\data\truck_02_base.rvmat"
								}
							}
						};
					};
					inventorySlotsCoefs[]={};
					inventorySlots[]={};
				};
				class Fender_1_1
				{
					displayName="$STR_CfgVehicleDmg_Fender0";
					fatalInjuryCoef=-1;
					componentNames[]=
					{
						"dmgZone_fender_1_1"
					};
					memoryPoints[]=
					{
						"dmgZone_fender_1_1"
					};
					class Health
					{
						hitpoints=1200;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1,
								
								{
									"DZ\vehicles\wheeled\truck_02\data\truck_02_base.rvmat"
								}
							},
							
							{
								0.69999999,
								
								{
									"DZ\vehicles\wheeled\truck_02\data\truck_02_base.rvmat"
								}
							},
							
							{
								0.5,
								
								{
									"DZ\vehicles\wheeled\truck_02\data\truck_02_base.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									"DZ\vehicles\wheeled\truck_02\data\truck_02_base.rvmat"
								}
							},
							
							{
								0,
								
								{
									"DZ\vehicles\wheeled\truck_02\data\truck_02_base.rvmat"
								}
							}
						};
					};
					transferToZonesNames[]=
					{
						"Front",
						"Reflector_1_1",
						"Engine"
					};
					transferToZonesCoefs[]={0.1,0.050000001,0.079999998};
					inventorySlots[]=
					{
						"truck_02_wheel_1_1",
						"truck_02_door_1_1"
					};
					inventorySlotsCoefs[]={0.15000001,0.1,0.1};
				};
				class Fender_2_1: Fender_1_1
				{
					memoryPoints[]=
					{
						"dmgZone_fender_2_1"
					};
					componentNames[]=
					{
						"dmgZone_fender_2_1"
					};
					transferToZonesNames[]=
					{
						"Front",
						"Reflector_2_1",
						"Engine"
					};
					inventorySlots[]=
					{
						"truck_02_wheel_2_1",
						"truck_02_door_2_1"
					};
				};
				class Fender_1_2: Fender_1_1
				{
					memoryPoints[]=
					{
						"dmgZone_fender_1_2"
					};
					componentNames[]=
					{
						"dmgZone_fender_1_2"
					};
					transferToZonesNames[]=
					{
						"Back",
						"FuelTank",
						"WindowLR"
					};
					transferToZonesCoefs[]={0.15000001,0.2,0.050000001};
					inventorySlots[]=
					{
						"truck_02_wheel_1_2",
						"truck_02_door_1_1"
					};
					inventorySlotsCoefs[]={0.2,0.1,0.2};
				};
				class Fender_2_2: Fender_1_1
				{
					memoryPoints[]=
					{
						"dmgZone_fender_2_2"
					};
					componentNames[]=
					{
						"dmgZone_fender_2_2"
					};
					transferToZonesNames[]=
					{
						"Back",
						"FuelTank",
						"WindowRR"
					};
					transferToZonesCoefs[]={0.15000001,0.2,0.050000001};
					inventorySlots[]=
					{
						"truck_02_wheel_2_2",
						"truck_02_door_2_1"
					};
					inventorySlotsCoefs[]={0.2,0.1,0.2};
				};
				class WindowFront
				{
					displayName="$STR_CfgVehicleDmg_Window0";
					fatalInjuryCoef=-1;
					memoryPoints[]=
					{
						"dmgZone_windowFront"
					};
					componentNames[]=
					{
						"dmgZone_windowFront"
					};
					class Health
					{
						hitpoints=120;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1,
								
								{
									"DZ\vehicles\wheeled\truck_02\data\truck_02_windows.rvmat"
								}
							},
							
							{
								0.69999999,
								{}
							},
							
							{
								0.5,
								
								{
									"DZ\vehicles\wheeled\truck_02\data\truck_02_windows.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									"DZ\vehicles\wheeled\truck_02\data\truck_02_windows.rvmat"
								}
							},
							
							{
								0,
								"hidden"
							}
						};
					};
					inventorySlots[]={};
					inventorySlotsCoefs[]={};
				};
				class WindowLR
				{
					displayName="$STR_CfgVehicleDmg_Window0";
					fatalInjuryCoef=-1;
					memoryPoints[]=
					{
						"dmgZone_windowLeft"
					};
					componentNames[]=
					{
						"dmgZone_windowLeft"
					};
					class Health
					{
						hitpoints=150;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1,
								
								{
									"DZ\vehicles\wheeled\truck_02\data\truck_02_windows.rvmat"
								}
							},
							
							{
								0.69999999,
								{}
							},
							
							{
								0.5,
								
								{
									"DZ\vehicles\wheeled\truck_02\data\truck_02_windows.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									"DZ\vehicles\wheeled\truck_02\data\truck_02_windows.rvmat"
								}
							},
							
							{
								0,
								"hidden"
							}
						};
					};
					inventorySlots[]={};
					inventorySlotsCoefs[]={};
				};
				class WindowRR: WindowLR
				{
					memoryPoints[]=
					{
						"dmgZone_windowRight"
					};
					componentNames[]=
					{
						"dmgZone_windowRight"
					};
				};
				class Engine
				{
					displayName="$STR_CfgVehicleDmg_Engine0";
					fatalInjuryCoef=0.001;
					memoryPoints[]=
					{
						"dmgZone_engine"
					};
					componentNames[]=
					{
						"dmgZone_engine"
					};
					class Health
					{
						hitpoints=1000;
						transferToGlobalCoef=1;
						healthLevels[]=
						{
							
							{
								1,
								
								{
									"DZ\vehicles\wheeled\truck_02\data\truck_02_engine.rvmat"
								}
							},
							
							{
								0.69999999,
								
								{
									"DZ\vehicles\wheeled\truck_02\data\truck_02_engine.rvmat"
								}
							},
							
							{
								0.5,
								
								{
									"DZ\vehicles\wheeled\truck_02\data\truck_02_engine.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									"DZ\vehicles\wheeled\truck_02\data\truck_02_engine.rvmat"
								}
							},
							
							{
								0,
								
								{
									"DZ\vehicles\wheeled\truck_02\data\truck_02_engine.rvmat"
								}
							}
						};
					};
					inventorySlots[]=
					{
						"TruckBattery",
						"SparkPlug"
					};
					inventorySlotsCoefs[]={0.1,0.050000001};
				};
				class FuelTank
				{
					displayName="$STR_CfgVehicleDmg_FuelTank0";
					fatalInjuryCoef=-1;
					componentNames[]=
					{
						"dmgZone_fuelTank"
					};
					class Health
					{
						hitpoints=500;
						transferToGlobalCoef=0;
						healthLevels[]=
						{
							
							{
								1,
								{}
							},
							
							{
								0.69999999,
								{}
							},
							
							{
								0.5,
								{}
							},
							
							{
								0.30000001,
								{}
							},
							
							{
								0,
								{}
							}
						};
					};
					inventorySlots[]={};
					inventorySlotsCoefs[]={};
				};
			};
		};
		class ObstacleGenerator
		{
			carve=1;
			timeToStationary=5;
			moveThreshold=0.5;
			class Shapes
			{
				class Cylindric
				{
					class Cyl1
					{
						radius=1;
						height=1.5;
						center[]={0,0,0.69999999};
					};
					class Cyl3
					{
						radius=1;
						height=1.5;
						center[]={0,0,-0.69999999};
					};
				};
			};
		};
		class GUIInventoryAttachmentsProps
		{
			class Engine
			{
				name="$STR_attachment_Engine0";
				description="";
				icon="set:dayz_inventory image:cat_vehicle_engine";
				attachmentSlots[]=
				{
					"TruckBattery",
					"SparkPlug"
				};
			};
			class Body
			{
				name="$STR_attachment_Body0";
				description="";
				icon="set:dayz_inventory image:cat_vehicle_body";
				attachmentSlots[]=
				{
					"Reflector_1_1",
					"Reflector_2_1",
					"truck_02_door_1_1",
			        "truck_02_door_2_1",
			        "truck_02_hull",
					"truck_02_wheel_spare"
				};
			};
			class Chassis
			{
				name="$STR_attachment_Chassis0";
				description="";
				icon="set:dayz_inventory image:cat_vehicle_chassis";
				attachmentSlots[]=
				{
					"truck_02_wheel_1_1",
			        "truck_02_wheel_1_2",
			        "truck_02_wheel_2_1",
			        "truck_02_wheel_2_2"
				};
			};
		};
	};
	class Truck_02: Truck_02_Base
	{
		scope=2;
		InteractActions[]={1048,1035};
		displayname="Dump Truck";
		descriptionShort="Hawling Dirt and Getting Skirt";
		Model="\DZ\vehicles\wheeled\truck_02\truck_02.p3d";
		maxspeed=60;
		attachments[]=
		{
			"TruckBattery",
			"Reflector_1_1",
			"Reflector_2_1",
			"SparkPlug",
			"truck_02_door_1_1",
			"truck_02_door_2_1",
			"truck_02_wheel_1_1",
			"truck_02_wheel_1_2",
			"truck_02_wheel_2_1",
			"truck_02_wheel_2_2",
			"truck_02_wheel_spare"
		};
		class Sounds
		{
			thrust=0.60000002;
			thrustTurbo=1;
			thrustGentle=0.30000001;
			thrustSmoothCoef=0.02;
			camposSmoothCoef=0.029999999;
			soundSetsFilter[]=
			{
				"offroad_Engine_Offload_Ext_Rpm1_SoundSet",
				"offroad_Engine_Offload_Ext_Rpm2_SoundSet",
				"offroad_Engine_Offload_Ext_Rpm3_SoundSet",
				"offroad_Engine_Offload_Ext_Rpm4_SoundSet",
				"offroad_Engine_Offload_Ext_Rpm5_SoundSet",
				"offroad_Engine_Ext_Rpm0_SoundSet",
				"offroad_Engine_Ext_Rpm1_SoundSet",
				"offroad_Engine_Ext_Rpm2_SoundSet",
				"offroad_Engine_Ext_Rpm3_SoundSet",
				"offroad_Engine_Ext_Rpm4_SoundSet",
				"offroad_Engine_Ext_Rpm5_SoundSet",
				"offroad_Engine_Ext_Broken_SoundSet",
				"offroad_Tires_rock_slow_Ext_SoundSet",
				"offroad_Tires_rock_fast_Ext_SoundSet",
				"offroad_Tires_grass_slow_Ext_SoundSet",
				"offroad_Tires_grass_fast_Ext_SoundSet",
				"offroad_Tires_gravel_slow_Ext_SoundSet",
				"offroad_Tires_gravel_fast_Ext_SoundSet",
				"offroad_Tires_gravel_dust_fast_Ext_SoundSet",
				"offroad_Tires_asphalt_slow_Ext_SoundSet",
				"offroad_Tires_asphalt_fast_Ext_SoundSet",
				"offroad_Tires_water_slow_Ext_SoundSet",
				"offroad_Tires_water_fast_Ext_SoundSet",
				"Offroad_skid_dirt_SoundSet",
				"offroad_dirt_turn_SoundSet",
				"offroad_Rain_Ext_SoundSet",
				"offroad_damper_left_SoundSet",
				"offroad_damper_right_SoundSet"
			};
			soundSetsInt[]=
			{
				"Offroad_Tires_Asphalt_Fast_General_Int_SoundSet",
				"Offroad_Wind_SoundSet"
			};
		};
	};
};	
	
class CfgNonAIVehicles
{
	class ProxyCrew;
	class ProxyCrew_Driver: ProxyCrew
	{
		scope=1;
		model="\DZ\vehicles\wheeled\proxies\Crew_Driver.p3d";
	};
	class ProxyCrew_Cargo: ProxyCrew
	{
		scope=1;
		model="\DZ\vehicles\wheeled\proxies\Crew_Cargo.p3d";
	};
	class ProxyAttachment;
	class ProxyVehiclePart: ProxyAttachment
	{
		scope=1;
		simulation="ProxyInventory";
		autocenter=0;
		animated=0;
		shadow=1;
		reversed=0;
	};
	class ProxyTruck_02_Wheel: ProxyVehiclePart
	{
		model="DZ\vehicles\wheeled\Truck_02\proxy\Truck_02_Wheel.p3d";
		inventorySlot[]=
		{
			"Truck_02_Wheel_1_1",
			"Truck_02_Wheel_1_2",
			"Truck_02_Wheel_2_1",
			"Truck_02_Wheel_2_2"
		};
	};
	class ProxyTruck_02_Wheel_ruined: ProxyVehiclePart
	{
		model="DZ\vehicles\wheeled\Truck_02\proxy\Truck_02_Wheel_ruined.p3d";
		inventorySlot[]=
		{
			"Truck_02_Wheel_1_1",
			"Truck_02_Wheel_1_2",
			"Truck_02_Wheel_2_1",
			"Truck_02_Wheel_2_2"
		};
	};
	class ProxyTruck_02_Door_1_1: ProxyVehiclePart
	{
		model="DZ\vehicles\wheeled\Truck_02\proxy\Truck_02_Door_1_1.p3d";
		inventorySlot="Truck_02_Door_1_1";
	};
	class ProxyTruck_02_Door_2_1: ProxyVehiclePart
	{
		model="DZ\vehicles\wheeled\Truck_02\proxy\Truck_02_Door_2_1.p3d";
		inventorySlot="Truck_02_Door_2_1";
	};
};
