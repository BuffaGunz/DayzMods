class CfgPatches
{
	class RuckModPack_Beast
	{
		units[]=
		{
			"Ruger1022",
			"Beast556",
			"MK_V",
			"Colt1911",
			"1911_Engraved",
			"M85"
		};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data",
			"DZ_Sounds_Weapons",
			"DZ_Weapons_Firearms",
			"DZ_Weapons_Firearms_Ruger1022",
			"DZ_Pistols_1911",
			"DZ_Weapons_Magazines",
			"DZ_Weapons_Firearms_Winchester70"
		};
	};
};
class Mode_Safe;
class Mode_Single;
class Mode_SemiAuto;
class Mode_Burst;
class Mode_FullAuto;
class OpticsInfoRifle;
class OpticsInfoPistol;
class cfgWeapons
{
	class Winchester70_Base;
	class M85: Winchester70_Base
	{
		scope=2;
		displayName="Zastava M85 Rifle";
		descriptionShort="Reliable sporting rifle with a 5 round internal magazine chambered in 7.62x39";
		model="\dz\weapons\firearms\winchester70\winchester70.p3d";
		attachments[]=
		{
			"weaponWrap",
			"weaponOpticsHunting",
			"suppressorImpro"
		};
		itemSize[]={10,3};
		chamberSize=5;
		chamberedRound="";
		chamberableFrom[]=
		{
			"Ammo_762x39",
			"Ammo_762x39Tracer"
		};
		weight=2721;
		absorbency=0;
		repairableWithKits[]={1};
		repairCosts[]={25};
		PPDOFProperties[]={1,0.5,20,170,4,10};
		WeaponLength=1.15;
		barrelArmor=3.125;
		winchesterTypeOpticsMount=1;
		initSpeedMultiplier=1.15;
		magazines[]={};
		DisplayMagazine=0;
		ejectType=0;
		recoilModifier[]={1,1,1};
		swayModifier[]={2.2,2.2,1.2};
		simpleHiddenSelections[]=
		{
			"hide_barrel"
		};
		hiddenSelections[]=
		{
			"camo"
		};
		class NoiseShoot
		{
			strength=100;
			type="shot";
		};
		modes[]=
		{
			"Single"
		};
		class Single: Mode_Single
		{
			soundSetShot[]=
			{
				"SKS_Shot_SoundSet",
				"SKS_Tail_SoundSet",
				"SKS_InteriorTail_SoundSet"
			};
			soundSetShotExt[]=
			{
				
				{
					"SKS_silencerHomeMade_SoundSet",
					"SKS_silencerHomeMadeTail_SoundSet",
					"SKS_silencerInteriorHomeMadeTail_SoundSet"
				}
			};
			reloadTime=1;
			recoil="recoil_Winchester";
			recoilProne="recoil_Winchester_prone";
			dispersion=0.00050000002;
			magazineSlot="magazine";
		};
		class OpticsInfo: OpticsInfoRifle
		{
			discreteDistance[]={200};
			discreteDistanceInitIndex=0;
			distanceZoomMin=200;
			distanceZoomMax=200;
		};
		class InventorySlotsOffsets
		{
			class Shoulder
			{
				position[]={0,-0.02,-0.029999999};
				orientation[]={0,-30,0};
			};
			class Melee
			{
				position[]={0,-0.02,0.0099999998};
				orientation[]={0,30,0};
			};
		};
		weaponStateAnim="dz\anims\anm\player\reloads\cz527\w_cz527_states.anm";
		hiddenSelectionsTextures[]=
		{
			"dz\weapons\firearms\winchester70\data\winchester70_CO.paa"
		};
		hiddenSelectionsMaterials[]=
		{
			"dz\weapons\firearms\winchester70\data\winchester70.rvmat"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=200;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\weapons\firearms\winchester70\data\winchester70.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\weapons\firearms\winchester70\data\winchester70.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\weapons\firearms\winchester70\data\winchester70_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\weapons\firearms\winchester70\data\winchester70_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\weapons\firearms\winchester70\data\winchester70_destruct.rvmat"
							}
						}
					};
				};
			};
		};
		class Particles
		{
			class OnFire
			{
				class SmokeCloud
				{
					overrideParticle="weapon_shot_winded_smoke";
				};
				class MuzzleFlash
				{
					overrideParticle="weapon_shot_mosin9130_01";
					ignoreIfSuppressed=1;
					illuminateWorld=1;
					positionOffset[]={0.1,0,0};
				};
			};
			class OnOverheating
			{
				maxOverheatingValue=1;
				shotsToStartOverheating=1;
				overheatingDecayInterval=0.5;
				class SmokingBarrel1
				{
					overrideParticle="smoking_barrel_small";
					onlyWithinOverheatLimits[]={0.1,1};
					positionOffset[]={0,0,0};
					onlyWithinRainLimits[]={0,0.2};
				};
				class OpenChamberSmoke
				{
					onlyIfBoltIsOpen=1;
					overrideParticle="smoking_barrel_small";
					overridePoint="Nabojnicestart";
				};
			};
			class OnBulletCasingEject
			{
				class ChamberSmokeRaise
				{
					overrideParticle="weapon_shot_chamber_smoke";
					overridePoint="Nabojnicestart";
				};
			};
		};
	};
	class Rifle_Base;
	class Ruger1022_Base: Rifle_Base
	{
	};
	class Beast556: Ruger1022_Base
	{
		scope=2;
		displayName="Beast556";
		descriptionShort="SemiAuto Hunting Rifle Chambered In 556x45";
		model="\dz\weapons\firearms\Ruger1022\Ruger1022.p3d";
		itemSize[]={9,3};
		chamberableFrom[]=
		{
			"Ammo_556x45",
			"Ammo_556x45Tracer"
		};
		magazines[]=
		{
			"Mag_STANAG_30Rnd",
			"Mag_STANAGCoupled_30Rnd",
			"Mag_STANAG_60Rnd",
			"Mag_CMAG_10Rnd",
			"Mag_CMAG_20Rnd",
			"Mag_CMAG_30Rnd",
			"Mag_CMAG_40Rnd",
			"Mag_CMAG_10Rnd_Green",
			"Mag_CMAG_20Rnd_Green",
			"Mag_CMAG_30Rnd_Green",
			"Mag_CMAG_40Rnd_Green",
			"Mag_CMAG_10Rnd_Black",
			"Mag_CMAG_20Rnd_Black",
			"Mag_CMAG_30Rnd_Black",
			"Mag_CMAG_40Rnd_Black"
		};
		attachments[]=
		{
			"weaponWrap",
			"weaponOpticsHunting",
			"suppressorImpro"
		};
		class NoiseShoot
		{
			strength=100;
			type="shot";
		};
		modes[]=
		{
			"SemiAuto"
		};
		class SemiAuto: Mode_SemiAuto
		{
			soundSetShot[]=
			{
				"SCOUT_Shot_SoundSet",
				"SCOUT_Tail_SoundSet",
				"SCOUT_InteriorTail_SoundSet"
			};
			soundSetShotExt[]=
			{
				
				{
					"SCOUT_silencer_SoundSet",
					"SCOUT_silencerTail_SoundSet",
					"SCOUT_silencerInteriorTail_SoundSet"
				},
				
				{
					"SCOUT_silencerHomeMade_SoundSet",
					"SCOUT_silencerHomeMadeTail_SoundSet",
					"SCOUT_silencerInteriorTail_SoundSet"
				}
			};
			envShootingDecrease=0.050000001;
			envShootingDecreaseExt[]={0.050000001,0.050000001};
			reloadTime=0.1;
			recoil="recoil_scout";
			dispersion=0.00075000001;
			magazineSlot="magazine";
		};
		hiddenSelectionsTextures[]=
		{
			"RuckModPack\Data\Beast\Beast556_co.paa"
		};
		hiddenSelectionsMaterials[]=
		{
			"dz\weapons\firearms\Ruger1022\data\ruger1022.rvmat"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=200;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\weapons\firearms\Ruger1022\data\ruger1022.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\weapons\firearms\Ruger1022\data\ruger1022.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\weapons\firearms\Ruger1022\data\ruger1022_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\weapons\firearms\Ruger1022\data\ruger1022_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\weapons\firearms\Ruger1022\data\ruger1022_destruct.rvmat"
							}
						}
					};
				};
			};
		};
		class Particles
		{
			class OnFire
			{
				class MuzzleFlash
				{
					overrideParticle="weapon_shot_mosin9130_01";
					ignoreIfSuppressed=1;
					illuminateWorld=1;
					positionOffset[]={-0.050000001,0,0};
				};
			};
			class OnOverheating
			{
				maxOverheatingValue=1;
				shotsToStartOverheating=1;
				overheatingDecayInterval=0.5;
				class SmokingBarrel1
				{
					overrideParticle="smoking_barrel_small";
					onlyWithinOverheatLimits[]={0.1,1};
					positionOffset[]={0,0,0};
					onlyWithinRainLimits[]={0,0.2};
				};
				class OpenChamberSmoke
				{
					onlyIfBoltIsOpen=1;
					overrideParticle="smoking_barrel_small";
					overridePoint="Nabojnicestart";
				};
			};
			class OnBulletCasingEject
			{
				class ChamberSmokeRaise
				{
					overrideParticle="weapon_shot_chamber_smoke";
					overridePoint="Nabojnicestart";
				};
			};
		};
		weaponStateAnim="dz\anims\anm\player\reloads\Ruger1022\w_Ruger1022_states.anm";
	};
	class OpticsInfoPistol;
	class Pistol_Base;
	class Colt1911_Base: Pistol_Base
	{
	};	
	class MK_V: Colt1911_Base
	{
		scope=2;
		displayName="MK V";
		descriptionShort="Integrally suppressed pistol chambered in 45ACP";
		model="\RuckModPack\Data\Beast\data\Mk_V.p3d";
		attachments[]={};
		weight=1106;
		absorbency=0;
		repairableWithKits[]={1};
		repairCosts[]={25};
		PPDOFProperties[]={1,0.89999998,10,250,4,10};
		WeaponLength=0.33000001;
		ShoulderDistance=0.40000001;
		barrelArmor=1.523;
		initSpeedMultiplier=1;
		chamberSize=1;
		chamberedRound="";
		magazines[]=
		{
			"Mag_1911_7Rnd",
			"Mag_Mk_V_15Rnd"
		};
		chamberableFrom[]=
		{
			"Ammo_45ACP"
		};
		magazineSwitchTime=0.23999999;
		ejectType=1;
		recoilModifier[]={1,1,1};
		swayModifier[]={1.3,1.3,0.80000001};
		hiddenSelections[]=
		{
			"camoGround"
		};
		class NoiseShoot
		{
			strength=40;
			type="shot";
		};
		modes[]=
		{
			"SemiAuto"
		};
		class SemiAuto: Mode_SemiAuto
		{
			soundSetShot[]=
			{
				"Colt1911_silencerPro_SoundSet",
				"Colt1911_silencerTail_SoundSet",
				"Colt1911_silencerInteriorTail_SoundSet"
			};
			soundSetShotExt[]=
			{
				
				{
					"Colt1911_silencerPro_SoundSet",
					"Colt1911_silencerTail_SoundSet",
					"Colt1911_silencerInteriorTail_SoundSet"
				}
			};
			envShootingDecrease=0.050000001;
			envShootingDecreaseExt[]={0.050000001,0.050000001};
			reloadTime=0.13;
			recoil="recoil_1911";
			recoilProne="recoil_1911_prone";
			dispersion=0.0060000001;
			magazineSlot="magazine";
		};
		class OpticsInfo: OpticsInfoPistol
		{
			memoryPointCamera="eye";
			discreteDistance[]={25};
			discreteDistanceInitIndex=0;
			modelOptics="-";
			distanceZoomMin=100;
			distanceZoomMax=100;
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=200;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\weapons\pistols\1911\data\1911.rvmat",
								"DZ\weapons\attachments\muzzle\data\suppressor_pb6p9.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\weapons\pistols\1911\data\1911.rvmat",
								"DZ\weapons\attachments\muzzle\data\suppressor_pb6p9.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\weapons\pistols\1911\data\1911_damage.rvmat",
								"DZ\weapons\attachments\muzzle\data\suppressor_pb6p9_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\weapons\pistols\1911\data\1911_damage.rvmat",
								"DZ\weapons\attachments\muzzle\data\suppressor_pb6p9_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\weapons\pistols\1911\data\1911_destruct.rvmat",
								"DZ\weapons\attachments\muzzle\data\suppressor_pb6p9_destruct.rvmat"
							}
						}
					};
				};
			};
		};
		class Particles
		{
			class OnFire
			{
				class SmokeCloud
				{
					overrideParticle="weapon_shot_winded_smoke";
				};
				class MuzzleFlash
				{
					overrideParticle="weapon_shot_akm_02";
					onlyWithinHealthLabel[]={0,3};
				};
			};
			class OnOverheating
			{
				maxOverheatingValue=8;
				shotsToStartOverheating=8;
				overheatingDecayInterval=1;
				class SmokingBarrel1
				{
					overrideParticle="smoking_barrel_small";
					onlyWithinOverheatLimits[]={0,1};
					positionOffset[]={0,0,0};
					onlyWithinRainLimits[]={0,1};
				};
				class OpenChamberSmoke
				{
					onlyIfBoltIsOpen=1;
					overrideParticle="smoking_barrel_small";
					overridePoint="Nabojnicestart";
				};
			};
			class OnBulletCasingEject
			{
				class ChamberSmokeRaise
				{
					overrideParticle="weapon_shot_chamber_smoke";
					overridePoint="Nabojnicestart";
				};
			};
		};
		weaponStateAnim="dz\anims\anm\player\reloads\1911\w_1911_states.anm";
	};
};

class CfgMagazines
{	
	class Mag_1911_7Rnd;
    class Mag_Mk_V_15Rnd: Mag_1911_7Rnd
	{
		scope=2;
		displayName="Mag_Mk_V_15Rnd";
		descriptionShort="Holds upto 15Rnd of 45acp";
		model="\RuckModPack\Data\Beast\data\Mk_V_Mag_15Rnd.p3d";
		weight=68;
		weightPerQuantityUnit=12;
		itemSize[]={1,2};
		count=15;
		ammo="Bullet_45ACP";
		ammoItems[]=
		{
			"Ammo_45ACP"
		};
		tracersEvery=0;
		mass=10;
		hiddenSelections[]=
		{
			"camo"
		};
		hiddenSelectionsTextures[]=
		{
			"dz\weapons\attachments\data\1911_mag_co.paa"
		};
		hiddenSelectionsMaterials[]=
		{
			"dz\weapons\attachments\data\1911.rvmat"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=100;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\weapons\attachments\data\1911.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\weapons\attachments\data\1911.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\weapons\attachments\data\1911_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\weapons\attachments\data\1911_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\weapons\attachments\data\1911_destruct.rvmat"
							}
						}
					};
				};
			};
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class MagRifle_fill_in
				{
					soundSet="MagRifle_fill_in_SoundSet";
					id=1;
				};
				class MagRifle_fill_loop
				{
					soundSet="MagRifle_fill_loop_SoundSet";
					id=2;
				};
				class MagRifle_fill_out
				{
					soundSet="MagRifle_fill_out_SoundSet";
					id=3;
				};
				class MagRifle_empty_in
				{
					soundSet="MagRifle_empty_in_SoundSet";
					id=4;
				};
				class MagRifle_empty_loop
				{
					soundSet="MagRifle_empty_loop_SoundSet";
					id=5;
				};
				class MagRifle_empty_out
				{
					soundSet="MagRifle_empty_out_SoundSet";
					id=6;
				};
				class MagPistol_fill_in
				{
					soundSet="MagPistol_fill_in_SoundSet";
					id=7;
				};
				class MagPistol_fill_loop
				{
					soundSet="MagPistol_fill_loop_SoundSet";
					id=8;
				};
				class MagPistol_fill_out
				{
					soundSet="MagPistol_fill_out_SoundSet";
					id=9;
				};
				class MagPistol_empty_in
				{
					soundSet="MagPistol_empty_in_SoundSet";
					id=10;
				};
				class MagPistol_empty_loop
				{
					soundSet="MagPistol_empty_loop_SoundSet";
					id=11;
				};
				class MagPistol_empty_out
				{
					soundSet="MagPistol_empty_out_SoundSet";
					id=12;
				};
			};
		};
	};
};

class CfgNonAIVehicles
{
	class ProxyAttachment;
	class ProxyMk_V: ProxyAttachment
	{
		scope=2;
		inventorySlot="pistol";
		model="\RuckModPack\Data\Beast\data\Stealth.p3d";
	};
};
