class CJ_LootChests
{
	static Weapon_Base CreateWeaponWithMagazine( string sWeapon, string sMagazine )
    {
        Weapon_Base oWpn = Weapon_Base.Cast(GetGame().CreateObject( sWeapon , "0 0 0" ));
        oWpn.SpawnAmmo(sMagazine);
        return oWpn;
    }
	
	static Weapon_Base CreateWeapon(string predefinedname, out string mag)
	{
		Weapon_Base weapon;
		ItemBase optic;
		LCConfig config = GetDayZGame().GetLootChestsConfig();
		LCPredefinedWeapon wpname;
		
		if ( predefinedname.Contains("LC_predefined") )
		{
				for (int wp = 0; wp < config.LCPredefinedWeapons.Count(); wp++)
				{
					wpname = config.LCPredefinedWeapons.Get(wp);
					if (wpname.defname == predefinedname)
					{
						if (wpname.magazine == "")
						{
							weapon = Weapon_Base.Cast(GetGame().CreateObject( wpname.weapon , "0 0 0" ));
						} else {
							weapon = CreateWeaponWithMagazine( wpname.weapon, wpname.magazine );
							//magazine = ItemBase.Cast(GetGame().CreateObject( wpname.magazine , "0 0 0" ));
							mag = wpname.magazine;
						}
						if (weapon && wpname.attachments.Count()>0 )
						{
							for (int attch = 0; attch < wpname.attachments.Count(); attch++)
							{
								weapon.GetInventory().CreateAttachment( wpname.attachments.Get(attch) );
							}	
						}
						if (weapon && wpname.optic !="")
						{
							optic = ItemBase.Cast(weapon.GetInventory().CreateAttachment( wpname.optic ));
							if (wpname.opticbattery == true	)
							{
								optic.GetInventory().CreateAttachment("Battery9V");
							}
						}
					//LCLogger.Log("predefined weapon " + weapon);
					
					return weapon;	
					}
						
				}
		}
		
		weapon = Weapon_Base.Cast(GetGame().CreateObject( predefinedname , "0 0 0" ));

		return weapon;
		
	}
	
	static int GetIndexOfCategoryName(string catname)
	{
		LCConfig config = GetDayZGame().GetLootChestsConfig();
		for (int i = 0; i < config.LootCategories.Count(); i++)
		{
			if (config.LootCategories.Get(i).name == catname)
				return i;
		}
		return 0;
	}
	
	static void CreateLootChest(LootChestsManager lm, vector position, vector rotation, TStringArray items, string keyclass, int openable, bool light, string containertype, float lootrand, string name)
	{
	//containertype = "SeaChest";
	ItemBase lootchestContainer = ItemBase.Cast(GetGame().CreateObject(containertype, position)); //CreateObjectEx
	/*
	if (lootchestContainer.GetEconomyProfile() && lootchestContainer.GetEconomyProfile().GetLifetime() == 1800)
	{
		LCLogger.Log("Looks like entry for chest is missing in types.xml, chest will despawn after short time - You should read carefully changenotes of mod!!!");
	}
	*/
	ItemBase item;
	lm.AddChestToArray(lootchestContainer);
	CJ_Openable_Placeable_Base cjchest;
	Class.CastTo(cjchest,lootchestContainer);
	cjchest.SetChestLight(light);
	cjchest.SetLocation(name);
	if (keyclass.Length() > 0 && keyclass != "CJ_Key_Base")
	{
		array<string> keynumstring = new array<string>;
		keyclass.Split("y", keynumstring);
		
		//LCLogger.Log("XXXXXX string " + keynumstring + " trololo " + keynumstring[1]);
		int keynum = keynumstring[1].ToInt();
		cjchest.SetKeyNum(keynum);
		cjchest.SetOpenableBy(openable);
	} else {
		cjchest.Unlock();
	}
	//LCLogger.Log("key class " + cjchest.GetKeyClass());
	string itemtesting;
	Weapon_Base oWpn1;
	string magazine;
	LCConfig config = GetDayZGame().GetLootChestsConfig();
	ref LCPredefinedWeapon wpname;
	float rand, rarity;
	int randi;
	int j;
	int MaxSpareMags = 4;
	bool isadded = false;
	InventoryLocation wpn_il = new InventoryLocation;
	string randwpn, raritypart, itempart;
	TStringArray loc;	
	lootchestContainer.GetInventory().UnlockInventory(HIDE_INV_FROM_SCRIPT);
	if (config.MaxSpareMags)
	{
		MaxSpareMags = config.MaxSpareMags;
	}
	//vymazat inventar - spawne se kvuli novemu kodu
	//lootchestContainer.GetInventory(). IDK
		
	for(int i = 0; i < items.Count(); i++)
	    {
	        //TODO pridat nahodnost
			//if TR_predefined ... prida to predefinovanou zbran s attachmentama
			itemtesting = items.Get(i);
			//LCLogger.Log("item " + itemtesting);
			raritypart = "";
			rarity = 0;
			if ( itemtesting.Contains("LC_Table") )
			{
				//vybere nahodny item a spawne ho do truhly
				if ( itemtesting.Contains("LC_Table_Weapons") )
				{
					randwpn = config.LootCategories.Get(GetIndexOfCategoryName(itemtesting)).Loot.GetRandomElement();
					oWpn1 = CreateWeapon( config.LootCategories.Get(GetIndexOfCategoryName(itemtesting)).Loot.GetRandomElement(), magazine );
					rand = Math.RandomFloatInclusive(0.0, 1.0);
					if (rand > lootrand && oWpn1)
					{
						isadded = lootchestContainer.GetInventory().AddEntityToInventory(oWpn1); //CreateEntityInCargoEx
						if (isadded)
						{
							LCLogger.Debug("crate filled with weapon: " + oWpn1);
							rand = Math.RandomIntInclusive(0, 4);
							rand = Math.RandomIntInclusive(0, MaxSpareMags);
							if (rand > 0 && magazine)
							{
								for(j = 0; j < rand; j++)
								{
									lootchestContainer.GetInventory().CreateInInventory(magazine);
								}
								LCLogger.Debug("crate filled with " + rand + " magazines: " + magazine);
							}  
						}
						else
						{
							LCLogger.Debug("weapon: " + oWpn1 + " not fit to crate, its probably full or weapon is longer than 10 slots... SNAFU?");
							GetGame().ObjectDelete(oWpn1);
						}
  
					} 
					else
					{
						GetGame().ObjectDelete(oWpn1);
					}
					
				} 
				else 
				{
					randwpn = config.LootCategories.Get(GetIndexOfCategoryName(itemtesting)).Loot.GetRandomElement();
					randwpn = config.LootCategories.Get(GetIndexOfCategoryName(itemtesting)).Loot.GetRandomElement();
					
					loc = new TStringArray;
					randwpn.Split( "|", loc );
					itempart = loc.Get(0);
					raritypart = loc.Get(1);
					if (raritypart != "")
					{
						rarity = raritypart.ToFloat();
					}
					
					rand = Math.RandomFloatInclusive(0.0, 1.0);	
					if (raritypart == "" && rand > lootrand)
					{
						item = ItemBase.Cast(lootchestContainer.GetInventory().CreateInInventory( randwpn ));
						if (item)
						{
							LCLogger.Debug("crate filled with item " + randwpn);
							if (config.RandomQuantity)
							{
								SetRandomQuantity(item);
							}
							
						}
					}
					else if (rarity >= rand)
					{
						item = ItemBase.Cast(lootchestContainer.GetInventory().CreateInInventory( itempart ));
						if (item)
						{
							LCLogger.Debug("crate filled with item " + itempart);
							if (config.RandomQuantity)
							{
								SetRandomQuantity(item);
							}
							
						}
					}
					
				}

				
			} else if (itemtesting.Contains("LC_predefined")) {
				
				oWpn1 = CreateWeapon(itemtesting,magazine);
				
				isadded = lootchestContainer.GetInventory().AddEntityToInventory(oWpn1);
				if (isadded)
				{
					rand = Math.RandomIntInclusive(0, 4);
					rand = Math.RandomIntInclusive(0, MaxSpareMags);
					LCLogger.Debug("crate filled with weapon: " + oWpn1);
					if (rand > 0 && magazine)
					{
						for(j = 0; j < rand; j++)
						{
							lootchestContainer.GetInventory().CreateInInventory(magazine);
						}
						LCLogger.Debug("crate filled with " + rand + " magazines: " + magazine);
					}
				}
				else
				{
					LCLogger.Debug("weapon: " + oWpn1 + " not fit to crate, its probably full or weapon is longer than 10 slots... SNAFU?");
					GetGame().ObjectDelete(oWpn1);
				}
				
			} else {
				
				rand = Math.RandomFloatInclusive(0.0, 1.0);
				
				randwpn = items.Get(i);
				loc = new TStringArray;
				randwpn.Split( "|", loc );
				itempart = loc.Get(0);
				raritypart = loc.Get(1);
				if (raritypart != "")
				{
					rarity = raritypart.ToFloat();
				}
				
				if (raritypart == "" && rand > lootrand)
				{
					
					//lootchestContainer.GetInventory().CreateInInventory(items.Get(i));
					item = ItemBase.Cast(lootchestContainer.GetInventory().CreateInInventory(items.Get(i)));
					if (item)
					{
						LCLogger.Debug("crate filled with item " + items.Get(i));
						if (config.RandomQuantity)
						{
							SetRandomQuantity(item);
						}
						
					}
					
				}
				else if (rarity >= rand)
				{
					item = ItemBase.Cast(lootchestContainer.GetInventory().CreateInInventory( itempart ));
					if (item)
					{
						LCLogger.Debug("crate filled with item " + itempart);
						if (config.RandomQuantity)
						{
							SetRandomQuantity(item);
						}
						
					}
				}
				
			}
					
		}
	
	lootchestContainer.GetInventory().LockInventory(HIDE_INV_FROM_SCRIPT);
	lootchestContainer.SetOrientation(rotation);
	GetGame().RemoteObjectTreeDelete(lootchestContainer);
	GetGame().RemoteObjectTreeCreate(lootchestContainer);
	}
	
	static void SetRandomQuantity(ItemBase item)
	{
		
		if (item.GetQuantityMax())
		{
			int qmax = item.GetQuantityMax();
			LCLogger.Debug("get max quantity " + qmax);
			int qrnd = Math.RandomIntInclusive(1,qmax);
			qrnd = Math.RandomIntInclusive(1,qmax);
			if (qmax > 0)
			{
				LCLogger.Debug("set random quantity " + qrnd);
				item.SetQuantity(qrnd);
			}
		}		
		if( item.GetEconomyProfile() )
		{
			LCLogger.Debug("CE profile ");
			float q_min = item.GetEconomyProfile().GetQuantityMin();
			float q_max = item.GetEconomyProfile().GetQuantityMax();
			if( q_max > 0 )
			{
				float quantity_randomized = Math.RandomFloatInclusive(q_min, q_max);
				item.SetQuantityNormalized(quantity_randomized, false);
				LCLogger.Debug("set CE random quantity " + quantity_randomized);
			}
		}
		Magazine_Base mag;	
        if (Class.CastTo(mag, item))
        {
            int ammocount = mag.GetAmmoCount();
			int qarnd = Math.RandomIntInclusive(1,ammocount);
			mag.ServerSetAmmoCount(qarnd);
		}
		
	}
	
}