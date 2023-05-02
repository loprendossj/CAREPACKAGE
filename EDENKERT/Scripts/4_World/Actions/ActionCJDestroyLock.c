class ActionCJDestroyLockCB : ActionContinuousBaseCB
{
    static ref LCToolsConfig m_LootChestsConfig;
	override void CreateActionComponent()
    {
        m_LootChestsConfig = GetDayZGame().GetLootChestsToolsConfig();	
		int time = UATimeSpent.LOCK;
		for(int i = 0; i < m_LootChestsConfig.LCTools.Count(); i++)
		{
			//Print("config name " + m_LootChestsConfig.LCTools.Get(i).name + " item name " + m_ActionData.m_MainItem.ClassName());
			if(m_LootChestsConfig.LCTools.Get(i).name == m_ActionData.m_MainItem.ClassName())
			{
				time = m_LootChestsConfig.LCTools.Get(i).time;
				//Print("used tool " + m_LootChestsConfig.LCTools.Get(i).name);
			}
				
		}		
		m_ActionData.m_ActionComponent = new CAContinuousTime(time);

    }
};

class ActionCJDestroyLock: ActionContinuousBase
{	
	
	void ActionCJDestroyLock()
	{
		m_CallbackClass = ActionCJDestroyLockCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
	}
	
	override void CreateConditionComponents()
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTNone;
	}
	
	override bool CanBeUsedInVehicle()
	{
		return false;
	}
};