class CfgPatches
{
	class RuckBus_Bus
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
	class ikarusWheel: CarWheel
	{
		scope=2;
		displayName="#STR_CfgWheel0";
		descriptionShort="Bus Wheel";
		model="\DZ\vehicles\wheeled\transitbus\proxy_big\ikaruswheel.p3d";
		weight=15000;
		inventorySlot[]=
		{
			"BusWheel_1_1",
			"BusWheel_2_1"
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
	};
	class ikarusWheel_destroyed: CarWheel
	{
		scope=2;
		displayName="#STR_CfgWheel0";
		descriptionShort="Bus Wheel";
		model="\DZ\vehicles\wheeled\transitbus\proxy_big\ikaruswheel_destroyed.p3d";
		weight=10000;
		inventorySlot[]=
		{
			"BusWheel_1_1",
			"BusWheel_2_1"
		};
		rotationFlags=4;
		radius=0.2;
		width=0.20999999;
		tyreOffroadResistance=0.1;
		tyreGrip=0.2;
		tyreRollResistance=0.30000001;
	};
	class ikaruswheel_rear: CarWheel
	{
		scope=2;
		displayName="#STR_CfgWheel0";
		descriptionShort="Bus Wheel";
		model="\DZ\vehicles\wheeled\transitbus\proxy_big\ikaruswheel_rear.p3d";
		weight=15000;
		inventorySlot[]=
		{
			"BusWheel_1_2",
			"BusWheel_2_2"
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
	};
	class ikaruswheel_rear_destroyed: CarWheel
	{
		scope=2;
		displayName="#STR_CfgWheel0";
		descriptionShort="Bus Wheel";
		model="\DZ\vehicles\wheeled\transitbus\proxy_big\ikaruswheel_rear_destroyed.p3d";
		weight=10000;
		inventorySlot[]=
		{
			"BusWheel_1_2",
			"BusWheel_2_2"
		};
		rotationFlags=4;
		radius=0.2;
		width=0.20999999;
		tyreOffroadResistance=0.1;
		tyreGrip=0.2;
		tyreRollResistance=0.30000001;
	};
	class ikarusdoors_left: CarDoor
	{
		scope=2;
		displayName="#STR_CfgDoor0";
		descriptionShort="Bus Door";
		model="\DZ\vehicles\wheeled\transitbus\proxy_big\ikarusdoors_left.p3d";
		weight=15000;
		inventorySlot[]=
		{
			"BusLeftDoors_1",
			"BusLeftDoors_2",
			"BusLeftDoors_3"
		};
		rotationFlags=8;
		hiddenSelectionsMaterials[]=
		{
			"DZ\vehicles\wheeled\transitbus\data\ikarus_doors.rvmat"
		};
		class DamageSystem: DamageSystem
		{
			class GlobalHealth: GlobalHealth
			{
			};
			class DamageZones: DamageZones
			{
				class Window: Window
				{
					class Health: Health
					{
						healthLevels[]=
						{
							
							{
								1,
								
								{
									"DZ\vehicles\wheeled\transitbus\data\glass_i.rvmat"
								}
							},
							
							{
								0.69999999,
								{}
							},
							
							{
								0.5,
								
								{
									"DZ\vehicles\wheeled\transitbus\data\glass_i_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									"DZ\vehicles\wheeled\transitbus\data\glass_i_damage.rvmat"
								}
							},
							
							{
								0,
								"DZ\vehicles\wheeled\transitbus\data\glass_i_destruct.rvmat"
							}
						};
					};
				};
				class Doors: Doors
				{
					class Health: Health
					{
						RefTexsMats[]=
						{
							"DZ\vehicles\wheeled\transitbus\data\ikarus_doors.rvmat"
						};
						healthLevels[]=
						{
							
							{
								1,
								
								{
									"DZ\vehicles\wheeled\transitbus\data\ikarus_doors.rvmat"
								}
							},
							
							{
								0.69999999,
								
								{
									"DZ\vehicles\wheeled\transitbus\data\ikarus_doors.rvmat"
								}
							},
							
							{
								0.5,
								
								{
									"DZ\vehicles\wheeled\transitbus\data\ikarus_doors.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									"DZ\vehicles\wheeled\transitbus\data\ikarus_doors.rvmat"
								}
							},
							
							{
								0,
								
								{
									"DZ\vehicles\wheeled\transitbus\data\ikarus_doors.rvmat"
								}
							}
						};
					};
				};
			};
		};
	};
	class IkarusDoors_Right: ikarusdoors_left
	{
		displayName="#STR_CfgDoor0";
		descriptionShort="Bus Door";
		model="\DZ\vehicles\wheeled\transitbus\proxy_big\ikarusdoors_right.p3d";
		inventorySlot[]=
		{
			"BusRightDoors_1",
			"BusRightDoors_2",
			"BusRightDoors_3"
		};
		rotationFlags=4;
	};
	class ikarusHood: CarDoor
	{
		scope=2;
		displayName="Bus Hood";
		descriptionShort="Hood for a bus.";
		model="\DZ\vehicles\wheeled\transitbus\proxy_big\ikarushood.p3d";
		weight=15000;
		inventorySlot[]=
		{
			"BusHood"
		};
		rotationFlags=2;
		hiddenSelectionsMaterials[]=
		{
			"DZ\vehicles\wheeled\transitbus\data\ikarus_hood.rvmat"
		};
		class DamageSystem: DamageSystem
		{
			class DamageZones: DamageZones
			{
				class Doors: Doors
				{
					class Health: Health
					{
						RefTexsMats[]=
						{
							"DZ\vehicles\wheeled\transitbus\data\ikarus_hood.rvmat"
						};
						healthLevels[]=
						{
							
							{
								1,
								
								{
									"DZ\vehicles\wheeled\transitbus\data\ikarus_hood.rvmat"
								}
							},
							
							{
								0.69999999,
								
								{
									"DZ\vehicles\wheeled\transitbus\data\ikarus_hood.rvmat"
								}
							},
							
							{
								0.5,
								
								{
									"DZ\vehicles\wheeled\transitbus\data\ikarus_hood_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									"DZ\vehicles\wheeled\transitbus\data\ikarus_hood_damage.rvmat"
								}
							},
							
							{
								0,
								
								{
									"DZ\vehicles\wheeled\transitbus\data\ikarus_hood_destruct.rvmat"
								}
							}
						};
					};
				};
			};
		};
	};
	class ikarus: Carscript
	{
		scope=2;
		Model="\DZ\vehicles\wheeled\transitbus\transitbus_big.p3d";
		attachments[]=
		{
			"TruckBattery",
			"Reflector_1_1",
			"Reflector_2_1",
			"CarRadiator",
			"GlowPlug",
			"BusRightDoors_1",
			"BusRightDoors_2",
			"BusRightDoors_3",
			"BusHood",
			"BusLeftDoors_1",
			"BusLeftDoors_2",
			"BusLeftDoors_3",
			"BusWheel_1_1",
			"BusWheel_2_1",
			"BusWheel_1_2",
			"BusWheel_2_2"
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
			"DZ\vehicles\wheeled\transitbus\data\headlight_glass_ca.paa",
			"DZ\vehicles\wheeled\transitbus\data\headlight_glass_ca.paa",
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
			"DZ\vehicles\wheeled\transitbus\data\glass.rvmat",
			"DZ\vehicles\wheeled\transitbus\data\glass.rvmat",
			"DZ\vehicles\wheeled\transitbus\data\ikarus_body.rvmat",
			"DZ\vehicles\wheeled\transitbus\data\ikarus_body.rvmat",
			"DZ\vehicles\wheeled\transitbus\data\ikarus_body.rvmat",
			"DZ\vehicles\wheeled\transitbus\data\ikarus_body.rvmat",
			"DZ\vehicles\wheeled\transitbus\data\ikarus_body.rvmat",
			"DZ\vehicles\wheeled\transitbus\data\ikarus_body.rvmat",
			"DZ\vehicles\wheeled\transitbus\data\ikarus_body.rvmat",
			"DZ\vehicles\wheeled\transitbus\data\ikarus_body.rvmat",
			"DZ\vehicles\wheeled\transitbus\data\ikarus_body.rvmat",
			"DZ\vehicles\wheeled\transitbus\data\ikarus_body.rvmat"
		};
		dashboardMatOn="DZ\vehicles\wheeled\transitbus\data\ikarus_dashboard.rvmat";
		dashboardMatOff="DZ\vehicles\wheeled\transitbus\data\ikarus_dashboard.rvmat";
		frontReflectorMatOn="DZ\vehicles\wheeled\transitbus\data\ikarus_ext_details_lights.rvmat";
		frontReflectorMatOff="DZ\vehicles\wheeled\transitbus\data\ikarus_ext_details.rvmat";
		brakeReflectorMatOn="DZ\vehicles\wheeled\transitbus\data\ikarus_ext_details_lights.rvmat";
		brakeReflectorMatOff="DZ\vehicles\wheeled\transitbus\data\ikarus_ext_details_lights.rvmat";
		ReverseReflectorMatOn="DZ\vehicles\wheeled\transitbus\data\ikarus_ext_details_lights.rvmat";
		ReverseReflectorMatOff="DZ\vehicles\wheeled\transitbus\data\ikarus_ext_details_lights.rvmat";
		TailReflectorMatOn="DZ\vehicles\wheeled\transitbus\data\ikarus_ext_details_lights.rvmat";
		TailReflectorMatOff="DZ\vehicles\wheeled\transitbus\data\ikarus_ext_details_lights.rvmat";
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
			class Cargo1
			{
				actionSel="seat_cargo1";
				proxyPos="crewCargo1";
				getInPos="pos cargo 3";
				getInDir="pos cargo dir 3";
			};
			class Cargo2
			{
				actionSel="seat_cargo2";
				proxyPos="crewCargo2";
				getInPos="pos cargo 3";
				getInDir="pos cargo dir 3";
			};
			class Cargo3
			{
				actionSel="seat_cargo3";
				proxyPos="crewCargo3";
				getInPos="pos cargo 3";
				getInDir="pos cargo dir 3";
			};
			class Cargo4
			{
				actionSel="seat_cargo4";
				proxyPos="crewCargo4";
				getInPos="pos cargo 3";
				getInDir="pos cargo dir 3";
			};
			class Cargo5
			{
				actionSel="seat_cargo5";
				proxyPos="crewCargo5";
				getInPos="pos cargo 3";
				getInDir="pos cargo dir 3";
			};
			class Cargo6
			{
				actionSel="seat_cargo6";
				proxyPos="crewCargo6";
				getInPos="pos cargo 3";
				getInDir="pos cargo dir 3";
			};
			class Cargo7
			{
				actionSel="seat_cargo7";
				proxyPos="crewCargo7";
				getInPos="pos cargo 3";
				getInDir="pos cargo dir 3";
			};
			class Cargo8
			{
				actionSel="seat_cargo8";
				proxyPos="crewCargo8";
				getInPos="pos cargo 3";
				getInDir="pos cargo dir 3";
			};
			class Cargo9
			{
				actionSel="seat_cargo9";
				proxyPos="crewCargo3";
				getInPos="pos cargo 3";
				getInDir="pos cargo dir 3";
			};
			class Cargo10
			{
				actionSel="seat_cargo10";
				proxyPos="crewCargo1";
				getInPos="pos cargo 3";
				getInDir="pos cargo dir 3";
			};
			class Cargo11
			{
				actionSel="seat_cargo11";
				proxyPos="crewCargo11";
				getInPos="pos cargo 3";
				getInDir="pos cargo dir 3";
			};
			class Cargo12
			{
				actionSel="seat_cargo12";
				proxyPos="crewCargo12";
				getInPos="pos cargo 3";
				getInDir="pos cargo dir 3";
			};
			class Cargo13
			{
				actionSel="seat_cargo13";
				proxyPos="crewCargo13";
				getInPos="pos cargo 3";
				getInDir="pos cargo dir 3";
			};
			class Cargo14
			{
				actionSel="seat_cargo14";
				proxyPos="crewCargo14";
				getInPos="pos cargo 3";
				getInDir="pos cargo dir 3";
			};
			class Cargo15
			{
				actionSel="seat_cargo15";
				proxyPos="crewCargo15";
				getInPos="pos cargo 3";
				getInDir="pos cargo dir 3";
			};
			class Cargo16
			{
				actionSel="seat_cargo16";
				proxyPos="crewCargo16";
				getInPos="pos cargo 3";
				getInDir="pos cargo dir 3";
			};
			class Cargo17
			{
				actionSel="seat_cargo17";
				proxyPos="crewCargo17";
				getInPos="pos cargo 3";
				getInDir="pos cargo dir 3";
			};
			class Cargo18
			{
				actionSel="seat_cargo18";
				proxyPos="crewCargo18";
				getInPos="pos cargo 3";
				getInDir="pos cargo dir 3";
			};
			class Cargo19
			{
				actionSel="seat_cargo19";
				proxyPos="crewCargo19";
				getInPos="pos cargo 3";
				getInDir="pos cargo dir 3";
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
				reactionTime=0.89999998;
				defaultThrust=0.85000002;
				gentleThrust=0.69999999;
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
				torqueCurve[]={650,0,750,40,1400,80,3400,114,5400,95,8000,0};
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
							inventorySlot="BusWheel_1_1";
						};
						class Right: Right
						{
							animDamper="damper_2_1";
							inventorySlot="BusWheel_2_1";
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
							inventorySlot="BusWheel_1_2";
						};
						class Right: Right
						{
							animDamper="damper_2_2";
							inventorySlot="BusWheel_2_2";
						};
					};
				};
			};
		};
		class Cargo
		{
			itemsCargoSize[]={10,80};
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
					hitpoints=1000;
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
									"DZ\vehicles\wheeled\transitbus\data\ikarus_body.rvmat"
								}
							},
							
							{
								0.69999999,
								
								{
									"DZ\vehicles\wheeled\transitbus\data\ikarus_body.rvmat"
								}
							},
							
							{
								0.5,
								
								{
									"DZ\vehicles\wheeled\transitbus\data\ikarus_body.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									"DZ\vehicles\wheeled\transitbus\data\ikarus_body.rvmat"
								}
							},
							
							{
								0,
								
								{
									"DZ\vehicles\wheeled\transitbus\data\ikarus_body.rvmat"
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
						"CarRadiator",
						"BusWheel_1_1",
			            "BusWheel_1_2"
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
									"DZ\vehicles\wheeled\transitbus\data\ikarus_ext_details_lights.rvmat"
								}
							},
							
							{
								0.69999999,
								{}
							},
							
							{
								0.5,
								
								{
									"DZ\vehicles\wheeled\transitbus\data\ikarus_ext_details_lights.rvmat"
								}
							},
							
							{
								0.30000001,
								{}
							},
							
							{
								0,
								
								{
									"DZ\vehicles\wheeled\transitbus\data\ikarus_ext_details_lights.rvmat"
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
						"BusWheel_2_1"
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
						"BusWheel_2_1"
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
									"DZ\vehicles\wheeled\transitbus\data\ikarus_body.rvmat"
								}
							},
							
							{
								0.69999999,
								
								{
									"DZ\vehicles\wheeled\transitbus\data\ikarus_body.rvmat"
								}
							},
							
							{
								0.5,
								
								{
									"DZ\vehicles\wheeled\transitbus\data\ikarus_body.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									"DZ\vehicles\wheeled\transitbus\data\ikarus_body.rvmat"
								}
							},
							
							{
								0,
								
								{
									"DZ\vehicles\wheeled\transitbus\data\ikarus_body.rvmat"
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
						"BusWheel_1_2",
						"BusWheel_2_2"
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
									"DZ\vehicles\wheeled\transitbus\data\ikarus_body.rvmat"
								}
							},
							
							{
								0.69999999,
								
								{
									"DZ\vehicles\wheeled\transitbus\data\ikarus_body.rvmat"
								}
							},
							
							{
								0.5,
								
								{
									"DZ\vehicles\wheeled\transitbus\data\ikarus_body.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									"DZ\vehicles\wheeled\transitbus\data\ikarus_body.rvmat"
								}
							},
							
							{
								0,
								
								{
									"DZ\vehicles\wheeled\transitbus\data\ikarus_body.rvmat"
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
									"DZ\vehicles\wheeled\transitbus\data\ikarus_body.rvmat"
								}
							},
							
							{
								0.69999999,
								
								{
									"DZ\vehicles\wheeled\transitbus\data\ikarus_body.rvmat"
								}
							},
							
							{
								0.5,
								
								{
									"DZ\vehicles\wheeled\transitbus\data\ikarus_body.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									"DZ\vehicles\wheeled\transitbus\data\ikarus_body.rvmat"
								}
							},
							
							{
								0,
								
								{
									"DZ\vehicles\wheeled\transitbus\data\ikarus_body.rvmat"
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
						"BusWheel_1_1"
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
						"BusWheel_2_1"
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
						"BusWheel_1_2"
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
						"BusWheel_2_2"
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
									"DZ\vehicles\wheeled\transitbus\data\glass_i.rvmat"
								}
							},
							
							{
								0.69999999,
								{}
							},
							
							{
								0.5,
								
								{
									"DZ\vehicles\wheeled\transitbus\data\glass_i_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									"DZ\vehicles\wheeled\transitbus\data\glass_i_damage.rvmat"
								}
							},
							
							{
								0,
								"DZ\vehicles\wheeled\transitbus\data\glass_i_destruct.rvmat"
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
									"DZ\vehicles\wheeled\transitbus\data\glass_i.rvmat"
								}
							},
							
							{
								0.69999999,
								{}
							},
							
							{
								0.5,
								
								{
									"DZ\vehicles\wheeled\transitbus\data\glass_i_damage.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									DZ\vehicles\wheeled\transitbus\data\glass_i_damage.rvmat"
								}
							},
							
							{
								0,
								"DZ\vehicles\wheeled\transitbus\data\glass_i_destruct.rvmat"
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
									"DZ\vehicles\wheeled\transitbus\data\ikarus_engine.rvmat"
								}
							},
							
							{
								0.69999999,
								
								{
									"DZ\vehicles\wheeled\transitbus\data\ikarus_engine.rvmat"
								}
							},
							
							{
								0.5,
								
								{
									"DZ\vehicles\wheeled\transitbus\data\ikarus_engine.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									"DZ\vehicles\wheeled\transitbus\data\ikarus_engine.rvmat"
								}
							},
							
							{
								0,
								
								{
									"DZ\vehicles\wheeled\transitbus\data\ikarus_engine.rvmat"
								}
							}
						};
					};
					inventorySlots[]=
					{
						"TruckBattery",
						"GlowPlug"
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
					"CarRadiator",
					"GlowPlug"
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
					"BusRightDoors_1",
			        "BusRightDoors_2",
			        "BusRightDoors_3",
			        "BusHood",
			        "BusLeftDoors_1",
			        "BusLeftDoors_2",
			        "BusLeftDoors_3",
					"NivaWheel_Spare_1"
				};
			};
			class Chassis
			{
				name="$STR_attachment_Chassis0";
				description="";
				icon="set:dayz_inventory image:cat_vehicle_chassis";
				attachmentSlots[]=
				{
					"BusWheel_1_1",
			        "BusWheel_2_1",
			        "BusWheel_1_2",
			        "BusWheel_2_2"
				};
			};
		};
	};
};	
	
