modded class ActionConstructor
{
    override void RegisterActions(TTypenameArray actions)
    {
        super.RegisterActions(actions);		
		
		actions.Insert(ActionMilitaryLootChestOpen);
		actions.Insert(ActionWoodenLootChestOpen);
		actions.Insert(ActionWoodenAmmoLootChestOpen);
		actions.Insert(ActionSafeLootChestOpen);
		actions.Insert(ActionRegisterLootChestOpen);
		actions.Insert(ActionUnlockCJChest);
		actions.Insert(ActionBreachCJChest);
		actions.Insert(ActionBreachLockCJChest);		
	}
}