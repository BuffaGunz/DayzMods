modded class Van_01 extends CarScript
{
	protected ref UniversalTemperatureSource m_UTSource;
	protected ref UniversalTemperatureSourceSettings m_UTSSettings;
	protected ref UniversalTemperatureSourceLambdaEngine m_UTSLEngine;
	
	override void TailLightsShineOn()
	{
		string material = ConfigGetString("TailReflectorMatOn");
		string material_off = ConfigGetString("TailReflectorMatOff");
		
		if (material != ""  &&  material_off != "")
		{
			SetObjectMaterial(SELECTION_ID_TAIL_LIGHT_R, material);
			SetObjectMaterial(SELECTION_ID_TAIL_LIGHT_L, material);
		}
	}
	
	override void TailLightsShineOff()
	{
		string material = ConfigGetString("TailReflectorMatOff");
		
		if (material != "")
		{
			SetObjectMaterial(SELECTION_ID_TAIL_LIGHT_L, material);
			SetObjectMaterial(SELECTION_ID_TAIL_LIGHT_R, material);
		}
	}
	
	override void BrakeLightsShineOn()
	{
		string material = ConfigGetString("brakeReflectorMatOn");
		string materialt = ConfigGetString("TailReflectorMatOn");
		
		if (material != "" && m_HeadlightsOn)
		{
			SetObjectMaterial(SELECTION_ID_BRAKE_LIGHT_L, material);
			SetObjectMaterial(SELECTION_ID_BRAKE_LIGHT_R, material);
		}
		else if (material != "" && !m_HeadlightsOn)
		{
			SetObjectMaterial(SELECTION_ID_BRAKE_LIGHT_L, material);
			SetObjectMaterial(SELECTION_ID_BRAKE_LIGHT_R, material);
			SetObjectMaterial(SELECTION_ID_TAIL_LIGHT_L, materialt);
			SetObjectMaterial(SELECTION_ID_TAIL_LIGHT_R, materialt);
		}
	}
	
	override void BrakeLightsShineOff()
	{
		string material = ConfigGetString("brakeReflectorMatOff");
		string materialt = ConfigGetString("TailReflectorMatOff");
		
		if (material != "" && m_HeadlightsOn)
		{
			SetObjectMaterial(SELECTION_ID_BRAKE_LIGHT_L, material);
			SetObjectMaterial(SELECTION_ID_BRAKE_LIGHT_R, material);
		}
		else if (material != "" && !m_HeadlightsOn)
		{
			SetObjectMaterial(SELECTION_ID_BRAKE_LIGHT_L, material);
			SetObjectMaterial(SELECTION_ID_BRAKE_LIGHT_R, material);
			SetObjectMaterial(SELECTION_ID_TAIL_LIGHT_L, materialt);
			SetObjectMaterial(SELECTION_ID_TAIL_LIGHT_R, materialt);
		}
	}

	void Van_01()
	{
		//m_dmgContactCoef = 0.070; //TODO::Set proper value
		
		m_EngineStartOK 		= "offroad_engine_start_SoundSet";
		m_EngineStartBattery 	= "offroad_engine_failed_start_battery_SoundSet";
		m_EngineStartPlug 		= "offroad_engine_failed_start_sparkplugs_SoundSet";
		m_EngineStartFuel 		= "offroad_engine_failed_start_fuel_SoundSet";
		m_EngineStopFuel 		= "offroad_engine_stop_fuel_SoundSet";
		
		m_CarDoorOpenSound 		= "offroad_door_open_SoundSet";
		m_CarDoorCloseSound 	= "offroad_door_close_SoundSet";
		m_CarSeatShiftInSound 	= "Offroad_SeatShiftIn_SoundSet";
		m_CarSeatShiftOutSound 	= "Offroad_SeatShiftOut_SoundSet";
		
		m_CarHornShortSoundName = "Offroad_Horn_Short_SoundSet";
		m_CarHornLongSoundName	= "Offroad_Horn_SoundSet";
		
		SetEnginePos("0 0.7 1.2");
	}
	
	override void EEInit()
	{		
		super.EEInit();
		
		if (GetGame().IsServer() || !GetGame().IsMultiplayer())
		{
 			m_UTSSettings 						= new UniversalTemperatureSourceSettings();
			m_UTSSettings.m_ManualUpdate 		= true;
			m_UTSSettings.m_TemperatureItemCap 	= GameConstants.ITEM_TEMPERATURE_NEUTRAL_ZONE_MIDDLE;
			m_UTSSettings.m_TemperatureCap		= 0;
			m_UTSSettings.m_RangeFull			= 0.5;
			m_UTSSettings.m_RangeMax			= 2;
			
			m_UTSLEngine						= new UniversalTemperatureSourceLambdaEngine();
			m_UTSource							= new UniversalTemperatureSource(this, m_UTSSettings, m_UTSLEngine);
		}		
	}
	
	override void OnEngineStart()
	{
		super.OnEngineStart();

		if (GetGame().IsServer() || !GetGame().IsMultiplayer())
		{
			m_UTSource.SetDefferedActive(true, 20.0);
		}
	}
	
	override void OnEngineStop()
	{
		super.OnEngineStop();

		if (GetGame().IsServer() || !GetGame().IsMultiplayer())
		{
			m_UTSource.SetDefferedActive(false, 10.0);
		}
	}
	
	override void EOnPostSimulate(IEntity other, float timeSlice)
	{
		if (GetGame().IsServer() || !GetGame().IsMultiplayer())
		{
			if (m_UTSource.IsActive())
			{
				m_UTSource.Update(m_UTSSettings, m_UTSLEngine);
			}
		}
	}
	
	//-----------------------------------------------------------
	override int GetAnimInstance()
	{
		return VehicleAnimInstances.HATCHBACK;
	}
	
	override float GetTransportCameraDistance()
	{
		return 3.5;
	}

	//-----------------------------------------------------------
	override int GetSeatAnimationType( int posIdx )
	{
		switch( posIdx )
		{
		case 0:
			return DayZPlayerConstants.VEHICLESEAT_DRIVER;
		case 1:
			return DayZPlayerConstants.VEHICLESEAT_CODRIVER;
		case 2:
			return DayZPlayerConstants.VEHICLESEAT_PASSENGER_L;
		case 3:
			return DayZPlayerConstants.VEHICLESEAT_PASSENGER_L;
		case 4:
			return DayZPlayerConstants.VEHICLESEAT_PASSENGER_L;
		}

		return 0;
	}
	
	// Override for car-specific light type
	override CarLightBase CreateFrontLight()
	{
		return CarLightBase.Cast(ScriptedLightBase.CreateLight(Van_01FrontLight));
	}
	
	// Override for car-specific light type
	override CarRearLightBase CreateRearLight()
	{
		return CarRearLightBase.Cast(ScriptedLightBase.CreateLight(Van_01RearLight));
	}

	override bool CanReleaseAttachment(EntityAI attachment)
	{
		if (!super.CanReleaseAttachment(attachment))
		{
			return false;
		}
		
		if (EngineIsOn() || GetCarDoorsState("NivaHood") == CarDoorState.DOORS_CLOSED)
		{
			string attType = attachment.GetType();
			if (attType == "CarRadiator" || attType == "CarBattery" || attType == "SparkPlug")
			{
				return false;
			}
		}

		return true;
	}
	
	override protected bool CanManipulateSpareWheel(string slotSelectionName)
	{
		return GetCarDoorsState("Van_01_Trunk_1") != CarDoorState.DOORS_CLOSED;
	}
	
	override bool CanDisplayCargo()
	{
		if (!super.CanDisplayCargo())
		{
			return false;
		}
		
		if (GetCarDoorsState("Van_01_Trunk_1") == CarDoorState.DOORS_CLOSED)
		{
			return false;
		}
		
		return true;
	}
	
	//-----------------------------------------------------------	
	override int GetCarDoorsState( string slotType )
	{
		CarDoor carDoor;

		Class.CastTo( carDoor, FindAttachmentBySlotName( slotType ) );
		if ( !carDoor )
			return CarDoorState.DOORS_MISSING;
	
		switch( slotType )
		{
			case "Van_01_Door_1_1":
				if ( GetAnimationPhase("DoorsDriver") > 0.5 )
					return CarDoorState.DOORS_OPEN;
				else
					return CarDoorState.DOORS_CLOSED;

			break;
			
			case "Van_01_Door_2_1":
				if ( GetAnimationPhase("DoorsCoDriver") > 0.5 )
					return CarDoorState.DOORS_OPEN;
				else
					return CarDoorState.DOORS_CLOSED;

			break;
			
			case "Van_01_Door_2_2":
				if ( GetAnimationPhase("DoorsCargo1") > 0.5 )
					return CarDoorState.DOORS_OPEN;
				else
					return CarDoorState.DOORS_CLOSED;

			break;
			
			case "Van_01_Trunk_1":
				if ( GetAnimationPhase("DoorsCargo3") > 0.5 )
					return CarDoorState.DOORS_OPEN;
				else
					return CarDoorState.DOORS_CLOSED;
			break;
			
			case "Van_01_Trunk_2":
				if ( GetAnimationPhase("DoorsCargo2") > 0.5 )
					return CarDoorState.DOORS_OPEN;
				else
					return CarDoorState.DOORS_CLOSED;

			break;
		}

		return CarDoorState.DOORS_MISSING;
	}

	//-----------------------------------------------------------
	override bool CrewCanGetThrough( int posIdx )
	{
		switch( posIdx )
		{
			case 0:
				if ( GetCarDoorsState( "Van_01_Door_1_1" ) == CarDoorState.DOORS_CLOSED )
					return false;

				return true;
			break;
			
			case 1:
				if ( GetCarDoorsState( "Van_01_Door_2_1" ) == CarDoorState.DOORS_CLOSED )
					return false;

				return true;
			break;

			case 2:
				if ( GetCarDoorsState( "Van_01_Door_2_2" ) == CarDoorState.DOORS_CLOSED )
					return false;

				return true;
			break;

			case 3:
				if ( GetCarDoorsState( "Van_01_Door_2_2" ) == CarDoorState.DOORS_CLOSED )
					return false;
			
			case 4:
				if ( GetCarDoorsState( "Van_01_Door_2_2" ) == CarDoorState.DOORS_CLOSED )
					return false;

				return true;
			break;
		}

		return false;
	}

    override string GetDoorSelectionNameFromSeatPos(int posIdx)
	{
		switch (posIdx)
		{
			case 0:
			case 2:
				return "doors_driver";
			case 1:
			case 3:
				return "doors_codriver";
		}
		
		return super.GetDoorSelectionNameFromSeatPos(posIdx);
	}
	
	override string GetDoorInvSlotNameFromSeatPos(int posIdx)
	{
		switch (posIdx)
		{
			case 0:
			case 2:
				return "Van_01_Door_1_1";
			case 1:
			case 3:
				return "Van_01_Door_2_1";
		}
		
		return super.GetDoorInvSlotNameFromSeatPos(posIdx);
	}

	//-----------------------------------------------------------
	override float OnSound( CarSoundCtrl ctrl, float oldValue )
	{
		switch ( ctrl )
		{
			case CarSoundCtrl.DOORS:
				float newValue = 0;
				
				//-----
				if ( GetCarDoorsState( "Van_01_Door_1_1" ) == CarDoorState.DOORS_CLOSED )
					newValue += 0.25;

				//-----
				if ( GetCarDoorsState( "Van_01_Door_2_1" ) == CarDoorState.DOORS_CLOSED )
					newValue += 0.25;
			
				//-----
				if ( GetCarDoorsState( "Van_01_Door_2_2" ) == CarDoorState.DOORS_CLOSED )
					newValue += 0.25;

				//-----
				if ( GetCarDoorsState( "Van_01_Trunk_1" ) == CarDoorState.DOORS_CLOSED )
					newValue += 0.125;

				//-----
				if ( GetCarDoorsState( "Van_01_Trunk_2" ) == CarDoorState.DOORS_CLOSED )
					newValue += 0.125;

				if ( newValue > 1 )
					newValue = 1;
			
				return newValue;
			break;
		}

		return oldValue;
	}

	//-----------------------------------------------------------
	override string GetAnimSourceFromSelection( string selection )
	{
		switch( selection )
		{
		case "doors_driver":
			return "DoorsDriver";
		case "doors_codriver":
			return "DoorsCoDriver";
		case "doors_cargo1":
			return "DoorsCargo1";
		case "doors_cargo2":
			return "DoorsCargo2";
		case "doors_cargo3":
			return "DoorsCargo3";
		case "doors_hood":
			return "DoorsHood";
		}

		return "";
	}

	//-----------------------------------------------------------
	override string GetDoorConditionPointFromSelection( string selection )
	{
			switch( selection )
		{
			case "seat_driver":
				return "seat_con_1_1";
			break;
			case "seat_codriver":
				return "seat_con_2_1";
			break;
			case "seat_cargo1":
			case "seat_cargo2":
			case "seat_cargo3":
				return "seat_con_1_2";
			break;
		}

		return "";
	};

	//-----------------------------------------------------------
	override bool IsVitalTruckBattery()
	{
		return false;
	}

	//-----------------------------------------------------------
	override bool IsVitalGlowPlug()
	{
		return false;
	}

	//-----------------------------------------------------------
	override bool CanReachSeatFromSeat( int currentSeat, int nextSeat )
	{
		switch( currentSeat )
		{
		case 0:
			if ( nextSeat == 1 )
				return true;
			break;
		case 1:
			if ( nextSeat == 0 )
				return true;
			break;
		case 2:
			if ( nextSeat == 3 )
				return true;
			break;
		case 3:
			if ( nextSeat == 2 )
				return true;
			break;
		}
		
		return false;
	}

	//-----------------------------------------------------------
	override bool CanReachDoorsFromSeat( string pDoorsSelection, int pCurrentSeat )
	{
		switch (pCurrentSeat)
		{
			case 0:
				return pDoorsSelection == "DoorsDriver";
	
			case 1:
				return pDoorsSelection == "DoorsCoDriver";
	
			case 2:
				return pDoorsSelection == "DoorsDriver";
	
			case 3:
				return pDoorsSelection == "DoorsCoDriver";
		}
		
		return false;		
	}
	
	override int GetSeatIndexFromDoor( string pDoorSelection )
	{
		switch (pDoorSelection)
		{
			case "DoorsDriver":
				return 0;
			case "DoorsCoDriver":
				return 1;
		}

		return -1;
	}
	
	override void SetActions()
	{
		super.SetActions();

		AddAction(ActionAnimateSeats);
		AddAction(ActionSidePlateInteract);
	}
	
	override void OnDebugSpawn()
	{
		EntityAI entity;
		
		if ( Class.CastTo(entity, this) )
		{

			entity.GetInventory().CreateInInventory( "CarBattery" );
			entity.GetInventory().CreateInInventory( "SparkPlug" );
			entity.GetInventory().CreateInInventory( "CarRadiator" );

		    entity.GetInventory().CreateInInventory("Van_01_Wheel");
		    entity.GetInventory().CreateInInventory("Van_01_Wheel");
			entity.GetInventory().CreateInInventory("Van_01_Wheel");
			entity.GetInventory().CreateInInventory("Van_01_Wheel");
			entity.GetInventory().CreateInInventory("Van_01_Wheel");

		    entity.GetInventory().CreateInInventory("Van_01_Door_1_1");
		    entity.GetInventory().CreateInInventory("Van_01_Door_2_1");
		    entity.GetInventory().CreateInInventory("Van_01_Door_2_2");
		    entity.GetInventory().CreateInInventory("Van_01_Trunk_1");
		    entity.GetInventory().CreateInInventory("Van_01_Trunk_2");
			
			entity.GetInventory().CreateInInventory( "HeadlightH7" );
			entity.GetInventory().CreateInInventory( "HeadlightH7" );
		};
		Fill( CarFluid.FUEL, 100 );
		Fill( CarFluid.COOLANT, 6.0 );
		Fill( CarFluid.OIL, 4.0 );
	
	}
}