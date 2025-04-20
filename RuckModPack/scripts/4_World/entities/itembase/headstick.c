modded class LongWoodenStick: Inventory_Base
{
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionClapBearTrapWithThisItem);
		AddAction(ActionBreakLongWoodenStick);
		AddAction(ActionAttachToConstruction);
		AddAction(ActionTogglePlaceObject);
		AddAction(ActionPlaceObject);
	}
}
modded class SharpWoodenStick: LongWoodenStick
{
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionClapBearTrapWithThisItem);
		AddAction(ActionCookOnStick);
		AddAction(ActionTogglePlaceObject);
		AddAction(ActionPlaceObject);
	}
}