class RuckChest : DeployableContainer_Base
{
    protected string GetLidAnimName() { return "lidclosing"; }
	
	protected bool m_IsOpen;  

    protected void UpdateVisualState()
    {
        if (IsOpen())
        {
            // open 
            SetAnimationPhase(GetLidAnimName(), 0.0);
        }
        else
        {
            // closed 
            SetAnimationPhase(GetLidAnimName(), 1.0);
        }
    }

    override void EEInit()
    {
        super.EEInit();
        UpdateVisualState();  
    }
	

    override void InitItemVariables()
    {
        super.InitItemVariables();
        RegisterNetSyncVariableBool("m_IsOpen");
    }

    bool IsOpen()
    {
        return m_IsOpen;
    }

    void Open()
    {
        if (!m_IsOpen)
        {
            m_IsOpen = true;
            SetSynchDirty();      
            SoundSynchRemote();    
        }
    }

    void Close()
    {
        if (m_IsOpen)
        {
            m_IsOpen = false;
            SetSynchDirty();
            SoundSynchRemote();
        }
    }

    override bool CanDisplayCargo()
    {
        return m_IsOpen;
    }
	
	protected bool IsCargoEmpty()
    {
        CargoBase cargo = GetInventory().GetCargo();
        if (!cargo) return true;
        return cargo.GetItemCount() == 0;
    }
	
	override bool CanPutIntoHands(EntityAI parent)
	{
		if (!super.CanPutIntoHands(parent))
			return false;

		if (!IsCargoEmpty())
			return false;

		return true;
	}

    override bool CanReceiveItemIntoCargo(EntityAI item) 
	{ 
		return true; 
	}
	
    override bool CanLoadItemIntoCargo(EntityAI item)
    {
		return true; 
	}
	
    override bool CanReleaseCargo(EntityAI cargo)
	{ 
		return true; 
	}

    override void InitItemSounds()
    {
        super.InitItemSounds();
        ItemSoundHandler h = GetItemSoundHandler();
        if (GetBarrelOpenSoundset()  != string.Empty) h.AddSound(SoundConstants.ITEM_BARREL_OPEN,  GetBarrelOpenSoundset());
        if (GetBarrelCloseSoundset() != string.Empty) h.AddSound(SoundConstants.ITEM_BARREL_CLOSE, GetBarrelCloseSoundset());
    }
	
	string GetBarrelOpenSoundset()
	{
		return "barrel_open_SoundSet"; 
	}
	
    string GetBarrelCloseSoundset()
	{
		return "barrel_close_SoundSet"; 
	}

    override void OnVariablesSynchronized()
    {
        super.OnVariablesSynchronized();
        UpdateVisualState();  
    }
	
	override void SetActions()
    {
        super.SetActions();
        AddAction(ActionOpenRuckChest);
        AddAction(ActionCloseRuckChest);
		AddAction(ActionTogglePlaceObject);
		AddAction(ActionPlaceObject);
    }
}
