class CraftRuckChest extends RecipeBase
{	
	override void Init()
	{
		m_Name = "#craft " + "Storage Chest"; 
		m_IsInstaRecipe = false;
		m_AnimationLength = 2;
		m_Specialty = -0.02;
		
		m_MinDamageIngredient[0] = -1;
		m_MaxDamageIngredient[0] = 3;
		
		m_MinQuantityIngredient[0] = 8;
		m_MaxQuantityIngredient[0] = -1;
		
		m_MinDamageIngredient[1] = -1;
		m_MaxDamageIngredient[1] = 3;
		
		m_MinQuantityIngredient[1] = 16;
		m_MaxQuantityIngredient[1] = -1;
		
		
		InsertIngredient(0,"WoodenPlank");
		
		m_IngredientAddHealth[0] = 0;
		m_IngredientSetHealth[0] = -1;
		m_IngredientAddQuantity[0] = -10;
		m_IngredientDestroy[0] = false;
		m_IngredientUseSoftSkills[0] = false;
		
		InsertIngredient(1,"Nail");
		
		m_IngredientAddHealth[1] = 0;
		m_IngredientSetHealth[1] = -1; 
		m_IngredientAddQuantity[1] = -30;
		m_IngredientDestroy[1] = false;
		m_IngredientUseSoftSkills[1] = false;
		
		AddResult("RuckChest");

		m_ResultSetFullQuantity[0] = false;
		m_ResultSetQuantity[0] = -1;
		m_ResultSetHealth[0] = -1;
		m_ResultInheritsHealth[0] = 0;
		m_ResultInheritsColor[0] = -1;
		m_ResultToInventory[0] = -2;
		m_ResultUseSoftSkills[0] = false;
		m_ResultReplacesIngredient[0] = -1;
	}

	override bool CanDo(ItemBase ingredients[], PlayerBase player)
	{
		return true;
	}
};

