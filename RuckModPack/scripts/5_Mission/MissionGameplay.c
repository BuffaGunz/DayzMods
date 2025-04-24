modded class MissionGameplay
{   
	
	int m_RuckBudzState = 0;

	autoptr RuckBudzWidget m_RuckBudzwidget = new RuckBudzWidget;
	
	override void OnUpdate(float timeslice)
	{        
		super.OnUpdate(timeslice); 
		
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
	
}