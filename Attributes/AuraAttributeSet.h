// © 2024 Olinick Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AuraTypes.h"
#include "AuraAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT(BlueprintType)
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties() {}

	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;
	
	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;

	UPROPERTY()
	AController* SourceController = nullptr;

	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;
	
	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;

	UPROPERTY()
	AController* TargetController = nullptr;

	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;

	UPROPERTY()
	AActor* DamageCauser = nullptr;
};

// typedef is sppecific to the FGameplayAttribute() signature, but TStaticFuncPtr is generic to any signature chosen
//typedef TBaseStaticDelegateInstance<FGameplayAttribute(), FDefaultDelegateUserPolicy>::FFuncPtr FAttributeFuncPtr;
template<class T>
using TStaticFuncPtr = typename TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;

class AAuraPlayerController;

/**
 * 
 */
UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UAuraAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;

	void Debuff(const FEffectProperties& Props);

	void IncrementPrimaryAttribte(FGameplayTag AttributeTag, int32 IncrementValue);

	void SendXPEvent(const FEffectProperties& Props);

	TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> TagsToAttributes;
	
	/**
* 
	* Primary Attributes
	*/

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Dexterity, Category = "Primary Attributes")
	FGameplayAttributeData Dexterity;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Dexterity);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Intelligence, Category = "Primary Attributes")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Intelligence);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Resilience, Category = "Primary Attributes")
	FGameplayAttributeData Resilience;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Resilience);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category = "Primary Attributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Strength);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Vigor, Category = "Primary Attributes")
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Vigor);

	

	/**
	* Secondary Attributes
	*/

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArcaneAttackDamage, Category = "Secondary Attributes")
	FGameplayAttributeData ArcaneAttackDamage;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ArcaneAttackDamage);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_FireAttackDamage, Category = "Secondary Attributes")
	FGameplayAttributeData FireAttackDamage;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, FireAttackDamage);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_LightningAttackDamage, Category = "Secondary Attributes")
	FGameplayAttributeData LightningAttackDamage;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, LightningAttackDamage);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_IceAttackDamage, Category = "Secondary Attributes")
	FGameplayAttributeData IceAttackDamage;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, IceAttackDamage);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_PhysicalAttackDamage, Category = "Secondary Attributes")
	FGameplayAttributeData PhysicalAttackDamage;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, PhysicalAttackDamage);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armor, Category = "Secondary Attributes")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Armor);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArmorPenetration, Category = "Secondary Attributes")
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ArmorPenetration);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitChance, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalHitChance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitChance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitDamage, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalHitDamage;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitDamage);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitResistance, Category = "Secondary Attributes")
	FGameplayAttributeData CriticalHitResistance;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, CriticalHitResistance);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_StaminaRegeneration, Category = "Secondary Attributes")
	FGameplayAttributeData StaminaRegeneration;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, StaminaRegeneration);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Secondary Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Secondary Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxMana);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxStamina, Category = "Secondary Attributes")
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, MaxStamina);

	/**
	* Resistance Attributes
	*/

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ResistanceArcane, Category = "Secondary Attributes")
	FGameplayAttributeData ResistanceArcane;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ResistanceArcane);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ResistanceFire, Category = "Secondary Attributes")
	FGameplayAttributeData ResistanceFire;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ResistanceFire);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ResistanceLightning, Category = "Secondary Attributes")
	FGameplayAttributeData ResistanceLightning;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ResistanceLightning);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ResistanceIce, Category = "Secondary Attributes")
	FGameplayAttributeData ResistanceIce;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ResistanceIce);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ResistancePhysical, Category = "Secondary Attributes")
	FGameplayAttributeData ResistancePhysical;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ResistancePhysical);

	/** 
	* Vital Attributes
	*/ 

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Vital Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Health);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Vital Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Mana);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Stamina, Category = "Vital Attributes")
	FGameplayAttributeData Stamina;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, Stamina);

	/** 
	* End Vital Attributes
	*/

	/**
	* Meta Attributes
	*/
	UPROPERTY(BlueprintReadOnly, Category = "Meta Attributes")
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, IncomingDamage);

	UPROPERTY(BlueprintReadOnly, Category = "Meta Attributes")
	FGameplayAttributeData IncomingXP;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, IncomingXP); // mudar

	UPROPERTY(BlueprintReadOnly, Category = "Meta Attributes")
	FGameplayAttributeData ResidualDamage;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet, ResidualDamage); //??

	/**
	* End Meta Attributes
	*/

	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;

	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;

	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& OldResilience) const;

	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& OldVigor) const;

	UFUNCTION()
	void OnRep_Dexterity(const FGameplayAttributeData& OldDexterity) const;

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;

	UFUNCTION()
	void OnRep_Stamina(const FGameplayAttributeData& OldStamina) const;
	
	UFUNCTION()
	void OnRep_ArcaneAttackDamage(const FGameplayAttributeData& OldArcaneAttackDamage) const;

	UFUNCTION()
	void OnRep_FireAttackDamage(const FGameplayAttributeData& OldFireAttackDamage) const;

	UFUNCTION()
	void OnRep_LightningAttackDamage(const FGameplayAttributeData& OldLightningAttackDamage) const;

	UFUNCTION()
	void OnRep_IceAttackDamage(const FGameplayAttributeData& OldIceAttackDamage) const;

	UFUNCTION()
	void OnRep_PhysicalAttackDamage(const FGameplayAttributeData& OldPhysicalAttackDamage) const;

	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldArmor) const;

	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const;

	//UFUNCTION()
	//void OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const;

	UFUNCTION()
	void OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const;

	UFUNCTION()
	void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const;

	UFUNCTION()
	void OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const;

	//UFUNCTION()
	//void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const;

	//UFUNCTION()
	//void OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const;

	UFUNCTION()
	void OnRep_StaminaRegeneration(const FGameplayAttributeData& OldStaminaRegeneration) const;

	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const;

	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;

	UFUNCTION()
	void OnRep_MaxStamina(const FGameplayAttributeData& OldMaxStamina) const;

	UFUNCTION()
	void OnRep_ResistanceArcane(const FGameplayAttributeData& OldResistanceArcane) const;

	UFUNCTION()
	void OnRep_ResistanceFire(const FGameplayAttributeData& OldResistanceFire) const;

	UFUNCTION()
	void OnRep_ResistanceLightning(const FGameplayAttributeData& OldResistanceLightning) const;

	UFUNCTION()
	void OnRep_ResistanceIce(const FGameplayAttributeData& OldResistanceIce) const;

	UFUNCTION()
	void OnRep_ResistancePhysical(const FGameplayAttributeData& OldResistancePhysical) const;

private:
	void HandleIncomingDamage(FEffectProperties& Props);
	void HandleIncomingXP(const FEffectProperties& Props);
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
	void ShowFloatingText(const FEffectProperties& Props, const float& LocalIncomingDamage, bool bBlockedHit, bool bCriticalHit, bool bStabHit);
	void StartResidualDamage(const FEffectProperties& Props, float FullDamage);
	FORCEINLINE void ResetResidualDamage() { SetResidualDamage(0.f); }

	bool bTopOffHealth = false;
	bool bTopOffMana = false;
	bool bTopOffStamina = false;

	float ComboTime = 1.f;
};
