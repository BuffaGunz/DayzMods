modded class Truck_02 extends CarScript
{
	protected ref UniversalTemperatureSource m_UTSource;
	protected ref UniversalTemperatureSourceSettings m_UTSSettings;
	protected ref UniversalTemperatureSourceLambdaEngine m_UTSLEngine;

	void Truck_02()
	{
		//m_dmgContactCoef 		= 0.018;
		m_enginePtcPos 			= "0 1.346 2.205";
		
		m_EngineStartOK 		= "Truck_01_engine_start_SoundSet";
		m_EngineStartBattery	= "Truck_01_engine_failed_start_battery_SoundSet";
		m_EngineStartPlug 		= "Truck_01_engine_failed_start_sparkplugs_SoundSet";
		m_EngineStartFuel 		= "Truck_01_engine_failed_start_fuel_SoundSet";
		m_EngineStopFuel 		= "Truck_01_engine_stop_fuel_SoundSet";

		m_CarDoorOpenSound 		= "Truck_01_door_open_SoundSet";
		m_CarDoorCloseSound 	= "Truck_01_door_close_SoundSet";
		
		m_CarHornShortSoundName = "Truck_01_Horn_Short_SoundSet";
		m_CarHornLongSoundName	= "Truck_01_Horn_SoundSet";
		
		SetEnginePos("0 1.4 2.25");
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
	
	override float GetTransportCameraDistance()
	{
		return 6.5;
	}
	
	override vector GetTransportCameraOffset()
	{
		return "0 3.2 0";
	}
	
	override int GetAnimInstance()
	{
		return VehicleAnimInstances.V3S;
	}

	override int GetSeatAnimationType(int posIdx)
	{
		switch (posIdx)
		{
		case 0:
			return DayZPlayerConstants.VEHICLESEAT_DRIVER;
		case 1:
			return DayZPlayerConstants.VEHICLESEAT_CODRIVER;
		}

		return 0;
	}

	// Override for car-specific light type
	override CarLightBase CreateFrontLight()
	{
		return CarLightBase.Cast(ScriptedLightBase.CreateLight(Truck_02FrontLight));
	}
	
	// Override for car-specific light type
	override CarRearLightBase CreateRearLight()
	{
		return CarRearLightBase.Cast(ScriptedLightBase.CreateLight(Truck_02RearLight));
	}
	
	override bool CanReleaseAttachment(EntityAI attachment)
	{
		if (!super.CanReleaseAttachment(attachment))
		{
			return false;
		}
		
		if (EngineIsOn() && attachment.GetType() == "TruckBattery")
		{
			return false;
		}

		return true;
	}


	override int GetCarDoorsState( string slotType )
	{
		CarDoor carDoor;
		
		switch( slotType )
		{
			case "Truck_02_Door_1_1":
				Class.CastTo( carDoor, FindAttachmentBySlotName( slotType ) );
				if ( carDoor )
				{
					if ( GetAnimationPhase("DoorsDriver") > 0.5 )
					{
						return CarDoorState.DOORS_OPEN;
					}
					else
					{
						return CarDoorState.DOORS_CLOSED;
					}
				}

				return CarDoorState.DOORS_MISSING;
			break;
			
			case "Truck_02_Door_2_1":
				Class.CastTo( carDoor, FindAttachmentBySlotName( slotType ) );
				if ( carDoor )
				{
					if ( GetAnimationPhase("DoorsCoDriver") > 0.5 )
					{
						return CarDoorState.DOORS_OPEN;
					}
					else
					{
						return CarDoorState.DOORS_CLOSED;
					}
				}

				return CarDoorState.DOORS_MISSING;
			break;
		}
		
		return CarDoorState.DOORS_MISSING;
	}

	override bool CrewCanGetThrough( int posIdx )
	{
		CarDoor carDoor;
		switch( posIdx )
		{
			case 0:
				if ( GetCarDoorsState( "Truck_02_Door_1_1" ) == CarDoorState.DOORS_CLOSED )
				{
					return false;
				}
			
				return true;
			break;
			
			case 1:
				if ( GetCarDoorsState( "Truck_02_Door_2_1" ) == CarDoorState.DOORS_CLOSED )
				{
					return false;
				}
			
				return true;
			break;
		}

		return false;
	}
	
	override string GetDoorSelectionNameFromSeatPos(int posIdx)
	{
		switch( posIdx )
		{
			case 0:
				return "doors_driver";
			break;
			case 1:
				return "doors_codriver";
			break;
		}

		return super.GetDoorSelectionNameFromSeatPos(posIdx);
	}

	override string GetDoorInvSlotNameFromSeatPos(int posIdx)
	{
		switch( posIdx )
		{
			case 0:
				return "Truck_02_Door_1_1";
			break;
			case 1:
				return "Truck_02_Door_2_1";
			break;
		}

		return super.GetDoorInvSlotNameFromSeatPos(posIdx);
	}
	
	override float OnSound( CarSoundCtrl ctrl, float oldValue )
	{
		switch ( ctrl )
		{
			case CarSoundCtrl.DOORS:
				float newValue = 0;

				//-----
				if ( GetCarDoorsState( "Truck_02_Door_1_1" ) == CarDoorState.DOORS_CLOSED )
				{
					newValue += 0.4;
				}

				if ( GetCarDoorsState( "Truck_02_Door_2_1" ) == CarDoorState.DOORS_CLOSED )
				{
					newValue += 0.4;
				}

				if ( newValue > 1 )
					newValue = 1;

			return newValue;
			break;
		}

		return oldValue;
	}
	
	override string GetAnimSourceFromSelection( string selection )
	{
		switch( selection )
		{
		case "doors_driver":
			return "DoorsDriver";
		case "doors_codriver":
			return "DoorsCoDriver";
		case "doors_hood":
			return "DoorsHood";
		case "doors_trunk":
			return "DoorsTrunk";			
		case "wheelsideplate1":
			return "WheelSidePlate1";
		case "wheelsideplate2":
			return "WheelSidePlate2";
		}

		return "";
	}

	override bool IsVitalCarBattery()
	{
		return false;
	}

	override bool IsVitalSparkPlug()
	{
		return false;
	}

	override bool IsVitalGlowPlug()
	{
		return false;
	}

	override bool IsVitalEngineBelt()
	{
		return false;
	}
	
	override bool IsVitalRadiator()
	{
		return false;
	}

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
		}

		return false;
	}

	override bool CanReachDoorsFromSeat( string pDoorsSelection, int pCurrentSeat )
	{
		switch( pCurrentSeat )
		{
		case 0:
			if (pDoorsSelection == "DoorsDriver")
			{
				return true;
			}
		break;

		case 1:
			if (pDoorsSelection == "DoorsCoDriver")
			{
				return true;
			}
		break;
		}
		
		return false;		
	}
	
	override int GetSeatIndexFromDoor( string pDoorSelection )
	{
		switch (pDoorSelection)
		{
			case "DoorsDriver":
				return 0;
				break;
			case "DoorsCoDriver":
				return 1;
				break;
		}
		return -1;
	}
	
	override void OnDebugSpawn()
	{
		EntityAI entity;
		
		if ( Class.CastTo(entity, this) )
		{
			entity.GetInventory().CreateInInventory( "Truck_02_Wheel" );
			entity.GetInventory().CreateInInventory( "Truck_02_Wheel" );
			entity.GetInventory().CreateInInventory( "Truck_02_Wheel" );
			entity.GetInventory().CreateInInventory( "Truck_02_Wheel" );

			entity.GetInventory().CreateInInventory( "TruckBattery" );
			entity.GetInventory().CreateInInventory( "SparkPlug" );

			entity.GetInventory().CreateInInventory( "Truck_02_Door_1_1" );
			entity.GetInventory().CreateInInventory( "Truck_02_Door_2_1" );

			entity.GetInventory().CreateInInventory( "HeadlightH7" );
			entity.GetInventory().CreateInInventory( "HeadlightH7" );
		}

		Fill( CarFluid.FUEL, 50 );
		Fill( CarFluid.OIL, 4.0 );
	};
}