class ActionOpenRuckChest: ActionInteractBase
{
    void ActionOpenRuckChest()
    {
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
        m_Text = "#open";
    }

    override void CreateConditionComponents()
    {
        m_ConditionItem   = new CCINone;
        m_ConditionTarget = new CCTObject(UAMaxDistances.DEFAULT);
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        RuckChest crate = RuckChest.Cast(target.GetObject());
        return crate && !crate.IsOpen();
    }

    override void OnExecuteServer(ActionData action_data)
    {
        RuckChest crate = RuckChest.Cast(action_data.m_Target.GetObject());
        if (!crate) return;

        crate.Open();
        if (crate.GetBarrelOpenSoundset() != string.Empty)
            crate.StartItemSoundServer(SoundConstants.ITEM_BARREL_OPEN);
    }

    override void OnExecuteClient(ActionData action_data)
    {
        RuckChest crate = RuckChest.Cast(action_data.m_Target.GetObject());
        if (crate) crate.Open();
    }
}

class ActionCloseRuckChest: ActionInteractBase
{
    void ActionCloseRuckChest()
    {
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
        m_Text = "#close";
    }

    override void CreateConditionComponents()
    {
        m_ConditionItem   = new CCINone;
        m_ConditionTarget = new CCTObject(UAMaxDistances.DEFAULT);
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {
        RuckChest crate = RuckChest.Cast(target.GetObject());
        return crate && crate.IsOpen();
    }

    override void OnExecuteServer(ActionData action_data)
    {
        RuckChest crate = RuckChest.Cast(action_data.m_Target.GetObject());
        if (!crate) return;

        crate.Close();
        if (crate.GetBarrelCloseSoundset() != string.Empty)
            crate.StartItemSoundServer(SoundConstants.ITEM_BARREL_CLOSE);
    }

    override void OnExecuteClient(ActionData action_data)
    {
        RuckChest crate = RuckChest.Cast(action_data.m_Target.GetObject());
        if (crate) crate.Close();
    }
}
