class LootChestsPlace
{
    string name;
	int number;
	ref TStringArray pos;
	string keyclass;
	int openable; // 0 - keys only, 1 - keys and lockpicks, 2 - all tools
    ref TStringArray chest;
	//float spawnrate;
	float lootrandomize;
	bool light;
	ref TStringArray loot;

    void LootChestsPlace(string nam, int num, TStringArray xz, string kye, int opnb, TStringArray cont, float lrd, bool lig, TStringArray lt) 
	{
        name = nam;
		number = num;
		pos = xz;
		keyclass = kye;
		openable = opnb;
		chest = cont;
		//spawnrate = spr;
		lootrandomize = lrd;
		light = lig;
		loot = lt; 
    }
}

class LCLootCategory
{
    string name;
    ref TStringArray Loot;

    void LCLootCategory( string nam, TStringArray loot )
    {
        name = nam;
        Loot = loot;
    }
}

class LCTool
{
    string name;
    int time;
	int dmg;
	string desc;

    void LCTool( string nam, int tim, int dam, string des )
    {
        name = nam;
        time = tim;
		dmg = dam;
		desc = des;
    }
}

class LCPredefinedWeapon
{
	string defname;
	string weapon;
	string magazine;
	ref TStringArray attachments;
	string optic;
	bool opticbattery;
	
	void LCPredefinedWeapon( string def, string weap, string mag, TStringArray att, string opt, bool batt)
	{
		defname = def;
		weapon = weap;
		magazine = mag;
		attachments = att;
		optic = opt;
		opticbattery = batt;
	}
	
}

class LCConfig
{
	bool EnableDebug;
	bool DeleteLogs;
	int MaxSpareMags;
	bool RandomQuantity;
	// udelat kategorie
	ref array< ref LootChestsPlace > LootChestsLocations;
	ref array< ref LCPredefinedWeapon > LCPredefinedWeapons;
	ref array< ref LCLootCategory > LootCategories;
	void LCConfig()
	{
		LootChestsLocations = new ref array< ref LootChestsPlace >;
		LCPredefinedWeapons = new ref array< ref LCPredefinedWeapon >;
		LootCategories = new ref array< ref LCLootCategory >;
	}

}

class LootChestsConfig
{

    protected const static string m_ConfigRoot = "$profile:\\CJ_LootChests\\";

    static void LoadConfig(string configName, out LCConfig configData)
    {
        string configPath = m_ConfigRoot + configName;

        if (!FileExist(configPath))
        {
            LCLogger.Log("'" + configName + "' does not exist, creating default config");
            CreateDefaultConfig(configData);
            SaveConfig(configName, configData);
            return;
        }

        JsonFileLoader<LCConfig>.JsonLoadFile(configPath, configData);
        LCLogger.Log("'" + configName + "' found, loading existing config");

    }

    protected static void SaveConfig(string configName, LCConfig configData)
    {
        string configPath = m_ConfigRoot + configName;

        if (!FileExist(m_ConfigRoot))
        {
            LCLogger.Log("'" + m_ConfigRoot + "' does not exist, creating directory");
            MakeDirectory(m_ConfigRoot);
        }

        JsonFileLoader<LCConfig>.JsonSaveFile(configPath, configData);
    }
	
	static void UpgradeConfig(string configName, out LCConfig configData)
    {
        string configPath = m_ConfigRoot + configName;

        if (!FileExist(configPath))
        {
            LCLogger.Log("'"  + configName + "' does not exist, creating default config");
            CreateDefaultConfig(configData);
            SaveConfig(configName, configData);
            return;
        }
		JsonFileLoader<LCConfig>.JsonLoadFile(configPath, configData);
		
		//upgrades...
			
        JsonFileLoader<LCConfig>.JsonSaveFile(configPath, configData);
    }

    protected static void CreateDefaultConfig(out LCConfig configData)
    {
        configData = new LCConfig();
		configData.EnableDebug = false;
		configData.DeleteLogs = false;
		configData.MaxSpareMags = 3;
		configData.RandomQuantity = false;
		configData.LootChestsLocations.Insert( new LootChestsPlace("Tisy Headquarter 1st Floor", 1, {"1682.076172 452.607544 14221.965820|-17 0 0", "1676.587280 452.601898 14216.867188|-107 0 0", "1685.815186 452.601898 14207.984375|164 0 0", "1679.410400 452.601898 14208.116211|-107 0 0", "1688.860352 453.277802 14208.918945|167 0 0", "1694.700806 452.601898 14213.243164|74 0 0", "1686.572998 452.601898 14223.329102|73 0 0", "1687.903076 452.601898 14223.464844|-106 0 0", "1682.593018 452.601898 14218.558594|0 0 0"}, "CJ_Key1", 0, {"CJ_LootChest_Brown_Small", "CJ_LootChest_Brown_Medium", "CJ_LootChest_Brown_Large"}, 0.0, false, {"LC_Table_Weapons_1", "LC_Table_Weapons_2",  "NailBox", "NailBox", "NailBox", "CombatKnife", "Rag", "HandSaw", "Hammer"} ) );
		configData.LootChestsLocations.Insert( new LootChestsPlace("Tisy Headquarter 2nd Floor", 1, {"1680.452637 456.617462 14221.413086|-16.999992 0 0", "1677.494141 456.617462 14214.438477|-106.999557 0 0", "1679.578125 456.617462 14218.459961|72.999779 0 0", "1676.767212 456.617462 14220.083008|-39.999939 0 0", "1684.607544 456.617462 14208.651367|69.999794 0 0", "1687.046753 456.617462 14210.420898|17.999992 0 0", "1693.652954 456.617462 14210.448242|162.999771 0 0", "1691.022583 456.617462 14221.329102|162.999771 0 0"}, "CJ_Key2", 1, {"CJ_LootChest_Olive_Small", "CJ_LootChest_Olive_Medium", "CJ_LootChest_Olive_Large"}, 0.5, false, {"LC_Table_Weapons_2", "LC_Table_Magazines_1", "LC_Table_Magazines_2", "BandageDressing", "NVGHeadstrap", "TTSKOPants", "TTsKOJacket_Camo", "TacticalBaconCan", "NVGoggles", "LC_predefined_SVD"} ) );
		configData.LootChestsLocations.Insert( new LootChestsPlace("Tisy Headquarter Bunker", 1, {"1693.641968 448.389740 14206.955078|162.999771 0 0", "1686.152344 448.389740 14206.158203|-15.999994 0 0", "1680.582642 448.389740 14206.187500|-153.999619 0 0", "1683.969604 448.389740 14213.902344|-105.999565 0 0", "1687.283569 448.389740 14211.497070|-15.999994 0 0", "1689.146851 448.389740 14208.608398|164.999847 0 0", "1690.969727 448.389740 14210.279297|-134.999619 0 0"}, "CJ_Key3", 2, {"CJ_LootChest_Tan_Small", "CJ_LootChest_Tan_Medium", "CJ_LootChest_Tan_Large"}, 0.9, false, {"LC_Table_Weapons_1", "LC_Table_Weapons_2", "LC_Table_Magazines_1", "LC_Table_Magazines_2", "LC_Table_Attachments", "LC_predefined_AKM", "LC_predefined_M4", "AmmoBox_545x39_20Rnd", "AmmoBox_545x39_20Rnd", "AmmoBox_545x39_20Rnd", "AmmoBox_762x39_20Rnd", "AmmoBox_762x39_20Rnd", "AmmoBox_762x39_20Rnd", "AmmoBox_762x39_20Rnd", "AmmoBox_762x39_20Rnd", "BandageDressing", "WeaponCleaningKit"} ) );
		
		configData.LCPredefinedWeapons.Insert(new LCPredefinedWeapon("LC_predefined_SVD", "SVD", "Mag_SVD_10Rnd", { "AK_Suppressor" }, "PSO11Optic", true ));
		configData.LCPredefinedWeapons.Insert(new LCPredefinedWeapon("LC_predefined_VSS", "VSS", "Mag_VSS_10Rnd", { "AK_Suppressor" }, "KobraOptic", true ));
		configData.LCPredefinedWeapons.Insert(new LCPredefinedWeapon("LC_predefined_Tundra", "Winchester70", "", { "" }, "HuntingOptic", false ));
		configData.LCPredefinedWeapons.Insert(new LCPredefinedWeapon("LC_predefined_Blaze", "B95", "", { "" }, "HuntingOptic", false ));
		configData.LCPredefinedWeapons.Insert(new LCPredefinedWeapon("LC_predefined_M4", "M4A1", "Mag_STANAG_30Rnd", { "M4_Suppressor", "M4_RISHndgrd_Black" ,"M4_MPBttstck_Black" }, "ACOGOptic_6x", false ));
		configData.LCPredefinedWeapons.Insert(new LCPredefinedWeapon("LC_predefined_SKS", "SKS", "", { "" }, "PUScopeOptic", false ));
		configData.LCPredefinedWeapons.Insert(new LCPredefinedWeapon("LC_predefined_CZ527", "CZ527", "Mag_CZ527_5rnd", { "" }, "HuntingOptic", false ));
		configData.LCPredefinedWeapons.Insert(new LCPredefinedWeapon("LC_predefined_AKM", "AKM", "Mag_AKM_30Rnd", { "AK_Suppressor", "AK_WoodHndgrd" ,"AK_WoodBttstck" }, "KobraOptic", true ));
		configData.LCPredefinedWeapons.Insert(new LCPredefinedWeapon("LC_predefined_AK74", "AK74", "Mag_AK74_30Rnd", { "AK_Suppressor", "AK74_Hndgrd", "AK74_WoodBttstck" }, "KobraOptic", true ));
		configData.LCPredefinedWeapons.Insert(new LCPredefinedWeapon("LC_predefined_AK101", "AK101", "Mag_AK101_30Rnd", { "AK_Suppressor", "AK_PlasticHndgrd", "AK_PlasticBttstck" }, "KobraOptic", true ));
		configData.LCPredefinedWeapons.Insert(new LCPredefinedWeapon("LC_predefined_FAL", "FAL", "Mag_FAL_20Rnd", { "Fal_OeBttstck" }, "ACOGOptic", false ));
		configData.LCPredefinedWeapons.Insert(new LCPredefinedWeapon("LC_predefined_MP5", "MP5k", "Mag_MP5_30Rnd", { "MP5_Compensator", "MP5k_StockBttstck", "MP5_RailHndgrd" }, "ReflexOptic", true ));
		
		configData.LootCategories.Insert(new LCLootCategory("LC_Table_Weapons_1", { "Glock19", "Colt1911", "MakarovIJ70"} ));
		configData.LootCategories.Insert(new LCLootCategory("LC_Table_Weapons_2", { "LC_predefined_M4", "LC_predefined_AKM", "LC_predefined_MP5", "LC_predefined_SVD", "LC_predefined_VSS", "LC_predefined_Tundra", "LC_predefined_Blaze", "LC_predefined_SKS", "LC_predefined_CZ527", "LC_predefined_AK74", "LC_predefined_AK101", "LC_predefined_FAL"} ));
		configData.LootCategories.Insert(new LCLootCategory("LC_Table_Magazines_1", { "Mag_MP5_30Rnd", "Mag_AK74_30Rnd", "Mag_CZ527_5rnd"} ));
		configData.LootCategories.Insert(new LCLootCategory("LC_Table_Magazines_2", { "Mag_STANAG_30Rnd", "Mag_AKM_30Rnd", "Mag_FAL_20Rnd"} ));
		configData.LootCategories.Insert(new LCLootCategory("LC_Table_Attachments", { "AK_Suppressor", "M4_Suppressor", "ACOGOptic"} ));
		configData.LootCategories.Insert(new LCLootCategory("LC_Table_Ammo", { "AmmoBox_545x39_20Rnd"} ));
	}
}

class LCToolsConfig
{
	ref array< ref LCTool > LCTools;
	void LCToolsConfig()
	{
		LCTools = new ref array< ref LCTool >;
	}

}

class LootChestsToolsConfig
{

    protected const static string m_ConfigRoot = "$profile:\\CJ_LootChests\\";

    static void LoadConfig(string configName, out LCToolsConfig configData)
    {
        string configPath = m_ConfigRoot + configName;

        if (!FileExist(configPath))
        {
            LCLogger.Log("'" + configName + "' does not exist, creating default config");
            CreateDefaultConfig(configData);
            SaveConfig(configName, configData);
            return;
        }

        JsonFileLoader<LCToolsConfig>.JsonLoadFile(configPath, configData);
        LCLogger.Log("'" + configName + "' found, loading existing config");

    }

    protected static void SaveConfig(string configName, LCToolsConfig configData)
    {
        string configPath = m_ConfigRoot + configName;

        if (!FileExist(m_ConfigRoot))
        {
            LCLogger.Log("'" + m_ConfigRoot + "' does not exist, creating directory");
            MakeDirectory(m_ConfigRoot);
        }

        JsonFileLoader<LCToolsConfig>.JsonSaveFile(configPath, configData);
    }
	
	static void UpgradeConfig(string configName, out LCToolsConfig configData)
    {
        string configPath = m_ConfigRoot + configName;

        if (!FileExist(configPath))
        {
            LCLogger.Log("'"  + configName + "' does not exist, creating default config");
            CreateDefaultConfig(configData);
            SaveConfig(configName, configData);
            return;
        }
		JsonFileLoader<LCToolsConfig>.JsonLoadFile(configPath, configData);
		
		//upgrades...
			
        JsonFileLoader<LCToolsConfig>.JsonSaveFile(configPath, configData);
    }

    protected static void CreateDefaultConfig(out LCToolsConfig configData)
    {
        configData = new LCToolsConfig();
	
		configData.LCTools.Insert(new ref LCTool("SledgeHammer", 5, 50, ""));
		configData.LCTools.Insert(new ref LCTool("Crowbar", 30, 25, ""));
		configData.LCTools.Insert(new ref LCTool("Lockpick", 60, 25, ""));
		configData.LCTools.Insert(new ref LCTool("CJ_Key1", 3, 10, "Black Key|This key will open a military crate inside the Tisy Headquarters Building!"));
		configData.LCTools.Insert(new ref LCTool("CJ_Key2", 3, 10, "Military Key|This key will open a military crate inside the Tisy Headquarters Building!"));
		configData.LCTools.Insert(new ref LCTool("CJ_Key3", 3, 10, "Tisy HQ Key|This key will open a military crate inside the Tisy Headquarters Building!"));
		configData.LCTools.Insert(new ref LCTool("CJ_Key4", 3, 10, "NAME of KEY|DESCRIPTION of KEY"));
		configData.LCTools.Insert(new ref LCTool("CJ_Key5", 3, 10, ""));
		configData.LCTools.Insert(new ref LCTool("CJ_Key6", 3, 10, ""));
		configData.LCTools.Insert(new ref LCTool("CJ_Key7", 3, 10, "Red Key|This red key will open a crate hidden somewhere at the military airfield."));
		configData.LCTools.Insert(new ref LCTool("CJ_Key8", 3, 10, ""));
		configData.LCTools.Insert(new ref LCTool("CJ_Key9", 3, 10, ""));
		configData.LCTools.Insert(new ref LCTool("CJ_Key10", 3, 10, ""));
		configData.LCTools.Insert(new ref LCTool("CJ_Key11", 3, 10, ""));
		configData.LCTools.Insert(new ref LCTool("CJ_Key12", 3, 10, ""));
		configData.LCTools.Insert(new ref LCTool("CJ_Key101", 3, 10, ""));
		configData.LCTools.Insert(new ref LCTool("CJ_Key102", 3, 10, ""));
		configData.LCTools.Insert(new ref LCTool("CJ_Key103", 3, 10, ""));
		configData.LCTools.Insert(new ref LCTool("CJ_Key200", 3, 10, ""));
		configData.LCTools.Insert(new ref LCTool("CJ_Key201", 3, 10, ""));
		configData.LCTools.Insert(new ref LCTool("CJ_Key202", 3, 10, ""));
		configData.LCTools.Insert(new ref LCTool("CJ_Key203", 3, 10, ""));
		configData.LCTools.Insert(new ref LCTool("CJ_Key204", 3, 10, ""));
		
	}
}