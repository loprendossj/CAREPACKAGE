modded class DayZGame
{	
	protected ref LCConfig m_LootChestsConfig;
	protected ref LCToolsConfig m_LootChestsToolsConfig;

	
    void SetLootChestsConfig(LCConfig config)
    {
        m_LootChestsConfig = config;
    }

    LCConfig GetLootChestsConfig()
    {
		return m_LootChestsConfig;
    }
	
	void SetLootChestsToolsConfig(LCToolsConfig config)
    {
        m_LootChestsToolsConfig = config;
    }

    LCToolsConfig GetLootChestsToolsConfig()
    {
		return m_LootChestsToolsConfig;
    }
};