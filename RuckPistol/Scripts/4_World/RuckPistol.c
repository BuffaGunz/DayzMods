class RuckPistol : Pistol_Base
{
	override RecoilBase SpawnRecoilObject()
	{
		return new MakarovRecoil(this);
	}
	
	override void OnDebugSpawn()
	{
		GameInventory inventory = GetInventory();
		
		SpawnAttachedMagazine("Mag_RuckPistol_12Rnd");
	}
};