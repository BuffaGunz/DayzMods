class CfgPatches
{
	class RuckModPack_Weapons
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = 
		{
			"DZ_Data",
			"DZ_Weapons_Muzzles",
			"DZ_Weapons_Optics",
			"DZ_Weapons_Magazines",
		    "DZ_Pistols_Glock",
		    "DZ_Pistols_CZ75",
		    "DZ_Pistols_FNX45",
			"DZ_Pistols_1911",
			"DZ_Pistols_DE",
			"DZ_Pistols_Derringer",
			"DZ_Pistols_Encore",
			"DZ_Pistols_Magnum",
			"DZ_Pistols_mkii",
			"DZ_Pistols_p1",
			"DZ_Pistols_pmm",
		    "DZ_Weapons_Firearms_AK101",
		    "DZ_Weapons_Firearms_aug",
		    "DZ_Weapons_Firearms_Famas",
		    "DZ_Weapons_Firearms_M4",
		    "DZ_Weapons_Firearms_M16A2",
		    "DZ_Weapons_Firearms_Scout",
		    "DZ_Weapons_Firearms_CZ550",
		    "DZ_Weapons_Firearms_FAL",
		    "DZ_Weapons_Firearms_M14",
		    "DZ_Weapons_Firearms_SV98",
		    "DZ_Weapons_Firearms_SVD",
		    "DZ_Weapons_Firearms_CZ527",
		    "DZ_Weapons_Firearms_AKM",
		    "DZ_Weapons_Firearms_SSG82",
		    "DZ_Weapons_Firearms_AK74",
			"DZ_Weapons_Firearms_B95",
			"DZ_Weapons_Firearms_cz61",
			"DZ_Weapons_Firearms_IZH18",
			"DZ_Weapons_Firearms_M249Para",
			"DZ_Weapons_Firearms_MosinNagant",
			"DZ_Weapons_Firearms_MP5",
			"DZ_Weapons_Firearms_groza",
			"DZ_Weapons_Firearms_pm73rak",
			"DZ_Weapons_Firearms_PP19",
			"DZ_Weapons_Firearms_Repeater",
			"DZ_Weapons_Firearms_Ruger1022",
			"DZ_Weapons_Firearms_Scout",
			"DZ_Weapons_Firearms_SKS",
			"DZ_Weapons_Firearms_Trumpet",
			"DZ_Weapons_Firearms_UMP",
			"DZ_Weapons_Firearms_VSS",
			"DZ_Weapons_Firearms_Winchester70",
			"DZ_Weapons_Shotguns_Izh18Shotgun",
			"DZ_Weapons_Shotguns_Izh43",
			"DZ_Weapons_Shotguns_MP133",
			"DZ_Weapons_Firearms_SaigaK"
		};
	};
};

class CfgVehicles
{
	class ItemSuppressor;
	class ImprovisedSuppressor: ItemSuppressor
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=2;
				};
			};
		};
	};
	class M4_Suppressor: ItemSuppressor
	{
		inventorySlot[]=
		{
			"weaponMuzzleM4",
			"suppressorImpro"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=10;
				};
			};
		};
	};
	class AK_Suppressor: ItemSuppressor
	{
		inventorySlot[]=
		{
			"weaponMuzzleAK",
			"suppressorImpro"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=10;
				};
			};
		};
	};	
	class PistolSuppressor: ItemSuppressor
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=10;
				};
			};
		};
	};
	class ItemOptics_Base;
	class BUISOptic: ItemOptics_Base
	{
		inventorySlot[]=
		{
			"weaponOpticsHunting",
			"weaponOpticsMosin",
			"WeaponOptics",
			"weaponOpticsAK",
			"weaponOpticsLRS"
		};
	};	
	class M68Optic: ItemOptics_Base
	{
		inventorySlot[]=
		{
			"weaponOpticsHunting",
			"weaponOpticsMosin",
			"WeaponOptics",
			"weaponOpticsLRS"
		};
	};
	class M4_T3NRDSOptic: ItemOptics_Base
	{
		inventorySlot[]=
		{
			"weaponOpticsHunting",
			"weaponOpticsMosin",
			"WeaponOptics",
			"weaponOpticsLRS"
		};
	};
	class ReflexOptic: ItemOptics_Base
	{
		inventorySlot[]=
		{
			"weaponOpticsHunting",
			"weaponOpticsMosin",
			"WeaponOptics",
			"weaponOpticsLRS"
		};
	};
	class ACOGOptic: ItemOptics_Base
	{
		inventorySlot[]=
		{
			"weaponOpticsHunting",
			"weaponOpticsMosin",
			"WeaponOptics",
			"weaponOpticsLRS"
		};
	};
	class ACOGOptic_6x: ItemOptics_Base
	{
		inventorySlot[]=
		{
			"weaponOpticsHunting",
			"weaponOpticsMosin",
			"WeaponOptics",
			"weaponOpticsLRS"
		};
	};
	class PUScopeOptic: ItemOptics_Base
	{
		inventorySlot[]=
		{
			"weaponOpticsHunting",
			"weaponOpticsMosin",
			"WeaponOptics",
			"weaponOpticsLRS"
		};
	};
	class KashtanOptic: ItemOptics_Base
	{
		inventorySlot[]=
		{
			"weaponOpticsHunting",
			"weaponOpticsMosin",
			"WeaponOptics",
			"weaponOpticsAK",
			"weaponOpticsLRS"
		};
	};
	class LongrangeOptic: ItemOptics_Base
	{
		inventorySlot[]=
		{
			"weaponOpticsHunting",
			"weaponOpticsMosin",
			"WeaponOptics",
			"weaponOpticsLRS"
		};
	};
	class HuntingOptic: ItemOptics_Base
	{
		inventorySlot[]=
		{
			"weaponOpticsHunting",
			"weaponOpticsMosin",
			"WeaponOptics",
			"weaponOpticsLRS"
		};
	};
	class PSO1Optic: ItemOptics_Base
	{
		inventorySlot[]=
		{
			"weaponOpticsHunting",
			"weaponOpticsMosin",
			"WeaponOptics",
			"weaponOpticsAK",
			"weaponOpticsLRS"
		};
	};
	class PSO11Optic: ItemOptics_Base
	{
		inventorySlot[]=
		{
			"weaponOpticsHunting",
			"weaponOpticsMosin",
			"WeaponOptics",
			"weaponOpticsAK",
			"weaponOpticsLRS"
		};
	};
	class KobraOptic: ItemOptics_Base
	{
		inventorySlot[]=
		{
			"weaponOpticsHunting",
			"weaponOpticsMosin",
			"WeaponOptics",
			"weaponOpticsAK",
			"weaponOpticsLRS"
		};
	};
	class KazuarOptic: ItemOptics_Base
	{
		inventorySlot[]=
		{
			"weaponOpticsHunting",
			"weaponOpticsMosin",
			"WeaponOptics",
			"weaponOpticsAK",
			"weaponOpticsLRS"
		};
	};
	class StarlightOptic: ItemOptics_Base
	{
		inventorySlot[]=
		{
			"weaponOpticsHunting",
			"weaponOpticsMosin",
			"WeaponOptics",
			"weaponOpticsLRS"
		};
	};
	class FNP45_MRDSOptic: ItemOptics_Base
	{
		inventorySlot[]=
		{
			"pistolOptics",
			"weaponOpticsCrossbow"
		};
	};
	class PistolOptic: ItemOptics_Base
	{
		inventorySlot[]=
		{
			"pistolOptics",
			"weaponOpticsCrossbow"
		};
	};
};	

class cfgWeapons
{
	class BoltActionRifle_ExternalMagazine_Base;
	class Rifle_Base;
	class Pistol_Base;
	class MakarovIJ70_Base;
	class MakarovIJ70: MakarovIJ70_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};
	class P1_Base;
	class P1: P1_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};
	class MKII_Base;
	class MKII: MKII_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};
	class Magnum_Base;
	class Magnum: Magnum_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};
	class SawedoffMagnum: Magnum_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};
	class LongHorn_Base;
	class LongHorn: LongHorn_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};
	class Derringer_Base: Pistol_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};
	class Derringer_Black: Derringer_Base
	{
	};
	class Derringer_Pink: Derringer_Base
	{
	};
	class Derringer_Grey: Derringer_Base
	{
	};
	class Deagle_Base;
	class Deagle: Deagle_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};
	class Deagle_Gold: Deagle
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};
	class Colt1911_Base;
	class Colt1911: Colt1911_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};
	class Engraved1911: Colt1911_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};
	class Saiga_Base;
	class Saiga: Saiga_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};
	class Mp133Shotgun_Base;
	class Mp133Shotgun: Mp133Shotgun_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};
	class Mp133Shotgun_PistolGrip: Mp133Shotgun_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};
	class Izh43Shotgun_Base;
	class Izh43Shotgun: Izh43Shotgun_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};
	class SawedoffIzh43Shotgun: Izh43Shotgun_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};
	class Izh18Shotgun_Base;
	class Izh18Shotgun: Izh18Shotgun_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};
	class SawedoffIzh18Shotgun: Izh18Shotgun_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};
	class Winchester70_Base;
	class Winchester70: Winchester70_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};
	class Winchester70_Black: Winchester70
	{
	};
	class Winchester70_Green: Winchester70
	{
	};
	class VSS_Base;
	class VSS: VSS_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};
	class ASVAL: VSS_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};
	class Vikhr: VSS_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};
	class UMP45_Base;
	class UMP45: UMP45_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};
	class Trumpet_Base;
	class Trumpet: Trumpet_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};
	class SKS_Base;
	class SKS: SKS_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};
	class SKS_Black: SKS
	{
	};
	class SKS_Green: SKS
	{
	};
	class Ruger1022_Base;
	class Ruger1022: Ruger1022_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};	
	class Repeater_Base: Rifle_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};
	class PP19_Base: Rifle_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};
	class PM73Rak_Base;
	class PM73Rak: PM73Rak_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};
	class Groza_Base;
	class Groza: Groza_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};
	class MP5K_Base;
	class MP5K: MP5K_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};
	class Mosin9130_Base;
	class SawedoffMosin9130_Base;
	class Mosin9130: Mosin9130_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};
	class Mosin9130_Black: Mosin9130
	{
	};
	class Mosin9130_Green: Mosin9130
	{
	};
	class Mosin9130_Camo: Mosin9130
	{
	};
	class SawedoffMosin9130: SawedoffMosin9130_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};
	class SawedoffMosin9130_Black: SawedoffMosin9130
	{
	};
	class SawedoffMosin9130_Green: SawedoffMosin9130
	{
	};
	class SawedoffMosin9130_Camo: SawedoffMosin9130
	{
	};
	class M249_Base;
	class M249: M249_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};
	class Izh18_Base;
	class Izh18: Izh18_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};
	class SawedoffIzh18: Izh18
	{
	};
	class CZ61_Base;
	class CZ61: CZ61_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};	
	class B95_Base;
	class B95: B95_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};	
	class FNX45_Base: Pistol_Base
	{
		magazines[]=
		{
			"Mag_1911_7Rnd",
			"Mag_FNX45_15Rnd"
		};
	};	
	class FNX45: FNX45_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};
	class FNX45_arrow: FNX45
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};
	class CZ75_Base: Pistol_Base
	{
		magazines[]=
		{
			"Mag_Glock_15Rnd",
			"Mag_CZ75_15Rnd",
			"Mag_P1_8Rnd"
		};
	};
	class CZ75: CZ75_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};
	class Glock19_Base: Pistol_Base
	{
		magazines[]=
		{
			"Mag_Glock_15Rnd",
			"Mag_CZ75_15Rnd",
			"Mag_P1_8Rnd"
		};
	};	
	class Glock19: Glock19_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};
	class AK101_Base: Rifle_Base
	{
		magazines[]=
		{
			"Mag_AK101_30Rnd",
			"Mag_AK101_30Rnd_Black",
			"Mag_AK101_30Rnd_Green",
			"Mag_Aug_30Rnd",
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
			"Mag_CMAG_40Rnd_Black",
			"Mag_FAMAS_25Rnd",
			"Mag_Scout_5Rnd"
		};
	};
	class AK101: AK101_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};
	class AK101_Black: AK101
	{
	};
	class AK101_Green: AK101
	{
	};
	class Aug_Base: Rifle_Base
	{
		magazines[]=
		{
			"Mag_AK101_30Rnd",
			"Mag_AK101_30Rnd_Black",
			"Mag_AK101_30Rnd_Green",
			"Mag_Aug_30Rnd",
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
			"Mag_CMAG_40Rnd_Black",
			"Mag_FAMAS_25Rnd",
			"Mag_Scout_5Rnd"
		};
	};
	class Aug: Aug_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};
	class AugShort: Aug_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};	
	class Famas_Base: Rifle_Base
	{
		magazines[]=
		{
			"Mag_AK101_30Rnd",
			"Mag_AK101_30Rnd_Black",
			"Mag_AK101_30Rnd_Green",
			"Mag_Aug_30Rnd",
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
			"Mag_CMAG_40Rnd_Black",
			"Mag_FAMAS_25Rnd",
			"Mag_Scout_5Rnd"
		};
	};
	class FAMAS: Famas_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};
	class SawedoffFAMAS: Famas_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};
	class M4A1_Base: Rifle_Base
	{
		magazines[]=
		{
			"Mag_AK101_30Rnd",
			"Mag_AK101_30Rnd_Black",
			"Mag_AK101_30Rnd_Green",
			"Mag_Aug_30Rnd",
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
			"Mag_CMAG_40Rnd_Black",
			"Mag_FAMAS_25Rnd",
			"Mag_Scout_5Rnd"
		};
	};
	class M4A1: M4A1_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};
	class M4A1_Green: M4A1
	{
	};
	class M4A1_Black: M4A1
	{
	};
	class M16A2_Base: Rifle_Base
	{
		magazines[]=
		{
			"Mag_AK101_30Rnd",
			"Mag_AK101_30Rnd_Black",
			"Mag_AK101_30Rnd_Green",
			"Mag_Aug_30Rnd",
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
			"Mag_CMAG_40Rnd_Black",
			"Mag_FAMAS_25Rnd",
			"Mag_Scout_5Rnd"
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};
	class Scout_Base: BoltActionRifle_ExternalMagazine_Base
	{
		magazines[]=
		{
			"Mag_AK101_30Rnd",
			"Mag_AK101_30Rnd_Black",
			"Mag_AK101_30Rnd_Green",
			"Mag_Aug_30Rnd",
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
			"Mag_CMAG_40Rnd_Black",
			"Mag_FAMAS_25Rnd",
			"Mag_Scout_5Rnd"
		};
	};	
	class Scout: Scout_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};
	class Scout_Chernarus: Scout
	{
	};
	class Scout_Livonia: Scout
	{
	};
	class CZ550_Base: BoltActionRifle_ExternalMagazine_Base
	{
		magazines[]=
		{
			"Mag_CZ550_4rnd",
			"Mag_CZ550_10rnd",
			"Mag_FAL_20Rnd",
			"Mag_M14_10Rnd",
			"Mag_M14_20Rnd"
		};
	};
	class CZ550: CZ550_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};
	class FAL_Base: Rifle_Base
	{
		magazines[]=
		{
			"Mag_CZ550_4rnd",
			"Mag_CZ550_10rnd",
			"Mag_FAL_20Rnd",
			"Mag_M14_10Rnd",
			"Mag_M14_20Rnd"
		};
	};
	class FAL: FAL_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};
	class M14_Base: Rifle_Base
	{
		magazines[]=
		{
			"Mag_CZ550_4rnd",
			"Mag_CZ550_10rnd",
			"Mag_FAL_20Rnd",
			"Mag_M14_10Rnd",
			"Mag_M14_20Rnd"
		};
	};
	class M14: M14_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};
	class SV98_Base: BoltActionRifle_ExternalMagazine_Base
	{
		magazines[]=
		{
			"Mag_SV98_10rnd",
			"Mag_SVD_10Rnd"
		};
	};	
	class SV98: SV98_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};
    class SVD_Base: Rifle_Base
	{
		magazines[]=
		{
			"Mag_SV98_10rnd",
			"Mag_SVD_10Rnd"
		};
	};	
	class SVD: SVD_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};
	class SVD_Wooden: SVD_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};
	class CZ527_Base: BoltActionRifle_ExternalMagazine_Base
	{
		magazines[]=
		{
			"Mag_AKM_30Rnd",
			"Mag_AKM_Palm30Rnd",
			"Mag_AKM_Palm30Rnd_Black",
			"Mag_AKM_Palm30Rnd_Green",
			"Mag_AKM_Drum75Rnd",
			"Mag_AKM_Drum75Rnd_Green",
			"Mag_AKM_Drum75Rnd_Black",
			"Mag_AKM_Drum_TEST",
			"Mag_CZ527_5rnd"
		};
	};	
	class CZ527: CZ527_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};
	class CZ527_Black: CZ527
	{
	};
	class CZ527_Green: CZ527
	{
	};
	class CZ527_Camo: CZ527
	{
	};
	class AKM_Base: Rifle_Base
	{
		magazines[]=
		{
			"Mag_AKM_30Rnd",
			"Mag_AKM_Palm30Rnd",
			"Mag_AKM_Palm30Rnd_Black",
			"Mag_AKM_Palm30Rnd_Green",
			"Mag_AKM_Drum75Rnd",
			"Mag_AKM_Drum75Rnd_Green",
			"Mag_AKM_Drum75Rnd_Black",
			"Mag_AKM_Drum_TEST",
			"Mag_CZ527_5rnd"
		};
	};
	class AKM: AKM_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};	
	class SSG82_Base: BoltActionRifle_ExternalMagazine_Base
	{
		magazines[]=
		{
			"Mag_AK74_30Rnd",
			"Mag_AK74_30Rnd_Black",
			"Mag_AK74_30Rnd_Green",
			"Mag_AK74_45Rnd",
			"Mag_SSG82_5rnd"
		};
	};
	class SSG82: SSG82_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};
	class AK74_Base: Rifle_Base
	{
		magazines[]=
		{
			"Mag_AK74_30Rnd",
			"Mag_AK74_30Rnd_Black",
			"Mag_AK74_30Rnd_Green",
			"Mag_AK74_45Rnd",
			"Mag_SSG82_5rnd"
		};
	};	
	class AK74: AK74_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
				};
			};
	    };
	};	
};	

class CfgMagazines
{
	class DefaultMagazine;
    class Magazine_Base: DefaultMagazine
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_FNX45_15Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_357Speedloader_6Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_Deagle_9rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_1911_7Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_CZ75_15Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_Glock_15Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};	
	class Mag_P1_8Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_IJ70_8Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_MP5_15Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_MP5_30Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_PM73_15Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_PM73_25Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_CZ61_20Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_FAMAS_25Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_MKII_10Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_ShockCartridge: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_Ruger1022_10Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_Ruger1022_15Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_Ruger1022_30Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_CLIP762x54_5Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_762x54Snaploader_2Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_308WinSnaploader_2Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_CLIP762x39_10Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_CLIP9x19_10Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_AKM_30Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_AKM_Drum75Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_AKM_Drum75Rnd_Black: Mag_AKM_Drum75Rnd
	{
	};
	class Mag_AKM_Drum75Rnd_Green: Mag_AKM_Drum75Rnd
	{
	};
	class Mag_AKM_Palm30Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_AKM_Palm30Rnd_Black: Mag_AKM_Palm30Rnd
	{
	};
	class Mag_AKM_Palm30Rnd_Green: Mag_AKM_Palm30Rnd
	{
	};
	class Mag_CZ527_5rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_STANAG_30Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_STANAGCoupled_30Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_STANAG_60Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_CMAG_10Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_CMAG_10Rnd_Black: Mag_CMAG_10Rnd
	{
	};
	class Mag_CMAG_10Rnd_Green: Mag_CMAG_10Rnd
	{
	};
	class Mag_CMAG_20Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_CMAG_20Rnd_Black: Mag_CMAG_20Rnd
	{
	};
	class Mag_CMAG_20Rnd_Green: Mag_CMAG_20Rnd
	{
	};
	class Mag_CMAG_30Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_CMAG_30Rnd_Black: Mag_CMAG_30Rnd
	{
	};
	class Mag_CMAG_30Rnd_Green: Mag_CMAG_30Rnd
	{
	};
	class Mag_CMAG_40Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_CMAG_40Rnd_Black: Mag_CMAG_40Rnd
	{
	};
	class Mag_CMAG_40Rnd_Green: Mag_CMAG_40Rnd
	{
	};
	class Mag_AK101_30Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_Aug_30Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_AK101_30Rnd_Black: Mag_AK101_30Rnd
	{
	};
	class Mag_AK101_30Rnd_Green: Mag_AK101_30Rnd
	{
	};
	class Mag_AK74_30Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_AK74_30Rnd_Black: Mag_AK74_30Rnd
	{
	};
	class Mag_AK74_30Rnd_Green: Mag_AK74_30Rnd
	{
	};
	class Mag_AK74_45Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_SVD_10Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_FAL_20Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_Scout_5Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_UMP_25Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_VSS_10Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_VAL_20Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_Vikhr_30Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};	
	class Mag_M249_Box200Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_PP19_64Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_CZ550_4rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_CZ550_10rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_SSG82_5rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_12gaSnaploader_2Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_Saiga_5Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_Saiga_8Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_Saiga_Drum20Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_Dartgun_CO2: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_Groza_20Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_MakarovPB_8Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_AKM_Drum_TEST: Mag_AKM_Drum75Rnd
	{
		scope=2;
		displayName="Tracer testing mag";
		descriptionShort="Hope it won't cause lag";
		count=300;
		ammo="Bullet_762x39Tracer";
		ammoItems[]=
		{
			"Ammo_762x39Tracer"
		};
	};
	class Mag_M14_10Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_M14_20Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
	class Mag_SV98_10Rnd: Magazine_Base
	{
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=400;
					
				};
			};
		};
	};
};
