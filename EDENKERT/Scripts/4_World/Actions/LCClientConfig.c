class LCClientConfig
{
	protected static ref LCClientConfig Instance;
	protected PlayerBase player;
	static ref LCToolsConfig m_LootChestsToolsConfig;

	void LCClientConfig()
	{
		m_LootChestsToolsConfig = GetDayZGame().GetLootChestsToolsConfig();
		GetRPCManager().AddRPC( "CJ_LootChests", "SyncConfig", this, SingleplayerExecutionType.Server );
		ConfigRequest();
	}

	static LCClientConfig GetInstance()
	{
		if (!Instance)
        {
            Instance = new LCClientConfig();
        }
		return Instance;
	}
	
	static void ClearInstance()
	{
		Instance = null;
	}
	
	void ConfigRequest()
	{
		Print("Multiplayer game " + GetGame().IsMultiplayer());
		if(!GetGame().IsMultiplayer()) return; //fix Community Offline Mode - RPC is disabled
		GameOptions gameOptions = new GameOptions;
		ListOptionsAccess lang = ListOptionsAccess.Cast( gameOptions.GetOptionByType( AT_OPTIONS_LANGUAGE ) );
		string currentLang;
		lang.GetItemText(lang.GetIndex(), currentLang);
		Print( "Requesting config " );
		GetRPCManager().SendRPC("CJ_LootChests", "RequestConfig",  new Param1<string>( currentLang ), true);
	}
	
	void SyncConfig( CallType type, ref ParamsReadContext ctx, ref PlayerIdentity sender, ref Object target )
    {
        Param1< LCToolsConfig > data;
        if ( !ctx.Read( data ) ) return;
        
        if( type == CallType.Client )
        {
			//prenos konfigu
			Print( "Client received config" );
			m_LootChestsToolsConfig = data.param1;
			//Print("XXXXXX config " + m_LootChestsToolsConfig);
			GetDayZGame().SetLootChestsToolsConfig(m_LootChestsToolsConfig);
		}
	}
	
};