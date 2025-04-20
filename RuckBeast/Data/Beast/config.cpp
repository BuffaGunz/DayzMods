class CfgPatches
{
	class RuckBeast_Beast
	{
		units[]=
		{
			"Ruger1022",
			"Beast556"
		};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data",
			"DZ_Sounds_Weapons",
			"DZ_Weapons_Firearms",
			"DZ_Weapons_Firearms_Ruger1022"
		};
	};
};
class Mode_Safe;
class Mode_SemiAuto;
class Mode_Burst;
class Mode_FullAuto;
class OpticsInfoRifle;
class cfgWeapons
{
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
			dispersion=0.00075000001;
			magazineSlot="magazine";
		};
		hiddenSelectionsTextures[]=
		{
			"RuckBeast\Data\Beast\Beast556_co.paa"
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
				class SmokeCloud
				{
					overrideParticle="weapon_shot_winded_smoke";
				};
				class MuzzleFlash
				{
					overrideParticle="weapon_shot_fnx_02";
					ignoreIfSuppressed=1;
					illuminateWorld=1;
					positionOffset[]={0,0,0};
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
					onlyWithinOverheatLimits[]={0.40000001,1};
					positionOffset[]={0.1,0,0};
					onlyWithinRainLimits[]={0,0.2};
				};
				class OpenChamberSmoke
				{
					onlyIfBoltIsOpen=1;
					overrideParticle="smoking_barrel_small";
					overridePoint="Nabojnicestart";
				};
			};
		};
	};
};