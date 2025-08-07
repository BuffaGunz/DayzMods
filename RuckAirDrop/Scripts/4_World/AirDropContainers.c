class AirdropContainerRed extends Land_ContainerLocked_Red_DE
{
	protected Particle m_ParticleEfx;
	protected Object m_VisualLootCrate; 
	bool m_InventoryUnlocked = false;

	void EEInit()
	{
		if (GetGame().IsServer())
		{
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(DelayedInit, 100, false);
		}
		
		if (!GetGame().IsDedicatedServer())
		{
			// Spawn smoke
			m_ParticleEfx = Particle.PlayOnObject(ParticleList.GRENADE_M18_RED_LOOP, this, Vector(0, 1.5, 0));
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.StopSmoke, 600000, false);

			// Spawn visual loot crate
			SpawnVisualLootCrate();
		}
	}
	
	void DelayedInit()
	{
		if (GetInventory())
		{
			if (!FindAttachmentBySlotName("Truck_01_WoodenCrate1"))
			{
				GetInventory().CreateAttachment("RuckStorageRed");
			}

			if (!m_InventoryUnlocked)
			{
				GetInventory().LockInventory(LOCK_FROM_SCRIPT);
			}
		}
	}

	void SpawnVisualLootCrate()
	{
		// Create at origin so it spawns in local space
		m_VisualLootCrate = Object.Cast(GetGame().CreateObjectEx("StaticObj_Misc_SupplyBox2_DE", "0 0 0", ECE_LOCAL));

		if (m_VisualLootCrate)
		{
			// Attach to this container so it moves with it
			AddChild(m_VisualLootCrate, -1);

			// Set local offset so it's visually inside
			vector localOffset = "0 -0.3 0"; // tweak as needed
			m_VisualLootCrate.SetPosition(localOffset);
			m_VisualLootCrate.SetOrientation("0 0 0");

			// Make static so no physics apply
			m_VisualLootCrate.SetFlags(EntityFlags.STATIC, false);
		}
	}

	void StopSmoke()
	{
		if (m_ParticleEfx)
		{
			m_ParticleEfx.Stop();
			m_ParticleEfx = null;
		}
	}

	override void EEDelete(EntityAI parent)
	{
		StopSmoke();

		if (m_VisualLootCrate)
		{
			GetGame().ObjectDelete(m_VisualLootCrate);
			m_VisualLootCrate = null;
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
			m_InventoryUnlocked = true;
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

class AirdropContainerBlue extends Land_ContainerLocked_Blue_DE
{
	protected Particle m_ParticleEfx;
	protected Object m_VisualLootCrate; 
	bool m_InventoryUnlocked = false;

	void EEInit()
	{
		if (GetGame().IsServer())
		{
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(DelayedInit, 100, false);
		}
		
		if (!GetGame().IsDedicatedServer())
		{
			m_ParticleEfx = Particle.PlayOnObject(ParticleList.BlueSmoke, this, Vector(0, 1.5, 0));
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.StopSmoke, 600000, false);
			
			SpawnVisualLootCrate();
		}
	}
	
	void DelayedInit()
	{
		if (GetInventory())
		{
			if (!FindAttachmentBySlotName("Truck_01_WoodenCrate1"))
			{
				GetInventory().CreateAttachment("RuckStorageBlue");
			}

			if (!m_InventoryUnlocked)
			{
				GetInventory().LockInventory(LOCK_FROM_SCRIPT);
			}
		}
	}
	
	void SpawnVisualLootCrate()
	{
		m_VisualLootCrate = Object.Cast(GetGame().CreateObjectEx("StaticObj_Misc_SupplyBox2_DE", "0 0 0", ECE_LOCAL));

		if (m_VisualLootCrate)
		{
			AddChild(m_VisualLootCrate, -1);

			vector localOffset = "0 -0.3 0";
			m_VisualLootCrate.SetPosition(localOffset);
			m_VisualLootCrate.SetOrientation("0 0 0");

			m_VisualLootCrate.SetFlags(EntityFlags.STATIC, false);
		}
	}

	void StopSmoke()
	{
		if (m_ParticleEfx)
		{
			m_ParticleEfx.Stop();
			m_ParticleEfx = null;
		}
	}

	override void EEDelete(EntityAI parent)
	{
		StopSmoke();

		if (m_VisualLootCrate)
		{
			GetGame().ObjectDelete(m_VisualLootCrate);
			m_VisualLootCrate = null;
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
			m_InventoryUnlocked = true;  
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

class AirdropContainerYellow extends Land_ContainerLocked_Yellow_DE
{
	protected Particle m_ParticleEfx;
	protected Object m_VisualLootCrate; 
	bool m_InventoryUnlocked = false;
	
	void EEInit()
	{
		if (GetGame().IsServer())
		{
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(DelayedInit, 100, false);
		}
		
		if (!GetGame().IsDedicatedServer())
		{
			m_ParticleEfx = Particle.PlayOnObject(ParticleList.GRENADE_M18_YELLOW_LOOP, this, Vector(0, 1.5, 0));
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.StopSmoke, 600000, false);
			
			SpawnVisualLootCrate();
		}
	}
	
	void DelayedInit()
	{
		if (GetInventory())
		{
			if (!FindAttachmentBySlotName("Truck_01_WoodenCrate1"))
			{
				GetInventory().CreateAttachment("RuckStorageYellow");
			}

			if (!m_InventoryUnlocked)
			{
				GetInventory().LockInventory(LOCK_FROM_SCRIPT);
			}
		}
	}
	
	void SpawnVisualLootCrate()
	{
		m_VisualLootCrate = Object.Cast(GetGame().CreateObjectEx("StaticObj_Misc_SupplyBox2_DE", "0 0 0", ECE_LOCAL));

		if (m_VisualLootCrate)
		{
			AddChild(m_VisualLootCrate, -1);

			vector localOffset = "0 -0.3 0";
			m_VisualLootCrate.SetPosition(localOffset);
			m_VisualLootCrate.SetOrientation("0 0 0");

			m_VisualLootCrate.SetFlags(EntityFlags.STATIC, false);
		}
	}

	void StopSmoke()
	{
		if (m_ParticleEfx)
		{
			m_ParticleEfx.Stop();
			m_ParticleEfx = null;
		}
	}

	override void EEDelete(EntityAI parent)
	{
		StopSmoke();

		if (m_VisualLootCrate)
		{
			GetGame().ObjectDelete(m_VisualLootCrate);
			m_VisualLootCrate = null;
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
			m_InventoryUnlocked = true;  
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

class AirdropContainerOrange extends Land_ContainerLocked_Orange_DE
{
	protected Particle m_ParticleEfx;
	protected Object m_VisualLootCrate; 
	bool m_InventoryUnlocked = false;

	void EEInit()
	{
		if (GetGame().IsServer())
		{
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(DelayedInit, 100, false);
		}
		
		if (!GetGame().IsDedicatedServer())
		{
			m_ParticleEfx = Particle.PlayOnObject(ParticleList.OrangeSmoke, this, Vector(0, 1.5, 0));
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.StopSmoke, 600000, false);
			
			SpawnVisualLootCrate();
		}
	}
	
	void DelayedInit()
	{
		if (GetInventory())
		{
			if (!FindAttachmentBySlotName("Truck_01_WoodenCrate1"))
			{
				GetInventory().CreateAttachment("RuckStorageOrange");
			}

			if (!m_InventoryUnlocked)
			{
				GetInventory().LockInventory(LOCK_FROM_SCRIPT);
			}
		}
	}
	
	void SpawnVisualLootCrate()
	{
		m_VisualLootCrate = Object.Cast(GetGame().CreateObjectEx("StaticObj_Misc_SupplyBox2_DE", "0 0 0", ECE_LOCAL));

		if (m_VisualLootCrate)
		{
			AddChild(m_VisualLootCrate, -1);

			vector localOffset = "0 -0.3 0";
			m_VisualLootCrate.SetPosition(localOffset);
			m_VisualLootCrate.SetOrientation("0 0 0");

			m_VisualLootCrate.SetFlags(EntityFlags.STATIC, false);
		}
	}

	void StopSmoke()
	{
		if (m_ParticleEfx)
		{
			m_ParticleEfx.Stop();
			m_ParticleEfx = null;
		}
	}

	override void EEDelete(EntityAI parent)
	{
		StopSmoke();

		if (m_VisualLootCrate)
		{
			GetGame().ObjectDelete(m_VisualLootCrate);
			m_VisualLootCrate = null;
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
