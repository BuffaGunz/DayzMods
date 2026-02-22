modded class ZombieBase extends DayZInfected
{
	override bool CanBeSkinned()
	{
		return true;
	}
}

modded class ActionSkinning
{
	ref map<string, ref array<string>> m_ZombieClothingDrops;

	void InitZombieClothingDrops()
	{
		if (m_ZombieClothingDrops)
			return;

		m_ZombieClothingDrops = new map<string, ref array<string>>;
		
		m_ZombieClothingDrops.Insert("ZmbF_BlueCollarFat_Blue",  MakeDropList({ "JumpsuitPants_Blue", "JumpsuitJacket_Blue", "WorkingBoots_Brown" }));
		m_ZombieClothingDrops.Insert("ZmbF_BlueCollarFat_Green", MakeDropList({ "JumpsuitPants_Green", "JumpsuitJacket_Green", "WorkingBoots_Brown" }));
		m_ZombieClothingDrops.Insert("ZmbF_BlueCollarFat_Red",   MakeDropList({ "JumpsuitPants_Red", "JumpsuitJacket_Red", "WorkingBoots_Brown" }));
		m_ZombieClothingDrops.Insert("ZmbF_BlueCollarFat_White", MakeDropList({ "JumpsuitPants_Grey", "JumpsuitJacket_Gray", "WorkingBoots_Brown" }));
		m_ZombieClothingDrops.Insert("ZmbF_Clerk_Normal_Blue",  MakeDropList({ "Skirt_White", "Rag" }));
		m_ZombieClothingDrops.Insert("ZmbF_Clerk_Normal_Green", MakeDropList({ "Skirt_White", "Rag" }));
		m_ZombieClothingDrops.Insert("ZmbF_Clerk_Normal_Red",   MakeDropList({ "Skirt_Red", "Rag" }));
		m_ZombieClothingDrops.Insert("ZmbF_Clerk_Normal_White", MakeDropList({ "Skirt_Yellow", "Rag" }));
		m_ZombieClothingDrops.Insert("ZmbF_DoctorSkinny",        MakeDropList({ "SlacksPants_White", "LabCoat", "DressShoes_Brown" }));
		m_ZombieClothingDrops.Insert("ZmbF_NurseFat",            MakeDropList({ "NurseDress_Blue", "DressShoes_Brown" }));
		m_ZombieClothingDrops.Insert("ZmbF_NurseFat_Winter",     MakeDropList({ "NurseDress_Blue", "DressShoes_Brown" }));
		m_ZombieClothingDrops.Insert("ZmbF_PatientOld",          MakeDropList({ "MedicalScrubsShirt_Blue", "MedicalScrubsPants_Blue" }));
		m_ZombieClothingDrops.Insert("ZmbF_PatientOld_Winter",   MakeDropList({ "MedicalScrubsShirt_Blue", "MedicalScrubsPants_Blue" }));
		m_ZombieClothingDrops.Insert("ZmbM_DoctorFat",           MakeDropList({ "SlacksPants_White", "MedicalScrubsShirt_White", "DressShoes_Sunburst" }));
		m_ZombieClothingDrops.Insert("ZmbM_DoctorFat_Winter",    MakeDropList({ "SlacksPants_White", "MedicalScrubsShirt_White", "DressShoes_Sunburst" }));
		m_ZombieClothingDrops.Insert("ZmbM_PatientSkinny",       MakeDropList({ "MedicalScrubsShirt_Blue" }));
		m_ZombieClothingDrops.Insert("ZmbM_PatientSkinny_Winter",MakeDropList({ "MedicalScrubsShirt_Blue" }));
		m_ZombieClothingDrops.Insert("ZmbF_HikerSkinny_Blue",  MakeDropList({ "CanvasPants_Violet", "HikingJacket_Blue", "HikingBootsLow_Black" }));
		m_ZombieClothingDrops.Insert("ZmbF_HikerSkinny_Green", MakeDropList({ "CanvasPants_Beige", "HikingJacket_Green", "HikingBootsLow_Beige" }));
		m_ZombieClothingDrops.Insert("ZmbF_HikerSkinny_Grey",  MakeDropList({ "CanvasPants_Grey", "HikingJacket_Black", "HikingBootsLow_Black" }));
		m_ZombieClothingDrops.Insert("ZmbF_HikerSkinny_Red",   MakeDropList({ "CanvasPants_Red", "HikingJacket_Red", "HikingBootsLow_Grey" }));
		m_ZombieClothingDrops.Insert("ZmbF_CitizenANormal_Brown", MakeDropList({ "SlacksPants_Blue", "DressShoes_Black", "WoolCoat_Black" }));
		m_ZombieClothingDrops.Insert("ZmbF_CitizenANormal_Beige", MakeDropList({ "SlacksPants_Blue", "DressShoes_Beige", "WoolCoat_Beige" }));
		m_ZombieClothingDrops.Insert("ZmbF_CitizenANormal_Blue",  MakeDropList({ "SlacksPants_Beige", "DressShoes_Brown", "WoolCoat_Blue" }));
		m_ZombieClothingDrops.Insert("ZmbF_CitizenBSkinny", MakeDropList({ "Rag" }));
		m_ZombieClothingDrops.Insert("ZmbF_JoggerSkinny_Blue",  MakeDropList({ "Hoodie_Blue", "Breeches_Blue", "JoggingShoes_Blue" }));
		m_ZombieClothingDrops.Insert("ZmbF_JoggerSkinny_Brown", MakeDropList({ "Hoodie_Brown", "Breeches_Beige", "JoggingShoes_Red" }));
		m_ZombieClothingDrops.Insert("ZmbF_JoggerSkinny_Green", MakeDropList({ "Hoodie_Green", "Breeches_Green", "JoggingShoes_Blue" }));
		m_ZombieClothingDrops.Insert("ZmbF_JoggerSkinny_Red",   MakeDropList({ "Hoodie_Red", "Breeches_Red", "JoggingShoes_Black" }));
		m_ZombieClothingDrops.Insert("ZmbF_ParamedicNormal_Blue",  MakeDropList({ "ParamedicJacket_Blue", "ParamedicPants_Blue", "WorkingBoots_Green" }));
		m_ZombieClothingDrops.Insert("ZmbF_ParamedicNormal_Red",   MakeDropList({ "ParamedicJacket_Crimson", "ParamedicPants_Crimson", "WorkingBoots_Green" }));
		m_ZombieClothingDrops.Insert("ZmbF_ParamedicNormal_Green", MakeDropList({ "ParamedicJacket_Red", "ParamedicPants_Green", "WorkingBoots_Green" }));
		m_ZombieClothingDrops.Insert("ZmbF_ClerkFat_Black",       MakeDropList({ "WomanSuit_Black", "DressShoes_Black", "SlacksPants_Beige" }));
		m_ZombieClothingDrops.Insert("ZmbF_ClerkFat_GreyPattern", MakeDropList({ "Rag", "DressShoes_Black", "SlacksPants_Black" }));
		m_ZombieClothingDrops.Insert("ZmbF_ClerkFat_BluePattern", MakeDropList({ "WomanSuit_Black", "DressShoes_Black", "SlacksPants_Khaki" }));
		m_ZombieClothingDrops.Insert("ZmbF_ClerkFat_White",       MakeDropList({ "WomanSuit_Black", "DressShoes_Black", "SlacksPants_DarkGrey" }));
		m_ZombieClothingDrops.Insert("ZmbF_JournalistNormal_Blue",  MakeDropList({ "Rag", "CargoPants_Black", "HikingBoots_Black" }));
		m_ZombieClothingDrops.Insert("ZmbF_JournalistNormal_Green", MakeDropList({ "Sweater_Green", "CargoPants_Blue", "HikingBoots_Black" }));
		m_ZombieClothingDrops.Insert("ZmbF_JournalistNormal_Red",   MakeDropList({ "Sweater_Red", "CargoPants_Blue", "HikingBoots_Black" }));
		m_ZombieClothingDrops.Insert("ZmbF_JournalistNormal_White", MakeDropList({ "Sweater_Gray", "CargoPants_Green", "HikingBoots_Black" }));
		m_ZombieClothingDrops.Insert("ZmbF_MechanicNormal_Beige",  MakeDropList({ "JumpsuitPants_Grey", "JoggingShoes_White", "TShirt_Beige" }));
		m_ZombieClothingDrops.Insert("ZmbF_MechanicNormal_Green",  MakeDropList({ "JumpsuitPants_Blue", "JoggingShoes_Red", "TShirt_Green" }));
		m_ZombieClothingDrops.Insert("ZmbF_MechanicNormal_Grey",   MakeDropList({ "JumpsuitPants_Red", "JoggingShoes_Blue", "TShirt_Grey" }));
		m_ZombieClothingDrops.Insert("ZmbF_MechanicNormal_Orange", MakeDropList({ "JumpsuitPants_Green", "JoggingShoes_Violet", "TShirt_OrangeWhiteStripes" }));
		m_ZombieClothingDrops.Insert("ZmbF_MilkMaidOld_Beige", MakeDropList({ "Rag", "Wellies_Brown" }));
		m_ZombieClothingDrops.Insert("ZmbF_MilkMaidOld_Black", MakeDropList({ "Rag", "Wellies_Black" }));
		m_ZombieClothingDrops.Insert("ZmbF_MilkMaidOld_Green", MakeDropList({ "Rag", "Wellies_Brown" }));
		m_ZombieClothingDrops.Insert("ZmbF_MilkMaidOld_Grey",  MakeDropList({ "Rag", "Wellies_Brown" }));
		m_ZombieClothingDrops.Insert("ZmbF_PoliceWomanNormal", MakeDropList({ "PolicePants", "PoliceJacket", "DressShoes_Beige" }));
		m_ZombieClothingDrops.Insert("ZmbF_ShortSkirt_beige",   MakeDropList({ "Skirt_Yellow", "Rag" }));
		m_ZombieClothingDrops.Insert("ZmbF_ShortSkirt_black",   MakeDropList({ "Rag", "Rag" }));
		m_ZombieClothingDrops.Insert("ZmbF_ShortSkirt_brown",   MakeDropList({ "Skirt_Yellow", "Rag" }));
		m_ZombieClothingDrops.Insert("ZmbF_ShortSkirt_checks",  MakeDropList({ "Rag", "Rag" }));
		m_ZombieClothingDrops.Insert("ZmbF_ShortSkirt_green",   MakeDropList({ "Skirt_Yellow", "Rag" }));
		m_ZombieClothingDrops.Insert("ZmbF_ShortSkirt_grey",    MakeDropList({ "Rag", "Rag" }));
		m_ZombieClothingDrops.Insert("ZmbF_ShortSkirt_red",     MakeDropList({ "Skirt_Red", "Rag" }));
		m_ZombieClothingDrops.Insert("ZmbF_ShortSkirt_stripes", MakeDropList({ "Rag", "Rag" }));
		m_ZombieClothingDrops.Insert("ZmbF_ShortSkirt_white",   MakeDropList({ "Skirt_White", "Rag" }));
		m_ZombieClothingDrops.Insert("ZmbF_ShortSkirt_yellow",  MakeDropList({ "Rag", "Rag" }));
		m_ZombieClothingDrops.Insert("ZmbF_SkaterYoung_Brown",   MakeDropList({ "ShortJeans_Black", "AthleticShoes_Brown", "TShirt_Beige" }));
		m_ZombieClothingDrops.Insert("ZmbF_SkaterYoung_Striped", MakeDropList({ "ShortJeans_Blue", "AthleticShoes_Blue", "TShirt_OrangeWhiteStripes" }));
		m_ZombieClothingDrops.Insert("ZmbF_SkaterYoung_Violet",  MakeDropList({ "ShortJeans_Green", "AthleticShoes_Green", "TShirt_Blue" }));
		m_ZombieClothingDrops.Insert("ZmbF_SurvivorNormal_Blue",   MakeDropList({ "Jeans_Brown", "AthleticShoes_Green", "TShirt_Blue" }));
		m_ZombieClothingDrops.Insert("ZmbF_SurvivorNormal_Orange", MakeDropList({ "Jeans_Blue", "AthleticShoes_Blue", "TShirt_OrangeWhiteStripes" }));
		m_ZombieClothingDrops.Insert("ZmbF_SurvivorNormal_Red",    MakeDropList({ "Jeans_Black", "AthleticShoes_Blue", "TShirt_RedBlackStripes" }));
		m_ZombieClothingDrops.Insert("ZmbF_SurvivorNormal_White",  MakeDropList({ "Jeans_Blue", "AthleticShoes_Brown", "TShirt_White" }));
		m_ZombieClothingDrops.Insert("ZmbF_VillagerOld_Blue",  MakeDropList({ "TrackSuitPants_Red", "Sweater_Blue", "JoggingShoes_Red" }));
		m_ZombieClothingDrops.Insert("ZmbF_VillagerOld_Green", MakeDropList({ "TrackSuitPants_LightBlue", "Sweater_Green", "JoggingShoes_Black" }));
		m_ZombieClothingDrops.Insert("ZmbF_VillagerOld_Red",   MakeDropList({ "TrackSuitPants_Green", "Sweater_Red", "JoggingShoes_White" }));
		m_ZombieClothingDrops.Insert("ZmbF_VillagerOld_White", MakeDropList({ "TrackSuitPants_Blue", "Sweater_Gray", "JoggingShoes_White" }));
		m_ZombieClothingDrops.Insert("ZmbM_CitizenASkinny_Blue",  MakeDropList({ "SlacksPants_Blue", "DressShoes_Black", "WoolCoat_BlueCheck" }));
		m_ZombieClothingDrops.Insert("ZmbM_CitizenASkinny_Grey",  MakeDropList({ "SlacksPants_LightGrey", "DressShoes_Sunburst", "WoolCoat_GreyCheck" }));
		m_ZombieClothingDrops.Insert("ZmbM_CitizenASkinny_Red",   MakeDropList({ "SlacksPants_Brown", "DressShoes_Brown", "WoolCoat_RedCheck" }));
		m_ZombieClothingDrops.Insert("ZmbM_CitizenBFat_Blue",     MakeDropList({ "Jeans_Blue", "JoggingShoes_White", "TrackSuitJacket_Blue" }));
		m_ZombieClothingDrops.Insert("ZmbM_CitizenBFat_Green",    MakeDropList({ "Jeans_Brown", "JoggingShoes_Blue", "TrackSuitJacket_Green" }));
		m_ZombieClothingDrops.Insert("ZmbM_CitizenBFat_Red",      MakeDropList({ "Jeans_Black", "JoggingShoes_Red", "TrackSuitJacket_Red" }));
		m_ZombieClothingDrops.Insert("ZmbM_CommercialPilotOld_Blue",  MakeDropList({ "Jeans_Blue", "HikingBoots_Black", "BomberJacket_Brown" }));
		m_ZombieClothingDrops.Insert("ZmbM_CommercialPilotOld_Brown", MakeDropList({ "Jeans_Black", "HikingBoots_Black", "BomberJacket_Brown" }));
		m_ZombieClothingDrops.Insert("ZmbM_CommercialPilotOld_Grey",  MakeDropList({ "Jeans_Brown", "HikingBoots_Black", "BomberJacket_Grey" }));
		m_ZombieClothingDrops.Insert("ZmbM_CommercialPilotOld_Olive", MakeDropList({ "Jeans_Blue", "HikingBoots_Black", "BomberJacket_Olive" }));
		m_ZombieClothingDrops.Insert("ZmbM_ConstrWorkerNormal_Beige", MakeDropList({ "Jeans_Black", "WorkingBoots_Brown", "TShirt_Beige", "ReflexVest" }));
		m_ZombieClothingDrops.Insert("ZmbM_ConstrWorkerNormal_Black", MakeDropList({ "Jeans_BlueDark", "WorkingBoots_Brown", "TShirt_Black", "ReflexVest" }));
		m_ZombieClothingDrops.Insert("ZmbM_ConstrWorkerNormal_Green", MakeDropList({ "Jeans_Brown", "WorkingBoots_Brown", "TShirt_Green", "ReflexVest" }));
		m_ZombieClothingDrops.Insert("ZmbM_ConstrWorkerNormal_Grey",  MakeDropList({ "Jeans_Blue", "WorkingBoots_Brown", "TShirt_Grey", "ReflexVest" }));
		m_ZombieClothingDrops.Insert("ZmbM_FarmerFat_Beige", MakeDropList({ "CargoPants_Beige", "Wellies_Grey", "Rag" }));
		m_ZombieClothingDrops.Insert("ZmbM_FarmerFat_Blue",  MakeDropList({ "CargoPants_Blue", "Wellies_Black", "Rag" }));
		m_ZombieClothingDrops.Insert("ZmbM_FarmerFat_Brown", MakeDropList({ "CargoPants_Grey", "Wellies_Green", "Rag" }));
		m_ZombieClothingDrops.Insert("ZmbM_FarmerFat_Green", MakeDropList({ "CargoPants_Green", "Wellies_Black", "Rag" }));
		m_ZombieClothingDrops.Insert("ZmbM_FirefighterNormal", MakeDropList({ "FirefighterJacket_Beige", "FirefightersPants_Beige", "Wellies_Brown" }));
		m_ZombieClothingDrops.Insert("ZmbM_FishermanOld_Blue",  MakeDropList({ "Shirt_BlueCheck", "CanvasPants_Grey", "Wellies_Grey" }));
		m_ZombieClothingDrops.Insert("ZmbM_FishermanOld_Green", MakeDropList({ "Shirt_GreenCheck", "CanvasPants_Blue", "Wellies_Green" }));
		m_ZombieClothingDrops.Insert("ZmbM_FishermanOld_Grey",  MakeDropList({ "Shirt_WhiteCheck", "CanvasPants_Red", "Wellies_Green" }));
		m_ZombieClothingDrops.Insert("ZmbM_FishermanOld_Red",   MakeDropList({ "Shirt_RedCheck", "CanvasPants_Beige", "Wellies_Green" }));
		m_ZombieClothingDrops.Insert("ZmbM_Gamedev_Black", MakeDropList({ "Rag", "CargoPants_Green", "WorkingBoots_Beige" }));
		m_ZombieClothingDrops.Insert("ZmbM_Gamedev_Blue",  MakeDropList({ "Rag", "CargoPants_Blue", "WorkingBoots_Beige" }));
		m_ZombieClothingDrops.Insert("ZmbM_Gamedev_Gray",  MakeDropList({ "Rag", "CargoPants_Blue", "WorkingBoots_Beige" }));
		m_ZombieClothingDrops.Insert("ZmbM_HandymanNormal_Beige", MakeDropList({ "Rag", "Rag", "WorkingBoots_Brown" }));
		m_ZombieClothingDrops.Insert("ZmbM_HandymanNormal_Blue",  MakeDropList({ "Rag", "Rag", "WorkingBoots_Brown" }));
		m_ZombieClothingDrops.Insert("ZmbM_HandymanNormal_Green", MakeDropList({ "Rag", "Rag", "WorkingBoots_Brown" }));
		m_ZombieClothingDrops.Insert("ZmbM_HandymanNormal_Grey",  MakeDropList({ "Rag", "Rag", "WorkingBoots_Brown" }));
		m_ZombieClothingDrops.Insert("ZmbM_HandymanNormal_White", MakeDropList({ "Rag", "Rag", "WorkingBoots_Brown" }));
		m_ZombieClothingDrops.Insert("ZmbM_HeavyIndustryWorker", MakeDropList({ "FirefighterJacket_Beige", "FirefightersPants_Beige", "WorkingBoots_Beige" }));
		m_ZombieClothingDrops.Insert("ZmbM_HermitSkinny_Beige", MakeDropList({ "CanvasPantsMidi_Beige", "WorkingBoots_Beige" }));
		m_ZombieClothingDrops.Insert("ZmbM_HermitSkinny_Black", MakeDropList({ "Rag", "WorkingBoots_Beige" }));
		m_ZombieClothingDrops.Insert("ZmbM_HermitSkinny_Green", MakeDropList({ "Rag", "WorkingBoots_Beige" }));
		m_ZombieClothingDrops.Insert("ZmbM_HermitSkinny_Red",   MakeDropList({ "CanvasPantsMidi_Red", "WorkingBoots_Beige" }));
		m_ZombieClothingDrops.Insert("ZmbM_HikerSkinny_Blue",   MakeDropList({ "QuiltedJacket_Blue", "CanvasPants_Blue", "HikingBoots_Brown" }));
		m_ZombieClothingDrops.Insert("ZmbM_HikerSkinny_Green",  MakeDropList({ "QuiltedJacket_Green", "CanvasPants_Beige", "HikingBoots_Black" }));
		m_ZombieClothingDrops.Insert("ZmbM_HikerSkinny_Yellow", MakeDropList({ "QuiltedJacket_Yellow", "CanvasPants_Red", "HikingBoots_Black" }));
		m_ZombieClothingDrops.Insert("ZmbM_HunterOld_Autumn", MakeDropList({ "HuntingJacket_Autumn", "HunterPants_Autumn", "HikingBoots_Black" }));
		m_ZombieClothingDrops.Insert("ZmbM_HunterOld_Spring", MakeDropList({ "HuntingJacket_Spring", "HunterPants_Spring", "HikingBoots_Black" }));
		m_ZombieClothingDrops.Insert("ZmbM_HunterOld_Summer", MakeDropList({ "HuntingJacket_Summer", "HunterPants_Summer", "WorkingBoots_Green" }));
		m_ZombieClothingDrops.Insert("ZmbM_HunterOld_Winter", MakeDropList({ "HuntingJacket_Winter", "HunterPants_Winter", "WorkingBoots_Beige" }));
		m_ZombieClothingDrops.Insert("ZmbM_Jacket_beige",       MakeDropList({ "Rag", "Rag", "WorkingBoots_Brown" }));
		m_ZombieClothingDrops.Insert("ZmbM_Jacket_black",       MakeDropList({ "Rag", "Rag", "WorkingBoots_Brown" }));
		m_ZombieClothingDrops.Insert("ZmbM_Jacket_blue",        MakeDropList({ "Rag", "Rag", "WorkingBoots_Brown" }));
		m_ZombieClothingDrops.Insert("ZmbM_Jacket_bluechecks",  MakeDropList({ "Rag", "Rag", "WorkingBoots_Brown" }));
		m_ZombieClothingDrops.Insert("ZmbM_Jacket_brown",       MakeDropList({ "Rag", "Rag", "WorkingBoots_Brown" }));
		m_ZombieClothingDrops.Insert("ZmbM_Jacket_greenchecks", MakeDropList({ "Rag", "Rag", "WorkingBoots_Brown" }));
		m_ZombieClothingDrops.Insert("ZmbM_Jacket_grey",        MakeDropList({ "Rag", "Rag", "WorkingBoots_Brown" }));
		m_ZombieClothingDrops.Insert("ZmbM_Jacket_khaki",       MakeDropList({ "Rag", "Rag", "WorkingBoots_Brown" }));
		m_ZombieClothingDrops.Insert("ZmbM_Jacket_magenta",     MakeDropList({ "Rag", "Rag", "WorkingBoots_Brown" }));
		m_ZombieClothingDrops.Insert("ZmbM_Jacket_stripes",     MakeDropList({ "Rag", "Rag", "WorkingBoots_Brown" }));
		m_ZombieClothingDrops.Insert("ZmbM_JoggerSkinny_Blue",  MakeDropList({ "TrackSuitJacket_Blue", "TrackSuitPants_Red", "JoggingShoes_Blue" }));
		m_ZombieClothingDrops.Insert("ZmbM_JoggerSkinny_Green", MakeDropList({ "TrackSuitJacket_Green", "TrackSuitPants_BlueDark", "JoggingShoes_White" }));
		m_ZombieClothingDrops.Insert("ZmbM_JoggerSkinny_Red",   MakeDropList({ "TrackSuitJacket_Red", "TrackSuitPants_Green", "JoggingShoes_Red" }));
		m_ZombieClothingDrops.Insert("ZmbM_JournalistSkinny", MakeDropList({ "Sweater_Gray", "Jeans_Blue", "HikingBootsLow_Beige" }));
		m_ZombieClothingDrops.Insert("ZmbM_MechanicSkinny_Blue",  MakeDropList({ "JumpsuitJacket_Blue", "JumpsuitPants_Blue", "JoggingShoes_Blue" }));
		m_ZombieClothingDrops.Insert("ZmbM_MechanicSkinny_Green", MakeDropList({ "JumpsuitJacket_Green", "JumpsuitPants_Green", "JoggingShoes_Blue" }));
		m_ZombieClothingDrops.Insert("ZmbM_MechanicSkinny_Grey",  MakeDropList({ "JumpsuitJacket_Gray", "JumpsuitPants_Grey", "JoggingShoes_Blue" }));
		m_ZombieClothingDrops.Insert("ZmbM_MechanicSkinny_Red",   MakeDropList({ "JumpsuitJacket_Red", "JumpsuitPants_Red", "JoggingShoes_Blue" }));
		m_ZombieClothingDrops.Insert("ZmbM_MotobikerFat_Black", MakeDropList({ "RidersJacket_Black", "Jeans_Black", "WorkingBoots_Brown" }));
		m_ZombieClothingDrops.Insert("ZmbM_MotobikerFat_Beige", MakeDropList({ "RidersJacket_Black", "Jeans_Brown", "WorkingBoots_Green" }));
		m_ZombieClothingDrops.Insert("ZmbM_MotobikerFat_Blue",  MakeDropList({ "RidersJacket_Black", "Jeans_BlueDark", "WorkingBoots_Brown" }));
		m_ZombieClothingDrops.Insert("ZmbM_OffshoreWorker_Green",  MakeDropList({ "Raincoat_Green", "ParamedicPants_Green", "WorkingBoots_Beige" }));
		m_ZombieClothingDrops.Insert("ZmbM_OffshoreWorker_Orange", MakeDropList({ "Raincoat_Orange", "Rag", "WorkingBoots_Beige" }));
		m_ZombieClothingDrops.Insert("ZmbM_OffshoreWorker_Red",    MakeDropList({ "Raincoat_Red", "Rag", "WorkingBoots_Beige" }));
		m_ZombieClothingDrops.Insert("ZmbM_OffshoreWorker_Yellow", MakeDropList({ "Raincoat_Yellow", "ParamedicPants_Blue", "WorkingBoots_Beige" }));
		m_ZombieClothingDrops.Insert("ZmbM_PatrolNormal_Autumn",  MakeDropList({ "GorkaEJacket_Autumn", "GorkaPants_Autumn", "JungleBoots_Beige" }));
		m_ZombieClothingDrops.Insert("ZmbM_PatrolNormal_Flat",    MakeDropList({ "GorkaEJacket_Flat", "GorkaPants_Flat", "JungleBoots_Beige" }));
		m_ZombieClothingDrops.Insert("ZmbM_PatrolNormal_PautRev", MakeDropList({ "GorkaEJacket_PautRev", "GorkaPants_PautRev", "JungleBoots_Beige" }));
		m_ZombieClothingDrops.Insert("ZmbM_PatrolNormal_Summer",  MakeDropList({ "GorkaEJacket_Summer", "GorkaPants_Summer", "JungleBoots_Beige" }));
		m_ZombieClothingDrops.Insert("ZmbM_PatrolNormal_Winter",  MakeDropList({ "GorkaEJacket_Winter", "GorkaPants_Winter", "JungleBoots_Beige" }));
		m_ZombieClothingDrops.Insert("ZmbM_PolicemanFat",            MakeDropList({ "PolicePants", "PoliceJacket", "DressShoes_Brown" }));
		m_ZombieClothingDrops.Insert("ZmbM_PolicemanSpecForce",      MakeDropList({ "PolicePants", "PoliceJacketOrel", "HikingBoots_Brown" }));
		m_ZombieClothingDrops.Insert("ZmbM_PolicemanSpecForce_Heavy",MakeDropList({ "PolicePants", "PoliceJacketOrel", "HikingBoots_Brown" }));
		m_ZombieClothingDrops.Insert("ZmbM_PrisonerSkinny",   MakeDropList({ "PrisonUniformPants", "PrisonUniformJacket", "WorkingBoots_Grey" }));
		m_ZombieClothingDrops.Insert("ZmbM_priestPopSkinny",  MakeDropList({ "Rag", "Rag", "DressShoes_Black" }));
		m_ZombieClothingDrops.Insert("ZmbM_Santa",           MakeDropList({ "Rag", "Rag", "Wellies_Black" }));
		m_ZombieClothingDrops.Insert("ZmbM_SkaterYoung_Blue",  MakeDropList({ "CargoPants_Beige", "AthleticShoes_Blue", "Hoodie_Red" }));
		m_ZombieClothingDrops.Insert("ZmbM_SkaterYoung_Brown", MakeDropList({ "CargoPants_Blue", "AthleticShoes_Grey", "Hoodie_Brown" }));
		m_ZombieClothingDrops.Insert("ZmbM_SkaterYoung_Green", MakeDropList({ "CargoPants_Blue", "AthleticShoes_Blue", "Hoodie_Green" }));
		m_ZombieClothingDrops.Insert("ZmbM_SkaterYoung_Grey",  MakeDropList({ "CargoPants_Black", "AthleticShoes_Grey", "Hoodie_Grey" }));
		m_ZombieClothingDrops.Insert("ZmbM_ParamedicNormal_Blue",  MakeDropList({ "ParamedicJacket_Blue", "ParamedicPants_Blue", "WorkingBoots_Green" }));
		m_ZombieClothingDrops.Insert("ZmbM_ParamedicNormal_Red",   MakeDropList({ "ParamedicJacket_Crimson", "ParamedicPants_Crimson", "WorkingBoots_Green" }));
		m_ZombieClothingDrops.Insert("ZmbM_ParamedicNormal_Green", MakeDropList({ "ParamedicJacket_Red", "ParamedicPants_Green", "WorkingBoots_Green" }));
		m_ZombieClothingDrops.Insert("ZmbM_SoldierNormal",              MakeDropList({ "TTsKOPants", "MilitaryBoots_Brown", "TTsKOJacket_Camo" }));
		m_ZombieClothingDrops.Insert("ZmbM_eastSoldier_Heavy_Navy",     MakeDropList({ "OMKPants_Navy", "CombatBoots_Beige", "OMKJacket_Navy" }));
		m_ZombieClothingDrops.Insert("ZmbM_eastSoldier_normal_Navy",    MakeDropList({ "OMKPants_Navy", "CombatBoots_Beige", "OMKJacket_Navy" }));
		m_ZombieClothingDrops.Insert("ZmbM_usSoldier_Heavy_Woodland",   MakeDropList({ "USMCPants_Woodland", "CombatBoots_Black", "USMCJacket_Woodland" }));
		m_ZombieClothingDrops.Insert("ZmbM_usSoldier_Officer_Desert",   MakeDropList({ "Rag", "Rag", "DressShoes_Sunburst" }));
		m_ZombieClothingDrops.Insert("ZmbM_usSoldier_normal_Desert",    MakeDropList({ "USMCPants_Desert", "CombatBoots_Beige", "USMCJacket_Desert" }));
		m_ZombieClothingDrops.Insert("ZmbM_usSoldier_normal_Woodland",  MakeDropList({ "USMCPants_Woodland", "CombatBoots_Black", "USMCJacket_Woodland" }));
		m_ZombieClothingDrops.Insert("ZmbM_ClerkFat_Brown", MakeDropList({ "ManSuit_Brown", "DressShoes_Sunburst", "SlacksPants_Beige" }));
		m_ZombieClothingDrops.Insert("ZmbM_ClerkFat_Grey",  MakeDropList({ "ManSuit_DarkGrey", "DressShoes_Sunburst", "SlacksPants_DarkGrey" }));
		m_ZombieClothingDrops.Insert("ZmbM_ClerkFat_Khaki", MakeDropList({ "ManSuit_Khaki", "DressShoes_Sunburst", "SlacksPants_Khaki" }));
		m_ZombieClothingDrops.Insert("ZmbM_ClerkFat_White", MakeDropList({ "ManSuit_LightGrey", "DressShoes_Sunburst", "SlacksPants_DarkGrey" }));
		m_ZombieClothingDrops.Insert("ZmbM_VillagerOld_Blue",  MakeDropList({ "Sweater_Blue", "TrackSuitPants_Green", "HikingBootsLow_Grey" }));
		m_ZombieClothingDrops.Insert("ZmbM_VillagerOld_Green", MakeDropList({ "Sweater_Green", "TrackSuitPants_Red", "HikingBootsLow_Black" }));
		m_ZombieClothingDrops.Insert("ZmbM_VillagerOld_White", MakeDropList({ "Sweater_Gray", "TrackSuitPants_BlueDark", "HikingBootsLow_Grey" }));
		m_ZombieClothingDrops.Insert("ZmbM_NBC_Grey",  MakeDropList({ "NBCGlovesGray", "NBCBootsGray", "NBCPantsGray", "NBCJacketGray", "NBCHoodGray", "GP5GasMask", "GasMask_Filter" }));
		m_ZombieClothingDrops.Insert("ZmbM_NBC_White", MakeDropList({ "NBCGlovesGray", "NBCBootsWhite", "NBCPantsWhite", "NBCJacketWhite", "NBCHoodWhite", "AirborneMask" }));
		m_ZombieClothingDrops.Insert("ZmbM_NBC_Yellow", MakeDropList({ "NBCGlovesGray", "NBCBootsYellow", "NBCPantsYellow", "NBCJacketYellow", "NBCHoodYellow", "AirborneMask" }));
		m_ZombieClothingDrops.Insert("ZmbM_Mummy", MakeDropList({ "HandsCover_Improvised", "HeadCover_Improvised", "FaceCover_Improvised", "LegsCover_Improvised", "FeetCover_Improvised", "TorsoCover_Improvised" }));


	}

	array<string> MakeDropList(array<string> items)
	{
		ref array<string> outList = new array<string>;
		for (int i = 0; i < items.Count(); i++)
			outList.Insert(items[i]);
		return outList;
	}

	ItemBase SpawnDamagedOnGround(PlayerBase player, string itemType, vector pos)
	{
		EntityAI ent = EntityAI.Cast(player.SpawnEntityOnGroundPos(itemType, pos));
		ItemBase item = ItemBase.Cast(ent);
		if (!item)
			return null;

		float maxH = item.GetMaxHealth("", "");
		if (maxH <= 0)
			return item;

		if (Math.RandomIntInclusive(1, 3) == 1)
		{
			item.SetHealth("", "", 0); 
		}
		else
		{
			float frac = Math.RandomFloatInclusive(0.05, 0.20);
			item.SetHealth("", "", maxH * frac);
		}

		return item;
	}
	
	void SpawnZombieClothing(ActionData action_data, DayZInfected body)
	{
		if (!GetGame().IsServer() || !body)
			return;

		InitZombieClothingDrops();

		string zType = body.GetType();
		array<string> drops = m_ZombieClothingDrops.Get(zType);
		if (!drops)
			return;

		vector p = body.GetPosition();

		p[1] = GetGame().SurfaceY(p[0], p[2]) + 0.15;

		for (int i = 0; i < drops.Count(); i++)
		{
			string itemType = drops[i];
			if (itemType == "")
				continue;

			SpawnDamagedOnGround(action_data.m_Player, itemType, p);
		}
	}
	
	void SpawnInfectedSkeleton(ActionData action_data, DayZInfected body)
	{
		if (!GetGame().IsServer() || !body)
			return;

		string skelType = "StaticObj_Forest_HumanSkeleton";

		vector pos = body.GetPosition();
		pos[1] = GetGame().SurfaceY(pos[0], pos[2]) + 0.15;

		Object skel = GetGame().CreateObjectEx(skelType, pos, ECE_PLACE_ON_SURFACE);
		if (!skel)
			return;

		skel.PlaceOnSurface();
		vector skelPos = skel.GetPosition();

		vector normal = GetGame().SurfaceGetNormal(skelPos[0], skelPos[2]);

		vector dir = body.GetDirection();
		dir[1] = 0;
		if (dir.LengthSq() < 0.0001)
			dir = "1 0 0";
		dir.Normalize();

		vector right = dir * normal;
		right.Normalize();
		vector forward = normal * right;
		forward.Normalize();

		vector mat[3];
		mat[0] = forward;
		mat[1] = normal;
		mat[2] = right;

		vector angles = Math3D.MatrixToAngles(mat);

		skel.SetOrientation(angles);
		skel.SetPosition(skelPos);
	}

	override void OnFinishProgressServer(ActionData action_data)
	{
		Object targetObject = action_data.m_Target.GetObject();
		EntityAI body = EntityAI.Cast(targetObject);

		if (body)
		{
			MiscGameplayFunctions.RemoveAllAttachedChildrenByTypename(body, {Bolt_Base});

			SpawnDeerSkeleton(action_data, body);
		}

		HandleInfectedBody(action_data);

		super.OnFinishProgressServer(action_data);
	}

	override void HandlePlayerBody(ActionData action_data)
	{
		super.HandlePlayerBody(action_data);

		PlayerBase body;
		if (!Class.CastTo(body, action_data.m_Target.GetObject()))
			return;

		RuckHumanSkull skull = RuckHumanSkull.Cast(action_data.m_Player.SpawnEntityOnGroundOnCursorDir("RuckHumanSkull", 0.5));
		if (!skull)
			return;

		string name = body.GetCachedName();
		if (name == "" && body.GetIdentity())
			name = body.GetIdentity().GetName();

		body.StatUpdateByPosition(AnalyticsManagerServer.STAT_DISTANCE);
		body.StatUpdateByTime(AnalyticsManagerServer.STAT_PLAYTIME);

		float playtime = body.StatGet(AnalyticsManagerServer.STAT_PLAYTIME);
		float pk       = body.StatGet(AnalyticsManagerServer.STAT_PLAYERS_KILLED);
		float ik       = body.StatGet(AnalyticsManagerServer.STAT_INFECTED_KILLED);
		float dist     = body.StatGet(AnalyticsManagerServer.STAT_DISTANCE);
		float longest  = body.StatGet(AnalyticsManagerServer.STAT_LONGEST_SURVIVOR_HIT);

		skull.SetDeadPlayerData(name, playtime, pk, ik, dist, longest);
	}

	void SpawnDeerSkeleton(ActionData action_data, EntityAI body)
	{
		if (!GetGame().IsServer() || !body)
			return;

		string skelType;
		float yOffset;

		if (body.IsKindOf("Animal_CervusElaphusF"))
		{
			skelType = "StaticObj_Forest_DeerSkeleton_Dam";
			yOffset = 0.25;
		}
		else if (body.IsKindOf("Animal_CervusElaphus"))
		{
			skelType = "StaticObj_Forest_DeerSkeleton_Full";
			yOffset = 0.5;
		}
		else if (body.IsKindOf("Animal_CapreolusCapreolus") || body.IsKindOf("Animal_CapreolusCapreolusF"))
		{
			skelType = "StaticObj_Forest_DeerSkeleton_Pile";
			yOffset = 0.05;
		}
		else
			return;

		vector pos = body.GetPosition();
		pos[1] = GetGame().SurfaceY(pos[0], pos[2]) + yOffset;

		Object skel = GetGame().CreateObjectEx(skelType, pos, ECE_PLACE_ON_SURFACE);
		if (!skel)
			return;

		skel.PlaceOnSurface();
		vector skelPos = skel.GetPosition();

		vector normal = GetGame().SurfaceGetNormal(skelPos[0], skelPos[2]);

		vector dir = body.GetDirection();
		dir[1] = 0;
		if (dir.LengthSq() < 0.0001)
			dir = "1 0 0";
		dir.Normalize();

		vector right = dir * normal;
		right.Normalize();
		vector forward = normal * right;
		forward.Normalize();

		vector mat[3];
		mat[0] = forward;
		mat[1] = normal;
		mat[2] = right;

		vector angles = Math3D.MatrixToAngles(mat);

		skel.SetOrientation(angles);
		skel.SetPosition(skelPos);
	}

	void HandleInfectedBody(ActionData action_data)
	{
		DayZInfected body;
		if (!Class.CastTo(body, action_data.m_Target.GetObject()))
			return;

		for (int s = 0; s < body.GetInventory().AttachmentCount(); s++)
		{
			EntityAI att = body.GetInventory().GetAttachmentFromIndex(s);
			if (att)
				body.GetInventory().DropEntity(InventoryMode.SERVER, body, att);
		}
		
		SpawnZombieClothing(action_data, body);
		SpawnInfectedSkeleton(action_data, body);
	}

	override void SpawnItems(ActionData action_data)
	{
		EntityAI body = EntityAI.Cast(action_data.m_Target.GetObject());
		if (!body)
			return;

		string cfg_animal_class_path = "cfgVehicles " + body.GetType() + " Skinning ";
		vector bodyPosition = body.GetPosition();

		if (!g_Game.ConfigIsExisting(cfg_animal_class_path))
			return;

		int child_count = g_Game.ConfigGetChildrenCount(cfg_animal_class_path);

		string item_to_spawn;
		string cfg_skinning_organ_class;

		for (int i1 = 0; i1 < child_count; i1++)
		{
			g_Game.ConfigGetChildName(cfg_animal_class_path, i1, cfg_skinning_organ_class);
			cfg_skinning_organ_class = cfg_animal_class_path + cfg_skinning_organ_class + " ";
			g_Game.ConfigGetText(cfg_skinning_organ_class + "item", item_to_spawn);

			if (item_to_spawn == "")
				continue;

			int item_count = g_Game.ConfigGetInt(cfg_skinning_organ_class + "count");

			for (int i2 = 0; i2 < item_count; i2++)
			{
				vector spawnPos = bodyPosition;

				ItemBase spawn_result = CreateOrgan(action_data.m_Player, spawnPos, item_to_spawn, cfg_skinning_organ_class, action_data.m_MainItem);

				Edible_Base edible;
				if (spawn_result && body.IsInherited(DayZInfected) && Class.CastTo(edible, spawn_result) && edible.IsKindOf("HumanSteakMeat"))
				{
					edible.GetFoodStage().ChangeFoodStage(FoodStageType.ROTTEN);
					edible.Synchronize();
				}
			}
		}
	}
}

static const int RUCKHUMANSKULL_RPC_NAME = -91234560;

class RuckHumanSkull extends ItemBase
{
	string m_DeadPlayerName = "";
	bool   m_HasReceivedData;

	float m_Playtime;
	float m_PlayersKilled;
	float m_InfectedKilled;
	float m_Distance;
	float m_LongestShot;

	void RuckHumanSkull()
	{
		m_HasReceivedData = false;

		RegisterNetSyncVariableBool("m_HasReceivedData");

		RegisterNetSyncVariableFloat("m_Playtime",       0, 1e9, 0);
		RegisterNetSyncVariableFloat("m_PlayersKilled",  0, 1e6, 0);
		RegisterNetSyncVariableFloat("m_InfectedKilled", 0, 1e6, 0);
		RegisterNetSyncVariableFloat("m_Distance",       0, 1e9, 0);
		RegisterNetSyncVariableFloat("m_LongestShot",    0, 1e6, 1);
	}
	
	override void DeferredInit()
	{
		super.DeferredInit();

		if (GetGame().IsClient() && !m_HasReceivedData)
		{
			RPCSingleParam(RUCKHUMANSKULL_RPC_NAME, new Param1<bool>(true), true, NULL);
		}
	}
			
	void SetDeadPlayerData(string name, float playtime, float pk, float ik, float dist, float longest)
	{
		if (!GetGame().IsServer())
			return;

		m_DeadPlayerName  = name;
		m_Playtime        = playtime;
		m_PlayersKilled   = pk;
		m_InfectedKilled  = ik;
		m_Distance        = dist;
		m_LongestShot     = longest;

		m_HasReceivedData = false;

		SetSynchDirty();
	}
	
	override void OnRPC(PlayerIdentity sender, int rpc_type, ParamsReadContext ctx)
	{
		super.OnRPC(sender, rpc_type, ctx);

		if (rpc_type != RUCKHUMANSKULL_RPC_NAME)
			return;

		if (GetGame().IsServer())
		{
			Param1<bool> req = new Param1<bool>(false);
			if (!ctx.Read(req) || !sender)
				return;

			RPCSingleParam(RUCKHUMANSKULL_RPC_NAME, new Param1<string>(m_DeadPlayerName), true, sender);
			return;
		}

		if (GetGame().IsClient())
		{
			Param1<string> p = new Param1<string>("");
			if (!ctx.Read(p))
				return;

			m_DeadPlayerName = p.param1;
			m_HasReceivedData = true;
			return;
		}
	}

	override bool NameOverride(out string output)
	{
		output = "Human Skull";
		return true;
	}

	override bool DescriptionOverride(out string output)
	{
		string who = m_DeadPlayerName;
		if (who == "")
			who = "Unknown";

		ref FullTimeData t = new FullTimeData();
		TimeConversions.ConvertSecondsToFullTime(m_Playtime, t);

		output  = "-" + who + "-";
		output += "\n\n-Survivor Stats-";
		output += "\nTime Alive: " + t.FormatedNonZero();
		output += "\nLives Taken: " + StatValue(m_PlayersKilled);
		output += "\nUndead Put Down: " + StatValue(m_InfectedKilled);
		output += "\nLand Traveled On Foot: " + StatDistance(m_Distance);
		output += "\nBest Shot!: " + StatDistance(m_LongestShot, true);

		return true;
	}

	override bool OnStoreLoad(ParamsReadContext ctx, int version)
	{
		if (!super.OnStoreLoad(ctx, version))
			return false;

		if (!ctx.Read(m_DeadPlayerName))  m_DeadPlayerName = "";
		if (!ctx.Read(m_Playtime))       m_Playtime = 0;
		if (!ctx.Read(m_PlayersKilled))  m_PlayersKilled = 0;
		if (!ctx.Read(m_InfectedKilled)) m_InfectedKilled = 0;
		if (!ctx.Read(m_Distance))       m_Distance = 0;
		if (!ctx.Read(m_LongestShot))    m_LongestShot = 0;

		m_HasReceivedData = false;

		if (GetGame().IsServer())
			SetSynchDirty();

		return true;
	}

	override void OnStoreSave(ParamsWriteContext ctx)
	{
		super.OnStoreSave(ctx);

		ctx.Write(m_DeadPlayerName);
		ctx.Write(m_Playtime);
		ctx.Write(m_PlayersKilled);
		ctx.Write(m_InfectedKilled);
		ctx.Write(m_Distance);
		ctx.Write(m_LongestShot);
	}


	protected string StatDistance(float total_distance, bool meters_only = false)
	{
		if (total_distance > 0)
		{
			string distanceString;

			float kilometers = total_distance * 0.001;
			kilometers = Math.Round(kilometers);
			if (kilometers >= 10 && !meters_only)
			{
				distanceString = StatValue(kilometers, true) + " #STR_distance_unit_abbrev_kilometer_0";
			}
			else
			{
				distanceString = StatValue(total_distance) + " #STR_distance_unit_abbrev_meter_0";
			}

			return distanceString;
		}

		return "0 #STR_distance_unit_abbrev_meter_0";
	}

	protected string StatValue(float total_value, bool show_decimals = false)
	{
		if (total_value > 0)
		{
			string resultStr;

			int total_value_int = total_value;
			string number_str = total_value_int.ToString();

			if (total_value >= 1000)
			{
				int count;
				int first_length = number_str.Length() % 3;
				if (first_length > 0)
					count = 3 - first_length;

				for (int i = 0; i < number_str.Length(); ++i)
				{
					resultStr += number_str.Get(i);
					count++;

					if (count >= 3)
					{
						resultStr += " ";
						count = 0;
					}
				}
			}
			else
			{
				resultStr = number_str;
			}

			if (show_decimals)
			{
				string total_value_str = total_value.ToString();
				int decimal_idx = total_value_str.IndexOf(".");
				if (decimal_idx > -1)
				{
					resultStr.TrimInPlace();
					resultStr += total_value_str.Substring(decimal_idx, total_value_str.Length() - decimal_idx);
				}
			}

			return resultStr;
		}

		return "0";
	}
}