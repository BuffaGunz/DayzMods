class CfgPatches
{
	class RuckVan_Van
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
	class HatchbackDoors_Driver;
	class OffroadHatchback;
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
	class van_01_door_1_1: HatchbackDoors_Driver
	{
		scope=2;
		displayName="#STR_CfgDoor0";
		descriptionShort="DriverDoor";
		model="\DZ\vehicles\wheeled\van_01\proxy\van_01_door_1_1.p3d";
		weight=15000;
		inventorySlot[]=
		{
			"van_01_door_1_1"
		};
		rotationFlags=8;
		hiddenSelectionsMaterials[]=
		{
			"DZ\vehicles\wheeled\van_01\data\van_01_door_front.rvmat"
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
									"DZ\vehicles\wheeled\van_01\data\van_01_glass.rvmat"
								}
							},
							
							{
								0.69999999,
								{}
							},
							
							{
								0.5,
								
								{
									"DZ\vehicles\wheeled\van_01\data\van_01_glass.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									"DZ\vehicles\wheeled\van_01\data\van_01_glass.rvmat"
								}
							},
							
							{
								0,
								"hidden"
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
							"DZ\vehicles\wheeled\van_01\data\van_01_door_front.rvmat"
						};
						healthLevels[]=
						{
							
							{
								1,
								
								{
									"DZ\vehicles\wheeled\van_01\data\van_01_door_front.rvmat"
								}
							},
							
							{
								0.69999999,
								
								{
									"DZ\vehicles\wheeled\van_01\data\van_01_door_front.rvmat"
								}
							},
							
							{
								0.5,
								
								{
									"DZ\vehicles\wheeled\van_01\data\van_01_door_front.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									"DZ\vehicles\wheeled\van_01\data\van_01_door_front.rvmat"
								}
							},
							
							{
								0,
								
								{
									"DZ\vehicles\wheeled\van_01\data\van_01_door_front.rvmat"
								}
							}
						};
					};
				};
			};
		};
	};
	class van_01_door_2_1: HatchbackDoors_Driver
	{
		displayName="#STR_CfgDoor0";
		descriptionShort="CoDriverDoor";
		model="\DZ\vehicles\wheeled\van_01\proxy\van_01_door_2_1.p3d";
		inventorySlot[]=
		{
			"van_01_door_2_1"
		};
		rotationFlags=4;
	};
	class van_01_door_2_2: HatchbackDoors_Driver
	{
		displayName="#STR_CfgDoor0";
		descriptionShort="BackPassengerDoor";
		model="\DZ\vehicles\wheeled\van_01\proxy\van_01_door_2_2.p3d";
		inventorySlot[]=
		{
			"van_01_door_2_2"
		};
		rotationFlags=4;
	};
    class van_01_trunk_1: CarDoor
	{
		scope=2;
		displayName="#STR_CfgTrunk0";
		descriptionShort="Trunk";
		model="\DZ\vehicles\wheeled\van_01\proxy\van_01_trunk_1.p3d";
		weight=15000;
		inventorySlot[]=
		{
			"van_01_trunk_1"
		};
		rotationFlags=2;
		hiddenSelectionsMaterials[]=
		{
			"DZ\vehicles\wheeled\van_01\data\van_01_door_back_down.rvmat"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=500;
					RefTexsMats[]=
					{
						"dz\vehicles\wheeled\offroadhatchback\data\green\niva_hood.rvmat"
					};
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\vehicles\wheeled\van_01\data\van_01_door_back_down.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\vehicles\wheeled\van_01\data\van_01_door_back_down.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\vehicles\wheeled\van_01\data\van_01_door_back_down.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\vehicles\wheeled\van_01\data\van_01_door_back_down.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\vehicles\wheeled\van_01\data\van_01_door_back_down.rvmat"
							}
						}
					};
				};
			};
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class pickUp
				{
					soundSet="hatchbackdoors_driver_pickup_SoundSet";
					id=797;
				};
				class drop
				{
					soundset="hatchbackhood_drop_SoundSet";
					id=898;
				};
			};
		};
	};
	class van_01_trunk_2: CarDoor
	{
		scope=2;
		displayName="Van Trunk 1";
		descriptionShort="$STR_HatchbackHood1";
		model="\DZ\vehicles\wheeled\van_01\proxy\van_01_trunk_2.p3d";
		weight=15000;
		inventorySlot[]=
		{
			"van_01_trunk_2"
		};
		rotationFlags=2;
		hiddenSelectionsMaterials[]=
		{
			"DZ\vehicles\wheeled\van_01\data\van_01_door_back_top.rvmat"
		};
		class DamageSystem: DamageSystem
		{
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
									"DZ\vehicles\wheeled\van_01\data\van_01_glass.rvmat"
								}
							},
							
							{
								0.69999999,
								{}
							},
							
							{
								0.5,
								
								{
									"DZ\vehicles\wheeled\van_01\data\van_01_glass.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									"DZ\vehicles\wheeled\van_01\data\van_01_glass.rvmat"
								}
							},
							
							{
								0,
								"hidden"
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
							"DZ\vehicles\wheeled\van_01\data\van_01_door_back_top.rvmat"
						};
						healthLevels[]=
						{
							
							{
								1,
								
								{
									"DZ\vehicles\wheeled\van_01\data\van_01_door_back_top.rvmat"
								}
							},
							
							{
								0.69999999,
								
								{
									"DZ\vehicles\wheeled\van_01\data\van_01_door_back_top.rvmat"
								}
							},
							
							{
								0.5,
								
								{
									"DZ\vehicles\wheeled\van_01\data\van_01_door_back_top.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									"DZ\vehicles\wheeled\van_01\data\van_01_door_back_top.rvmat"
								}
							},
							
							{
								0,
								
								{
									"DZ\vehicles\wheeled\van_01\data\van_01_door_back_top.rvmat"
								}
							}
						};
					};
				};
			};
		};
	};
	class  van_01_Base: OffroadHatchback
	{
		scope=0;
		InteractActions[]=
		{
			"AT_ANIMATE_SEATS",
			"AT_GETIN_TRANSPORT"
		};
		displayName="Hippy Van";
		descriptionShort="Sweet Home Alabama";
		Model="\DZ\vehicles\wheeled\van_01\van_01.p3d";
		attachments[]=
		{
			"CarBattery",
			"Reflector_1_1",
			"Reflector_2_1",
			"CarRadiator",
			"SparkPlug",
			"van_01_door_1_1",
			"van_01_door_2_1",
			"van_01_door_2_2",
			"van_01_trunk_1",
			"van_01_trunk_2",
			"NivaWheel_1_1",
			"NivaWheel_1_2",
			"NivaWheel_2_1",
			"NivaWheel_2_2",
			"NivaWheel_Spare_1"
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
			"DZ\vehicles\wheeled\van_01\data\van_01_body.rvmat",
			"DZ\vehicles\wheeled\van_01\data\van_01_body.rvmat",
			"DZ\vehicles\wheeled\van_01\data\van_01_body.rvmat",
			"DZ\vehicles\wheeled\van_01\data\van_01_body.rvmat",
			"DZ\vehicles\wheeled\van_01\data\van_01_body.rvmat",
			"DZ\vehicles\wheeled\van_01\data\van_01_body.rvmat",
			"DZ\vehicles\wheeled\van_01\data\van_01_body.rvmat",
			"DZ\vehicles\wheeled\van_01\data\van_01_body.rvmat",
			"DZ\vehicles\wheeled\van_01\data\van_01_body.rvmat",
			"DZ\vehicles\wheeled\van_01\data\van_01_body.rvmat"
		};
		dashboardMatOn="dz\vehicles\wheeled\offroadhatchback\data\niva_dashboard_light.rvmat";
		dashboardMatOff="dz\vehicles\wheeled\offroadhatchback\data\niva_dashboard.rvmat";
		frontReflectorMatOn="dz\vehicles\wheeled\offroadhatchback\data\niva_lights.rvmat";
		frontReflectorMatOff="dz\vehicles\wheeled\offroadhatchback\data\green\niva_body.rvmat";
		brakeReflectorMatOn="dz\vehicles\wheeled\offroadhatchback\data\offroadhatchback_lights_e.rvmat";
		brakeReflectorMatOff="dz\vehicles\wheeled\offroadhatchback\data\offroadhatchback_lights.rvmat";
		ReverseReflectorMatOn="dz\vehicles\wheeled\offroadhatchback\data\offroadhatchback_lights_e.rvmat";
		ReverseReflectorMatOff="dz\vehicles\wheeled\offroadhatchback\data\offroadhatchback_lights.rvmat";
		TailReflectorMatOn="dz\vehicles\wheeled\offroadhatchback\data\OffroadHatchback_lights_e.rvmat";
		TailReflectorMatOff="dz\vehicles\wheeled\offroadhatchback\data\OffroadHatchback_lights.rvmat";
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
							inventorySlot="NivaWheel_1_1";
						};
						class Right: Right
						{
							animDamper="damper_2_1";
							inventorySlot="NivaWheel_1_2";
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
							inventorySlot="van_01_wheel_1_2";
						};
						class Right: Right
						{
							animDamper="damper_2_2";
							inventorySlot="van_01_wheel_2_2";
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
		class AnimationSources: AnimationSources
		{
			class SeatDriver
			{
				source="user";
				initPhase=0;
				animPeriod=0.80000001;
			};
			class SeatCoDriver
			{
				source="user";
				initPhase=0;
				animPeriod=0.80000001;
			};
			class damper_1_1
			{
				source="user";
				initPhase=0.48570001;
				animPeriod=1;
			};
			class damper_2_1: damper_1_1
			{
			};
			class damper_1_2
			{
				source="user";
				initPhase=0.40020001;
				animPeriod=1;
			};
			class damper_2_2: damper_1_2
			{
			};
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
									"DZ\vehicles\wheeled\van_01\data\van_01_body.rvmat"
								}
							},
							
							{
								0.69999999,
								
								{
									"DZ\vehicles\wheeled\van_01\data\van_01_body.rvmat"
								}
							},
							
							{
								0.5,
								
								{
									"DZ\vehicles\wheeled\van_01\data\van_01_body.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									"DZ\vehicles\wheeled\van_01\data\van_01_body.rvmat"
								}
							},
							
							{
								0,
								
								{
									"DZ\vehicles\wheeled\van_01\data\van_01_body.rvmat"
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
						"NivaWheel_1_1",
						"NivaWheel_1_2"
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
									"DZ\vehicles\wheeled\van_01\data\van_01_glass.rvmat"
								}
							},
							
							{
								0.69999999,
								{}
							},
							
							{
								0.5,
								
								{
									"DZ\vehicles\wheeled\van_01\data\van_01_glass.rvmat"
								}
							},
							
							{
								0.30000001,
								{}
							},
							
							{
								0,
								
								{
									"DZ\vehicles\wheeled\van_01\data\van_01_glass.rvmat"
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
						"NivaWheel_1_1"
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
						"NivaWheel_2_1"
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
									"DZ\vehicles\wheeled\van_01\data\van_01_body.rvmat"
								}
							},
							
							{
								0.69999999,
								
								{
									"DZ\vehicles\wheeled\van_01\data\van_01_body.rvmat"
								}
							},
							
							{
								0.5,
								
								{
									"DZ\vehicles\wheeled\van_01\data\van_01_body.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									"DZ\vehicles\wheeled\van_01\data\van_01_body.rvmat"
								}
							},
							
							{
								0,
								
								{
									"DZ\vehicles\wheeled\van_01\data\van_01_body.rvmat"
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
						"NivaTrunk",
						"NivaWheel_1_2",
						"NivaWheel_2_2"
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
									"DZ\vehicles\wheeled\van_01\data\van_01_body.rvmat"
								}
							},
							
							{
								0.69999999,
								
								{
									"DZ\vehicles\wheeled\van_01\data\van_01_body.rvmat"
								}
							},
							
							{
								0.5,
								
								{
									"DZ\vehicles\wheeled\van_01\data\van_01_body.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									"DZ\vehicles\wheeled\van_01\data\van_01_body.rvmat"
								}
							},
							
							{
								0,
								
								{
									"DZ\vehicles\wheeled\van_01\data\van_01_body.rvmat"
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
									"DZ\vehicles\wheeled\van_01\data\van_01_body.rvmat"
								}
							},
							
							{
								0.69999999,
								
								{
									"DZ\vehicles\wheeled\van_01\data\van_01_body.rvmat"
								}
							},
							
							{
								0.5,
								
								{
									"DZ\vehicles\wheeled\van_01\data\van_01_body.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									"DZ\vehicles\wheeled\van_01\data\van_01_body.rvmat"
								}
							},
							
							{
								0,
								
								{
									"DZ\vehicles\wheeled\van_01\data\van_01_body.rvmat"
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
						"NivaWheel_1_1",
						"van_01_door_1_1"
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
						"NivaWheel_2_1",
						"van_01_door_2_1"
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
						"van_01_trunk_1",
						"van_01_trunk_2",
						"NivaWheel_1_2",
						"van_01_door_1_1"
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
						"van_01_trunk_1",
						"van_01_trunk_2",
						"NivaWheel_2_2",
						"van_01_door_2_1"
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
									"DZ\vehicles\wheeled\van_01\data\van_01_glass.rvmat"
								}
							},
							
							{
								0.69999999,
								{}
							},
							
							{
								0.5,
								
								{
									"DZ\vehicles\wheeled\van_01\data\van_01_glass.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									"DZ\vehicles\wheeled\van_01\data\van_01_glass.rvmat"
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
									"DZ\vehicles\wheeled\van_01\data\van_01_glass.rvmat"
								}
							},
							
							{
								0.69999999,
								{}
							},
							
							{
								0.5,
								
								{
									"DZ\vehicles\wheeled\van_01\data\van_01_glass.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									"DZ\vehicles\wheeled\van_01\data\van_01_glass.rvmat"
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
									"DZ\vehicles\wheeled\van_01\data\van_01_engine.rvmat"
								}
							},
							
							{
								0.69999999,
								
								{
									"DZ\vehicles\wheeled\van_01\data\van_01_engine.rvmat"
								}
							},
							
							{
								0.5,
								
								{
									"DZ\vehicles\wheeled\van_01\data\van_01_engine.rvmat"
								}
							},
							
							{
								0.30000001,
								
								{
									"DZ\vehicles\wheeled\van_01\data\van_01_engine.rvmat"
								}
							},
							
							{
								0,
								
								{
									"DZ\vehicles\wheeled\van_01\data\van_01_engine.rvmat"
								}
							}
						};
					};
					inventorySlots[]=
					{
						"CarBattery",
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
					"CarBattery",
					"CarRadiator",
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
					"van_01_door_1_1",
			        "van_01_door_2_1",
			        "van_01_door_2_2",
			        "van_01_trunk_1",
			        "van_01_trunk_2",
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
					"NivaWheel_1_1",
			        "NivaWheel_1_2",
			        "NivaWheel_2_1",
			        "NivaWheel_2_2"
				};
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
	class Van_01: Van_01_Base
	{
		scope=2;
		InteractActions[]={1048,1035};
		displayname="s1203";
		Model="\DZ\vehicles\wheeled\van_01\van_01.p3d";
		maxspeed=60;
		attachments[]=
		{
			"CarBattery",
			"Reflector_1_1",
			"Reflector_2_1",
			"CarRadiator",
			"SparkPlug",
			"van_01_door_1_1",
			"van_01_door_2_1",
			"van_01_door_2_2",
			"van_01_trunk_1",
			"van_01_trunk_2",
			"NivaWheel_1_1",
			"NivaWheel_1_2",
			"NivaWheel_2_1",
			"NivaWheel_2_2",
			"NivaWheel_Spare_1"
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
	class ProxyVan_01_Door_1_1: ProxyVehiclePart
	{
		model="\DZ\vehicles\wheeled\Van_01\proxy\Van_01_Door_1_1.p3d";
		inventorySlot="Van_01_Door_1_1";
	};
	class ProxyVan_01_Door_2_1: ProxyVehiclePart
	{
		model="\DZ\vehicles\wheeled\Van_01\proxy\Van_01_Door_2_1.p3d";
		inventorySlot="Van_01_Door_2_1";
	};
	class ProxyVan_01_Door_2_2: ProxyVehiclePart
	{
		model="\DZ\vehicles\wheeled\Van_01\proxy\Van_01_Door_2_2.p3d";
		inventorySlot="Van_01_Door_2_2";
	};
	class ProxyVan_01_Trunk_1: ProxyVehiclePart
	{
		model="\DZ\vehicles\wheeled\Van_01\proxy\Van_01_Trunk_1.p3d";
		inventorySlot="Van_01_Trunk_1";
	};
	class ProxyVan_01_Trunk_2: ProxyVehiclePart
	{
		model="\DZ\vehicles\wheeled\Van_01\proxy\Van_01_Trunk_2.p3d";
		inventorySlot="Van_01_Trunk_2";
	};
	class ProxyVan_01_Wheel: ProxyVehiclePart
	{
		model="DZ\vehicles\wheeled\OffroadHatchback\proxy\nivaWheel.p3d";
		inventorySlot[]=
		{
			"NivaWheel_1_1",
			"NivaWheel_1_2",
			"NivaWheel_2_1",
			"NivaWheel_2_2",
			"NivaWheel_Spare_1"
		};
	};
	class ProxyVan_01_Wheel_ruined: ProxyVehiclePart
	{
		model="DZ\vehicles\wheeled\OffroadHatchback\proxy\nivaWheel_destroyed.p3d";
		inventorySlot[]=
		{
			"NivaWheel_1_1",
			"NivaWheel_1_2",
			"NivaWheel_2_1",
			"NivaWheel_2_2",
			"NivaWheel_Spare_1"
		};
	};
	class ProxyPart
	{
		scope=2;
		simulation="ProxyInventory";
		model="";
		inventorySlot="";
		autocenter=0;
		animated=0;
		shadow=1;
		reversed=1;
	};
	class ProxyBattery_truck: ProxyPart
	{
		model="DZ\vehicles\parts\battery_truck.p3d";
		inventorySlot[]=
		{
			"TruckBattery",
			"LargeBattery"
		};
	};
	class ProxyBattery_Car: ProxyPart
	{
		model="DZ\vehicles\parts\battery_car.p3d";
		inventorySlot[]=
		{
			"CarBattery",
			"LargeBattery"
		};
	};
	class Proxysparkplug: ProxyPart
	{
		model="DZ\vehicles\parts\sparkplug.p3d";
		inventorySlot="SparkPlug";
	};
	class ProxyReplacement_Headlight: ProxyPart
	{
		model="DZ\vehicles\parts\Replacement_Headlight.p3d";
		inventorySlot[]=
		{
			"Reflector_1_1",
			"Reflector_2_1"
		};
	};
	class ProxyRadiator_car: ProxyPart
	{
		model="DZ\vehicles\parts\Radiator_car.p3d";
		inventorySlot="CarRadiator";
	};
};
