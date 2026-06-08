// © 2024 Olinick Games. All rights reserved.


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AuraGameplayTags.h"
#include "AuraAbilityTypes.h"
#include "AbilitySystemComponent.h"
#include "Interaction/CombatInterface.h"
#include "Interaction/PlayerInterface.h"

struct AuraDamageStatics
{
	//Target
	DECLARE_ATTRIBUTE_CAPTUREDEF(Armor);
	//DECLARE_ATTRIBUTE_CAPTUREDEF(BlockChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitResistance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ResistanceArcane);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ResistanceFire);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ResistanceLightning);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ResistancePhysical);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ResistanceIce);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ResidualDamage);
	
	//Source
	DECLARE_ATTRIBUTE_CAPTUREDEF(ArmorPenetration);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalHitDamage);

	AuraDamageStatics()
	{
		//Target
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, Armor, Target, false);
		//DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, BlockChance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CriticalHitResistance, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, ResistanceArcane, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, ResistanceFire, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, ResistanceLightning, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, ResistancePhysical, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, ResistanceIce, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, ResidualDamage, Target, false);

		//Source
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, ArmorPenetration, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CriticalHitChance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAuraAttributeSet, CriticalHitDamage, Source, false);
	}
};

static const AuraDamageStatics& DamageStatics()
{
	static AuraDamageStatics DStatics;
	return DStatics;
}

UExecCalc_Damage::UExecCalc_Damage()
{
	//Target
	RelevantAttributesToCapture.Add(DamageStatics().ArmorDef);
	//RelevantAttributesToCapture.Add(DamageStatics().BlockChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().ResistanceArcaneDef);
	RelevantAttributesToCapture.Add(DamageStatics().ResistanceFireDef);
	RelevantAttributesToCapture.Add(DamageStatics().ResistanceLightningDef);
	RelevantAttributesToCapture.Add(DamageStatics().ResistancePhysicalDef);
	RelevantAttributesToCapture.Add(DamageStatics().ResistanceIceDef);
	RelevantAttributesToCapture.Add(DamageStatics().ResidualDamageDef);

	//Source
	RelevantAttributesToCapture.Add(DamageStatics().ArmorPenetrationDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitChanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().CriticalHitDamageDef);

}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams, FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition> TagsToCaptureDefs;
	const FAuraGameplayTags& Tags = FAuraGameplayTags::Get();
	//Target
	TagsToCaptureDefs.Add(Tags.Attributes_Secondary_Armor, DamageStatics().ArmorDef);
	//TagsToCaptureDefs.Add(Tags.Attributes_Secondary_BlockChance, DamageStatics().BlockChanceDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Secondary_CriticalHitResistance, DamageStatics().CriticalHitResistanceDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Arcane, DamageStatics().ResistanceArcaneDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Fire, DamageStatics().ResistanceFireDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Lightning, DamageStatics().ResistanceLightningDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Physical, DamageStatics().ResistancePhysicalDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Resistance_Ice, DamageStatics().ResistanceIceDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Meta_ResidualDamage, DamageStatics().ResidualDamageDef);

	//Source
	TagsToCaptureDefs.Add(Tags.Attributes_Secondary_ArmorPenetration, DamageStatics().ArmorPenetrationDef);
	TagsToCaptureDefs.Add(Tags.Attributes_Secondary_CriticalHitChance, DamageStatics().CriticalHitChanceDef);

	const UAbilitySystemComponent* SourceASC = ExecutionParams.GetSourceAbilitySystemComponent();
	UAbilitySystemComponent* TargetASC = ExecutionParams.GetTargetAbilitySystemComponent();

	AActor* SourceAvatar = SourceASC ? SourceASC->GetAvatarActor() : nullptr;
	AActor* TargetAvatar = TargetASC ? TargetASC->GetAvatarActor() : nullptr;

	int32 SourcePlayerLevel = 1;
	if (SourceAvatar->Implements<UCombatInterface>())
	{
		SourcePlayerLevel = ICombatInterface::Execute_GetPlayerLevel(SourceAvatar);
	}
	int32 TargetPlayerLevel = 1;
	if (TargetAvatar->Implements<UCombatInterface>())
	{
		TargetPlayerLevel = ICombatInterface::Execute_GetPlayerLevel(TargetAvatar);

		if (ICombatInterface::Execute_IsInvulnerable(TargetAvatar)) return;
	}

	const FGameplayEffectSpec Spec = ExecutionParams.GetOwningSpec();

	// Gather tags from source and target
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = SourceTags;
	EvaluationParameters.TargetTags = TargetTags;

	// Debuff
	DetermineDebuff(Spec, ExecutionParams, EvaluationParameters, TagsToCaptureDefs, SourceAvatar);

	const UCharacterClassInfo* CharacterClassInfo = UAuraAbilitySystemLibrary::GetCharacterClassInfo(SourceAvatar);

	// Get Damage Set by Caller Magnitude
	float Damage = 0.f;
	const float DamageBonus = Spec.GetSetByCallerMagnitude(Tags.DamageBonus, false, 1.f);

	for (const TTuple<FGameplayTag, FGameplayTag>& Pair : FAuraGameplayTags::Get().DamageTypesToResistances)
	{
		const FGameplayTag DamageType = Pair.Key;
		const FGameplayTag ResistanceTag = Pair.Value;

		checkf(TagsToCaptureDefs.Contains(ResistanceTag), TEXT("TagsToCaptureDefs doesn't contain Tag: [%s] in ExecCalc_Damage"), *ResistanceTag.ToString());
		const FGameplayEffectAttributeCaptureDefinition CaptureDef = TagsToCaptureDefs[ResistanceTag];
		
		float DamageTypeValue = Spec.GetSetByCallerMagnitude(Pair.Key, false);
		if (DamageTypeValue == 0.f) continue;
		DamageTypeValue *= DamageBonus;
		float Resistance = 0.f;
		ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(CaptureDef, EvaluationParameters, Resistance);
		Resistance = FMath::Clamp(Resistance, -100.f, 100.f);

		DamageTypeValue *= (100.f - Resistance) / 100.f;

		if (DamageType == FAuraGameplayTags::Get().Damage_Physical)
		{
			// Strengh Coefficient
			const FRealCurve* StrenghCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("Strengh"), FString());
			const float StrenghCoefficient = StrenghCurve->Eval(SourcePlayerLevel);
			DamageTypeValue *= StrenghCoefficient;
			
			
			// Armor
			float TargetArmor = 0.f;
			ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorDef, EvaluationParameters, TargetArmor);
			TargetArmor = FMath::Max<float>(TargetArmor, 0.f);

			// Armor Penetration
			float SourceArmorPenetration = 0.f;
			ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ArmorPenetrationDef, EvaluationParameters, SourceArmorPenetration);
			SourceArmorPenetration = FMath::Max<float>(SourceArmorPenetration, 0.f);

			// Armor Penetration Coefficient
			const FRealCurve* ArmorPenetrationCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("ArmorPenetration"), FString());
			const float ArmorPenetrationCoefficient = ArmorPenetrationCurve->Eval(SourcePlayerLevel);

			// ArmorPenetration ignores a percentage of the Target's Armor.
			const float EffectiveArmor = TargetArmor * ((100.f - SourceArmorPenetration * ArmorPenetrationCoefficient) / 100.f);

			// Effective Armor Coefficient
			const FRealCurve* EffectiveArmorCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("EffectiveArmor"), FString());
			const float EffectiveArmorCoefficient = EffectiveArmorCurve->Eval(TargetPlayerLevel);

			// Armor reduces a percentage of Damage
			DamageTypeValue *= (100.f - EffectiveArmor * EffectiveArmorCoefficient) / 100.f;
		}
		else if (DamageType == FAuraGameplayTags::Get().Damage_Arcane || DamageType == FAuraGameplayTags::Get().Damage_Fire || DamageType == FAuraGameplayTags::Get().Damage_Ice || DamageType == FAuraGameplayTags::Get().Damage_Lightning)
		{
			// Intelligence Coefficient 
			const FRealCurve* IntelligenceCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("Intelligence"), FString());
			const float IntelligenceCoefficient = IntelligenceCurve->Eval(SourcePlayerLevel);
			DamageTypeValue *= IntelligenceCoefficient;
		}

		Damage += DamageTypeValue;
	}

	// BlockChance
	//float TargetBlockChance = 0.f;
	//ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().BlockChanceDef, EvaluationParameters, TargetBlockChance);
	//TargetBlockChance = FMath::Max<float>(TargetBlockChance, 0.f);

	// EffectContextHandle
	FGameplayEffectContextHandle EffectContextHandle = Spec.GetContext();

	// Halve Damage
	//const bool bBlocked = FMath::RandRange(1, 100) < TargetBlockChance;
	//if (bBlocked)
	//{
	//	Damage *= .5f;
	//	UAuraAbilitySystemLibrary::SetIsBlockedHit(EffectContextHandle, bBlocked);
	//}


	// CriticalHit Chance
	float SourceCriticalHitChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitChanceDef, EvaluationParameters, SourceCriticalHitChance);
	SourceCriticalHitChance = FMath::Max<float>(SourceCriticalHitChance, 0.f);
	
	// CriticalHit Damage
	float SourceCriticalHitDamage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitDamageDef, EvaluationParameters, SourceCriticalHitDamage);
	SourceCriticalHitDamage = FMath::Max<float>(SourceCriticalHitDamage, 0.f);

	// CriticalHit Resistance
	float TargetCriticalHitResistance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().CriticalHitResistanceDef, EvaluationParameters, TargetCriticalHitResistance);
	TargetCriticalHitResistance = FMath::Max<float>(TargetCriticalHitResistance, 0.f);
	
	// CriticalHit Resistance Coefficient
	const FRealCurve* CriticalHitResistanceCurve = CharacterClassInfo->DamageCalculationCoefficients->FindCurve(FName("CriticalHitResistance"), FString());
	const float CriticalHitResistanceCoefficient = CriticalHitResistanceCurve->Eval(TargetPlayerLevel);

	// Apply Critical
	bool bCritical = FMath::RandRange(1, 100) < (SourceCriticalHitChance - TargetCriticalHitResistance * CriticalHitResistanceCoefficient);

	// Stunned
	//if (TargetAvatar && TargetAvatar->Implements<UCombatInterface>() && ICombatInterface::Execute_IsStunned(TargetAvatar))
	//{
	//	bCritical = true;
	//	Damage = 2.f * Damage;
	//	//TargetASC->RemoveActiveEffectsWithAppliedTags(FGameplayTagContainer(FAuraGameplayTags::Get().Debuff_Stun));
	//}
	
	if (bCritical)
	{
		Damage = 2.f * Damage + SourceCriticalHitDamage;
		UAuraAbilitySystemLibrary::SetIsCriticalHit(EffectContextHandle, bCritical);
	}

	// Residual Damage ??
	float ResidualDamage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(DamageStatics().ResidualDamageDef, EvaluationParameters, ResidualDamage);
	ResidualDamage = FMath::Max<float>(ResidualDamage, 0.f);

	Damage += ResidualDamage;
	// Residual Damage ??

	//Combo
	if (SourceAvatar->Implements<UPlayerInterface>())
	{
		const int32 ComboCount = IPlayerInterface::Execute_GetComboCount(SourceAvatar);
		Damage *= (1.f + ComboCount * .2f);
	}

	const FGameplayModifierEvaluatedData EvaluatedData(UAuraAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Additive, Damage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
}

void UExecCalc_Damage::DetermineDebuff(const FGameplayEffectSpec& Spec, const FGameplayEffectCustomExecutionParameters& ExecutionParams, FAggregatorEvaluateParameters& EvaluationParameters, const TMap<FGameplayTag, FGameplayEffectAttributeCaptureDefinition>& InTagsToDefs, AActor* SourceAvatar) const
{
	const FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();
	for (TTuple<FGameplayTag, FGameplayTag> Pair : GameplayTags.DamageTypesToDebuffs)
	{
		const FGameplayTag& DamageType = Pair.Key;
		const FGameplayTag& DebuffType = Pair.Value;
		const float DamageValue = Spec.GetSetByCallerMagnitude(DamageType, false, -1.f);
		if (DamageValue > -.5f) // .5 padding for floating point [im]precision
		{
			// Determine if there was a successful debuff
			const float SourceDebuffChance = Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Chance, false, -1.f);
			const FGameplayTag& ResistanceTag = GameplayTags.DamageTypesToResistances[DamageType];
			float TargetDebuffResistance = 0.f;
			ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(InTagsToDefs[ResistanceTag], EvaluationParameters, TargetDebuffResistance);
			TargetDebuffResistance = FMath::Max<float>(TargetDebuffResistance, 0.f);
			const float EffectiveDebuffChance = SourceDebuffChance * (100 - TargetDebuffResistance) / 100.f;
			const bool bDebuff = FMath::RandRange(1, 100) < EffectiveDebuffChance;

			 
			if (bDebuff)
			{
				if (SourceAvatar) ICombatInterface::Execute_ResetDebuffCount(SourceAvatar);

				FGameplayEffectContextHandle ContextHandle = Spec.GetContext();

				UAuraAbilitySystemLibrary::SetIsSuccessfullDebuff(ContextHandle, true);
				UAuraAbilitySystemLibrary::SetDamageType(ContextHandle, DamageType);

				const float DebuffDamage = Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Damage, false, -1.f);
				const float DebuffDuration = Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Duration, false, -1.f);
				const float DebuffFrequency = Spec.GetSetByCallerMagnitude(GameplayTags.Debuff_Frequency, false, -1.f);

				UAuraAbilitySystemLibrary::SetDebuffDamage(ContextHandle, DebuffDamage);
				UAuraAbilitySystemLibrary::SetDebuffDuration(ContextHandle, DebuffDuration);
				UAuraAbilitySystemLibrary::SetDebuffFrequency(ContextHandle, DebuffFrequency);
			}
		}
	}
}
