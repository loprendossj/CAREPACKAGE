class ActionUnlockCJChestCB : ActionContinuousBaseCB
{
    static ref LCToolsConfig m_LootChestsConfig;
	override void CreateActionComponent()
    {
        m_LootChestsConfig = GetDayZGame().GetLootChestsToolsConfig();	
		int time;
		for(int i = 0; i < m_LootChestsConfig.LCTools.Count(); i++)
		{
			
			if(m_LootChestsConfig.LCTools.Get(i).name == m_ActionData.m_MainItem.ClassName())
			{
				time = m_LootChestsConfig.LCTools.Get(i).time;
			} else {
				time = UATimeSpent.LOCK;
			}
				
		}		
		m_ActionData.m_ActionComponent = new CAContinuousTime(time);

    }
}

class ActionUnlockCJChest : ActionCJDestroyLock

{
    static ref LCToolsConfig m_LootChestsConfig;
	void ActionUnlockCJCChest()
    {
        m_CallbackClass = ActionUnlockCJChestCB;
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
		m_FullBody = true;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
		m_SpecialtyWeight = UASoftSkillsWeight.PRECISE_HIGH;

    }

    override void CreateConditionComponents()
    {
       	m_ConditionItem = new CCINonRuined;
		//m_ConditionItem = new CCINone;
    	//m_ConditionTarget = new CCTNone;
		m_ConditionTarget = new CCTCursor(UAMaxDistances.DEFAULT);

    }

    override string GetText()
    {
        return "#unlock";
    }

    override bool ActionCondition(PlayerBase player, ActionTarget target, ItemBase item)
    {	

		m_LootChestsConfig = GetDayZGame().GetLootChestsToolsConfig();
		for(int i = 0; i < m_LootChestsConfig.LCTools.Count(); i++)
		{
			if(m_LootChestsConfig.LCTools.Get(i).name == item.ClassName())
			{
				if (m_LootChestsConfig.LCTools.Get(i).time == -1)
				{
					return false;
				}
					
			}
				
		}	
		
		if(!target)
			return false;
		
		if (!target.GetObject())
			return false;
		
		CJ_Openable_Placeable_Base chest = CJ_Openable_Placeable_Base.Cast(target.GetObject());
		if(chest)
		{
			if (chest.IsLocked())
			{
				//Print("XXXXX key class " + Entity.Cast(item).GetType() + " chest key "+ chest.GetKeyNum());
				string chestkey = "CJ_Key" + chest.GetKeyNum().ToString();
				if ((item.ClassName() == "Lockpick" && chest.GetOpenableBy() !=0 ) || Entity.Cast(item).GetType() == chestkey )
				{
					return true;
				} else {
					return false;
				}
				
			}
			
		}						
        return false;
    }
	
    override void OnFinishProgressServer(ActionData action_data)
    {
      	m_LootChestsConfig = GetDayZGame().GetLootChestsToolsConfig();
		int percdmg = 1;
		//LCLogger.Log("item in hand " + EntityAI.Cast(action_data.m_MainItem).GetType() );
		for(int i = 0; i < m_LootChestsConfig.LCTools.Count(); i++)
		{		
			if(m_LootChestsConfig.LCTools.Get(i).name == EntityAI.Cast(action_data.m_MainItem).GetType())
			{
				percdmg = m_LootChestsConfig.LCTools.Get(i).dmg;
				//LCLogger.Log("unlock " + action_data.m_MainItem.ClassName() + " dmg "+ percdmg );	
			}
				
		}
		action_data.m_Player.GetSoftSkillsManager().AddSpecialty( m_SpecialtyWeight );
		
		float skillLevel = action_data.m_Player.GetSoftSkillsManager().GetSpecialtyLevel();
		float appliedDamage = EntityAI.Cast(action_data.m_MainItem).GetMaxHealth("", "") / 100 * percdmg ; 
		MiscGameplayFunctions.DealAbsoluteDmg(action_data.m_MainItem, appliedDamage);
		
		CJ_Openable_Placeable_Base chest = CJ_Openable_Placeable_Base.Cast(action_data.m_Target.GetObject());
		chest.Unlock();
	}
}