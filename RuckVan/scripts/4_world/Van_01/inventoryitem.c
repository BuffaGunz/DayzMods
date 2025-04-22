class van_01_wheel extends CarWheel 
{
	override void EEHealthLevelChanged(int oldLevel, int newLevel, string zone)
	{
		super.EEHealthLevelChanged(oldLevel, newLevel, zone);
		
		if (newLevel ==  GameConstants.STATE_RUINED)
		{
			string newWheel = "";
			switch (GetType())
			{
				case "Van_01_Wheel":
					newWheel = "Van_01_Wheel_ruined";
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

class Van_01_Wheel_ruined extends CarWheel {};
class van_01_door_1_1 extends CarDoor {};
class van_01_door_2_1 extends CarDoor {};
class van_01_door_2_2 extends CarDoor {};
class van_01_trunk_1 extends CarDoor {};
class van_01_trunk_2 extends CarDoor {};