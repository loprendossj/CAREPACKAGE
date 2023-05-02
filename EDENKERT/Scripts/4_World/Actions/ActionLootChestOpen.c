class ActionMilitaryLootChestOpen: ActionInteractBase
{
	void ActionMilitaryLootChestOpen()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_OPENDOORFW;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
		m_HUDCursorIcon = CursorIcons.OpenDoors;
	}

	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTNone;
	}

	override string GetText()
	{
		return "#open";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if( !target ) return false;

		if(!IsInReach(player, target, CJ_UAConstants.CJ_DISTANCE_DEFAULT)) return false;

		string leverSelection = target.GetObject().GetActionComponentName(target.GetComponentIndex());
		if(leverSelection && leverSelection == "lever")
			return false;		
		
		//ItemBase building = ItemBase.Cast(target.GetObject());
		CJ_Openable_Placeable_Base building = CJ_Openable_Placeable_Base.Cast(target.GetObject());
		if(building)
		{
			if (!building.IsLocked())
			{
				return !building.IsOpen();
			}
			
		}
		return false;
	}
	
	override void OnStartServer( ActionData action_data )
	{
		CJ_Openable_Placeable_Base building = CJ_Openable_Placeable_Base.Cast(action_data.m_Target.GetObject());
		if(building)
		{	
			building.Open();
			LCLogger.Log("Player " + action_data.m_Player.GetIdentity().GetName() + " has open a military lootchest at the " + building.GetLocation() + " on coordinates " + building.GetPosition());
			return;
		}
		
	}
};

class ActionWoodenLootChestOpen: ActionInteractBase
{
	void ActionWoodenLootChestOpen()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_OPENDOORFW;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
		m_HUDCursorIcon = CursorIcons.OpenDoors;
	}

	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTNone;
	}

	override string GetText()
	{
		return "#open";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if( !target ) return false;

		if(!IsInReach(player, target, CJ_UAConstants.CJ_DISTANCE_DEFAULT)) return false;

		string leverSelection = target.GetObject().GetActionComponentName(target.GetComponentIndex());
		if(leverSelection && leverSelection == "lever")
			return false;		
		
		//ItemBase building = ItemBase.Cast(target.GetObject());
		CJ_Openable_Placeable_Base building = CJ_Openable_Placeable_Base.Cast(target.GetObject());
		if(building)
		{
			if (!building.IsLocked())
			{
				return !building.IsOpen();
			}
			
		}
		return false;
	}
	
	
	override void OnStartServer( ActionData action_data )
	{
		CJ_Openable_Placeable_Base building = CJ_Openable_Placeable_Base.Cast(action_data.m_Target.GetObject());
		if(building)
		{	
			building.Open();
			LCLogger.Log("Player " + action_data.m_Player.GetIdentity().GetName() + " has open a wooden lootchest at the " + building.GetLocation() + " on coordinates " + building.GetPosition());
			return;
		}
		
	}
};

class ActionWoodenAmmoLootChestOpen: ActionInteractBase
{
	void ActionWoodenAmmoLootChestOpen()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_OPENDOORFW;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
		m_HUDCursorIcon = CursorIcons.OpenDoors;
	}

	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTNone;
	}

	override string GetText()
	{
		return "#open";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if( !target ) return false;

		if(!IsInReach(player, target, CJ_UAConstants.CJ_DISTANCE_DEFAULT)) return false;

		string leverSelection = target.GetObject().GetActionComponentName(target.GetComponentIndex());
		if(leverSelection && leverSelection == "lever")
			return false;		
		
		//ItemBase building = ItemBase.Cast(target.GetObject());
		CJ_Openable_Placeable_Base building = CJ_Openable_Placeable_Base.Cast(target.GetObject());
		if(building)
		{
			if (!building.IsLocked())
			{
				return !building.IsOpen();
			}
			
		}
		return false;
	}
	
	
	override void OnStartServer( ActionData action_data )
	{
		CJ_Openable_Placeable_Base building = CJ_Openable_Placeable_Base.Cast(action_data.m_Target.GetObject());
		if(building)
		{	
			building.Open();
			LCLogger.Log("Player " + action_data.m_Player.GetIdentity().GetName() + " has open a ammunition lootchest at the " + building.GetLocation() + " on coordinates " + building.GetPosition());
			return;
		}
		
	}
};

class ActionSafeLootChestOpen: ActionInteractBase
{
	void ActionSafeLootChestOpen()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_OPENDOORFW;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
		m_HUDCursorIcon = CursorIcons.OpenDoors;
	}

	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTNone;
	}

	override string GetText()
	{
		return "#open";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if( !target ) return false;

		if(!IsInReach(player, target, CJ_UAConstants.CJ_DISTANCE_DEFAULT)) return false;

		string leverSelection = target.GetObject().GetActionComponentName(target.GetComponentIndex());
		if(leverSelection && leverSelection == "lever")
			return false;		
		
		//ItemBase building = ItemBase.Cast(target.GetObject());
		CJ_Openable_Placeable_Base building = CJ_Openable_Placeable_Base.Cast(target.GetObject());
		if(building)
		{
			if (!building.IsLocked())
			{
				return !building.IsOpen();
			}
			
		}
		return false;
	}
	
	
	override void OnStartServer( ActionData action_data )
	{
		CJ_Openable_Placeable_Base building = CJ_Openable_Placeable_Base.Cast(action_data.m_Target.GetObject());
		if(building)
		{	
			building.Open();
			LCLogger.Log("Player " + action_data.m_Player.GetIdentity().GetName() + " has open a safe at the " + building.GetLocation() + " on coordinates " + building.GetPosition());
			return;
		}
		
	}
};

class ActionRegisterLootChestOpen: ActionInteractBase
{
	void ActionRegisterLootChestOpen()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_OPENDOORFW;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
		m_HUDCursorIcon = CursorIcons.OpenDoors;
	}

	override void CreateConditionComponents()  
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTNone;
	}

	override string GetText()
	{
		return "#open";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if( !target ) return false;

		if(!IsInReach(player, target, CJ_UAConstants.CJ_DISTANCE_DEFAULT)) return false;

		string leverSelection = target.GetObject().GetActionComponentName(target.GetComponentIndex());
		if(leverSelection && leverSelection == "lever")
			return false;		
		
		//ItemBase building = ItemBase.Cast(target.GetObject());
		CJ_Openable_Placeable_Base building = CJ_Openable_Placeable_Base.Cast(target.GetObject());
		if(building)
		{
			if (!building.IsLocked())
			{
				return !building.IsOpen();
			}
			
		}
		return false;
	}
	
	
	override void OnStartServer( ActionData action_data )
	{
		CJ_Openable_Placeable_Base building = CJ_Openable_Placeable_Base.Cast(action_data.m_Target.GetObject());
		if(building)
		{	
			building.Open();
			LCLogger.Log("Player " + action_data.m_Player.GetIdentity().GetName() + " has open a cash register at the " + building.GetLocation() + " on coordinates " + building.GetPosition());
			return;
		}
		
	}
};