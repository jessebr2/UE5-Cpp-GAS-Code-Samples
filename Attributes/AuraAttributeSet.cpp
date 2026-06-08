// © 2024 Olinick Games. All rights reserved.


#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AuraAbilityTypes.h"
#include "Aura/AuraLogChannels.h"
#include "AuraGameplayTags.h"
#include "GameplayEffectComponents/TargetTagsGameplayEffectComponent.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"
#include "Interaction/CombatInterface.h"
#include "Interaction/EnemyInterface.h"
#include "Interaction/PlayerInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Player/AuraPlayerController.h"
#include "Net/UnrealNetwork.h"

UAuraAttributeSet::UAuraAttributeSet()
{
	const FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();

	/* Primary Attributes */
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Dexterity, GetDexterityAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Intelligence, GetIntelligenceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Resilience, GetResilienceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Strengh, GetStrengthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Vigor, GetVigorAttribute);

	/* Secondary Attributes */
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_ArcaneAttackDamage, GetArcaneAttackDamageAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_FireAttackDamage, GetFireAttackDamageAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_LightningAttackDamage, GetLightningAttackDamageAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_IceAttackDamage, GetIceAttackDamageAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_PhysicalAttackDamage, GetPhysicalAttackDamageAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_Armor, GetArmorAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_ArmorPenetration, GetArmorPenetrationAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_CriticalHitChance, GetCriticalHitChanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_CriticalHitDamage, GetCriticalHitDamageAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_CriticalHitResistance, GetCriticalHitResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_StaminaRegeneration, GetStaminaRegenerationAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_MaxHealth, GetMaxHealthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_MaxMana, GetMaxManaAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_MaxStamina, GetMaxStaminaAttribute);

	/* Resistance Attributes */
	TagsToAttributes.Add(GameplayTags.Attributes_Resistance_Arcane, GetResistanceArcaneAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Resistance_Fire, GetResistanceFireAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Resistance_Lightning, GetResistanceLightningAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Resistance_Ice, GetResistanceIceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Resistance_Physical, GetResistancePhysicalAttribute);

}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	// Primary Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Resilience, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Vigor, COND_None, REPNOTIFY_Always);

	// Secondary Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ArmorPenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalHitChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalHitDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, CriticalHitResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, StaminaRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, MaxStamina, COND_None, REPNOTIFY_Always);

	// Resistance Attributes
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ResistanceArcane, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ResistanceFire, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ResistanceLightning, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, ResistancePhysical, COND_None, REPNOTIFY_Always);

	// VitalAttributes
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet, Mana, COND_None, REPNOTIFY_Always);
}

void UAuraAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	}
	if (Attribute == GetStaminaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxStamina());
	}
}

void UAuraAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{
	//Source = causer of the effect, Target = target of the effect (Owner of this AS)

	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();
		if (!Props.SourceController && Props.SourceAvatarActor)
		{
			if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}
		if (Props.SourceController)
		{
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}
}

void UAuraAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties Props;
	SetEffectProperties(Data, Props);

	if (Props.TargetCharacter && Props.TargetCharacter->Implements<UCombatInterface>() && ICombatInterface::Execute_IsDead(Props.TargetCharacter)) return;

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
	}
	if (Data.EvaluatedData.Attribute == GetStaminaAttribute())
	{
		SetStamina(FMath::Clamp(GetStamina(), 0.f, GetMaxStamina()));
	}
	if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{
		HandleIncomingDamage(Props);
	}
	if (Data.EvaluatedData.Attribute == GetIncomingXPAttribute())
	{
		HandleIncomingXP(Props);
	}
}

void UAuraAttributeSet::HandleIncomingDamage(FEffectProperties& Props)
{
	float LocalIncomingDamage = GetIncomingDamage();
	SetIncomingDamage(0.f);

	/* Combo */
	StartResidualDamage(Props, LocalIncomingDamage);

	bool bBlockedHit = false;
	const bool bTargetIsCombatInterface = Props.TargetAvatarActor && Props.TargetAvatarActor->Implements<UCombatInterface>();
	if (LocalIncomingDamage > 0.1f)
	{
		if (bTargetIsCombatInterface && ICombatInterface::Execute_IsShielding(Props.TargetAvatarActor) && ICombatInterface::Execute_IsCoveredShieldAngle(Props.TargetAvatarActor, Props.SourceAvatarActor))
		{
			if (ICombatInterface::Execute_IsInvulnerable(Props.TargetAvatarActor)) return;

			const float ShieldDefense = ICombatInterface::Execute_GetShieldDefense(Props.TargetAvatarActor);

			const UCharacterClassInfo* CharacterClassInfo = UAuraAbilitySystemLibrary::GetCharacterClassInfo(Props.TargetAvatarActor);

			// Shield Defense Coefficient
			const FRealCurve* ShieldDefenseCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("ShieldDefense"), FString());
			const float ShieldDefenseCoefficient = ShieldDefenseCurve->Eval(GetResilience());

			const float MaxDamageDefense = ShieldDefense * ShieldDefenseCoefficient;
			float DamageDefended = FMath::Min(MaxDamageDefense, LocalIncomingDamage);


			if (Props.TargetAvatarActor->Implements<UPlayerInterface>())
			{
				// Shield Cost Coefficient
				const FRealCurve* ShieldCostCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("ShieldCost"), FString());
				const float ShieldCostCoefficient = ShieldCostCurve->Eval(GetDexterity());
				const float DefenseCost = DamageDefended * ShieldCostCoefficient;

				if (GetStamina() < DefenseCost)
				{
					DamageDefended = 0.f;
					UAuraAbilitySystemLibrary::SetIsSuccessfullDebuff(Props.EffectContextHandle, true);
					UAuraAbilitySystemLibrary::SetDebuffDamage(Props.EffectContextHandle, 0.f);
					UAuraAbilitySystemLibrary::SetDebuffDuration(Props.EffectContextHandle, 2.f);
					SetStamina(0.f);
				}
				else
				{
					const float NewStamina = GetStamina() - DefenseCost;
					SetStamina(FMath::Clamp(NewStamina, 0.f, GetMaxStamina()));
				}
			}
			if (DamageDefended > 0.1f)
			{
				bBlockedHit = true;
				LocalIncomingDamage -= DamageDefended;
				const AActor* DamageCauser = UAuraAbilitySystemLibrary::GetDamageCauser(Props.EffectContextHandle);
				if (DamageCauser && DamageCauser->ActorHasTag(FName("Weapon")) && LocalIncomingDamage < .1f) // DamageCauser is a Weapon And All damage was defended, The Attacker will get Hit React
				{
					ICombatInterface::Execute_DirectionalHitReact(Props.SourceAvatarActor, Props.TargetAvatarActor->GetActorLocation());
				}
			}
		}
		
		const float NewHealth = GetHealth() - LocalIncomingDamage;
		
		SetHealth(FMath::Clamp(NewHealth, 0.f, GetMaxHealth()));
		ICombatInterface::Execute_DisableWeaponCollision(Props.TargetAvatarActor);
		
		const bool bStabHit = UAuraAbilitySystemLibrary::IsStabHit(Props.EffectContextHandle);
		const bool bFatal = NewHealth < .1f;

		if (bTargetIsCombatInterface)
		{
			if (bFatal)
			{
				ICombatInterface::Execute_SpawnReactEffect(Props.TargetAvatarActor, UAuraAbilitySystemLibrary::GetImpactPoint(Props.EffectContextHandle), nullptr);
				ICombatInterface::Execute_Die(Props.TargetAvatarActor, UAuraAbilitySystemLibrary::GetDeathImpulse(Props.EffectContextHandle));
				if (Props.SourceAvatarActor->Implements<UPlayerInterface>())
				{
					SendXPEvent(Props);
				}
			}
			else 
			{
				if (bBlockedHit)
				{
					ICombatInterface::Execute_ShieldingReact(Props.TargetAvatarActor);
				}
				else
				{
					ICombatInterface::Execute_SpawnReactEffect(Props.TargetAvatarActor, UAuraAbilitySystemLibrary::GetImpactPoint(Props.EffectContextHandle), nullptr);
					if (bStabHit)
					{
						if (ICombatInterface::Execute_CanBeKnocked(Props.TargetAvatarActor))
						{
							const FVector KnockBackForce = UAuraAbilitySystemLibrary::GetKnockbackForce(Props.EffectContextHandle);
							ICombatInterface::Execute_ApplyKnockBackForce(Props.TargetAvatarActor, KnockBackForce);
						}
						else
						{
							//ICombatInterface::Execute_GetStunned(Props.TargetAvatarActor, Props, .5f);
							ICombatInterface::Execute_DirectionalHitReact(Props.TargetAvatarActor, Props.SourceAvatarActor->GetActorLocation());
						}
					}
					else
					{
						ICombatInterface::Execute_DirectionalHitReact(Props.TargetAvatarActor, Props.SourceAvatarActor->GetActorLocation());
					}
				}
				ICombatInterface::Execute_ReceiveDamageReport(Props.TargetAvatarActor);
				ICombatInterface::Execute_SetCombatTarget(Props.TargetAvatarActor, Props.SourceAvatarActor);
			}
		}
		

		//const bool bBlockedHit = UAuraAbilitySystemLibrary::IsBlockedHit(Props.EffectContextHandle);
		const bool bCriticalHit = UAuraAbilitySystemLibrary::IsCriticalHit(Props.EffectContextHandle);
		
		const FGameplayTag DamageType = UAuraAbilitySystemLibrary::GetDamageType(Props.EffectContextHandle);

		

  		ShowFloatingText(Props, LocalIncomingDamage, bBlockedHit, bCriticalHit, bStabHit);

		//const FGameplayTag DamageType = UAuraAbilitySystemLibrary::GetDamageType(Props.EffectContextHandle);


		//if (Props.TargetASC->HasMatchingGameplayTag(FAuraGameplayTags::Get().Debuff_Stun))
		//{
		//	Props.TargetASC->RemoveLooseGameplayTag(FAuraGameplayTags::Get().Debuff_Stun);
		//}

		if (UAuraAbilitySystemLibrary::IsSuccessfulDebuff(Props.EffectContextHandle) && !bFatal)
		{
			Debuff(Props);
		}
	}
}

void UAuraAttributeSet::HandleIncomingXP(const FEffectProperties& Props)
{
	const float LocalIncomingXP = GetIncomingXP();
	SetIncomingXP(0.f);

	// Source Character is the owner, since GA_ListenForEvents applies GE_EventBasedEffect, adding to IncomingXP
	if (Props.SourceCharacter->Implements<UPlayerInterface>()/* && Props.SourceCharacter->Implements<UCombatInterface>()*/)
	{
		IPlayerInterface::Execute_AddToXP(Props.SourceCharacter, LocalIncomingXP);
	}
}

void UAuraAttributeSet::Debuff(const FEffectProperties& Props)
{
	const FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();
	FGameplayEffectContextHandle EffectContext = Props.SourceASC->MakeEffectContext();
	EffectContext.AddSourceObject(Props.SourceAvatarActor);

	const FGameplayTag DamageType = UAuraAbilitySystemLibrary::GetDamageType(Props.EffectContextHandle);
	const float DebuffDamage = UAuraAbilitySystemLibrary::GetDebuffDamage(Props.EffectContextHandle);
	const float DebuffDuration = UAuraAbilitySystemLibrary::GetDebuffDuration(Props.EffectContextHandle);
	const float DebuffFrequency = UAuraAbilitySystemLibrary::GetDebuffFrequency(Props.EffectContextHandle);

	FString DebuffName = FString::Printf(TEXT("DynamicDebuff_%s"), *DamageType.ToString());
	UGameplayEffect* Effect = NewObject<UGameplayEffect>(GetTransientPackage(), FName(DebuffName));

	Effect->DurationPolicy = EGameplayEffectDurationType::HasDuration;
	Effect->Period = DebuffFrequency;
	Effect->DurationMagnitude = FScalableFloat(DebuffDuration);

	UTargetTagsGameplayEffectComponent* TargetTagsComponent = NewObject<UTargetTagsGameplayEffectComponent>(Effect);
	if (TargetTagsComponent)
	{
		// Configure the tags to be granted
		FInheritedTagContainer TagContainer;
		const FGameplayTag DebuffTag = GameplayTags.DamageTypesToDebuffs[DamageType];
		TagContainer.AddTag(DebuffTag);

		// Apply the configured tags to the gameplay effect
		TargetTagsComponent->SetAndApplyTargetTagChanges(TagContainer);
	}

	Effect->StackingType = EGameplayEffectStackingType::AggregateBySource;
	Effect->StackLimitCount = 1;

	const int32 Index = Effect->Modifiers.Num();
	Effect->Modifiers.Add(FGameplayModifierInfo());
	FGameplayModifierInfo& ModifierInfo = Effect->Modifiers[Index];

	ModifierInfo.ModifierMagnitude = FScalableFloat(DebuffDamage);
	ModifierInfo.ModifierOp = EGameplayModOp::Additive;
	ModifierInfo.Attribute = UAuraAttributeSet::GetIncomingDamageAttribute();

	if (FGameplayEffectSpec* MutableSpec = new FGameplayEffectSpec(Effect, EffectContext, 1.f))
	{
		FAuraGameplayEffectContext* AuraContext = static_cast<FAuraGameplayEffectContext*>(MutableSpec->GetContext().Get());
		TSharedPtr<FGameplayTag> DebuffDamageType = MakeShareable(new FGameplayTag(DamageType));
		AuraContext->SetDamageType(DebuffDamageType);

		Props.TargetASC->ApplyGameplayEffectSpecToSelf(*MutableSpec);
	}
}

void UAuraAttributeSet::IncrementPrimaryAttribte(FGameplayTag AttributeTag, int32 IncrementValue)
{
	if (AttributeTag.MatchesTagExact(FAuraGameplayTags::Get().Attributes_Primary_Dexterity))
	{
		SetDexterity(GetDexterity() + IncrementValue);
	}
	else if (AttributeTag.MatchesTagExact(FAuraGameplayTags::Get().Attributes_Primary_Intelligence))
	{
		SetIntelligence(GetIntelligence() + IncrementValue);
	}
	else if (AttributeTag.MatchesTagExact(FAuraGameplayTags::Get().Attributes_Primary_Resilience))
	{
		SetResilience(GetResilience() + IncrementValue);
	}
	else if (AttributeTag.MatchesTagExact(FAuraGameplayTags::Get().Attributes_Primary_Strengh))
	{
		SetStrength(GetStrength() + IncrementValue);
	}
	else if (AttributeTag.MatchesTagExact(FAuraGameplayTags::Get().Attributes_Primary_Vigor))
	{
		SetVigor(GetVigor() + IncrementValue);
	}
}

void UAuraAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);

	if (Attribute == GetMaxHealthAttribute() && bTopOffHealth)
	{
		SetHealth(GetMaxHealth());
		bTopOffHealth = false;
	}
	if (Attribute == GetMaxManaAttribute() && bTopOffMana)
	{
		SetMana(GetMaxMana());
		bTopOffMana = false;
	}
	if (Attribute == GetMaxStaminaAttribute() && bTopOffStamina)
	{
		SetStamina(GetMaxStamina());
		bTopOffStamina = false;
	}
}

void UAuraAttributeSet::ShowFloatingText(const FEffectProperties& Props, const float& LocalIncomingDamage, bool bBlockedHit, bool bCriticalHit, bool bStabHit)
{
	if (Props.SourceCharacter != Props.TargetCharacter)
	{
		if (Props.SourceCharacter->ActorHasTag(FName("Player")))
		{
			if (AAuraPlayerController* PC = Cast<AAuraPlayerController>(Props.SourceCharacter->Controller))
			{
				PC->ShowDamageNumber(LocalIncomingDamage, Props.TargetCharacter, bBlockedHit, bCriticalHit, bStabHit, Props.SourceCharacter);
				return;
			}
		}
		if (Props.TargetCharacter->ActorHasTag(FName("Player")))
		{
			if (AAuraPlayerController* PC = Cast<AAuraPlayerController>(Props.TargetCharacter->Controller))
			{
				PC->ShowDamageNumber(LocalIncomingDamage, Props.TargetCharacter, bBlockedHit, bCriticalHit, bStabHit, Props.SourceCharacter);
			}
		}
		
	}
}

void UAuraAttributeSet::SendXPEvent(const FEffectProperties& Props)
{
	if (Props.TargetCharacter->Implements<UCombatInterface>())
	{
		const int32 TargetLevel = ICombatInterface::Execute_GetPlayerLevel(Props.TargetCharacter);
		const ECharacterClass TargetClass = ICombatInterface::Execute_GetCharacterClass(Props.TargetCharacter);
		const int32 XPReward = UAuraAbilitySystemLibrary::GetXPRewardForClassAndLevel(Props.TargetCharacter, TargetClass, TargetLevel);

		const FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();
		FGameplayEventData Payload;
		Payload.EventTag = GameplayTags.Attributes_Meta_IncomingXP;
		Payload.EventMagnitude = XPReward;
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(Props.SourceCharacter, GameplayTags.Attributes_Meta_IncomingXP, Payload);
	}
}

void UAuraAttributeSet::StartResidualDamage(const FEffectProperties& Props, float FullDamage)
{
	SetResidualDamage(GetResidualDamage() + FullDamage * .1f);

	FTimerHandle ComboTimer;
	if (Props.SourceCharacter)
		Props.SourceCharacter->GetWorldTimerManager().SetTimer(ComboTimer, this, &UAuraAttributeSet::ResetResidualDamage, ComboTime, false);
	else
		SetResidualDamage(0.f);
}

void UAuraAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Strength, OldStrength);
}

void UAuraAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Intelligence, OldIntelligence);
}

void UAuraAttributeSet::OnRep_Resilience(const FGameplayAttributeData& OldResilience) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Resilience, OldResilience);
}

void UAuraAttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldVigor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Vigor, OldVigor);
}

void UAuraAttributeSet::OnRep_Dexterity(const FGameplayAttributeData& OldDexterity) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Dexterity, OldDexterity);
}

void UAuraAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Health, OldHealth);
}

void UAuraAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Mana, OldMana);
}

void UAuraAttributeSet::OnRep_Stamina(const FGameplayAttributeData& OldStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Stamina, OldStamina);
}

void UAuraAttributeSet::OnRep_ArcaneAttackDamage(const FGameplayAttributeData& OldArcaneAttackDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ArcaneAttackDamage, OldArcaneAttackDamage);
}

void UAuraAttributeSet::OnRep_FireAttackDamage(const FGameplayAttributeData& OldFireAttackDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, FireAttackDamage, OldFireAttackDamage);
}

void UAuraAttributeSet::OnRep_LightningAttackDamage(const FGameplayAttributeData& OldLightningAttackDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, LightningAttackDamage, OldLightningAttackDamage);
}

void UAuraAttributeSet::OnRep_IceAttackDamage(const FGameplayAttributeData& OldIceAttackDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, IceAttackDamage, OldIceAttackDamage);
}

void UAuraAttributeSet::OnRep_PhysicalAttackDamage(const FGameplayAttributeData& OldPhysicalAttackDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, PhysicalAttackDamage, OldPhysicalAttackDamage);
}

void UAuraAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, Armor, OldArmor);
}

void UAuraAttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ArmorPenetration, OldArmorPenetration);
}

void UAuraAttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitChance, OldCriticalHitChance);
}

void UAuraAttributeSet::OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitDamage, OldCriticalHitDamage);
}

void UAuraAttributeSet::OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, CriticalHitResistance, OldCriticalHitResistance);
}

void UAuraAttributeSet::OnRep_StaminaRegeneration(const FGameplayAttributeData& OldStaminaRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, StaminaRegeneration, OldStaminaRegeneration);
}

void UAuraAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxHealth, OldMaxHealth);
}

void UAuraAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxMana, OldMaxMana);
}

void UAuraAttributeSet::OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, MaxStamina, OldMaxStamina);
}

void UAuraAttributeSet::OnRep_ResistanceArcane(const FGameplayAttributeData& OldResistanceArcane) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ResistanceArcane, OldResistanceArcane);
}

void UAuraAttributeSet::OnRep_ResistanceFire(const FGameplayAttributeData& OldResistanceFire) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ResistanceFire, OldResistanceFire);
}

void UAuraAttributeSet::OnRep_ResistanceLightning(const FGameplayAttributeData& OldResistanceLightning) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ResistanceLightning, OldResistanceLightning);
}

void UAuraAttributeSet::OnRep_ResistanceIce(const FGameplayAttributeData& OldResistanceIce) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ResistanceIce, OldResistanceIce);
}

void UAuraAttributeSet::OnRep_ResistancePhysical(const FGameplayAttributeData& OldResistancePhysical) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet, ResistancePhysical, OldResistancePhysical);
}

