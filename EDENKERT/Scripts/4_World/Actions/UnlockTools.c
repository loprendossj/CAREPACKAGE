modded class SledgeHammer extends Inventory_Base
{
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionBreachCJChest);
		
	}
};

modded class Crowbar: Inventory_Base
{
	override void SetActions()
	{
		super.SetActions();

		AddAction(ActionBreachLockCJChest);
		
	}
};

modded class Lockpick: Inventory_Base
{
	override void SetActions()
	{
		super.SetActions();

		AddAction(ActionUnlockCJChest);
		
	}
};