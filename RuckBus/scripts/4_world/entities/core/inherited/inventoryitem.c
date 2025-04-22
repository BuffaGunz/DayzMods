class IkarusWheel extends CarWheel 
{
	override void EEKilled(Object killer)
	{
		string newWheel = "";
		switch( GetType() )
		{
			case "IkarusWheel":
				newWheel = "IkarusWheel_destroyed";
			break;
			
			case "ikaruswheel_rear":
					newWheel = "ikaruswheel_rear_destroyed";
			break;
		}
		if ( newWheel != "" )
		{
			ReplaceWheelLambda lambda = new ReplaceWheelLambda ( this, newWheel, NULL);
			lambda.SetTransferParams(true, true, true);
			GetInventory().ReplaceItemWithNew(InventoryMode.SERVER, lambda);
		}
	}

	override int GetMeleeTargetType()
	{
		return EMeleeTargetType.NONALIGNABLE;
	}
	
	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionDetach);
		AddAction(ActionAttachOnSelection);
	}
};

class IkarusWheel_destroyed extends CarWheel {};
class BusLeftDoors_1 extends CarDoor {};
class BusRightDoors_1 extends CarDoor {};
class BusLeftDoors_2 extends CarDoor {};
class BusRightDoors_2 extends CarDoor {};
class BusLeftDoors_3 extends CarDoor {};
class BusRightDoors_3 extends CarDoor {};
class BusHood extends CarDoor {};
