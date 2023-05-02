
class CJ_LootChest_Base : CJ_Openable_Placeable_Base 
{    
	protected PointLightBase m_Light;
	static vector 	m_LightLocalPosition 	= "0.1 0.3 0.1";
	static vector 	x_LightLocalPosition 	= "0.0 0.60 0.0";
	static vector 	y_LightLocalPosition 	= "0.0 0.15 0.35";
	static vector 	z_LightLocalPosition 	= "0.0 0.15 0.35";
	static vector 	m_LightLocalOrientation = "0 0 0";

	void CJ_LootChest_Base()
	{
		//fill with loot
		//CJ_LootChests.FillIt();
		//udelat plneni i pro spawnute truhly
		//CJ_LootChests.FillLootChest(EntityAI.Cast(this));
		if ( GetGame().IsServer() )
		{
			// not working good - weapon entity need synchronize
			//GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(FillChest, 100, false);
		}
		if ( GetGame().IsClient() )
		{
            if (IsOpen() && !m_Light && GetChestLight())
            {
                m_Light = PointLightBase.Cast(GetGame().CreateObject("PointLightBase", GetPosition(), true));
				m_Light.AttachOnObject(this, m_LightLocalPosition, m_LightLocalOrientation);
                m_Light.SetRadiusTo( 3 );
                m_Light.SetBrightnessTo(2);
                m_Light.SetDiffuseColor(1, 1, 0.25);
                m_Light.SetCastShadow(true);
				m_Light.SetFlareVisible(false);
            }
		}	
	}
	
	void ~CJ_LootChest_Base()
	{
		if (m_Light)
		m_Light.FadeOut();

		m_Light = NULL;
	}
	
	void FillChest()
	{
		//CJ_LootChests.FillLootChest(EntityAI.Cast(this));
	}
	
	override void UpdateVisualState()
    {
        if ( IsOpen() )
        {
            SetAnimationPhase("Doors1",0);
            SetAnimationPhase("Doors2",1);
			if (GetGame().IsClient() && !m_Light & GetChestLight())
			{
				m_Light = PointLightBase.Cast(GetGame().CreateObject("PointLightBase", GetPosition(), true));
				m_Light.AttachOnObject(this, m_LightLocalPosition, m_LightLocalOrientation);
                m_Light.SetRadiusTo( 3 );
                m_Light.SetBrightnessTo(2);
                m_Light.SetDiffuseColor(1, 1, 0.25);
                m_Light.SetCastShadow(true);
				m_Light.SetFlareVisible(false);
			}
        }
        else
        {
            SetAnimationPhase("Doors1",1);
            SetAnimationPhase("Doors2",0);
        }
    }
	override bool CanPutInCargo( EntityAI parent )
    {
        return false;
    }
    
    override bool CanPutIntoHands(EntityAI parent)
	{
		return false;
    } 
};

class CJ_MilitaryCrate_Base : CJ_LootChest_Base 
{    
	override void SoundChestOpenPlay()
	{
		EffectSound sound =	SEffectManager.PlaySound( "MilitaryLootChestsOpen_SoundSet", GetPosition() );
		sound.SetSoundAutodestroy( true );
	}
	
	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionMilitaryLootChestOpen);
	}
};

class CJ_WoodenCrate_Base : CJ_LootChest_Base 
{    
	override void SoundChestOpenPlay()
	{
		EffectSound sound =	SEffectManager.PlaySound( "WoodenLootChestsOpen_SoundSet", GetPosition() );
		sound.SetSoundAutodestroy( true );
	}
	
	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionWoodenLootChestOpen);
	}
};

class CJ_AmmoCrate_Small_Base : CJ_LootChest_Base 
{    
	override void SoundChestOpenPlay()
	{
		EffectSound sound =	SEffectManager.PlaySound( "WoodenLootChestsOpen_SoundSet", GetPosition() );
		sound.SetSoundAutodestroy( true );
	}
	
	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionWoodenAmmoLootChestOpen);
	}
};

class CJ_AmmoCrate_Large_Base : CJ_LootChest_Base 
{    
	override void SoundChestOpenPlay()
	{
		EffectSound sound =	SEffectManager.PlaySound( "WoodenLootChestsOpen_SoundSet", GetPosition() );
		sound.SetSoundAutodestroy( true );
	}
	
	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionWoodenAmmoLootChestOpen);
	}
};

class CJ_MoneySafe_Old_Base : CJ_LootChest_Base 
{    	
	void CJ_MoneySafe_Old_Base()
	{
		//fill with loot
		//CJ_LootChests.FillIt();
		//udelat plneni i pro spawnute truhly
		//CJ_LootChests.FillLootChest(EntityAI.Cast(this));
		if ( GetGame().IsServer() )
		{
			// not working good - weapon entity need synchronize
			//GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(FillChest, 100, false);
		}
		if ( GetGame().IsClient() )
		{
            if (IsOpen() && !m_Light && GetChestLight())
            {
                m_Light = PointLightBase.Cast(GetGame().CreateObject("PointLightBase", GetPosition(), true));
				m_Light.AttachOnObject(this, x_LightLocalPosition, m_LightLocalOrientation);
                m_Light.SetRadiusTo( 3 );
                m_Light.SetBrightnessTo(2);
                m_Light.SetDiffuseColor(1, 1, 0.25);
                m_Light.SetCastShadow(true);
				m_Light.SetFlareVisible(false);
            }
		}	
	}
	override void UpdateVisualState()
    {
        if ( IsOpen() )
        {
            SetAnimationPhase("Doors1",0);
            SetAnimationPhase("Doors2",1);
			if (GetGame().IsClient() && !m_Light & GetChestLight())
			{
				m_Light = PointLightBase.Cast(GetGame().CreateObject("PointLightBase", GetPosition(), true));
				m_Light.AttachOnObject(this, x_LightLocalPosition, m_LightLocalOrientation);
                m_Light.SetRadiusTo( 3 );
                m_Light.SetBrightnessTo(2);
                m_Light.SetDiffuseColor(1, 1, 0.25);
                m_Light.SetCastShadow(true);
				m_Light.SetFlareVisible(false);
			}
        }
        else
        {
            SetAnimationPhase("Doors1",1);
            SetAnimationPhase("Doors2",0);
        }
    }
	
	override void SoundChestOpenPlay()
	{
		EffectSound sound =	SEffectManager.PlaySound( "MoneySafeLootChestsOpen_SoundSet", GetPosition() );
		sound.SetSoundAutodestroy( true );
	}
	
	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionSafeLootChestOpen);
	}
};

class CJ_MoneySafe_New_Base : CJ_LootChest_Base 
{    
	void CJ_MoneySafe_Old_Base()
	{
		//fill with loot
		//CJ_LootChests.FillIt();
		//udelat plneni i pro spawnute truhly
		//CJ_LootChests.FillLootChest(EntityAI.Cast(this));
		if ( GetGame().IsServer() )
		{
			// not working good - weapon entity need synchronize
			//GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(FillChest, 100, false);
		}
		if ( GetGame().IsClient() )
		{
            if (IsOpen() && !m_Light && GetChestLight())
            {
                m_Light = PointLightBase.Cast(GetGame().CreateObject("PointLightBase", GetPosition(), true));
				m_Light.AttachOnObject(this, x_LightLocalPosition, m_LightLocalOrientation);
                m_Light.SetRadiusTo( 3 );
                m_Light.SetBrightnessTo(2);
                m_Light.SetDiffuseColor(1, 1, 0.25);
                m_Light.SetCastShadow(true);
				m_Light.SetFlareVisible(false);
            }
		}	
	}
	override void UpdateVisualState()
    {
        if ( IsOpen() )
        {
            SetAnimationPhase("Doors1",0);
            SetAnimationPhase("Doors2",1);
			if (GetGame().IsClient() && !m_Light & GetChestLight())
			{
				m_Light = PointLightBase.Cast(GetGame().CreateObject("PointLightBase", GetPosition(), true));
				m_Light.AttachOnObject(this, x_LightLocalPosition, m_LightLocalOrientation);
                m_Light.SetRadiusTo( 3 );
                m_Light.SetBrightnessTo(2);
                m_Light.SetDiffuseColor(1, 1, 0.25);
                m_Light.SetCastShadow(true);
				m_Light.SetFlareVisible(false);
			}
        }
        else
        {
            SetAnimationPhase("Doors1",1);
            SetAnimationPhase("Doors2",0);
        }
    }
	
	override void SoundChestOpenPlay()
	{
		EffectSound sound =	SEffectManager.PlaySound( "MoneySafeLootChestsOpen_SoundSet", GetPosition() );
		sound.SetSoundAutodestroy( true );
	}
	
	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionSafeLootChestOpen);
	}
};

class CJ_CashRegister_Old_Base : CJ_LootChest_Base 
{    
	void CJ_MoneySafe_Old_Base()
	{
		//fill with loot
		//CJ_LootChests.FillIt();
		//udelat plneni i pro spawnute truhly
		//CJ_LootChests.FillLootChest(EntityAI.Cast(this));
		if ( GetGame().IsServer() )
		{
			// not working good - weapon entity need synchronize
			//GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(FillChest, 100, false);
		}
		if ( GetGame().IsClient() )
		{
            if (IsOpen() && !m_Light && GetChestLight())
            {
                m_Light = PointLightBase.Cast(GetGame().CreateObject("PointLightBase", GetPosition(), true));
				m_Light.AttachOnObject(this, y_LightLocalPosition, m_LightLocalOrientation);
                m_Light.SetRadiusTo( 1 );
                m_Light.SetBrightnessTo(1);
                m_Light.SetDiffuseColor(0.33, 1, 0.33);
                m_Light.SetCastShadow(true);
				m_Light.SetFlareVisible(false);
            }
		}	
	}
	override void UpdateVisualState()
    {
        if ( IsOpen() )
        {
            SetAnimationPhase("Doors1",0);
            SetAnimationPhase("Doors2",0);
			if (GetGame().IsClient() && !m_Light & GetChestLight())
			{
				m_Light = PointLightBase.Cast(GetGame().CreateObject("PointLightBase", GetPosition(), true));
				m_Light.AttachOnObject(this, y_LightLocalPosition, m_LightLocalOrientation);
                m_Light.SetRadiusTo( 1 );
                m_Light.SetBrightnessTo(1);
                m_Light.SetDiffuseColor(0.33, 1, 0.33);
                m_Light.SetCastShadow(true);
				m_Light.SetFlareVisible(false);
			}
        }
        else
        {
            SetAnimationPhase("Doors1",1);
            SetAnimationPhase("Doors2",1);
        }
    }
	
	override void SoundChestOpenPlay()
	{
		EffectSound sound =	SEffectManager.PlaySound( "CashRegisterLootChestsOpen_SoundSet", GetPosition() );
		sound.SetSoundAutodestroy( true );
	}
	
	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionRegisterLootChestOpen);
	}
};

class CJ_CashRegister_New_Base : CJ_LootChest_Base 
{    
	void CJ_MoneySafe_Old_Base()
	{
		//fill with loot
		//CJ_LootChests.FillIt();
		//udelat plneni i pro spawnute truhly
		//CJ_LootChests.FillLootChest(EntityAI.Cast(this));
		if ( GetGame().IsServer() )
		{
			// not working good - weapon entity need synchronize
			//GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(FillChest, 100, false);
		}
		if ( GetGame().IsClient() )
		{
            if (IsOpen() && !m_Light && GetChestLight())
            {
                m_Light = PointLightBase.Cast(GetGame().CreateObject("PointLightBase", GetPosition(), true));
				m_Light.AttachOnObject(this, y_LightLocalPosition, m_LightLocalOrientation);
                m_Light.SetRadiusTo( 1 );
                m_Light.SetBrightnessTo(1);
                m_Light.SetDiffuseColor(0.33, 1, 0.33);
                m_Light.SetCastShadow(true);
				m_Light.SetFlareVisible(false);
            }
		}	
	}
	override void UpdateVisualState()
    {
        if ( IsOpen() )
        {
            SetAnimationPhase("Doors1",0);
            SetAnimationPhase("Doors2",0);
			if (GetGame().IsClient() && !m_Light & GetChestLight())
			{
				m_Light = PointLightBase.Cast(GetGame().CreateObject("PointLightBase", GetPosition(), true));
				m_Light.AttachOnObject(this, y_LightLocalPosition, m_LightLocalOrientation);
                m_Light.SetRadiusTo( 1 );
                m_Light.SetBrightnessTo(1);
                m_Light.SetDiffuseColor(0.33, 1, 0.33);
                m_Light.SetCastShadow(true);
				m_Light.SetFlareVisible(false);
			}
        }
        else
        {
            SetAnimationPhase("Doors1",1);
            SetAnimationPhase("Doors2",1);
        }
    }
	
	override void SoundChestOpenPlay()
	{
		EffectSound sound =	SEffectManager.PlaySound( "CashRegisterLootChestsOpen_SoundSet", GetPosition() );
		sound.SetSoundAutodestroy( true );
	}
	
	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionRegisterLootChestOpen);
	}
};