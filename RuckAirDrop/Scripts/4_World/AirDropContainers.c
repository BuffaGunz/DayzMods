class AirdropContainerRed extends Land_ContainerLocked_Red_DE
{
	protected Particle m_ParticleEfx;
	protected Object m_VisualLootCrate; 
	bool m_InventoryUnlocked = false;

	static const int RUCK_MAX_CONTAINER_LIFETIME   = 1800000; 
	static const int RUCK_CHECK_INTERVAL           = 100000;  
	static const float RUCK_NEARBY_RADIUS          = 50.0;

	protected int  m_RuckElapsedMs = 0;    
	protected bool m_RuckTimerArmed = false; 

	void EEInit()
	{
		if (GetGame().IsServer())
		{
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(DelayedInit, 100, false);

			Ruck_StartTimerIfNeeded();
		}
		
		if (!GetGame().IsDedicatedServer())
		{
			m_ParticleEfx = Particle.PlayOnObject(ParticleList.GRENADE_M18_RED_LOOP, this, Vector(0, 1.5, 0));
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
		if (GetGame()) GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(this.Ruck_TimerTick);
		m_RuckTimerArmed = false;

		StopSmoke();
		if (m_VisualLootCrate)
		{
			GetGame().ObjectDelete(m_VisualLootCrate);
			m_VisualLootCrate = null;
		}

		#ifdef SERVER
			#ifdef BASICMAP
				RuckBasicMarkerService.ServerRemoveMarkerFor(this);
			#endif
			#ifdef LBmaster_Groups
				RuckLBMasterMarkerService.ServerRemoveMarkerFor(this);
			#endif
			#ifdef EXPANSIONMODNAVIGATION
				RuckExpansionMarkerService.ServerRemoveMarkerFor(this);
			#endif
			#ifdef RUCKMAP
				RuckMapDropCache.ServerRemove(this);
			#endif
		#endif

		super.EEDelete(parent);
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
	
	void Ruck_CreateAllMarkersAfterLoad()
	{
		#ifdef SERVER
			#ifdef BASICMAP
				RuckBasicMarkerService.ServerRecreateAfterLoad(this);
			#endif
			#ifdef LBmaster_Groups
				RuckLBMasterMarkerService.ServerRecreateAfterLoad(this);
			#endif
			#ifdef EXPANSIONMODNAVIGATION
				RuckExpansionMarkerService.ServerRecreateAfterLoad(this);
			#endif
			#ifdef RUCKMAP
				RuckMapDropCache.ServerRecreateAfterLoad(this);
			#endif
		#endif
	}

	override void OnStoreSave(ParamsWriteContext ctx)
	{
		super.OnStoreSave(ctx);
		ctx.Write(m_InventoryUnlocked);

		ctx.Write(m_RuckElapsedMs);
		ctx.Write(m_RuckTimerArmed);
	}
	
	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		if (!super.OnStoreLoad(ctx, version)) return false;
		if (!ctx.Read(m_InventoryUnlocked))   return false;

		if (!ctx.Read(m_RuckElapsedMs))  m_RuckElapsedMs  = 0;
		if (!ctx.Read(m_RuckTimerArmed)) m_RuckTimerArmed = false;
		
		SetAffectPathgraph(true, true);
		SetSynchDirty();
		GetGame().UpdatePathgraphRegionByObject(this);

		#ifdef SERVER
		if (!m_InventoryUnlocked)
		{
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(RuckPlane.SpawnZombiesAtDrop, 10000, false, this, "ShippingContainerKeys_Red");
		}
		#endif
		
		#ifdef SERVER
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.Ruck_CreateAllMarkersAfterLoad, 100, false);

		Ruck_StartTimerIfNeeded();
		#endif

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

	protected void Ruck_StartTimerIfNeeded()
	{
		if (!GetGame().IsServer()) return;
		if (m_RuckTimerArmed) return;

		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.Ruck_TimerTick, RUCK_CHECK_INTERVAL, true);
		m_RuckTimerArmed = true;
	}

	protected void Ruck_TimerTick()
	{
		if (!GetGame().IsServer()) return;

		vector pos = GetPosition();

		array<Man> players = {};
		GetGame().GetPlayers(players);

		bool nearby = false;
		foreach (Man p : players)
		{
			if (p && vector.Distance(pos, p.GetPosition()) <= RUCK_NEARBY_RADIUS)
			{
				nearby = true;
				break;
			}
		}

		if (!nearby)
		{
			m_RuckElapsedMs += RUCK_CHECK_INTERVAL;

			if (m_RuckElapsedMs >= RUCK_MAX_CONTAINER_LIFETIME)
			{
				GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(this.Ruck_TimerTick);
				m_RuckTimerArmed = false;

				GetGame().ObjectDelete(this);
				PrintFormat("[Cleanup] Deleted container (timer): %1", this);
				return;
			}
		}
	}
}

class AirdropContainerBlue extends Land_ContainerLocked_Blue_DE
{
	protected Particle m_ParticleEfx;
	protected Object m_VisualLootCrate; 
	bool m_InventoryUnlocked = false;
	
	static const int RUCK_MAX_CONTAINER_LIFETIME   = 1800000; 
	static const int RUCK_CHECK_INTERVAL           = 100000;  
	static const float RUCK_NEARBY_RADIUS          = 50.0;

	protected int  m_RuckElapsedMs = 0;    
	protected bool m_RuckTimerArmed = false; 

	void EEInit()
	{
		if (GetGame().IsServer())
		{
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(DelayedInit, 100, false);
			
			Ruck_StartTimerIfNeeded();
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
		if (GetGame()) GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(this.Ruck_TimerTick);
		m_RuckTimerArmed = false;
		
		StopSmoke();
		if (m_VisualLootCrate)
		{
			GetGame().ObjectDelete(m_VisualLootCrate);
			m_VisualLootCrate = null;
		}

		#ifdef SERVER
			#ifdef BASICMAP
				RuckBasicMarkerService.ServerRemoveMarkerFor(this);
			#endif
			#ifdef LBmaster_Groups
				RuckLBMasterMarkerService.ServerRemoveMarkerFor(this);
			#endif
			#ifdef EXPANSIONMODNAVIGATION
				RuckExpansionMarkerService.ServerRemoveMarkerFor(this);
			#endif
			#ifdef RUCKMAP
				RuckMapDropCache.ServerRemove(this);
			#endif
		#endif

		super.EEDelete(parent);
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
	
	void Ruck_CreateAllMarkersAfterLoad()
	{
		#ifdef SERVER
			#ifdef BASICMAP
				RuckBasicMarkerService.ServerRecreateAfterLoad(this);
			#endif
			#ifdef LBmaster_Groups
				RuckLBMasterMarkerService.ServerRecreateAfterLoad(this);
			#endif
			#ifdef EXPANSIONMODNAVIGATION
				RuckExpansionMarkerService.ServerRecreateAfterLoad(this);
			#endif
			#ifdef RUCKMAP
				RuckMapDropCache.ServerRecreateAfterLoad(this);
			#endif
		#endif

	}
	
	override void OnStoreSave(ParamsWriteContext ctx)
	{
		super.OnStoreSave(ctx);
		ctx.Write(m_InventoryUnlocked);
		
		ctx.Write(m_RuckElapsedMs);
		ctx.Write(m_RuckTimerArmed);
	}
	
	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		if (!super.OnStoreLoad(ctx, version)) return false;
		if (!ctx.Read(m_InventoryUnlocked))   return false;
		
		if (!ctx.Read(m_RuckElapsedMs))  m_RuckElapsedMs  = 0;
		if (!ctx.Read(m_RuckTimerArmed)) m_RuckTimerArmed = false;

		#ifdef SERVER
		if (!m_InventoryUnlocked)
		{
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(RuckPlane.SpawnZombiesAtDrop, 10000, false, this, "ShippingContainerKeys_Blue");
		}
		#endif
		
		#ifdef SERVER
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.Ruck_CreateAllMarkersAfterLoad, 100, false);

		Ruck_StartTimerIfNeeded();
		#endif

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
	
	protected void Ruck_StartTimerIfNeeded()
	{
		if (!GetGame().IsServer()) return;
		if (m_RuckTimerArmed) return;

		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.Ruck_TimerTick, RUCK_CHECK_INTERVAL, true);
		m_RuckTimerArmed = true;
	}

	protected void Ruck_TimerTick()
	{
		if (!GetGame().IsServer()) return;

		vector pos = GetPosition();

		array<Man> players = {};
		GetGame().GetPlayers(players);

		bool nearby = false;
		foreach (Man p : players)
		{
			if (p && vector.Distance(pos, p.GetPosition()) <= RUCK_NEARBY_RADIUS)
			{
				nearby = true;
				break;
			}
		}

		if (!nearby)
		{
			m_RuckElapsedMs += RUCK_CHECK_INTERVAL;

			if (m_RuckElapsedMs >= RUCK_MAX_CONTAINER_LIFETIME)
			{
				GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(this.Ruck_TimerTick);
				m_RuckTimerArmed = false;

				GetGame().ObjectDelete(this);
				PrintFormat("[Cleanup] Deleted container (timer): %1", this);
				return;
			}
		}
	}
}

class AirdropContainerYellow extends Land_ContainerLocked_Yellow_DE
{
	protected Particle m_ParticleEfx;
	protected Object m_VisualLootCrate; 
	bool m_InventoryUnlocked = false;
	
	static const int RUCK_MAX_CONTAINER_LIFETIME   = 1800000; 
	static const int RUCK_CHECK_INTERVAL           = 100000;  
	static const float RUCK_NEARBY_RADIUS          = 50.0;

	protected int  m_RuckElapsedMs = 0;    
	protected bool m_RuckTimerArmed = false; 
	
	void EEInit()
	{
		if (GetGame().IsServer())
		{
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(DelayedInit, 100, false);
			
			Ruck_StartTimerIfNeeded();
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
		if (GetGame()) GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(this.Ruck_TimerTick);
		m_RuckTimerArmed = false;
		
		StopSmoke();
		if (m_VisualLootCrate)
		{
			GetGame().ObjectDelete(m_VisualLootCrate);
			m_VisualLootCrate = null;
		}

		#ifdef SERVER
			#ifdef BASICMAP
				RuckBasicMarkerService.ServerRemoveMarkerFor(this);
			#endif
			#ifdef LBmaster_Groups
				RuckLBMasterMarkerService.ServerRemoveMarkerFor(this);
			#endif
			#ifdef EXPANSIONMODNAVIGATION
				RuckExpansionMarkerService.ServerRemoveMarkerFor(this);
			#endif
			#ifdef RUCKMAP
				RuckMapDropCache.ServerRemove(this);
			#endif
		#endif

		super.EEDelete(parent);
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
	
	void Ruck_CreateAllMarkersAfterLoad()
	{
		#ifdef SERVER
			#ifdef BASICMAP
				RuckBasicMarkerService.ServerRecreateAfterLoad(this);
			#endif
			#ifdef LBmaster_Groups
				RuckLBMasterMarkerService.ServerRecreateAfterLoad(this);
			#endif
			#ifdef EXPANSIONMODNAVIGATION
				RuckExpansionMarkerService.ServerRecreateAfterLoad(this);
			#endif
			#ifdef RUCKMAP
				RuckMapDropCache.ServerRecreateAfterLoad(this);
			#endif
		#endif

	}
	
	override void OnStoreSave(ParamsWriteContext ctx)
	{
		super.OnStoreSave(ctx);
		ctx.Write(m_InventoryUnlocked);
		
		ctx.Write(m_RuckElapsedMs);
		ctx.Write(m_RuckTimerArmed);
	}
	
	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		if (!super.OnStoreLoad(ctx, version)) return false;
		if (!ctx.Read(m_InventoryUnlocked))   return false;
		
		if (!ctx.Read(m_RuckElapsedMs))  m_RuckElapsedMs  = 0;
		if (!ctx.Read(m_RuckTimerArmed)) m_RuckTimerArmed = false;
		
		SetAffectPathgraph(true, true);
		SetSynchDirty();
		GetGame().UpdatePathgraphRegionByObject(this);

		#ifdef SERVER
		if (!m_InventoryUnlocked)
		{
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(RuckPlane.SpawnZombiesAtDrop, 10000, false, this, "ShippingContainerKeys_Yellow");
		}
		#endif
		
		#ifdef SERVER
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.Ruck_CreateAllMarkersAfterLoad, 100, false);

		Ruck_StartTimerIfNeeded();
		#endif

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
	
	protected void Ruck_StartTimerIfNeeded()
	{
		if (!GetGame().IsServer()) return;
		if (m_RuckTimerArmed) return;

		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.Ruck_TimerTick, RUCK_CHECK_INTERVAL, true);
		m_RuckTimerArmed = true;
	}

	protected void Ruck_TimerTick()
	{
		if (!GetGame().IsServer()) return;

		vector pos = GetPosition();

		array<Man> players = {};
		GetGame().GetPlayers(players);

		bool nearby = false;
		foreach (Man p : players)
		{
			if (p && vector.Distance(pos, p.GetPosition()) <= RUCK_NEARBY_RADIUS)
			{
				nearby = true;
				break;
			}
		}

		if (!nearby)
		{
			m_RuckElapsedMs += RUCK_CHECK_INTERVAL;

			if (m_RuckElapsedMs >= RUCK_MAX_CONTAINER_LIFETIME)
			{
				GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(this.Ruck_TimerTick);
				m_RuckTimerArmed = false;

				GetGame().ObjectDelete(this);
				PrintFormat("[Cleanup] Deleted container (timer): %1", this);
				return;
			}
		}
	}
}

class AirdropContainerOrange extends Land_ContainerLocked_Orange_DE
{
	protected Particle m_ParticleEfx;
	protected Object m_VisualLootCrate; 
	bool m_InventoryUnlocked = false;
	
	static const int RUCK_MAX_CONTAINER_LIFETIME   = 1800000; 
	static const int RUCK_CHECK_INTERVAL           = 100000;  
	static const float RUCK_NEARBY_RADIUS          = 50.0;

	protected int  m_RuckElapsedMs = 0;    
	protected bool m_RuckTimerArmed = false; 

	void EEInit()
	{
		if (GetGame().IsServer())
		{
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(DelayedInit, 100, false);
			
			Ruck_StartTimerIfNeeded();
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
		if (GetGame()) GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(this.Ruck_TimerTick);
		m_RuckTimerArmed = false;
		
		StopSmoke();
		if (m_VisualLootCrate)
		{
			GetGame().ObjectDelete(m_VisualLootCrate);
			m_VisualLootCrate = null;
		}

		#ifdef SERVER
			#ifdef BASICMAP
				RuckBasicMarkerService.ServerRemoveMarkerFor(this);
			#endif
			#ifdef LBmaster_Groups
				RuckLBMasterMarkerService.ServerRemoveMarkerFor(this);
			#endif
			#ifdef EXPANSIONMODNAVIGATION
				RuckExpansionMarkerService.ServerRemoveMarkerFor(this);
			#endif
			#ifdef RUCKMAP
				RuckMapDropCache.ServerRemove(this);
			#endif
		#endif

		super.EEDelete(parent);
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
	
	void Ruck_CreateAllMarkersAfterLoad()
	{
		#ifdef SERVER
			#ifdef BASICMAP
				RuckBasicMarkerService.ServerRecreateAfterLoad(this);
			#endif
			#ifdef LBmaster_Groups
				RuckLBMasterMarkerService.ServerRecreateAfterLoad(this);
			#endif
			#ifdef EXPANSIONMODNAVIGATION
				RuckExpansionMarkerService.ServerRecreateAfterLoad(this);
			#endif
			#ifdef RUCKMAP
				RuckMapDropCache.ServerRecreateAfterLoad(this);
			#endif
		#endif
	}

	override void OnStoreSave(ParamsWriteContext ctx)
	{
		super.OnStoreSave(ctx);
		ctx.Write(m_InventoryUnlocked);
		
		ctx.Write(m_RuckElapsedMs);
		ctx.Write(m_RuckTimerArmed);
	}
	
	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		if (!super.OnStoreLoad(ctx, version)) return false;
		if (!ctx.Read(m_InventoryUnlocked))   return false;
		
		if (!ctx.Read(m_RuckElapsedMs))  m_RuckElapsedMs  = 0;
		if (!ctx.Read(m_RuckTimerArmed)) m_RuckTimerArmed = false;
		
		SetAffectPathgraph(true, true);
		SetSynchDirty();
		GetGame().UpdatePathgraphRegionByObject(this);

		#ifdef SERVER
		if (!m_InventoryUnlocked)
		{
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(RuckPlane.SpawnZombiesAtDrop, 10000, false, this, "ShippingContainerKeys_Orange");
		}
		#endif
		
		#ifdef SERVER
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.Ruck_CreateAllMarkersAfterLoad, 100, false);

		Ruck_StartTimerIfNeeded();
		#endif

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
	
	protected void Ruck_StartTimerIfNeeded()
	{
		if (!GetGame().IsServer()) return;
		if (m_RuckTimerArmed) return;

		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(this.Ruck_TimerTick, RUCK_CHECK_INTERVAL, true);
		m_RuckTimerArmed = true;
	}

	protected void Ruck_TimerTick()
	{
		if (!GetGame().IsServer()) return;

		vector pos = GetPosition();

		array<Man> players = {};
		GetGame().GetPlayers(players);

		bool nearby = false;
		foreach (Man p : players)
		{
			if (p && vector.Distance(pos, p.GetPosition()) <= RUCK_NEARBY_RADIUS)
			{
				nearby = true;
				break;
			}
		}

		if (!nearby)
		{
			m_RuckElapsedMs += RUCK_CHECK_INTERVAL;

			if (m_RuckElapsedMs >= RUCK_MAX_CONTAINER_LIFETIME)
			{
				GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(this.Ruck_TimerTick);
				m_RuckTimerArmed = false;

				GetGame().ObjectDelete(this);
				PrintFormat("[Cleanup] Deleted container (timer): %1", this);
				return;
			}
		}
	}
}
