// © 2024 Olinick Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
/**
 * AuraGameplayTags
 *
 * Singleton containing native Gameplay Tags
 */

struct FAuraGameplayTags
{
public:
	static const FAuraGameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();

	//* Primary Attributes
	FGameplayTag Attributes_Primary_Dexterity;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Resilience;
	FGameplayTag Attributes_Primary_Strengh;
	FGameplayTag Attributes_Primary_Vigor;

	//* Secondary Attributes
	FGameplayTag Attributes_Secondary_ArcaneAttackDamage;
	FGameplayTag Attributes_Secondary_FireAttackDamage;
	FGameplayTag Attributes_Secondary_LightningAttackDamage;
	FGameplayTag Attributes_Secondary_IceAttackDamage;
	FGameplayTag Attributes_Secondary_PhysicalAttackDamage;
	FGameplayTag Attributes_Secondary_Armor;
	FGameplayTag Attributes_Secondary_ArmorPenetration;
	FGameplayTag Attributes_Secondary_CriticalHitChance;
	FGameplayTag Attributes_Secondary_CriticalHitDamage;
	FGameplayTag Attributes_Secondary_CriticalHitResistance;
	FGameplayTag Attributes_Secondary_StaminaRegeneration;
	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxMana;
	FGameplayTag Attributes_Secondary_MaxStamina;



	//* Vital Attributes
	FGameplayTag Attributes_Vital_Health;
	FGameplayTag Attributes_Vital_Mana;
	FGameplayTag Attributes_Vital_Stamina;
	FGameplayTag Attributes_LevelUp_Level;
	FGameplayTag Attributes_LevelUp_XP;
	FGameplayTag Attributes_LevelUp_XPNeeded;


	//* Meta Attributes
	FGameplayTag Attributes_Meta_IncomingXP;
	FGameplayTag Attributes_Meta_ResidualDamage;

	//* InputTags
	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_LMB_Shifted;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_RMB_Shifted;
	FGameplayTag InputTag_MMB;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;
	FGameplayTag InputTag_Passive_1;
	FGameplayTag InputTag_Passive_2;
	FGameplayTag InputTag_E;
	FGameplayTag InputTag_F;
	FGameplayTag InputTag_Q;
	FGameplayTag InputTag_Space;
	FGameplayTag InputTag_Esc;
	FGameplayTag InputTag_Up;
	FGameplayTag InputTag_Down;
	FGameplayTag InputTag_Left;
	FGameplayTag InputTag_Right;
	FGameplayTag InputTag_Move;
	FGameplayTag InputTag_Ok;
	FGameplayTag InputTag_Back;
	FGameplayTag InputTag_Nav_L;
	FGameplayTag InputTag_Nav_R;

	//* Button Tags
	FGameplayTag Button_Confirm;
	FGameplayTag Button_Cancel;
	FGameplayTag Button_0;
	FGameplayTag Button_1;
	FGameplayTag Button_2;
	FGameplayTag Button_3;
	FGameplayTag Button_4;
	FGameplayTag Button_5;
	FGameplayTag Button_6;
	FGameplayTag Button_7;
	FGameplayTag Button_8;
	FGameplayTag Button_9;
	FGameplayTag Button_10;
	FGameplayTag Button_11;
	FGameplayTag Button_12;
	FGameplayTag Button_13;
	FGameplayTag Button_14;
	FGameplayTag Button_15;
	FGameplayTag Button_16;
	FGameplayTag Button_17;
	FGameplayTag Button_18;
	FGameplayTag Button_19;
	FGameplayTag Button_20;
	FGameplayTag Button_21;
	FGameplayTag Button_22;
	FGameplayTag Button_23;
	FGameplayTag Button_24;
	FGameplayTag Button_25;
	FGameplayTag Button_26;
	FGameplayTag Button_27;
	FGameplayTag Button_28;
	FGameplayTag Button_29;
	FGameplayTag Button_30;
	FGameplayTag Button_31;
	FGameplayTag Button_32;
	FGameplayTag Button_33;
	FGameplayTag Button_34;
	FGameplayTag Button_35;
	FGameplayTag Button_36;
	FGameplayTag Button_37;
	FGameplayTag Button_38;
	FGameplayTag Button_39;

	//* Damage
	FGameplayTag Damage;
	FGameplayTag DamageBonus;

	//* Damage Types
	FGameplayTag Damage_Arcane;
	FGameplayTag Damage_Fire;
	FGameplayTag Damage_Lightning;
	FGameplayTag Damage_Ice;
	FGameplayTag Damage_Physical;

	FGameplayTag Damage_Parry;

	//* Resistances
	FGameplayTag Attributes_Resistance_Arcane;
	FGameplayTag Attributes_Resistance_Fire;
	FGameplayTag Attributes_Resistance_Lightning;
	FGameplayTag Attributes_Resistance_Ice;
	FGameplayTag Attributes_Resistance_Physical;

	//* Debuff
	FGameplayTag Debuff_Arcane;
	FGameplayTag Debuff_Burn;
	FGameplayTag Debuff_Stun;
	FGameplayTag Debuff_Lightning;
	FGameplayTag Debuff_Freeze;

	FGameplayTag Debuff_Chance;
	FGameplayTag Debuff_Damage;
	FGameplayTag Debuff_Duration;
	FGameplayTag Debuff_Frequency;

	FGameplayTag Debuff_Disabled;

	//* TMaps
	TMap<FGameplayTag, FGameplayTag> DamageTypesToResistances;
	TMap<FGameplayTag, FGameplayTag> DamageTypesToDebuffs;

	//* Effects
	FGameplayTag Effects_HitReact;
	FGameplayTag Effects_StaminaRegenBlocked;

	//* Abilities
	FGameplayTag Abilities_None;

	FGameplayTag Abilities_Interact_Pickup;
	FGameplayTag Abilities_Interact_EquipUnequip;
	FGameplayTag Abilities_Interact_TwoHanded;

	FGameplayTag Abilities_Targeting;

	FGameplayTag Abilities_Attack;
	FGameplayTag Abilities_Attack_Melee;
	FGameplayTag Abilities_Attack_MidRange;
	FGameplayTag Abilities_Attack_MidRange_Bite;
	FGameplayTag Abilities_Attack_Range;
	FGameplayTag Abilities_Attack_Dash;
	FGameplayTag Abilities_Attack_Smash;
	FGameplayTag Abilities_Cast_Spell;

	FGameplayTag Abilities_Projectile_Fire;
	FGameplayTag Abilities_Projectile_Arcane;

	FGameplayTag Abilities_Summon;
	FGameplayTag Abilities_Stab;
	FGameplayTag Abilities_StandUp;

	FGameplayTag Abilities_UseConsumable;

	FGameplayTag Abilities_ShieldOn;
	FGameplayTag Abilities_Parry;

	FGameplayTag Abilities_Move_Dodge;
	FGameplayTag Abilities_Move_Jump;
	FGameplayTag Abilities_Move_Sprint;

	FGameplayTag Abilities_Fire_FireBolt;
	FGameplayTag Abilities_Fire_Molotov;
	FGameplayTag Abilities_Fire_Dracarys;

	FGameplayTag Abilities_Lightning_Electrocute;

	FGameplayTag Abilities_HitReact;

	FGameplayTag Abilities_Status_Locked;
	FGameplayTag Abilities_Status_Eligible;
	FGameplayTag Abilities_Status_Unlocked;
	FGameplayTag Abilities_Status_Equipped;

	FGameplayTag Abilities_Type_Offensive;
	FGameplayTag Abilities_Type_Passive;
	FGameplayTag Abilities_Type_None;

	FGameplayTag Abilities_Passive_StaminaRegen;
	FGameplayTag Abilities_Passive_Footstep;

	FGameplayTag Abilities_Turn;

	FGameplayTag Abilities_Change_Magic;
	FGameplayTag Abilities_Change_Weapon;
	FGameplayTag Abilities_Change_Consumable;
	FGameplayTag Abilities_Change_Shield;

	//* Cooldowns
	FGameplayTag Cooldown_Fire_FireBolt;
	FGameplayTag Cooldown_Fire_Molotov;
	FGameplayTag Cooldown_Lightning_Electrocute;

	//* Combat Sockets
	FGameplayTag CombatSocket_Weapon;
	FGameplayTag CombatSocket_RightHand;
	FGameplayTag CombatSocket_LeftHand;
	FGameplayTag CombatSocket_Mouth;
	FGameplayTag CombatSocket_Tail;
	FGameplayTag CombatSocket_Tip;

	//* Attack Montages /// DEPRECATED
	FGameplayTag Montage_Attack_1;
	FGameplayTag Montage_Attack_2;
	FGameplayTag Montage_Attack_3;
	FGameplayTag Montage_Attack_4;

	//* Spell Montage

	FGameplayTag Montage_Spell;
	FGameplayTag Montage_Spell_Projectile;

	//* Block Tags
	FGameplayTag Player_Occupied;
	FGameplayTag Player_Block_InputPressed;
	FGameplayTag Player_Block_InputHeld;
	FGameplayTag Player_Block_InputReleased;
	FGameplayTag Player_Block_Move;
	FGameplayTag Player_Block_CursorTrace;

	//* Event Tags
	FGameplayTag Event_EquipWeapon;
	FGameplayTag Event_UnequipWeapon;
	FGameplayTag Event_EquipShield;
	FGameplayTag Event_UnequipShield;
	FGameplayTag Event_EquipUnequipFinish;
	FGameplayTag Event_ConsumeItem;
	FGameplayTag Event_OpenChest_Start;
	FGameplayTag Event_OpenChest_End;
	FGameplayTag Event_ParryOn;
	FGameplayTag Event_ParryOff;
	FGameplayTag Event_Stab;
	FGameplayTag Event_Drink;
	FGameplayTag Event_Footstep_Left;
	FGameplayTag Event_Footstep_Right;
	FGameplayTag Event_Sanctuary_Active;
	FGameplayTag Event_UpdateWarpTarget;
	FGameplayTag Event_Shoot;
	FGameplayTag Event_Arrow_AttachOnHand;
	FGameplayTag Event_Arrow_DetachFromHand;
	FGameplayTag Event_Smash;
	FGameplayTag Event_Effect_Start;
	FGameplayTag Event_Effect_End;
	FGameplayTag Event_Attack_End;
	FGameplayTag Event_Dodge_End;
	FGameplayTag Event_Reload;

	//* Combat Slot Tags
	FGameplayTag Slot_Combat_Weapon;
	FGameplayTag Slot_Combat_Shield;
	FGameplayTag Slot_Combat_Magic;
	FGameplayTag Slot_Combat_Consumable;
	FGameplayTag Slot_Combat_0;
	FGameplayTag Slot_Combat_1;
	FGameplayTag Slot_Combat_2;
	FGameplayTag Slot_Combat_3;

	//* Widget Tags
	FGameplayTag Widget;
	FGameplayTag Widget_LevelUp;
	FGameplayTag Widget_Menu_LevelUp;
	FGameplayTag Widget_Menu_Travel;
	FGameplayTag Widget_Menu_Equip;
	FGameplayTag Widget_Menu_Sanctuary;
	FGameplayTag Widget_Menu_Continue;
	FGameplayTag Widget_Menu_LoadGame;
	FGameplayTag Widget_Menu_NewGame;
	FGameplayTag Widget_Menu_Settings;
	FGameplayTag Widget_Menu_Start;
	FGameplayTag Widget_Menu_MainMenu;
	FGameplayTag Widget_Menu_DeleteGame;
	FGameplayTag Widget_Menu_InputHelp;
	FGameplayTag Widget_Menu_ChooseGamepad;
	FGameplayTag Widget_Menu_Equip_Weapon;
	FGameplayTag Widget_Menu_Equip_Shield;
	FGameplayTag Widget_Menu_Equip_Magic;
	FGameplayTag Widget_Menu_Equip_Consumable;
	FGameplayTag Widget_Menu_QuestionTwo;
	FGameplayTag Widget_Menu_YouDied;
	FGameplayTag Widget_Menu_QuitGame;
	FGameplayTag Widget_Menu_InfoMessage;
	FGameplayTag Widget_Menu_InputInfoMessage;
	FGameplayTag Widget_Menu_AcquireMagic;
	FGameplayTag Widget_SubMenu_WorldSelector;
	FGameplayTag Widget_SubMenu_LevelMapSelector;
	FGameplayTag Widget_LoadingScreen_Show;
	FGameplayTag Widget_LoadingScreen_Hide;
	FGameplayTag Widget_LoadingScreen_Instant;
	FGameplayTag Widget_Advise_DeleteGame;
	
	//* GameSlot Tags
	FGameplayTag GameSlot_0;
	FGameplayTag GameSlot_1;
	FGameplayTag GameSlot_2;
	FGameplayTag GameSlot_3;
	FGameplayTag GameSlot_4;
	FGameplayTag GameSlot_5;
	FGameplayTag GameSlot_6;
	FGameplayTag GameSlot_7;
	FGameplayTag GameSlot_8;
	FGameplayTag GameSlot_9;
	FGameplayTag GameSlot_Default;

	//* Sound Tags
	FGameplayTag Sound_UI_Confirm;
	FGameplayTag Sound_UI_Cancel;
	FGameplayTag Sound_UI_Select;
	FGameplayTag Sound_UI_Back;
	FGameplayTag Sound_UI_Error;
	FGameplayTag Sound_UI_Hover;
	FGameplayTag Sound_UI_Open;
	FGameplayTag Sound_UI_Close;
	FGameplayTag Sound_UI_Scroll;

	FGameplayTag World;
	FGameplayTag World_Asgard;
	FGameplayTag World_Alfheim;
	FGameplayTag World_Niflheim;
	FGameplayTag World_Niflheim_1;
	FGameplayTag World_Niflheim_2;
	FGameplayTag World_Niflheim_3;
	FGameplayTag World_Vanaheim;
	FGameplayTag World_Jotunheim;
	FGameplayTag World_Jotunheim_1;
	FGameplayTag World_Jotunheim_2;
	FGameplayTag World_Jotunheim_3;
	FGameplayTag World_Midgard;
	FGameplayTag World_Midgard_1;
	FGameplayTag World_Midgard_2;
	FGameplayTag World_Midgard_3;
	FGameplayTag World_Midgard_4;
	FGameplayTag World_Midgard_5;
	FGameplayTag World_Svartalfheim;
	FGameplayTag World_Svartalfheim_1;
	FGameplayTag World_Svartalfheim_2;
	FGameplayTag World_Svartalfheim_3;
	FGameplayTag World_Muspelheim;
	FGameplayTag World_Helheim;
	FGameplayTag World_Helheim_1;
	FGameplayTag World_Helheim_2;
	FGameplayTag World_Helheim_3;

private:
	static FAuraGameplayTags GameplayTags;
};