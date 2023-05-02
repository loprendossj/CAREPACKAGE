class CJ_Key_Base : Inventory_Base
{
	static ref LCToolsConfig m_LootChestsConfig;	
	override void SetActions()
	{
		super.SetActions();

		AddAction(ActionUnlockCJChest);
		
	}
	
	override string GetDisplayName()
	{
		if (GetKeyDisplayNameOrDesc(GetKeyIndex(this.ClassName()), 0) == "")
			return ConfigGetString("displayName");
		return GetKeyDisplayNameOrDesc(GetKeyIndex(this.ClassName()),0);
	}
	
	override string GetTooltip()
	{
		if (GetKeyDisplayNameOrDesc(GetKeyIndex(this.ClassName()), 1) == "")
			return ConfigGetString("descriptionShort");
		return GetKeyDisplayNameOrDesc(GetKeyIndex(this.ClassName()), 1);
	}
	
	int GetKeyIndex(string keyname)
	{
		int index = -1;
		m_LootChestsConfig = GetDayZGame().GetLootChestsToolsConfig();
		if (!m_LootChestsConfig)
			return index;
		for (int i = 0; i < m_LootChestsConfig.LCTools.Count(); i++)
		{
			if (keyname == m_LootChestsConfig.LCTools.Get(i).name)
			{
				index = i;
			}
		}
		
		return index;
	}
	
	string GetKeyDisplayNameOrDesc(int index, int type)
	{
		string desc;
		
		m_LootChestsConfig = GetDayZGame().GetLootChestsToolsConfig();
		if (!m_LootChestsConfig)
			return "";
		desc = m_LootChestsConfig.LCTools.Get(index).desc;
		if (!desc)
		{
			return "";
		}
		TStringArray loc = new TStringArray;
		desc.Split( "|", loc );
		return (loc.Get(type));
	}

}

class CJ_Key1 : CJ_Key_Base {}
class CJ_Key2 : CJ_Key_Base {}
class CJ_Key3 : CJ_Key_Base {}
class CJ_Key4 : CJ_Key_Base {}
class CJ_Key5 : CJ_Key_Base {}
class CJ_Key6 : CJ_Key_Base {}
class CJ_Key7 : CJ_Key_Base {}
class CJ_Key8 : CJ_Key_Base {}
class CJ_Key9 : CJ_Key_Base {}
class CJ_Key10 : CJ_Key_Base {}
class CJ_Key11 : CJ_Key_Base {}
class CJ_Key12 : CJ_Key_Base {}
class CJ_Key13 : CJ_Key_Base {}
class CJ_Key14 : CJ_Key_Base {}
class CJ_Key15 : CJ_Key_Base {}
class CJ_Key16 : CJ_Key_Base {}
class CJ_Key17 : CJ_Key_Base {}
class CJ_Key18 : CJ_Key_Base {}
class CJ_Key19 : CJ_Key_Base {}
class CJ_Key20 : CJ_Key_Base {}
class CJ_Key101 : CJ_Key_Base {}
class CJ_Key102 : CJ_Key_Base {}
class CJ_Key103 : CJ_Key_Base {}
class CJ_Key104 : CJ_Key_Base {}
class CJ_Key200 : CJ_Key_Base {}
class CJ_Key201 : CJ_Key_Base {}
class CJ_Key202 : CJ_Key_Base {}
class CJ_Key203 : CJ_Key_Base {}
class CJ_Key204 : CJ_Key_Base {}