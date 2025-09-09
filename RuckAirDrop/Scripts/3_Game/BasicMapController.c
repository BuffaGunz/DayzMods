#ifdef BASICMAP
modded class BasicMapController{

	override void LoadClientMarkers(){
		super.LoadClientMarkers();
		
		BasicMap().RequestGroupUpdate("RuckServer");
		BasicMap().RequestGroupUpdate("RuckServerPlane");
	}
}
#endif