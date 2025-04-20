class CfgPatches
{
	class RuckM16_556
	{
		units[]=
		{
			"M4A1",
			"M16A2",
			"M4A1_Green",
			"M4A1_Black",
			"ShotgunIzh43",
			"ShotgunIzh43_Sawedoff",
			"CZ75",
			"FNX45",
			"Glock19"
		};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data",
			"DZ_Weapons_Firearms",
			"DZ_Weapons_Firearms_M16A2",
			"DZ_Weapons_Firearms_M4",
			"DZ_Weapons_Firearms_IZH18",
			"DZ_Pistols",
			"DZ_Pistols_CZ75",
			"DZ_Pistols_FNX45",
			"DZ_Pistols_Glock"
		};
	};
};
class Mode_Safe;
class Mode_Single;
class Mode_SemiAuto;
class Mode_Burst;
class Mode_FullAuto;
class OpticsInfoRifle;
class cfgWeapons
{
	class Rifle_Base;
	class M16A2_Base: Rifle_Base
	{
		ironsightsExcludingOptics[]=
		{
			"M4_CarryHandleOptic",
			"BUISOptic",
			"M68Optic",
			"M4_T3NRDSOptic",
			"ReflexOptic",
			"ACOGOptic"
		};
		modes[]=
		{
			"SemiAuto",
			"Burst",
			"FullAuto"
		};
	    class FullAuto: Mode_FullAuto
		{
			soundSetShot[]=
			{
				"M16_Shot_SoundSet",
				"M16_Tail_SoundSet",
				"M16_InteriorTail_SoundSet"
			};
			soundSetShotExt[]=
			{
				
				{
					"M16_silencer_SoundSet",
					"M16_silencerTail_SoundSet",
					"M16_silencerInteriorTail_SoundSet"
				},
				
				{
					"M16_silencerHomeMade_SoundSet",
					"M16_silencerHomeMadeTail_SoundSet",
					"M16_silencerInteriorHomeMadeTail_SoundSet"
				}
			};
			reloadTime=0.064999998;
			recoil="recoil_m4";
			recoilProne="recoil_m4_prone";
			dispersion=0.0020000001;
			magazineSlot="magazine";
		};
		class SemiAuto: Mode_SemiAuto
		{
			soundSetShot[]=
			{
				"M16_Shot_SoundSet",
				"M16_Tail_SoundSet",
				"M16_InteriorTail_SoundSet"
			};
			soundSetShotExt[]=
			{
				
				{
					"M16_silencer_SoundSet",
					"M16_silencerTail_SoundSet",
					"M16_silencerInteriorTail_SoundSet"
				},
				
				{
					"M16_silencerHomeMade_SoundSet",
					"M16_silencerHomeMadeTail_SoundSet",
					"M16_silencerInteriorHomeMadeTail_SoundSet"
				}
			};
			reloadTime=0.12;
			dispersion=0.0020000001;
			magazineSlot="magazine";
		};
		class Burst: Mode_Burst
		{
			soundSetShot[]=
			{
				"M16_Shot_SoundSet",
				"M16_Tail_SoundSet",
				"M16_InteriorTail_SoundSet"
			};
			soundSetShotExt[]=
			{
				
				{
					"M16_silencer_SoundSet",
					"M16_silencerTail_SoundSet",
					"M16_silencerInteriorTail_SoundSet"
				},
				
				{
					"M16_silencerHomeMade_SoundSet",
					"M16_silencerHomeMadeTail_SoundSet",
					"M16_silencerInteriorHomeMadeTail_SoundSet"
				}
			};
			burst=3;
			reloadTime=0.064999998;
			dispersion=0.0020000001;
			magazineSlot="magazine";
		};
		class OpticsInfo: OpticsInfoRifle
		{
			memoryPointCamera="eye";
			discreteDistance[]={25};
			discreteDistanceInitIndex=0;
			modelOptics="-";
			distanceZoomMin=25;
			distanceZoomMax=25;
		};
		weaponStateAnim="dz\anims\anm\player\reloads\M4A1\w_M4A1_states.anm";
	};	
	class M16A2: M16A2_Base
	{
		attachments[]=
		{
			"weaponWrap",
			"weaponMuzzleM4",
			"weaponOptics",
			"weaponBayonet"
		};
	};
	class M4A1_Base: Rifle_Base
	{
		modes[]=
		{
			"SemiAuto",
			"Burst",
			"FullAuto"
		};
		class SemiAuto: Mode_SemiAuto
		{
			soundSetShot[]=
			{
				"M4_Shot_SoundSet",
				"M4_Tail_SoundSet",
				"M4_InteriorTail_SoundSet"
			};
			soundSetShotExt[]=
			{
				
				{
					"M4_silencer_SoundSet",
					"M4_silencerTail_SoundSet",
					"M4_silencerInteriorTail_SoundSet"
				},
				
				{
					"M4_silencerHomeMade_SoundSet",
					"M4_silencerHomeMadeTail_SoundSet",
					"M4_silencerInteriorHomeMadeTail_SoundSet"
				}
			};
			reloadTime=0.12;
			recoil="recoil_m4";
			recoilProne="recoil_m4_prone";
			dispersion=0.0020000001;
			magazineSlot="magazine";
		};
		class FullAuto: Mode_FullAuto
		{
			soundSetShot[]=
			{
				"M4_Shot_SoundSet",
				"M4_Tail_SoundSet",
				"M4_InteriorTail_SoundSet"
			};
			soundSetShotExt[]=
			{
				
				{
					"M4_silencer_SoundSet",
					"M4_silencerTail_SoundSet",
					"M4_silencerInteriorTail_SoundSet"
				},
				
				{
					"M4_silencerHomeMade_SoundSet",
					"M4_silencerHomeMadeTail_SoundSet",
					"M4_silencerInteriorHomeMadeTail_SoundSet"
				}
			};
			reloadTime=0.064999998;
			recoil="recoil_m4";
			recoilProne="recoil_m4_prone";
			dispersion=0.0020000001;
			magazineSlot="magazine";
		};
		class Burst: Mode_Burst
		{
			soundSetShot[]=
			{
				"M4_Shot_SoundSet",
				"M4_Tail_SoundSet",
				"M4_InteriorTail_SoundSet"
			};
			soundSetShotExt[]=
			{
				
				{
					"M4_silencer_SoundSet",
					"M4_silencerTail_SoundSet",
					"M4_silencerInteriorTail_SoundSet"
				},
				
				{
					"M4_silencerHomeMade_SoundSet",
					"M4_silencerHomeMadeTail_SoundSet",
					"M4_silencerInteriorHomeMadeTail_SoundSet"
				}
			};
			burst=3;
			reloadTime=0.064999998;
			dispersion=0.0020000001;
			magazineSlot="magazine";
		};
	};
	class M4A1: M4A1_Base
	{
	};
	class M4A1_Green: M4A1
	{
	};
	class M4A1_Black: M4A1
	{
	};	
	class Izh18_Base: Rifle_Base
	{
	};	
	class Izh18: Izh18_Base
	{
		attachments[]=
		{
			"weaponWrap",
			"weaponOpticsHunting",
			"suppressorImpro"
		};
	};
	class SawedoffIzh18: Izh18
	{
	};
	class Pistol_Base;
	class CZ75_Base: Pistol_Base
	{
		modes[]=
		{
			"SemiAuto",
			"Burst",
			"FullAuto"
		};
		class SemiAuto: Mode_SemiAuto
		{
			soundSetShot[]=
			{
				"CZ75_Shot_SoundSet",
				"CZ75_Tail_SoundSet",
				"CZ75_InteriorTail_SoundSet"
			};
			soundSetShotExt[]=
			{
				
				{
					"CZ75_silencerPro_SoundSet",
					"CZ75_silencerTail_SoundSet",
					"CZ75_silencerInteriorTail_SoundSet"
				}
			};
			reloadTime=0.13;
			recoil="recoil_cz75";
			recoilProne="recoil_cz75_prone";
			dispersion=0.0044999998;
			magazineSlot="magazine";
		};
		class FullAuto: Mode_FullAuto
		{
			soundSetShot[]=
			{
				"CZ75_Shot_SoundSet",
				"CZ75_Tail_SoundSet",
				"CZ75_InteriorTail_SoundSet"
			};
			soundSetShotExt[]=
			{
				
				{
					"CZ75_silencerPro_SoundSet",
					"CZ75_silencerTail_SoundSet",
					"CZ75_silencerInteriorTail_SoundSet"
				}
			};
			reloadTime=0.064999998;
			recoil="recoil_m4";
			recoilProne="recoil_m4_prone";
			dispersion=0.0020000001;
			magazineSlot="magazine";
		};
		class Burst: Mode_Burst
		{
			soundSetShot[]=
			{
				"CZ75_Shot_SoundSet",
				"CZ75_Tail_SoundSet",
				"CZ75_InteriorTail_SoundSet"
			};
			soundSetShotExt[]=
			{
				
				{
					"CZ75_silencerPro_SoundSet",
					"CZ75_silencerTail_SoundSet",
					"CZ75_silencerInteriorTail_SoundSet"
				}
			};
			burst=3;
			reloadTime=0.064999998;
			dispersion=0.0020000001;
			magazineSlot="magazine";
		};
	};
	class CZ75: CZ75_Base
	{
	};
	class FNX45_Base: Pistol_Base
	{
		modes[]=
		{
			"SemiAuto",
			"Burst",
			"FullAuto"
		};
		class SemiAuto: Mode_SemiAuto
		{
			soundSetShot[]=
			{
				"FNX45_Shot_SoundSet",
				"FNX45_Tail_SoundSet",
				"FNX45_InteriorTail_SoundSet"
			};
			soundSetShotExt[]=
			{
				
				{
					"FNX45_silencerPro_SoundSet",
					"FNX45_silencerTail_SoundSet",
					"FNX45_silencerInteriorTail_SoundSet"
				}
			};
			reloadTime=0.13;
			recoil="recoil_fnx";
			recoilProne="recoil_fnx_prone";
			dispersion=0.003;
			magazineSlot="magazine";
		};
		class FullAuto: Mode_FullAuto
		{
			soundSetShot[]=
			{
				"FNX45_Shot_SoundSet",
				"FNX45_Tail_SoundSet",
				"FNX45_InteriorTail_SoundSet"
			};
			soundSetShotExt[]=
			{
				
				{
					"FNX45_silencerPro_SoundSet",
					"FNX45_silencerTail_SoundSet",
					"FNX45_silencerInteriorTail_SoundSet"
				}
			};
			reloadTime=0.064999998;
			recoil="recoil_m4";
			recoilProne="recoil_m4_prone";
			dispersion=0.0020000001;
			magazineSlot="magazine";
		};
		class Burst: Mode_Burst
		{
			soundSetShot[]=
			{
				"FNX45_Shot_SoundSet",
				"FNX45_Tail_SoundSet",
				"FNX45_InteriorTail_SoundSet"
			};
			soundSetShotExt[]=
			{
				
				{
					"FNX45_silencerPro_SoundSet",
					"FNX45_silencerTail_SoundSet",
					"FNX45_silencerInteriorTail_SoundSet"
				}
			};
			burst=3;
			reloadTime=0.064999998;
			dispersion=0.0020000001;
			magazineSlot="magazine";
		};
	};
	class FNX45: FNX45_Base
	{
	};
	class FNX45_arrow: FNX45
	{
	};
	class Glock19_Base: Pistol_Base
	{
		modes[]=
		{
			"SemiAuto",
			"Burst",
			"FullAuto"
		};
		class SemiAuto: Mode_SemiAuto
		{
			soundSetShot[]=
			{
				"Glock19_Shot_SoundSet",
				"Glock19_Tail_SoundSet",
				"Glock19_InteriorTail_SoundSet"
			};
			soundSetShotExt[]=
			{
				
				{
					"Glock19_silencerPro_SoundSet",
					"Glock19_silencerTail_SoundSet",
					"Glock19_silencerInteriorTail_SoundSet"
				}
			};
			reloadTime=0.13;
			recoil="recoil_Glock";
			recoilProne="recoil_Glock_prone";
			dispersion=0.003;
			magazineSlot="magazine";
		};
		class FullAuto: Mode_FullAuto
		{
			soundSetShot[]=
			{
				"Glock19_Shot_SoundSet",
				"Glock19_Tail_SoundSet",
				"Glock19_InteriorTail_SoundSet"
			};
			soundSetShotExt[]=
			{
				
				{
					"Glock19_silencerPro_SoundSet",
					"Glock19_silencerTail_SoundSet",
					"Glock19_silencerInteriorTail_SoundSet"
				}
			};
			reloadTime=0.064999998;
			recoil="recoil_m4";
			recoilProne="recoil_m4_prone";
			dispersion=0.0020000001;
			magazineSlot="magazine";
		};
		class Burst: Mode_Burst
		{
			soundSetShot[]=
			{
				"Glock19_Shot_SoundSet",
				"Glock19_Tail_SoundSet",
				"Glock19_InteriorTail_SoundSet"
			};
			soundSetShotExt[]=
			{
				
				{
					"Glock19_silencerPro_SoundSet",
					"Glock19_silencerTail_SoundSet",
					"Glock19_silencerInteriorTail_SoundSet"
				}
			};
			burst=3;
			reloadTime=0.064999998;
			dispersion=0.0020000001;
			magazineSlot="magazine";
		};
	};
	class Glock19: Glock19_Base
	{
	};
};
