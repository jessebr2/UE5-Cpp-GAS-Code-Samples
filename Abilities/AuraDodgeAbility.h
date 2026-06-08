// Copyright Olinick Games

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraGameplayAbility.h"
#include "AuraDodgeAbility.generated.h"

/**
 * 
 */
UCLASS()
class AURA_API UAuraDodgeAbility : public UAuraGameplayAbility
{
	GENERATED_BODY()
	
protected:
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled);

	UFUNCTION(BlueprintCallable)
	void PerformAbility(float TimeHelded);

	void PlayAnimationAndWait(UAnimMontage* MontageToPlay);

	UFUNCTION(BlueprintCallable)
	void FinishDodgeAbility();

	UPROPERTY(EditDefaultsOnly)
	float ActivationReleaseTime = 0.4f;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAnimMontage> DirectionalDodgeAnimation;

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAnimMontage> BackwardDodgeAnimation;

private:
	
	bool bTargetingMode = false;
};
