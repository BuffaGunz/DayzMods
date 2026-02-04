modded class MissionGameplay
{
	static const int MAP_RETRY_INTERVAL_MS = 100;
	static const int MAP_RETRY_MAX_ATTEMPTS = 80; // Try for 8 seconds should never reach this tho.
	
	protected ref Ruck3DMarkerManager m_Ruck3DMarkers;
	
	override void OnInit()
	{
		super.OnInit();
		m_Ruck3DMarkers = new Ruck3DMarkerManager();
	}

	override void OnUpdate(float timeslice)
	{
		super.OnUpdate(timeslice);

		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
		if (!player)
			return;

		if (GetGame().GetUIManager().GetMenu())
		{
			if (m_Ruck3DMarkers)
				m_Ruck3DMarkers.ClearAll();
			return;
		}

		if (GetUApi().GetInputByID(UAMapToggle).LocalPress())
		{
			ItemBase mapItem = null;
			array<EntityAI> items = new array<EntityAI>();
			player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, items);

			foreach (EntityAI item : items)
			{
				if (item && item.IsInherited(ItemMap))
				{
					mapItem = ItemBase.Cast(item);
					break;
				}
			}
			if (!mapItem)
				return;

			EntityAI inHandEntity = player.GetHumanInventory().GetEntityInHands();

			if (!player.GetDayZPlayerInventory().IsIdle())
				return;

			InventoryLocation handInventoryLocation = new InventoryLocation;
			handInventoryLocation.SetHands(player, mapItem);
			if (player.GetInventory().HasInventoryReservation(mapItem, handInventoryLocation))
				return;

			if (inHandEntity == mapItem)
			{
				if (player.GetHumanInventory().CanRemoveEntityInHands())
					GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(TryOpenMapRetry, 0, false, player, mapItem, 0);
			}
			else
			{
				InventoryLocation invLocQBItem = new InventoryLocation;
				mapItem.GetInventory().GetCurrentInventoryLocation(invLocQBItem);
				if (player.GetInventory().HasInventoryReservation(mapItem, invLocQBItem))
					return;

				if (inHandEntity)
				{
					InventoryLocation Reserved_Item_il = new InventoryLocation;

					InventoryLocation inHandEntityFSwapDst = new InventoryLocation;
					inHandEntity.GetInventory().GetCurrentInventoryLocation(inHandEntityFSwapDst);

					int index = player.GetHumanInventory().FindUserReservedLocationIndex(inHandEntity);
					if (index >= 0)
						player.GetHumanInventory().GetUserReservedLocation(index, Reserved_Item_il);

					if (Reserved_Item_il)
						inHandEntityFSwapDst.CopyLocationFrom(Reserved_Item_il, true);

					if (index < 0 && GameInventory.CanSwapEntitiesEx(mapItem, inHandEntity))
						player.PredictiveSwapEntities(mapItem, inHandEntity);
					else if (GameInventory.CanForceSwapEntitiesEx(mapItem, handInventoryLocation, inHandEntity, inHandEntityFSwapDst))
						player.PredictiveForceSwapEntities(mapItem, inHandEntity, inHandEntityFSwapDst);
				}
				else
				{
					if (player.GetInventory().HasInventoryReservation(mapItem, handInventoryLocation))
						return;

					if (player.GetInventory().CanAddEntityIntoHands(mapItem))
						player.PredictiveTakeEntityToHands(mapItem);
				}

				GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(TryOpenMapRetry, 0, false, player, mapItem, 0);
			}
		}

		if (!GetGame().IsClient())
			return;

		if (!m_Ruck3DMarkers)
			m_Ruck3DMarkers = new Ruck3DMarkerManager();

		PlayerBase pb = PlayerBase.Cast(GetGame().GetPlayer());
		if (!pb)
		{
			m_Ruck3DMarkers.ClearAll();
			return;
		}

		bool hasGPS = false;
		MapNavigationBehaviour nav = pb.GetMapNavigationBehaviour();
		if (nav)
			hasGPS = (nav.GetNavigationType() & EMapNavigationType.GPS|EMapNavigationType.ALL == 0);

		ChernarusMap ruckMapItem = null;

		EntityAI inHandsMap = pb.GetHumanInventory().GetEntityInHands();
		ruckMapItem = ChernarusMap.Cast(inHandsMap);

		if (!ruckMapItem)
		{
			array<EntityAI> invItems = new array<EntityAI>();
			pb.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, invItems);

			foreach (EntityAI invItem : invItems)
			{
				ChernarusMap m = ChernarusMap.Cast(invItem);
				if (m)
				{
					ruckMapItem = m;
					break;
				}
			}
		}

		if (!ruckMapItem || !hasGPS || !ruckMapItem.Ruck_Is3DEnabledFromServer())
		{
			m_Ruck3DMarkers.ClearAll();
			return;
		}

		m_Ruck3DMarkers.Update(ruckMapItem);
	}

	void TryOpenMapRetry(PlayerBase player, ItemBase mapItem, int attempt)
	{
		if (!player || !mapItem)
			return;

		if (attempt > MAP_RETRY_MAX_ATTEMPTS)
			return; 

		if (!OpenMap(player, mapItem))
		{
			GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(TryOpenMapRetry, MAP_RETRY_INTERVAL_MS, false, player, mapItem, attempt + 1);
		}
	}

	bool OpenMap(PlayerBase player, ItemBase mapItem) // Runs the vanilla action unfold map i had some trouble find these actions untill taking a peak inside Zens map which pointed me to playerbase vanilla actions. Thanks zen also found the vanilla quickbar knowledege which i used for swapping items/weapons. 
	{
		if (!player || !mapItem)
			return false;

		if (GetGame().GetUIManager().GetMenu())
			return false;

		if (!player.GetDayZPlayerInventory().IsIdle())
			return false;

		if (player.GetHumanInventory().GetEntityInHands() != mapItem)
			return false;

		if (!player.GetHumanInventory().CanRemoveEntityInHands())
			return false;

		ActionManagerClient actionMgr = ActionManagerClient.Cast(player.GetActionManager());
		if (!actionMgr)
			return false;

		ActionBase action = ActionManagerClient.GetAction(ActionUnfoldMap);
		if (!action)
			return false;

		ActionTarget target = null;

		actionMgr.InjectAction(action, target, mapItem);
		actionMgr.PerformActionStart(action, target, mapItem);
		actionMgr.EjectAction(action);

		return true;
	}
};
