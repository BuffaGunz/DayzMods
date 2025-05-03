modded class MissionGameplay
{   
	 ref array<string> m_RuckAutorunInterruptInputs;
	 
	 int m_RuckBudzState = 0;

	autoptr RuckBudzWidget m_RuckBudzwidget = new RuckBudzWidget;

    override void OnInit()
    {
        super.OnInit();
        m_RuckAutorunInterruptInputs = new array<string>;
        m_RuckAutorunInterruptInputs.Insert("UARuckAutorunToggle");
        m_RuckAutorunInterruptInputs.Insert("UAMoveForward");
        m_RuckAutorunInterruptInputs.Insert("UAMoveBack");
        m_RuckAutorunInterruptInputs.Insert("UAMoveLeft");
        m_RuckAutorunInterruptInputs.Insert("UAMoveRight");
        m_RuckAutorunInterruptInputs.Insert("UAFire");
        m_RuckAutorunInterruptInputs.Insert("UATempRaiseWeapon");
        m_RuckAutorunInterruptInputs.Insert("UALeanLeft");
        m_RuckAutorunInterruptInputs.Insert("UALeanRight");
    }

    protected bool RuckCheckInput(string inputName)
    {
        if(GetUApi())
		{
            UAInput inp = GetUApi().GetInputByName(inputName);

            if(inp && inp.LocalPress())
            {
                return true;
            }
        }
        return false;
    }

    protected bool RuckAutorunShouldInterrupt(PlayerBase player)
    {
        if(!player.RuckIsAutorunning())
        {
            return false;
        }

        // Check player status
        if(player.IsInVehicle() || player.IsUnconscious() || player.IsRestrained() || !player.IsAlive())
        {
            return true;
        }

        // Check inputs
        for(int i=0; i<m_RuckAutorunInterruptInputs.Count(); i++)
        {
            string inputName = m_RuckAutorunInterruptInputs[i];
            
            if(RuckCheckInput(inputName))
            {
                return true;
            }
        }
        return false;
    }

    protected bool RuckAutorunShouldStart(PlayerBase player)
    {
        if(player.RuckIsAutorunning())
        {
            return false;
        }

        string autorunStartInput = m_RuckAutorunInterruptInputs[0];
        if(RuckCheckInput(autorunStartInput) && !player.RuckIsAutorunning() && !IsControlDisabled())
        {
            return true;
        }
        return false;
    }

    protected int RuckAutorunGetUpdatedSpeed(PlayerBase player)
    {
        if(player && (!player.CanSprint() || player.GetStaminaHandler().GetStamina() <= 0))
        {
            return DayZPlayerConstants.MOVEMENTIDX_RUN;
        }
        if(RuckCheckInput("UAWalkRunToggle"))
        {
            return DayZPlayerConstants.MOVEMENTIDX_WALK;
        }
        else if(RuckCheckInput("UAWalkRunTemp"))
        {
            return DayZPlayerConstants.MOVEMENTIDX_RUN;
        }
        else if(RuckCheckInput("UATurbo"))
        {
            return DayZPlayerConstants.MOVEMENTIDX_SPRINT;
        }
        else
        {
            // Used to indicate that there is to be no update to the speed
            return DayZPlayerConstants.MOVEMENTIDX_IDLE;
        }
    }

    protected void RuckAutorunStart()
    {
        RuckAutorunSync(true, DayZPlayerConstants.MOVEMENTIDX_SPRINT, 1);
    }

    protected void RuckAutorunStop()
    {
        RuckAutorunSync(false, DayZPlayerConstants.MOVEMENTIDX_IDLE, 0);
    }

    override void OnUpdate(float timeslice)
    {
        super.OnUpdate(timeslice);

        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());

        if (player)
        {
            if(RuckAutorunShouldInterrupt(player))
            {
                RuckAutorunStop();
            }
            else if(RuckAutorunShouldStart(player))
            {
                RuckAutorunStart();
            }
            else if(player.RuckIsAutorunning())
            {
                int speed = RuckAutorunGetUpdatedSpeed(player);
                if(speed != DayZPlayerConstants.MOVEMENTIDX_IDLE)
                {
                    RuckAutorunSync(true, speed, 1);
                }
            }
        }
		
		if ( GetGame().GetInput().LocalPress("UARuckBudzToggle") && GetGame().GetUIManager().GetMenu() == NULL ) 
		{
			
			if (m_RuckBudzState == 0) {  
				
				m_RuckBudzState++;
				
				GetGame().GetSoundScene().SetSoundVolume(0.45,1);	
			
				m_RuckBudzwidget.SetIcon("RuckModPack\\Data\\RuckBudz\\data\\volume_mid.edds");
				
			} else if (m_RuckBudzState == 1) {
				
				m_RuckBudzState++;
				
				GetGame().GetSoundScene().SetSoundVolume(0.08,1);	
			
				m_RuckBudzwidget.SetIcon("RuckModPack\\Data\\RuckBudz\\data\\volume_low.edds");
				
			} else if (m_RuckBudzState == 2) {  
				
				m_RuckBudzState++;
				
				GetGame().GetSoundScene().SetSoundVolume(0,1);	
			
				m_RuckBudzwidget.SetIcon("RuckModPack\\Data\\RuckBudz\\data\\volume_off.edds");
				
			}  else if (m_RuckBudzState >= 3) {
			    
				m_RuckBudzState = 0;
				
				GetGame().GetSoundScene().SetSoundVolume(1,1);
				
				m_RuckBudzwidget.SetIcon("RuckModPack\\Data\\RuckBudz\\data\\volume_full.edds");
				
			}
			
		}
    }

    protected void RuckAutorunSync(bool isRunning, int movementIdx, int angle)
    {
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());

        player.SetRuckAutorunning(isRunning);
        player.GetInputController().OverrideMovementSpeed(isRunning, movementIdx);
        player.GetInputController().OverrideMovementAngle(isRunning, angle);

        auto params = new Param3<bool, int, int>(isRunning, movementIdx, angle);
        GetGame().RPCSingleParam(player, -44201, params, true);
    }
	
}