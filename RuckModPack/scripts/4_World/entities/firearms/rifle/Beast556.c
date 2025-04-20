class Beast556_Base : RifleBoltFree_Base
{
	override RecoilBase SpawnRecoilObject()
	{
		return new ScoutRecoil(this);
	}
	
	override void OnDebugSpawn()
	{		
		GameInventory inventory = GetInventory();

		inventory.CreateInInventory( "HuntingOptic" );
		
		SpawnAttachedMagazine("Mag_CMAG_30Rnd");
	}	
};