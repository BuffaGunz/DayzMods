class CfgPatches
{
	class RuckPistol
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data",
			"DZ_Sounds_Weapons",
			"DZ_Pistols_pb6p9",
			"DZ_Weapons_Magazines"
		};
	};
};

class CfgMods
{
    class RuckPistol
    {
        dir = "RuckPistol";
        name = "Makarovepb";
		author="BuffaGunz";
        picture = "";
        action = "";
        hideName = 1;
        hidePicture = 1;
        version = "1.0";
        type = "mod";
        dependencies[] = {"Game", "World", "Mission"};

        class defs
        {
            class gameScriptModule
            {
                value = "";
                files[] = {"RuckPistol/Scripts/3_Game"};
            };
            class worldScriptModule
            {
                value = "";
                files[] = {"RuckPistol/Scripts/4_World"};
            };
			class missionScriptModule
            {
                value = "";
                files[] = {"RuckPistol/Scripts/5_Mission"};
            };
        };
    };
};

class cfgWeapons
{
	class  MakarovIJ70;
	class RuckPistol:  MakarovIJ70
	{
		scope=2;
		displayName="Makarov PB";
		descriptionShort="Semi-automatic-supressed pistol, Fed from a detachable magazine. Stealthy and lethal at short range. Uses .380 ACP rounds. A extremly durable pistol.";
		model="\DZ\weapons\pistols\pb6p9\pb6p9.p3d";
		attachments[]={};
		itemSize[]={4,2};
		hiddenSelections[] = {"zasleh"};
		hiddenSelectionsTextures[] = {"#(argb,8,8,3)color(0,0,0,0,ca)"};
		simpleHiddenSelections[] = {"zasleh"};
		simpleHiddenSelectionsTextures[] = {""};
		selectionFireAnim = "";    
		muzzleFlashParticle = ""; 
		muzzleFlashLight = 0;
		magazines[]+=
		{
			"Mag_RuckPistol_12Rnd"
		};
		chamberableFrom[]=
		{
			"Ammo_380"
		};
		class NoiseShoot
		{
			strength=10;
			type="sound";
		};
		class Mode_SemiAuto;
		class SemiAuto: Mode_SemiAuto
		{
			soundSetShot[]=
			{
				"Makarov_silencerPro_SoundSet",
				"Makarov_silencerTail_SoundSet",
				"Makarov_silencerInteriorTail_SoundSet"
			};
			soundSetShotExt[]=
			{
				
				{
					"Makarov_silencerPro_SoundSet",
					"Makarov_silencerTail_SoundSet",
					"Makarov_silencerInteriorTail_SoundSet"
				}
			};
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=150;
					healthLevels[]=
					{
						
						{
							1,
							
							{
								"DZ\weapons\pistols\pb6p9\data\pb6p9.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\weapons\pistols\pb6p9\data\pb6p9.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\weapons\pistols\pb6p9\data\pb6p9_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\weapons\pistols\pb6p9\data\pb6p9_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\weapons\pistols\pb6p9\data\pb6p9_destruct.rvmat"
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
					illuminateWorld=0;
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
	};
};

class CfgMagazines
{
	class Mag_IJ70_8Rnd;
	class Mag_RuckPistol_12Rnd: Mag_IJ70_8Rnd
	{
		scope=2;
		displayName="Mag_MakarovPB_12Rnd";
		descriptionShort="A magazine for the MakarovPB pistol which holds 12 rounds of .380 ACP";
		model="\DZ\weapons\attachments\magazine\magazine_pb6p9.p3d";
		weight=131;
		weightPerQuantityUnit=6;
		itemSize[]={1,2};
		count=12;
		ammo="Bullet_380";
		ammoItems[]=
		{
			"Ammo_380"
		};
		tracersEvery=0;
		mass=10;
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
								"DZ\weapons\attachments\magazine\data\magazine_pb6p9.rvmat"
							}
						},
						
						{
							0.69999999,
							
							{
								"DZ\weapons\attachments\magazine\data\magazine_pb6p9.rvmat"
							}
						},
						
						{
							0.5,
							
							{
								"DZ\weapons\attachments\magazine\data\magazine_pb6p9_damage.rvmat"
							}
						},
						
						{
							0.30000001,
							
							{
								"DZ\weapons\attachments\magazine\data\magazine_pb6p9_damage.rvmat"
							}
						},
						
						{
							0,
							
							{
								"DZ\weapons\attachments\magazine\data\magazine_pb6p9_destruct.rvmat"
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
		weaponStateAnim="dz\anims\anm\player\reloads\IJ70\w_IJ70_states.anm";
	};
};	

class CfgNonAIVehicles
{
	class ProxyAttachment;
	class ProxyMuzzle_flash_pistol_fnp: ProxyAttachment
	{
		scope = 2;
		model = "\RuckPistol\data\proxy_blank.p3d";
	};
};