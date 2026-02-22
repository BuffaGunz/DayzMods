modded class SharpWoodenStick: LongWoodenStick
{
	protected bool m_IsPlaced;

	void SharpWoodenStick()
	{
		RegisterNetSyncVariableBool("m_IsPlaced");
	}

	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionClapBearTrapWithThisItem);
		AddAction(ActionCookOnStick);
		AddAction(ActionTogglePlaceObject);
		AddAction(ActionPlaceObject);
	}

	override void OnPlacementComplete(Man player, vector position = "0 0 0", vector orientation = "0 0 0")
	{
		super.OnPlacementComplete(player, position, orientation);

		if (GetGame().IsServer())
		{
			m_IsPlaced = true;
			SetSynchDirty();
		}
	}

	override void OnStoreSave(ParamsWriteContext ctx)
	{
		super.OnStoreSave(ctx);
		ctx.Write(m_IsPlaced);
	}

	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		if (!super.OnStoreLoad(ctx, version))
			return false;

		if (!ctx.Read(m_IsPlaced))
			m_IsPlaced = false;

		SetSynchDirty();
		return true;
	}
}

modded class Hologram
{
	override void SetProjectionPosition(vector position)
	{
		if (m_Projection && m_Projection.GetType() == "SharpWoodenStick")
		{
			position[1] = position[1] + 0.15;
		}

		super.SetProjectionPosition(position);
	}

	override void EvaluateCollision(ItemBase action_item = null)
	{
		ItemBase item_in_hands = ItemBase.Cast(m_Player.GetHumanInventory().GetEntityInHands());

		if (item_in_hands && item_in_hands.IsInherited(SharpWoodenStick))
		{
			SetIsColliding(false);
			return;
		}

		super.EvaluateCollision(action_item);
	}

	override void SetProjectionEntity(EntityAI projection)
	{
		super.SetProjectionEntity(projection);

		if (!m_Parent || !m_Projection)
			return;

		if (!m_Parent.IsInherited(SharpWoodenStick))
			return;

		if (!m_Projection.IsInherited(SharpWoodenStick))
			return;

		CopyStickAttachmentsToProjection(ItemBase.Cast(m_Parent), ItemBase.Cast(m_Projection));
	}

	protected void CopyStickAttachmentsToProjection(ItemBase src, ItemBase dst)
	{
		if (!src || !dst)
			return;

		for (int a = dst.GetInventory().AttachmentCount() - 1; a >= 0; a--)
		{
			EntityAI oldAtt = dst.GetInventory().GetAttachmentFromIndex(a);
			if (oldAtt)
				oldAtt.Delete();
		}

		for (int i = 0; i < src.GetInventory().AttachmentCount(); i++)
		{
			EntityAI srcAtt = src.GetInventory().GetAttachmentFromIndex(i);
			if (!srcAtt)
				continue;

			int slotId = srcAtt.GetInventory().GetSlotId(0);

			EntityAI newAtt;
			if (slotId > 0)
				newAtt = dst.GetInventory().CreateAttachmentEx(srcAtt.GetType(), slotId);
			else
				newAtt = dst.GetInventory().CreateAttachment(srcAtt.GetType());

			ItemBase srcIB = ItemBase.Cast(srcAtt);
			ItemBase dstIB = ItemBase.Cast(newAtt);
			if (srcIB && dstIB)
			{
				dstIB.SetHealth("", "", srcIB.GetHealth("", ""));
				if (dstIB.HasQuantity() && srcIB.HasQuantity())
					dstIB.SetQuantity(srcIB.GetQuantity());
			}
		}
	}
}