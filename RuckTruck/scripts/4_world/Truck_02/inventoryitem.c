class truck_02_wheel extends CarWheel 
{
	override void EEHealthLevelChanged(int oldLevel, int newLevel, string zone)
	{
		super.EEHealthLevelChanged(oldLevel, newLevel, zone);
		
		if (newLevel ==  GameConstants.STATE_RUINED)
		{
			string newWheel = "";
			switch (GetType())
			{
				case "truck_02_wheel":
					newWheel = "truck_02_wheel_ruined";
					break;
			}

			if (newWheel != "")
			{
				//Unlock to allow creating a new item
				if (IsLockedInSlot())
					UnlockFromParent();

				IEntity child = GetChildren();
				while (child)
				{
					RemoveChild(child, false);
					vector matrix[4];
					GetTransform(matrix);
					GetInventory().DropEntityWithTransform(InventoryMode.SERVER, this, EntityAI.Cast(child), matrix);
					child = GetSibling();
				}

				ReplaceWheelLambda lambda = new ReplaceWheelLambda(this, newWheel, null);
				lambda.SetTransferParams(true, true, true);
				GetInventory().ReplaceItemWithNew(InventoryMode.SERVER, lambda);
			}
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

class truck_02_wheel_ruined extends CarWheel {};
class truck_02_door_1_1 extends CarDoor {};
class truck_02_door_2_1 extends CarDoor {};
class truck_02_hull extends CarDoor {};