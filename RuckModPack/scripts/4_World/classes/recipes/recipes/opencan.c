modded class OpenCan extends RecipeBase
{	
	override void Init()
	{
		m_Name = "#STR_OpenCan0";
		m_IsInstaRecipe = false;//should this recipe be performed instantly without animation
		m_AnimationLength = 1;//animation length in relative time units
		m_Specialty = 0.01;// value > 0 for roughness, value < 0 for precision
		
		m_AnywhereInInventory = false;//is this recipe valid even when neither of the items is in hands
		//conditions
		m_MinDamageIngredient[0] = -1;//-1 = disable check
		m_MaxDamageIngredient[0] = 3;//-1 = disable check
		
		m_MinQuantityIngredient[0] = -1;//-1 = disable check
		m_MaxQuantityIngredient[0] = -1;//-1 = disable check
		
		m_MinDamageIngredient[1] = -1;//-1 = disable check
		m_MaxDamageIngredient[1] = 3;//-1 = disable check
		
		m_MinQuantityIngredient[1] = -1;//-1 = disable check
		m_MaxQuantityIngredient[1] = -1;//-1 = disable check
		//----------------------------------------------------------------------------------------------------------------------
		
		//INGREDIENTS
		//ingredient 1
		InsertIngredientEx(0,"BakedBeansCan", "openBeanCan");//you can insert multiple ingredients this way
		InsertIngredientEx(0,"PeachesCan", "openBeanCan");//you can insert multiple ingredients this way
		InsertIngredientEx(0,"TacticalBaconCan", "openBeanCan");//you can insert multiple ingredients this way
		InsertIngredientEx(0,"SpaghettiCan", "openBeanCan");//you can insert multiple ingredients this way
		InsertIngredientEx(0,"SardinesCan", "openBeanCan");//you can insert multiple ingredients this way
		InsertIngredientEx(0,"UnknownFoodCan", "openBeanCan");//you can insert multiple ingredients this way
		
		m_IngredientAddHealth[0] = 0;// 0 = do nothing
		m_IngredientSetHealth[0] = -1; // -1 = do nothing
		m_IngredientAddQuantity[0] = 0;// 0 = do nothing
		m_IngredientDestroy[0] = false;//true = destroy, false = do nothing
		m_IngredientUseSoftSkills[0] = false;// set 'true' to allow modification of the values by softskills on this ingredient
		
		//ingredient 2
		InsertIngredient(1,"Sickle");//you can insert multiple ingredients this way
		InsertIngredient(1,"KukriKnife");
		InsertIngredient(1,"FangeKnife");
		InsertIngredient(1,"Hacksaw");
		InsertIngredient(1,"KitchenKnife");
		InsertIngredient(1,"SteakKnife");
		InsertIngredient(1,"StoneKnife");
		InsertIngredient(1,"CombatKnife");
		InsertIngredient(1,"HuntingKnife");
		InsertIngredient(1,"Machete");
		InsertIngredient(1,"CrudeMachete");
		InsertIngredient(1,"OrientalMachete");
		InsertIngredient(1,"AK_Bayonet");
		InsertIngredient(1,"M9A1_Bayonet");
		InsertIngredient(1,"Mosin_Bayonet");
		InsertIngredient(1,"SKS_Bayonet");
		InsertIngredient(1,"CanOpener");
		InsertIngredient(1,"FarmingHoe");
		InsertIngredient(1,"Shovel");
		InsertIngredient(1,"FieldShovel");
		InsertIngredient(1,"Crowbar");
		InsertIngredient(1,"Hammer");
		InsertIngredient(1,"Mace");
		InsertIngredient(1,"Wrench");
		InsertIngredient(1,"LugWrench");
		InsertIngredient(1,"Screwdriver");
		InsertIngredient(1,"SledgeHammer");
		InsertIngredient(1,"BaseballBat");
		InsertIngredient(1,"NailedBaseballBat");
		InsertIngredient(1,"BarbedBaseballBat");
		InsertIngredient(1,"PipeWrench");
		InsertIngredient(1,"Pickaxe");
		InsertIngredient(1,"WoodAxe");
		InsertIngredient(1,"FirefighterAxe");
		InsertIngredient(1,"Hatchet");
		InsertIngredient(1,"HandSaw");
		InsertIngredient(1,"Pliers");
		InsertIngredient(1,"Spear");
		InsertIngredient(1,"Pitchfork");
		InsertIngredient(1,"BoneKnife");
		InsertIngredient(1,"MeatTenderizer");
		InsertIngredient(1,"Cleaver");
		InsertIngredient(1,"Sword");
		InsertIngredient(1,"Iceaxe");
		InsertIngredient(1,"SurvivalShovel");
		
		m_IngredientAddHealth[1] = -0.5;// 0 = do nothing
		m_IngredientSetHealth[1] = -1; // -1 = do nothing
		m_IngredientAddQuantity[1] = 0;// 0 = do nothing
		m_IngredientDestroy[1] = false;// false = do nothing
		m_IngredientUseSoftSkills[1] = true;// set 'true' to allow modification of the values by softskills on this ingredient
		//----------------------------------------------------------------------------------------------------------------------
		
		//result1
		//AddResult("");//add results here

		m_ResultSetFullQuantity[0] = false;//true = set full quantity, false = do nothing
		m_ResultSetQuantity[0] = 0;//-1 = do nothing
		m_ResultSetHealth[0] = -1;//-1 = do nothing
		m_ResultInheritsHealth[0] = -1;// (value) == -1 means do nothing; a (value) >= 0 means this result will inherit health from ingredient number (value);(value) == -2 means this result will inherit health from all ingredients averaged(result_health = combined_health_of_ingredients / number_of_ingredients)
		m_ResultInheritsColor[0] = -1;// (value) == -1 means do nothing; a (value) >= 0 means this result classname will be a composite of the name provided in AddResult method and config value "color" of ingredient (value)
		m_ResultToInventory[0] = -2;//(value) == -2 spawn result on the ground;(value) == -1 place anywhere in the players inventory, (value) >= 0 means switch position with ingredient number(value)
		m_ResultUseSoftSkills[0] = false;// set 'true' to allow modification of the values by softskills on this result
		m_ResultReplacesIngredient[0] = -1;// value == -1 means do nothing; a value >= 0 means this result will transfer item propertiesvariables, attachments etc.. from an ingredient value
		
		//----------------------------------------------------------------------------------------------------------------------
	}

	override bool CanDo(ItemBase ingredients[], PlayerBase player)//final check for recipe's validity
	{
		return !ingredients[0].GetIsFrozen() && !player.IsPlacingLocal();
	}

	override void Do(ItemBase ingredients[], PlayerBase player,array<ItemBase> results, float specialty_weight)//gets called upon recipe's completion
	{
		ItemBase can = ingredients[0];
		ItemBase tool = ingredients[1];
		OpenItem.OpenAndSwitch(tool, can, player, specialty_weight);
	}
};
