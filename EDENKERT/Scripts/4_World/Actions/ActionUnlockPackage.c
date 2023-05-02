class ActionUnlockPackage: ActionInteractBase
{
	void ActionUnlockPackage()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
	}

	override string GetText()
	{
		return "#open";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if ( !target ) return false;
		
		CarePackage_base Package;
		if( Class.CastTo(Package, target.GetObject()) )
		{
			return Package.IsPackageLocked();
		}
		
		return false;
	}
	
	override void OnStartServer( ActionData action_data )
	{
		CarePackage_base Package = CarePackage_base.Cast(action_data.m_Target.GetObject());
		if(Package)
		{	
			Package.UnlockPackage();
			return;
		}
	}
};



