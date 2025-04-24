class MK_V : Pistol_Base
{
	override RecoilBase SpawnRecoilObject()
	{
		return new Colt1911Recoil(this);
	}
	
	//Debug menu Spawn Ground Special
	override void OnDebugSpawn()
	{
		GameInventory inventory = GetInventory();
		
		SpawnAttachedMagazine("Mag_Mk_V_15Rnd");
	}
};