class ShipContainerRed extends Land_ContainerLocked_Red_DE
{
	protected Object m_ShipLootCrate; 
	bool m_InventoryUnlocked = false;

	void EEInit()
	{
		if (GetGame().IsServer())
		{
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(DelayedInit, 100, false);
		}
		
		if (!GetGame().IsDedicatedServer())
		{
			SpawnShipLootCrate();
		}
	}
	
	void DelayedInit()
	{
		if (GetInventory())
		{
			if (!FindAttachmentBySlotName("Truck_01_WoodenCrate1"))
			{
				GetInventory().CreateAttachment("RuckShipStorage");
			}

			if (!m_InventoryUnlocked)
			{
				GetInventory().LockInventory(LOCK_FROM_SCRIPT);
			}
		}
	}
	
	void SpawnShipLootCrate()
	{
		m_ShipLootCrate = Object.Cast(GetGame().CreateObjectEx("StaticObj_Misc_SupplyBox2_DE", "0 0 0", ECE_LOCAL));

		if (m_ShipLootCrate)
		{
			AddChild(m_ShipLootCrate, -1);

			vector localOffset = "0 -0.3 0";
			m_ShipLootCrate.SetPosition(localOffset);
			m_ShipLootCrate.SetOrientation("0 0 0");

			m_ShipLootCrate.SetFlags(EntityFlags.STATIC, false);
		}
	}

	override void EEDelete(EntityAI parent)
	{
		if (m_ShipLootCrate)
		{
			GetGame().ObjectDelete(m_ShipLootCrate);
			m_ShipLootCrate = null;
		}
	}
	
	override bool CanReleaseAttachment(EntityAI attachment)
	{
			return false;
	}

	override bool CanReceiveAttachment(EntityAI attachment, int slotId)
	{
		return true;
	}
	
	override void OnDoorUnlocked(DoorLockParams params)
	{
		super.OnDoorUnlocked(params);

		int doorIdx = params.param1;
		m_LockedMask &= ~(1 << doorIdx);
		SetAnimationPhase(string.Format("side%1_lock", doorIdx + 1), 1);

		if (!GetGame().IsDedicatedServer())
		{
			SEffectManager.PlaySoundEnviroment("Land_ContainerLocked_lock_SoundSet", GetDoorSoundPos(doorIdx));
		}

		if (GetInventory())
		{
			GetInventory().UnlockInventory(LOCK_FROM_SCRIPT);
			m_InventoryUnlocked = true;  // <-- Track it
		}
	}

	override void OnStoreSave(ParamsWriteContext ctx)
	{
		super.OnStoreSave(ctx);
		ctx.Write(m_InventoryUnlocked);
	}
	
	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		if (!super.OnStoreLoad(ctx, version))
			return false;

		if (!ctx.Read(m_InventoryUnlocked))
			return false;

		return true;
	}

	bool HasInventory()
	{
		return true; 
	}
	
	override bool IsInventoryVisible()
	{
		return !GetInventory().IsInventoryLockedForLockType(LOCK_FROM_SCRIPT);
	}
}

class ShipContainerBlue extends Land_ContainerLocked_Blue_DE
{
	protected Object m_ShipLootCrate; 
	bool m_InventoryUnlocked = false;

	void EEInit()
	{
		if (GetGame().IsServer())
		{
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(DelayedInit, 100, false);
		}
		
		if (!GetGame().IsDedicatedServer())
		{
			SpawnShipLootCrate();
		}
	}
	
	void DelayedInit()
	{
		if (GetInventory())
		{
			if (!FindAttachmentBySlotName("Truck_01_WoodenCrate1"))
			{
				GetInventory().CreateAttachment("RuckShipStorage");
			}

			if (!m_InventoryUnlocked)
			{
				GetInventory().LockInventory(LOCK_FROM_SCRIPT);
			}
		}
	}
	
	void SpawnShipLootCrate()
	{
		m_ShipLootCrate = Object.Cast(GetGame().CreateObjectEx("StaticObj_Misc_SupplyBox2_DE", "0 0 0", ECE_LOCAL));

		if (m_ShipLootCrate)
		{
			AddChild(m_ShipLootCrate, -1);

			vector localOffset = "0 -0.3 0";
			m_ShipLootCrate.SetPosition(localOffset);
			m_ShipLootCrate.SetOrientation("0 0 0");

			m_ShipLootCrate.SetFlags(EntityFlags.STATIC, false);
		}
	}

	override void EEDelete(EntityAI parent)
	{
		if (m_ShipLootCrate)
		{
			GetGame().ObjectDelete(m_ShipLootCrate);
			m_ShipLootCrate = null;
		}
	}
	
	override bool CanReleaseAttachment(EntityAI attachment)
	{
			return false;
	}

	override bool CanReceiveAttachment(EntityAI attachment, int slotId)
	{
		return true;
	}
	
	override void OnDoorUnlocked(DoorLockParams params)
	{
		super.OnDoorUnlocked(params);

		int doorIdx = params.param1;
		m_LockedMask &= ~(1 << doorIdx);
		SetAnimationPhase(string.Format("side%1_lock", doorIdx + 1), 1);

		if (!GetGame().IsDedicatedServer())
		{
			SEffectManager.PlaySoundEnviroment("Land_ContainerLocked_lock_SoundSet", GetDoorSoundPos(doorIdx));
		}

		if (GetInventory())
		{
			GetInventory().UnlockInventory(LOCK_FROM_SCRIPT);
			m_InventoryUnlocked = true;  // <-- Track it
		}
	}

	override void OnStoreSave(ParamsWriteContext ctx)
	{
		super.OnStoreSave(ctx);
		ctx.Write(m_InventoryUnlocked);
	}
	
	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		if (!super.OnStoreLoad(ctx, version))
			return false;

		if (!ctx.Read(m_InventoryUnlocked))
			return false;

		return true;
	}

	bool HasInventory()
	{
		return true; 
	}
	
	override bool IsInventoryVisible()
	{
		return !GetInventory().IsInventoryLockedForLockType(LOCK_FROM_SCRIPT);
	}
}

class ShipContainerYellow extends Land_ContainerLocked_Yellow_DE
{
	protected Object m_ShipLootCrate; 
	bool m_InventoryUnlocked = false;

	void EEInit()
	{
		if (GetGame().IsServer())
		{
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(DelayedInit, 100, false);
		}
		
		if (!GetGame().IsDedicatedServer())
		{
			SpawnShipLootCrate();
		}
	}
	
	void DelayedInit()
	{
		if (GetInventory())
		{
			if (!FindAttachmentBySlotName("Truck_01_WoodenCrate1"))
			{
				GetInventory().CreateAttachment("RuckShipStorage");
			}

			if (!m_InventoryUnlocked)
			{
				GetInventory().LockInventory(LOCK_FROM_SCRIPT);
			}
		}
	}
	
	void SpawnShipLootCrate()
	{
		m_ShipLootCrate = Object.Cast(GetGame().CreateObjectEx("StaticObj_Misc_SupplyBox2_DE", "0 0 0", ECE_LOCAL));

		if (m_ShipLootCrate)
		{
			AddChild(m_ShipLootCrate, -1);

			vector localOffset = "0 -0.3 0";
			m_ShipLootCrate.SetPosition(localOffset);
			m_ShipLootCrate.SetOrientation("0 0 0");

			m_ShipLootCrate.SetFlags(EntityFlags.STATIC, false);
		}
	}

	override void EEDelete(EntityAI parent)
	{
		if (m_ShipLootCrate)
		{
			GetGame().ObjectDelete(m_ShipLootCrate);
			m_ShipLootCrate = null;
		}
	}
	
	override bool CanReleaseAttachment(EntityAI attachment)
	{
			return false;
	}

	override bool CanReceiveAttachment(EntityAI attachment, int slotId)
	{
		return true;
	}
	
	override void OnDoorUnlocked(DoorLockParams params)
	{
		super.OnDoorUnlocked(params);

		int doorIdx = params.param1;
		m_LockedMask &= ~(1 << doorIdx);
		SetAnimationPhase(string.Format("side%1_lock", doorIdx + 1), 1);

		if (!GetGame().IsDedicatedServer())
		{
			SEffectManager.PlaySoundEnviroment("Land_ContainerLocked_lock_SoundSet", GetDoorSoundPos(doorIdx));
		}

		if (GetInventory())
		{
			GetInventory().UnlockInventory(LOCK_FROM_SCRIPT);
			m_InventoryUnlocked = true;  // <-- Track it
		}
	}

	override void OnStoreSave(ParamsWriteContext ctx)
	{
		super.OnStoreSave(ctx);
		ctx.Write(m_InventoryUnlocked);
	}
	
	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		if (!super.OnStoreLoad(ctx, version))
			return false;

		if (!ctx.Read(m_InventoryUnlocked))
			return false;

		return true;
	}

	bool HasInventory()
	{
		return true; 
	}
	
	override bool IsInventoryVisible()
	{
		return !GetInventory().IsInventoryLockedForLockType(LOCK_FROM_SCRIPT);
	}
}

class ShipContainerOrange extends Land_ContainerLocked_Orange_DE
{
	protected Object m_ShipLootCrate; 
	bool m_InventoryUnlocked = false;

	void EEInit()
	{
		if (GetGame().IsServer())
		{
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(DelayedInit, 100, false);
		}
		
		if (!GetGame().IsDedicatedServer())
		{
			SpawnShipLootCrate();
		}
	}
	
	void DelayedInit()
	{
		if (GetInventory())
		{
			if (!FindAttachmentBySlotName("Truck_01_WoodenCrate1"))
			{
				GetInventory().CreateAttachment("RuckShipStorage");
			}

			if (!m_InventoryUnlocked)
			{
				GetInventory().LockInventory(LOCK_FROM_SCRIPT);
			}
		}
	}
	
	void SpawnShipLootCrate()
	{
		m_ShipLootCrate = Object.Cast(GetGame().CreateObjectEx("StaticObj_Misc_SupplyBox2_DE", "0 0 0", ECE_LOCAL));

		if (m_ShipLootCrate)
		{
			AddChild(m_ShipLootCrate, -1);

			vector localOffset = "0 -0.3 0";
			m_ShipLootCrate.SetPosition(localOffset);
			m_ShipLootCrate.SetOrientation("0 0 0");

			m_ShipLootCrate.SetFlags(EntityFlags.STATIC, false);
		}
	}

	override void EEDelete(EntityAI parent)
	{
		if (m_ShipLootCrate)
		{
			GetGame().ObjectDelete(m_ShipLootCrate);
			m_ShipLootCrate = null;
		}
	}
	
	override bool CanReleaseAttachment(EntityAI attachment)
	{
			return false;
	}

	override bool CanReceiveAttachment(EntityAI attachment, int slotId)
	{
		return true;
	}
	
	override void OnDoorUnlocked(DoorLockParams params)
	{
		super.OnDoorUnlocked(params);

		int doorIdx = params.param1;
		m_LockedMask &= ~(1 << doorIdx);
		SetAnimationPhase(string.Format("side%1_lock", doorIdx + 1), 1);

		if (!GetGame().IsDedicatedServer())
		{
			SEffectManager.PlaySoundEnviroment("Land_ContainerLocked_lock_SoundSet", GetDoorSoundPos(doorIdx));
		}

		if (GetInventory())
		{
			GetInventory().UnlockInventory(LOCK_FROM_SCRIPT);
			m_InventoryUnlocked = true;  // <-- Track it
		}
	}

	override void OnStoreSave(ParamsWriteContext ctx)
	{
		super.OnStoreSave(ctx);
		ctx.Write(m_InventoryUnlocked);
	}
	
	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		if (!super.OnStoreLoad(ctx, version))
			return false;

		if (!ctx.Read(m_InventoryUnlocked))
			return false;

		return true;
	}

	bool HasInventory()
	{
		return true; 
	}
	
	override bool IsInventoryVisible()
	{
		return !GetInventory().IsInventoryLockedForLockType(LOCK_FROM_SCRIPT);
	}
}
