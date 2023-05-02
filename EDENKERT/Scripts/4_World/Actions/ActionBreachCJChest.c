class ActionBreachCJChestCB : ActionContinuousBaseCB
{
    static ref LCToolsConfig m_LootChestsConfig;
	override void CreateActionComponent()
    {
    	m_LootChestsConfig = GetDayZGame().GetLootChestsToolsConfig();	
		int time;
		for(int i = 0; i < m_LootChestsConfig.LCTools.Count(); i++)
		{
			if(m_LootChestsConfig.LCTools.Get(i).name == "SledgeHammer")
				time = m_LootChestsConfig.LCTools.Get(i).time;
		}		
		m_ActionData.m_ActionComponent = new CAContinuousTime(time);
    }
}

class ActionBreachCJChest : ActionContinuousBase

{
    static ref LCToolsConfig m_LootChestsConfig;
	void ActionBreachCJChest()
    {
        m_CallbackClass = ActionBreachCJChestCB;
        m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_MINEROCK;
		m_FullBody = true;
        m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT;
		m_SpecialtyWeight = UASoftSkillsWeight.ROUGH_HIGH;

    }

    override void CreateConditionComponents()
    {
       	m_ConditionItem = new CCINonRuined;
    	m_ConditionTarget = new CCTNone;
		//m_ConditionTarget = new CCTCursor(UAMaxDistances.DEFAULT);

    }

    override string GetText()
    {
        return "#CJLC_destroy_lock";
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
			if (chest.IsLocked() && chest.GetOpenableBy() == 2)
			{
				return true;
			}
			
		}
								
        return false;
    }
	
    override void OnFinishProgressServer(ActionData action_data)
    {
        action_data.m_Player.GetSoftSkillsManager().AddSpecialty( m_SpecialtyWeight );
		m_LootChestsConfig = GetDayZGame().GetLootChestsToolsConfig();
		int percdmg = 1;
		for(int i = 0; i < m_LootChestsConfig.LCTools.Count(); i++)
		{
			if(m_LootChestsConfig.LCTools.Get(i).name == action_data.m_MainItem.ClassName())
			{
				percdmg = m_LootChestsConfig.LCTools.Get(i).dmg;
					
			}
				
		}		
		float skillLevel = action_data.m_Player.GetSoftSkillsManager().GetSpecialtyLevel();
		float appliedDamage = action_data.m_MainItem.GetMaxHealth("", "") / 100 * percdmg ; 

		MiscGameplayFunctions.DealAbsoluteDmg(action_data.m_MainItem, appliedDamage);
		
		PlayerBase player = PlayerBase.Cast(action_data.m_Player);
		CJ_Openable_Placeable_Base chest = CJ_Openable_Placeable_Base.Cast(action_data.m_Target.GetObject());
		chest.Unlock();
		EntityAI.Cast(action_data.m_Target.GetObject()).SetHealth("", "", 0);
		ref array<EntityAI> ChestItems = new array<EntityAI>;
		if (chest.GetInventory().EnumerateInventory( InventoryTraversalType.PREORDER, ChestItems) )
		{
			for (int j=0; j < ChestItems.Count(); j++)
			{
				EntityAI entity_item = ChestItems.Get(j);

				float rndnum = Math.RandomFloatInclusive( 0.0, 1.0 );
				entity_item.SetHealth("", "", entity_item.GetMaxHealth("", "") * rndnum );
		
			}
		}
	}
	
}