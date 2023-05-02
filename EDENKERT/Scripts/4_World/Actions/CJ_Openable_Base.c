class CJ_Openable_Placeable_Base: Container_Base 
{   
	private bool m_IsLocked = true;
	protected int m_KeyNum;
	protected int m_OpenableBy;
	protected bool m_LightEnabled;
	protected ref OpenableBehaviour m_Openable;
	protected string m_Location;
	
	void CJ_Openable_Placeable_Base()
	{
		m_Openable = new OpenableBehaviour(false);
		RegisterNetSyncVariableBool("m_Openable.m_IsOpened");
		RegisterNetSyncVariableBool("m_IsLocked");
		RegisterNetSyncVariableInt("m_KeyNum");
		RegisterNetSyncVariableInt("m_OpenableBy");
		RegisterNetSyncVariableBool("m_LightEnabled");
		RegisterNetSyncVariableBool("m_IsSoundSynchRemote");
	}
	
	void SetLocation(string loc)
	{
		m_Location = loc;
	}
	
	string GetLocation()
	{
		return m_Location;
	}
	
	override void EEInit()
	{
		super.EEInit();
        if(IsOpen())
            GetInventory().UnlockInventory(HIDE_INV_FROM_SCRIPT);
		else
			GetInventory().LockInventory(HIDE_INV_FROM_SCRIPT);		
	}

	override void Open()
	{
		m_Openable.Open();
		SoundSynchRemote();
		UpdateVisualState();
		GetInventory().UnlockInventory(HIDE_INV_FROM_SCRIPT);
	}

	override void Close()
	{
		m_Openable.Close();
		SoundSynchRemote();
		UpdateVisualState();
		GetInventory().LockInventory(HIDE_INV_FROM_SCRIPT);
	}

	override bool IsOpen()
	{
		return m_Openable.IsOpened();
	}
	
	override void OnVariablesSynchronized()
	{
		super.OnVariablesSynchronized();
				
		if ( IsOpen() && IsSoundSynchRemote())
			{
				SoundChestOpenPlay();
			}
	
		UpdateVisualState();
	}
	
	void SoundChestOpenPlay()
	{
		EffectSound sound =	SEffectManager.PlaySound( "MilitaryLootChestsOpen_SoundSet", GetPosition() );
		sound.SetSoundAutodestroy( true );
	}
	
	void SetKeyNum(int kye)
	{
		m_KeyNum = kye;
		SetSynchDirty();
	}
	
	int GetKeyNum()
	{
		return m_KeyNum;
	}
	
	void SetOpenableBy(int openable)
	{
		m_OpenableBy = openable;
		SetSynchDirty();
	}
	
	int GetOpenableBy()
	{
		return m_OpenableBy;
	}
	void SetChestLight(bool light)
	{
		m_LightEnabled = light;
		SetSynchDirty();
	}
	
	bool GetChestLight()
	{
		return m_LightEnabled;
	}
	
	void Unlock()
	{
		m_IsLocked = false;
		SetSynchDirty();
	}
	
	bool IsLocked()
	{
		return m_IsLocked;
	}

	void UpdateVisualState()
    {
        if ( IsOpen() )
        {
            SetAnimationPhase("Doors1",1);
            SetAnimationPhase("Doors2",1);
            SetAnimationPhase("Doors3",1);
            SetAnimationPhase("Doors4",1);
        }
        else
        {
            SetAnimationPhase("Doors1",0);
            SetAnimationPhase("Doors2",0);
            SetAnimationPhase("Doors3",0);
            SetAnimationPhase("Doors4",0);
        }
    }
	override bool CanPutInCargo( EntityAI parent )
    {
		//if( !super.CanPutInCargo(parent) ) {return false;}
        //return IsInvEmpty() && !IsOpen();
		return false;
    }
    
    override bool CanPutIntoHands(EntityAI parent)
	{
		//if( !super.CanPutIntoHands(parent) ) {return false;}
		//return IsInvEmpty() && !IsOpen();
		return false;
    }

    override bool IsDeployable() 
    {
        return true;
    } 
    
    override void OnInventoryEnter(Man player)
    {
        super.OnInventoryEnter(player);
        GetInventory().LockInventory(HIDE_INV_FROM_SCRIPT);        
    }
    
    override void OnInventoryExit(Man player)
    {
        super.OnInventoryExit(player);
        if(IsOpen())
            GetInventory().UnlockInventory(HIDE_INV_FROM_SCRIPT);        
    }	

    override void SetActions()
	{
		super.SetActions();
	}
};