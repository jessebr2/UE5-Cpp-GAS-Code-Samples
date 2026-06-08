// © 2024 Olinick Games. All rights reserved.


#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"

FAuraGameplayTags FAuraGameplayTags::GameplayTags;

void FAuraGameplayTags::InitializeNativeGameplayTags()
{
	//* Primary Attributes
	GameplayTags.Attributes_Primary_Dexterity = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Dexterity"), FString("Increases Critical Hit Chance"));
	GameplayTags.Attributes_Primary_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Intelligence"), FString("Increases magical damage"));
	GameplayTags.Attributes_Primary_Resilience = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Resilience"), FString("Increases Armor and Armor Penetration"));
	GameplayTags.Attributes_Primary_Strengh = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Strengh"), FString("Increases fisical damage"));
	GameplayTags.Attributes_Primary_Vigor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Primary.Vigor"), FString("Increases Health"));

	//* Secondary Attributes
	GameplayTags.Attributes_Secondary_ArcaneAttackDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ArcaneAttackDamage"), FString("Arcane Attack Damage"));
	GameplayTags.Attributes_Secondary_FireAttackDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.FireAttackDamage"), FString("Fire Attack Damage"));
	GameplayTags.Attributes_Secondary_LightningAttackDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.LightningAttackDamage"), FString("Lightning Attack Damage"));
	GameplayTags.Attributes_Secondary_IceAttackDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.IceAttackDamage"), FString("Ice Attack Damage"));
	GameplayTags.Attributes_Secondary_PhysicalAttackDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.PhysicalAttackDamage"), FString("Physical Attack Damage"));
	GameplayTags.Attributes_Secondary_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.Armor"), FString("Reduces damage taken, improves Block Chance"));
	GameplayTags.Attributes_Secondary_ArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.ArmorPenetration"), FString("Armor Penetration"));
	GameplayTags.Attributes_Secondary_CriticalHitChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitChance"), FString("Critical Hit Chance"));
	GameplayTags.Attributes_Secondary_CriticalHitDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitDamage"), FString("Critical Hit Damage"));
	GameplayTags.Attributes_Secondary_CriticalHitResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.CriticalHitResistance"), FString("Critical Hit Resistance"));
	GameplayTags.Attributes_Secondary_StaminaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.StaminaRegeneration"), FString("Stamina Regeneration"));
	GameplayTags.Attributes_Secondary_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxHealth"), FString("MaxHealth"));
	GameplayTags.Attributes_Secondary_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxMana"), FString("MaxMana"));
	GameplayTags.Attributes_Secondary_MaxStamina = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Secondary.MaxStamina"), FString("MaxStamina"));

	//* Vital Attributes
	GameplayTags.Attributes_Vital_Health = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Health"), FString("Current Health"));
	GameplayTags.Attributes_Vital_Mana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Mana"), FString("Current Mana"));
	GameplayTags.Attributes_Vital_Stamina = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Vital.Stamina"), FString("Current Stamina"));

	//* LevelUp Attributes
	GameplayTags.Attributes_LevelUp_Level = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.LevelUp.Level"), FString("Current Level"));
	GameplayTags.Attributes_LevelUp_XP = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.LevelUp.XP"), FString("Current XP"));
	GameplayTags.Attributes_LevelUp_XPNeeded = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.LevelUp.XPNeeded"), FString("XP to next Level"));

	//* Meta Attributes
	GameplayTags.Attributes_Meta_IncomingXP = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Meta.IncomingXP"), FString("IncomingXP Meta Attribute"));
	GameplayTags.Attributes_Meta_ResidualDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Meta.ResidualDamage"), FString("ResidualDamage Meta Attribute"));

	//* Imput Tags
	GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.LMB"), FString("Input Tag for Left Mouse Button"));
	GameplayTags.InputTag_LMB_Shifted = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.LMB_Shifted"), FString("Input Tag for Left Mouse Button + Shift Key"));
	GameplayTags.InputTag_RMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.RMB"), FString("Input Tag for Right Mouse Button"));
	GameplayTags.InputTag_RMB_Shifted = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.RMB_Shifted"), FString("Input Tag for Right Mouse Button + Shift Key"));
	GameplayTags.InputTag_MMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.MMB"), FString("Input Tag for Midle Mouse Button"));
	GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.1"), FString("Input Tag for 1 Key"));
	GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.2"), FString("Input Tag for 2 Key"));
	GameplayTags.InputTag_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.3"), FString("Input Tag for 3 Key"));
	GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.4"), FString("Input Tag for 4 Key"));
	GameplayTags.InputTag_Passive_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Passive.1"), FString("Input Tag for Passive 1"));
	GameplayTags.InputTag_Passive_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Passive.2"), FString("Input Tag for Passive 2"));
	GameplayTags.InputTag_E = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.E"), FString("Input Tag for E Key"));
	GameplayTags.InputTag_F = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.F"), FString("Input Tag for F Key"));
	GameplayTags.InputTag_Q = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Q"), FString("Input Tag for Q Key"));
	GameplayTags.InputTag_Space = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Space"), FString("Input Tag for Space Key"));
	GameplayTags.InputTag_Esc = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Esc"), FString("Input Tag for Esc Key"));
	GameplayTags.InputTag_Up = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Up"), FString("Input Tag for Up Key"));
	GameplayTags.InputTag_Down = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Down"), FString("Input Tag for Down Key"));
	GameplayTags.InputTag_Left = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Left"), FString("Input Tag for Left Key"));
	GameplayTags.InputTag_Right = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Right"), FString("Input Tag for Right Key"));
	GameplayTags.InputTag_Move = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Move"), FString("Input Tag for Move Key"));
	GameplayTags.InputTag_Ok = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Ok"), FString("Input Tag for Ok Key"));
	GameplayTags.InputTag_Back = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Back"), FString("Input Tag for Back Key"));
	GameplayTags.InputTag_Nav_L = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Nav.L"), FString("Input Tag for Navigate L"));
	GameplayTags.InputTag_Nav_R = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("InputTag.Nav.R"), FString("Input Tag for Navigate R"));

	//* Button Tags
	GameplayTags.Button_Confirm = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Button.Confirm"), FString("Input Tag for Confirm Button"));
	GameplayTags.Button_Cancel = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Button.Cancel"), FString("Input Tag for Cancel Button"));
	GameplayTags.Button_0 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Button.0"), FString("Input Tag for Button 0"));
	GameplayTags.Button_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Button.1"), FString("Input Tag for Button 1"));
	GameplayTags.Button_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Button.2"), FString("Input Tag for Button 2"));
	GameplayTags.Button_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Button.3"), FString("Input Tag for Button 3"));
	GameplayTags.Button_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Button.4"), FString("Input Tag for Button 4"));
	GameplayTags.Button_5 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Button.5"), FString("Input Tag for Button 5"));
	GameplayTags.Button_6 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Button.6"), FString("Input Tag for Button 6"));
	GameplayTags.Button_7 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Button.7"), FString("Input Tag for Button 7"));
	GameplayTags.Button_8 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Button.8"), FString("Input Tag for Button 8"));
	GameplayTags.Button_9 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Button.9"), FString("Input Tag for Button 9"));
	GameplayTags.Button_10 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Button.10"), FString("Input Tag for Button 10"));
	GameplayTags.Button_11 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Button.11"), FString("Input Tag for Button 11"));
	GameplayTags.Button_12 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Button.12"), FString("Input Tag for Button 12"));
	GameplayTags.Button_13 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Button.13"), FString("Input Tag for Button 13"));
	GameplayTags.Button_14 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Button.14"), FString("Input Tag for Button 14"));
	GameplayTags.Button_15 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Button.15"), FString("Input Tag for Button 15"));
	GameplayTags.Button_16 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Button.16"), FString("Input Tag for Button 16"));
	GameplayTags.Button_17 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Button.17"), FString("Input Tag for Button 17"));
	GameplayTags.Button_18 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Button.18"), FString("Input Tag for Button 18"));
	GameplayTags.Button_19 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Button.19"), FString("Input Tag for Button 19"));
	GameplayTags.Button_20 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Button.20"), FString("Input Tag for Button 20"));
	GameplayTags.Button_21 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Button.21"), FString("Input Tag for Button 21"));
	GameplayTags.Button_22 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Button.22"), FString("Input Tag for Button 22"));
	GameplayTags.Button_23 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Button.23"), FString("Input Tag for Button 23"));
	GameplayTags.Button_24 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Button.24"), FString("Input Tag for Button 24"));
	GameplayTags.Button_25 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Button.25"), FString("Input Tag for Button 25"));
	GameplayTags.Button_26 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Button.26"), FString("Input Tag for Button 26"));
	GameplayTags.Button_27 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Button.27"), FString("Input Tag for Button 27"));
	GameplayTags.Button_28 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Button.28"), FString("Input Tag for Button 28"));
	GameplayTags.Button_29 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Button.29"), FString("Input Tag for Button 29"));
	GameplayTags.Button_30 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Button.30"), FString("Input Tag for Button 30"));
	GameplayTags.Button_31 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Button.31"), FString("Input Tag for Button 31"));
	GameplayTags.Button_32 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Button.32"), FString("Input Tag for Button 32"));
	GameplayTags.Button_33 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Button.33"), FString("Input Tag for Button 33"));
	GameplayTags.Button_34 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Button.34"), FString("Input Tag for Button 34"));
	GameplayTags.Button_35 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Button.35"), FString("Input Tag for Button 35"));
	GameplayTags.Button_36 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Button.36"), FString("Input Tag for Button 36"));
	GameplayTags.Button_37 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Button.37"), FString("Input Tag for Button 37"));
	GameplayTags.Button_38 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Button.38"), FString("Input Tag for Button 38"));
	GameplayTags.Button_39 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Button.39"), FString("Input Tag for Button 39"));

	//* Damage
	GameplayTags.Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage"), FString("Damage"));
	GameplayTags.DamageBonus = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("DamageBonus"), FString("Damage Bonus"));

	//* Damage Types
	GameplayTags.Damage_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Arcane"), FString("Arcane Damage Type"));
	GameplayTags.Damage_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Fire"), FString("Fire Damage Type"));
	GameplayTags.Damage_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Lightning"), FString("Lightning Damage Type"));
	GameplayTags.Damage_Ice = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Ice"), FString("Ice Damage Type"));
	GameplayTags.Damage_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Physical"), FString("Physical Damage Type"));
	GameplayTags.Damage_Parry = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Damage.Parry"), FString("Parry Damage Type"));

	//* Resistances
	GameplayTags.Attributes_Resistance_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Arcane"), FString("Resistance to Arcane damage"));
	GameplayTags.Attributes_Resistance_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Fire"), FString("Resistance to Fire damage"));
	GameplayTags.Attributes_Resistance_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Lightning"), FString("Resistance to Lightning damage"));
	GameplayTags.Attributes_Resistance_Ice = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Ice"), FString("Resistance to Ice damage"));
	GameplayTags.Attributes_Resistance_Physical = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attributes.Resistance.Physical"), FString("Resistance to Physical damage"));

	//* Debuffs
	GameplayTags.Debuff_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Arcane"), FString("Debuff to Arcane Damage"));
	GameplayTags.Debuff_Burn = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Burn"), FString("Debuff to Fire Damage"));
	GameplayTags.Debuff_Stun = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Stun"), FString("Debuff to Lightning Damage"));
	GameplayTags.Debuff_Lightning = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Lightning"), FString("Debuff to Lightning Damage"));
	GameplayTags.Debuff_Freeze = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Freeze"), FString("Debuff to Ice Damage"));

	GameplayTags.Debuff_Chance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Chance"), FString("Debuff Chance"));
	GameplayTags.Debuff_Damage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Damage"), FString("Debuff Damage"));
	GameplayTags.Debuff_Duration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Duration"), FString("Debuff Duration"));
	GameplayTags.Debuff_Frequency = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Frequency"), FString("Debuff Frequency"));

	GameplayTags.Debuff_Disabled = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Debuff.Disabled"), FString("Disabled Tag"));


	//* Maps of Damage Types to Resistances
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Arcane, GameplayTags.Attributes_Resistance_Arcane);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Fire, GameplayTags.Attributes_Resistance_Fire);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Lightning, GameplayTags.Attributes_Resistance_Lightning);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Physical, GameplayTags.Attributes_Resistance_Physical);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Ice, GameplayTags.Attributes_Resistance_Ice);

	//* Maps of Damage Types to Debuffs
	GameplayTags.DamageTypesToDebuffs.Add(GameplayTags.Damage_Arcane, GameplayTags.Debuff_Arcane);
	GameplayTags.DamageTypesToDebuffs.Add(GameplayTags.Damage_Fire, GameplayTags.Debuff_Burn);
	GameplayTags.DamageTypesToDebuffs.Add(GameplayTags.Damage_Lightning, GameplayTags.Debuff_Lightning);
	GameplayTags.DamageTypesToDebuffs.Add(GameplayTags.Damage_Physical, GameplayTags.Debuff_Stun);
	GameplayTags.DamageTypesToDebuffs.Add(GameplayTags.Damage_Parry, GameplayTags.Debuff_Stun);
	GameplayTags.DamageTypesToDebuffs.Add(GameplayTags.Damage_Ice, GameplayTags.Debuff_Freeze);

	//* Effects
	GameplayTags.Effects_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Effects.HitReact"), FString("TagGranted when Hit Reacting"));
	GameplayTags.Effects_StaminaRegenBlocked = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Effects.StaminaRegenBlocked"), FString("TagGranted when StaminaRegen is Blocked"));
	//GameplayTags.Effects_ParryOn = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Effects.ParryOn"), FString("TagGranted when Parry is On"));

	//* Abilities
	GameplayTags.Abilities_None = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.None"), FString("No Ability - like the nullptr for Ability Tags"));

	GameplayTags.Abilities_Interact_Pickup = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Interact.Pickup"), FString("Pickup Item Ability Tags"));
	GameplayTags.Abilities_Interact_EquipUnequip = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Interact.EquipUnequip"), FString("Equip Unequip Weapon Ability Tags"));
	GameplayTags.Abilities_Interact_TwoHanded = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Interact.TwoHanded"), FString("Equip Two Handed Weapon Ability Tags"));
	
	GameplayTags.Abilities_Targeting = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Targeting"), FString("Targeting Ability Tags"));

	GameplayTags.Abilities_Attack = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Attack"), FString("Attack Ability Tag"));
	GameplayTags.Abilities_Attack_Melee = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Attack.Melee"), FString("Melee Attack Ability Tag"));
	GameplayTags.Abilities_Attack_MidRange = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Attack.MidRange"), FString("MidRange Attack Ability Tag"));
	GameplayTags.Abilities_Attack_MidRange_Bite = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Attack.MidRange.Bite"), FString("MidRange Bite Attack Ability Tag"));
	GameplayTags.Abilities_Attack_Range = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Attack.Range"), FString("Range Attack Ability Tag"));
	GameplayTags.Abilities_Attack_Dash = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Attack.Dash"), FString("Dash Attack Ability Tag"));
	GameplayTags.Abilities_Attack_Smash = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Attack.Smash"), FString("Smash Attack Ability Tag"));
	GameplayTags.Abilities_Cast_Spell = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.CastSpell"), FString("Cst Spell Ability Tag"));

	GameplayTags.Abilities_Projectile_Fire = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Projectile.Fire"), FString("Fire Projectile Ability Tag"));
	GameplayTags.Abilities_Projectile_Arcane = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Projectile.Arcane"), FString("Arcane Projectile Ability Tag"));

	GameplayTags.Abilities_Summon = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Summon"), FString("Summon Ability Tag"));
	GameplayTags.Abilities_Stab = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Stab"), FString("Stab Ability Tag"));
	GameplayTags.Abilities_StandUp = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.StandUp"), FString("StandUp Ability Tag"));

	GameplayTags.Abilities_UseConsumable = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.UseConsumable"), FString("Use Consumable Ability Tag"));

	GameplayTags.Abilities_ShieldOn = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.ShieldOn"), FString("ShieldOn Ability Tag"));
	GameplayTags.Abilities_Parry = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Parry"), FString("Parry Ability Tag"));

	GameplayTags.Abilities_Move_Dodge = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Move.Dodge"), FString("Dodge Ability Tag"));
	GameplayTags.Abilities_Move_Jump = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Move.Jump"), FString("Jump Ability Tag"));
	GameplayTags.Abilities_Move_Sprint = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Move.Sprint"), FString("Sprint Ability Tag"));

	GameplayTags.Abilities_Fire_FireBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Fire.FireBolt"), FString("FireBolt Ability Tag"));
	GameplayTags.Abilities_Fire_Molotov = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Fire.Molotov"), FString("Molotov Attack Ability Tag"));
	GameplayTags.Abilities_Fire_Dracarys = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Fire.Dracarys"), FString("Dracarys Attack Ability Tag"));

	GameplayTags.Abilities_Lightning_Electrocute = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Lightning.Electrocute"), FString("Electrocute Ability Tag"));

	GameplayTags.Abilities_HitReact = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.HitReact"), FString("HitReact Ability"));

	GameplayTags.Abilities_Status_Eligible = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Status.Eligible"), FString("Eligible Status"));
	GameplayTags.Abilities_Status_Equipped = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Status.Equipped"), FString("Equipped Status"));
	GameplayTags.Abilities_Status_Locked = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Status.Locked"), FString("Locked Status"));
	GameplayTags.Abilities_Status_Unlocked = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Status.Unlocked"), FString("Unlocked Status"));

	GameplayTags.Abilities_Type_Offensive = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Type.Offensive"), FString("Type Offensive"));
	GameplayTags.Abilities_Type_Passive = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Type.Passive"), FString("Type Passive"));
	GameplayTags.Abilities_Type_None = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Type.None"), FString("Type None"));

	GameplayTags.Abilities_Passive_StaminaRegen = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Passive.StaminaRegen"), FString("StaminaRegen Ability"));
	GameplayTags.Abilities_Passive_Footstep = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Passive.Footstep"), FString("Footstep Ability"));
	GameplayTags.Abilities_Passive_Footstep = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Passive.Footstep"), FString("Footstep Ability"));

	GameplayTags.Abilities_Turn = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Turn"), FString("Turn Ability"));

	GameplayTags.Abilities_Change_Magic = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Change.Magic"), FString("Change Magic Ability"));
	GameplayTags.Abilities_Change_Weapon = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Change.Weapon"), FString("Change Weapon Ability"));
	GameplayTags.Abilities_Change_Consumable = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Change.Consumable"), FString("Change Consumable Ability"));
	GameplayTags.Abilities_Change_Shield = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Abilities.Change.Shield"), FString("Change Shield Ability"));

	//* Cooldowns
	GameplayTags.Cooldown_Fire_FireBolt = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.Fire.FireBolt"), FString("FireBolt Cooldown Tag"));
	GameplayTags.Cooldown_Fire_Molotov = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.Fire.Molotov"), FString("Molotov Cooldown Tag"));
	GameplayTags.Cooldown_Lightning_Electrocute = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Cooldown.Lightning.Electrocute"), FString("Electrocute Cooldown Tag"));

	//* Combat Sockets
	GameplayTags.CombatSocket_Weapon = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.Weapon"), FString("Weapon Attack"));
	GameplayTags.CombatSocket_RightHand = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.RightHand"), FString("RightHand Attack"));
	GameplayTags.CombatSocket_LeftHand = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.LeftHand"), FString("LeftHand Attack"));
	GameplayTags.CombatSocket_Mouth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.Mouth"), FString("Mouth Attack"));
	GameplayTags.CombatSocket_Tail = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.Tail"), FString("Tail Attack"));
	GameplayTags.CombatSocket_Tip = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("CombatSocket.Tip"), FString("Tip Attack"));

	//* Attack Montages
	GameplayTags.Montage_Attack_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.1"), FString("Attack 1"));
	GameplayTags.Montage_Attack_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.2"), FString("Attack 2"));
	GameplayTags.Montage_Attack_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.3"), FString("Attack 3"));
	GameplayTags.Montage_Attack_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Attack.4"), FString("Attack 4"));

	//* Spell Montages
	GameplayTags.Montage_Spell = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Spell"), FString("Generic Spell Montage"));
	GameplayTags.Montage_Spell_Projectile = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Montage.Spell.Projectile"), FString("Projectile Spell Montage"));

	//* Block Tags
	GameplayTags.Player_Occupied = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Player.Occupied"), FString("Player is occupied"));
	GameplayTags.Player_Block_CursorTrace = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Player.Block.CursorTrace"), FString("Block tracing under ther cursor"));
	GameplayTags.Player_Block_InputHeld = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Player.Block.InputHeld"), FString("Block Input Held callback for input"));
	GameplayTags.Player_Block_InputPressed = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Player.Block.InputPressed"), FString("Block Input Pressed callback for input"));
	GameplayTags.Player_Block_InputReleased = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Player.Block.InputReleased"), FString("Block Input Released callback for input"));
	GameplayTags.Player_Block_Move = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Player.Block.Move"), FString("Block Move"));

	//* Event Tags
	GameplayTags.Event_EquipWeapon = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Event.EquipWeapon"), FString("Equip Weapon Event"));
	GameplayTags.Event_UnequipWeapon = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Event.UnequipWeapon"), FString("Unequip Weapon Event"));
	GameplayTags.Event_EquipShield = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Event.EquipShield"), FString("Equip Shield Event"));
	GameplayTags.Event_UnequipShield = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Event.UnequipShield"), FString("Unequip Shield Event"));
	GameplayTags.Event_EquipUnequipFinish = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Event.EquipUnequipFinish"), FString("EquipUnequipFinish Event"));
	GameplayTags.Event_ConsumeItem = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Event.ConsumeItem"), FString("Consume Item Event"));
	GameplayTags.Event_OpenChest_Start = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Event.OpenChest.Start"), FString("Start Open Chest Event"));
	GameplayTags.Event_OpenChest_End = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Event.OpenChest.End"), FString("End Open Chest Event"));
	GameplayTags.Event_ParryOn = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Event.ParryOn"), FString("Event Parry On"));
	GameplayTags.Event_ParryOff = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Event.ParryOff"), FString("Event Parry Off"));
	GameplayTags.Event_Stab = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Event.Stab"), FString("Event Stab"));
	GameplayTags.Event_Drink = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Event.Drink"), FString("Event Drink"));
	GameplayTags.Event_Footstep_Left = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Event.Footstep.Left"), FString("Event Left Footstep"));
	GameplayTags.Event_Footstep_Right = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Event.Footstep.Right"), FString("Event Right Footstep"));
	GameplayTags.Event_Sanctuary_Active = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Event.Sanctuary.Active"), FString("Event Sanctuary Active"));
	GameplayTags.Event_UpdateWarpTarget = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Event.UpdateWarpTarget"), FString("Event Update Warp Target"));
	GameplayTags.Event_Shoot = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Event.Shoot"), FString("Event Shoot Something"));
	GameplayTags.Event_Arrow_AttachOnHand = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Event.Arrow.AttachOnHand"), FString("Event Attach Arrow On Hand"));
	GameplayTags.Event_Arrow_DetachFromHand = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Event.Arrow.DetachFromHand"), FString("Event Detach Arrow From Hand"));
	GameplayTags.Event_Smash = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Event.Smash"), FString("Event Smash Something"));
	GameplayTags.Event_Effect_Start = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Event.Effect.Start"), FString("Event Start Effect"));
	GameplayTags.Event_Effect_End = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Event.Effect.End"), FString("Event End Effect"));
	GameplayTags.Event_Attack_End = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Event.Attack.End"), FString("Event End Attack"));
	GameplayTags.Event_Dodge_End = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Event.Dodge.End"), FString("Event End Dodge"));
	GameplayTags.Event_Reload = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Event.Reload"), FString("Event Reload"));

	//* Combat Slot Tags
	GameplayTags.Slot_Combat_Weapon = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Slot.Combat.Weapon"), FString("Weapon Combat Slot Tag"));
	GameplayTags.Slot_Combat_Shield = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Slot.Combat.Shield"), FString("Shield Combat Slot Tag"));
	GameplayTags.Slot_Combat_Magic = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Slot.Combat.Magic"), FString("Magic Combat Slot Tag"));
	GameplayTags.Slot_Combat_Consumable = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Slot.Combat.Consumable"), FString("Consumable Combat Slot Tag"));
	GameplayTags.Slot_Combat_0 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Slot.Combat.0"), FString("Combat Slot Tag 0"));
	GameplayTags.Slot_Combat_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Slot.Combat.1"), FString("Combat Slot Tag 1"));
	GameplayTags.Slot_Combat_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Slot.Combat.2"), FString("Combat Slot Tag 2"));
	GameplayTags.Slot_Combat_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Slot.Combat.3"), FString("Combat Slot Tag 3"));

	//* Widget Tags
	GameplayTags.Widget = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Widget"), FString("Widget Tag"));
	GameplayTags.Widget_LevelUp = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Widget.LevelUp"), FString("LevelUp Widget Tag"));
	GameplayTags.Widget_Menu_LevelUp = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Widget.Menu.LevelUp"), FString("LevelUp Menu Widget Tag"));
	GameplayTags.Widget_Menu_Travel = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Widget.Menu.Travel"), FString("Travel Menu Widget Tag"));
	GameplayTags.Widget_Menu_Equip = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Widget.Menu.Equip"), FString("Equip Menu Widget Tag"));
	GameplayTags.Widget_Menu_Sanctuary = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Widget.Menu.Sanctuary"), FString("Sanctuary Menu Widget Tag"));
	GameplayTags.Widget_Menu_Continue = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Widget.Menu.Continue"), FString("Continue Menu Widget Tag"));
	GameplayTags.Widget_Menu_LoadGame = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Widget.Menu.LoadGame"), FString("LoadGame Menu Widget Tag"));
	GameplayTags.Widget_Menu_NewGame = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Widget.Menu.NewGame"), FString("NewGame Menu Widget Tag"));
	GameplayTags.Widget_Menu_Settings = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Widget.Menu.Settings"), FString("Settings Menu Widget Tag"));
	GameplayTags.Widget_Menu_Start = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Widget.Menu.Start"), FString("Start Menu Widget Tag"));
	GameplayTags.Widget_Menu_MainMenu = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Widget.Menu.MainMenu"), FString("MainMenu Menu Widget Tag"));
	GameplayTags.Widget_Menu_DeleteGame = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Widget.Menu.DeleteGame"), FString("DeleteGame Menu Widget Tag"));
	GameplayTags.Widget_Menu_InputHelp = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Widget.Menu.InputHelp"), FString("InputHelp Menu Widget Tag"));
	GameplayTags.Widget_Menu_ChooseGamepad = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Widget.Menu.ChooseGamepad"), FString("ChooseGamepad Menu Widget Tag"));
	GameplayTags.Widget_Menu_Equip_Weapon = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Widget.Menu.Equip.Weapon"), FString("Equip Weapon Menu Widget Tag"));
	GameplayTags.Widget_Menu_Equip_Shield = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Widget.Menu.Equip.Shield"), FString("Equip Shield Menu Widget Tag"));
	GameplayTags.Widget_Menu_Equip_Magic = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Widget.Menu.Equip.Magic"), FString("Equip Magic Menu Widget Tag"));
	GameplayTags.Widget_Menu_Equip_Consumable = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Widget.Menu.Equip.Consumable"), FString("Equip Consumable Menu Widget Tag"));
	GameplayTags.Widget_Menu_QuestionTwo = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Widget.Menu.QuestionTwo"), FString("QuestionTwo Menu Widget Tag"));
	GameplayTags.Widget_Menu_YouDied = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Widget.Menu.YouDied"), FString("YouDied Menu Widget Tag"));
	GameplayTags.Widget_Menu_QuitGame = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Widget.Menu.QuitGame"), FString("QuitGame Menu Widget Tag"));
	GameplayTags.Widget_Menu_InfoMessage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Widget.Menu.InfoMessage"), FString("InfoMessage Menu Widget Tag"));
	GameplayTags.Widget_Menu_InputInfoMessage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Widget.Menu.InputInfoMessage"), FString("Input Info Message Menu Widget Tag"));
	GameplayTags.Widget_Menu_AcquireMagic = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Widget.Menu.AcquireMagic"), FString("Acquire Magic Menu Widget Tag"));
	GameplayTags.Widget_SubMenu_WorldSelector = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Widget.SubMenu.WorldSelector"), FString("WorldSelector Submenu Widget Tag"));
	GameplayTags.Widget_SubMenu_LevelMapSelector = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Widget.SubMenu.LevelMapSelector"), FString("LevelMapSelector Submenu Widget Tag"));
	GameplayTags.Widget_LoadingScreen_Show = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Widget.LoadingScreen.Show"), FString("Show Loading Screen Widget Tag"));
	GameplayTags.Widget_LoadingScreen_Hide = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Widget.LoadingScreen.Hide"), FString("Hide Loading Screen Widget Tag"));
	GameplayTags.Widget_LoadingScreen_Instant = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Widget.LoadingScreen.Instant"), FString("Instant Loading Screen Widget Tag"));
	GameplayTags.Widget_Advise_DeleteGame = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Widget.Advise.DeleteGame"), FString("Advise DeleteGame Widget Tag"));

	//* GameSlot Tags
	GameplayTags.GameSlot_0 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("GameSlot.0"), FString("GameSlot 0 GameplayTag"));
	GameplayTags.GameSlot_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("GameSlot.1"), FString("GameSlot 1 GameplayTag"));
	GameplayTags.GameSlot_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("GameSlot.2"), FString("GameSlot 2 GameplayTag"));
	GameplayTags.GameSlot_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("GameSlot.3"), FString("GameSlot 3 GameplayTag"));
	GameplayTags.GameSlot_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("GameSlot.4"), FString("GameSlot 4 GameplayTag"));
	GameplayTags.GameSlot_5 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("GameSlot.5"), FString("GameSlot 5 GameplayTag"));
	GameplayTags.GameSlot_6 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("GameSlot.6"), FString("GameSlot 6 GameplayTag"));
	GameplayTags.GameSlot_7 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("GameSlot.7"), FString("GameSlot 7 GameplayTag"));
	GameplayTags.GameSlot_8 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("GameSlot.8"), FString("GameSlot 8 GameplayTag"));
	GameplayTags.GameSlot_9 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("GameSlot.9"), FString("GameSlot 9 GameplayTag"));
	GameplayTags.GameSlot_Default = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("GameSlot.Default"), FString("GameSlot Default GameplayTag"));


	//* Sound Tags
	GameplayTags.Sound_UI_Confirm = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Sound.UI.Confirm"), FString("UI Confirm Sound Tag"));
	GameplayTags.Sound_UI_Cancel = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Sound.UI.Cancel"), FString("UI Cancel Sound Tag"));
	GameplayTags.Sound_UI_Select = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Sound.UI.Select"), FString("UI Select Sound Tag"));
	GameplayTags.Sound_UI_Back = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Sound.UI.Back"), FString("UI Back Sound Tag"));
	GameplayTags.Sound_UI_Error = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Sound.UI.Error"), FString("UI Error Sound Tag"));
	GameplayTags.Sound_UI_Hover = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Sound.UI.Hover"), FString("UI Hover Sound Tag"));
	GameplayTags.Sound_UI_Open = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Sound.UI.Open"), FString("UI Open Sound Tag"));
	GameplayTags.Sound_UI_Close = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Sound.UI.Close"), FString("UI Close Sound Tag"));
	GameplayTags.Sound_UI_Scroll = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Sound.UI.Scroll"), FString("UI Scroll Sound Tag"));

	GameplayTags.World = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("World"), FString("Generic World Tag"));
	GameplayTags.World_Asgard = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("World.Asgard"), FString("Asgard World Tag"));
	GameplayTags.World_Alfheim = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("World.Alfheim"), FString("Alfheim World Tag"));
	GameplayTags.World_Niflheim = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("World.Niflheim"), FString("Niflheim World Tag"));
	GameplayTags.World_Niflheim_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("World.Niflheim.1"), FString("Niflheim 1 World Tag"));
	GameplayTags.World_Niflheim_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("World.Niflheim.2"), FString("Niflheim 2 World Tag"));
	GameplayTags.World_Niflheim_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("World.Niflheim.3"), FString("Niflheim 3 World Tag"));
	GameplayTags.World_Vanaheim = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("World.Vanaheim"), FString("Vanaheim World Tag"));
	GameplayTags.World_Jotunheim = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("World.Jotunheim"), FString("Jotunheim World Tag"));
	GameplayTags.World_Jotunheim_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("World.Jotunheim.1"), FString("Jotunheim 1 World Tag"));
	GameplayTags.World_Jotunheim_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("World.Jotunheim.2"), FString("Jotunheim 2 World Tag"));
	GameplayTags.World_Jotunheim_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("World.Jotunheim.3"), FString("Jotunheim 3 World Tag"));
	GameplayTags.World_Midgard = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("World.Midgard"), FString("Midgard World Tag"));
	GameplayTags.World_Midgard_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("World.Midgard.1"), FString("Midgard 1 World Tag"));;
	GameplayTags.World_Midgard_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("World.Midgard.2"), FString("Midgard 2 World Tag"));;
	GameplayTags.World_Midgard_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("World.Midgard.3"), FString("Midgard 3 World Tag"));;
	GameplayTags.World_Midgard_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("World.Midgard.4"), FString("Midgard 4 World Tag"));;
	GameplayTags.World_Midgard_5 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("World.Midgard.5"), FString("Midgard 5 World Tag"));;
	GameplayTags.World_Svartalfheim = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("World.Svartalfheim"), FString("Svartalfheim World Tag"));
	GameplayTags.World_Svartalfheim_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("World.Svartalfheim.1"), FString("Svartalfheim 1 World Tag"));
	GameplayTags.World_Svartalfheim_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("World.Svartalfheim.2"), FString("Svartalfheim 2 World Tag"));
	GameplayTags.World_Svartalfheim_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("World.Svartalfheim.3"), FString("Svartalfheim 3 World Tag"));
	GameplayTags.World_Muspelheim = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("World.Muspelheim"), FString("Muspelheim World Tag"));
	GameplayTags.World_Helheim = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("World.Helheim"), FString("Helheim World Tag"));
	GameplayTags.World_Helheim_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("World.Helheim.1"), FString("Helheim 1 World Tag"));
	GameplayTags.World_Helheim_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("World.Helheim.2"), FString("Helheim 2 World Tag"));
	GameplayTags.World_Helheim_3 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("World.Helheim.3"), FString("Helheim 3 World Tag"));

}
