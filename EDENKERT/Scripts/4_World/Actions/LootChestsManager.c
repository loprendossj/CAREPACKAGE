static ref LootChestsManager g_LootChestsManager;
static ref LootChestsManager GetLootChestsManager()
{
    if ( !g_LootChestsManager )
    {
         g_LootChestsManager = new ref LootChestsManager();
    }
    
    return g_LootChestsManager;
}
class LootChestsManager
{
	protected ref TClassArray m_ChestsArray;
	void LootChestsManager()
	{
		m_ChestsArray = new TClassArray();
		LCConfig config = GetDayZGame().GetLootChestsConfig();
		
				TStringArray chestsspawned;
		string ChestsFilename = "$profile:\\CJ_LootChests\\spawnedchests.txt";
		FileHandle chestsFile = OpenFile(ChestsFilename, FileMode.READ);

		vector posi;
		array<Object> objects_in_vicinity;
		array<CargoBase> proxyCargos;
		int j;
		Object object_in_radius;
		//clean debug area 0 0 0
		objects_in_vicinity = new array<Object>;
		proxyCargos = new array<CargoBase>;
		GetGame().GetObjectsAtPosition3D(vector.Zero, 1.5, objects_in_vicinity, proxyCargos);
		for ( j = 0; j < objects_in_vicinity.Count(); j++ )
		{
			GetGame().ObjectDelete(objects_in_vicinity.Get(j));
		}
		LCLogger.Debug("Deleted " + objects_in_vicinity.Count() + " objects at zero vector");
		
		if (chestsFile != 0) {
			string sLine = "";
			while ( FGets(chestsFile,sLine) > 0 ) {
				LCLogger.Debug("Deleted old chest at " + sLine);
				posi = sLine.ToVector();
				objects_in_vicinity = new array<Object>;
				proxyCargos = new array<CargoBase>;
				GetGame().GetObjectsAtPosition3D(posi, 0.2, objects_in_vicinity, proxyCargos);
				LCLogger.Debug("Objects " + objects_in_vicinity.Count() );
				for ( j = 0; j < objects_in_vicinity.Count(); j++ )
				{
					object_in_radius = objects_in_vicinity.Get(j);
					LCLogger.Debug("Object " + object_in_radius.ClassName());
					CJ_Openable_Placeable_Base cjchest;
					Class.CastTo(cjchest, object_in_radius);
					if (cjchest)
					{
						LCLogger.Debug("Found chest " + posi.ToString());
						GetGame().ObjectDelete(object_in_radius);
		
					}
				}
				
					
			}
			CloseFile(chestsFile);
			DeleteFile(ChestsFilename);
		}
		
		int year, month, day, hour, minute, second;
		GetYearMonthDay(year, month, day);
		GetHourMinuteSecond(hour, minute, second);
		string timedate = ""+year.ToStringLen(2)+month.ToStringLen(2)+day.ToStringLen(2)+hour.ToStringLen(2)+minute.ToStringLen(2)+second.ToStringLen(2);
		int kqp = timedate.ToInt();
		//LCLogger.Log("randomizer " + timedate);
		//Math.Randomize(Math.Randomize(kqp));
		
		
		for(int i = 0; i < config.LootChestsLocations.Count(); i++)
		{
			TStringArray chests = config.LootChestsLocations.Get(i).chest;
			string keyclass = config.LootChestsLocations.Get(i).keyclass;
			int openable = config.LootChestsLocations.Get(i).openable;
			bool light = config.LootChestsLocations.Get(i).light;
			//string pos = config.LootChestsLocations.Get(i).pos;
			//string rot = config.LootChestsLocations.Get(i).rot;
			TStringArray positions =  config.LootChestsLocations.Get(i).pos;
			TStringArray loot = config.LootChestsLocations.Get(i).loot;
			float lootrand = config.LootChestsLocations.Get(i).lootrandomize;
			int chestnum = config.LootChestsLocations.Get(i).number;
			int rndnum = Math.RandomIntInclusive(0, positions.Count() - 1);
			string name = config.LootChestsLocations.Get(i).name;
			if (chestnum <= positions.Count())
			{
				//pokd neni vic truhel nez lokaci udelej smycku
				for (j = 0; j< chestnum; j++)
				{
					//iteruj na lokacich
					string chestclass = chests.GetRandomElement();
					chestclass = chests.GetRandomElement();
					chestclass = chests.GetRandomElement();

					rndnum = Math.RandomIntInclusive(0, positions.Count() - 1);
					rndnum = Math.RandomIntInclusive(0, positions.Count() - 1);
					//LCLogger.Log("num of positions " + positions.Count());
					string posrot = positions.Get(rndnum);
					TStringArray loc = new TStringArray;
					posrot.Split( "|", loc );
					string pos = loc.Get(0);
					string rot = loc.Get(1);
					//add check for commas in pos!
					if (pos.Contains(","))
					{
						LCLogger.Log("Position contains commas, thats wrong! Only one space between numbers! Fix yours config according example!!!");
					}
					else {
						CJ_LootChests.CreateLootChest( this, pos.ToVector(), rot.ToVector() , loot, keyclass, openable, light, chestclass, lootrand, name);
						LCLogger.Log("Created LootChest " + chestclass + " at " + pos);
						positions.RemoveOrdered(rndnum);
						if (lootrand == 1.0)
						{
							LCLogger.Log("randomization was set 1.0 that means 100% chance items will NOT spawned - see documentation");
						}
					}
					
				}
			}		
			
		}
		
	}
	
	
	void AddChestToArray(ItemBase chest)
	{
		m_ChestsArray.Insert(chest);
		LCLogger.Debug("Chest position " + chest.GetPosition() );
		string PrisonAdminFile = "$profile:\\CJ_LootChests\\spawnedchests.txt";
		string message = chest.GetPosition()[0].ToString() + " " + chest.GetPosition()[1].ToString() + " " + chest.GetPosition()[2].ToString();
		FileHandle chestsFile = OpenFile(PrisonAdminFile, FileMode.APPEND);
		FPrintln(chestsFile, message);
		CloseFile(chestsFile);
		
	}
	

	
}

static ref LootChestsEarlyRun g_LootChestsEarlyRun;
static ref LootChestsEarlyRun GetLootChestsEarlyRun()
{
    if ( !g_LootChestsEarlyRun )
    {
         g_LootChestsEarlyRun = new ref LootChestsEarlyRun();
    }
    
    return g_LootChestsEarlyRun;
}
class LootChestsEarlyRun
{
	protected ref TClassArray m_ChestsArray;
	void LootChestsEarlyRun()
	{
		LCConfig config = GetDayZGame().GetLootChestsConfig();
		if (config.DeleteLogs)
		{
			DeleteFile("$profile:\\CJ_LootChests\\LootChests_LOG.log");
		}
		LCLogger.Log("LootChests started!");
		GetRPCManager().AddRPC("CJ_LootChests", "RequestConfig", this, SingleplayerExecutionType.Server);
	}
	
	void RequestConfig(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
	{
		if(type == CallType.Server)
        {
			Param1<string> data;
			if (!ctx.Read(data)) return; //Return if data sent over was null/unable to deserialize 
			string clientLang = data.param1;
			LCLogger.Log("Sending data to client " + sender.GetName());
			LCToolsConfig toolsconfig =  GetDayZGame().GetLootChestsToolsConfig();
			GetRPCManager().SendRPC( "CJ_LootChests", "SyncConfig", new Param1<LCToolsConfig>(toolsconfig), true, sender );
		}
	}
}