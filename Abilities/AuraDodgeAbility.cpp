// Copyright Olinick Games


#include "AbilitySystem/Abilities/AuraDodgeAbility.h"
#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystemGlobals.h"
#include "Animation/AnimMontage.h"
#include "Interaction/CombatInterface.h"
#include "Interaction/PlayerInterface.h"

void UAuraDodgeAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (GetAvatarActorFromActorInfo())
	{
		if (ICombatInterface::Execute_IsInvulnerable(GetAvatarActorFromActorInfo()))
		{
			ICombatInterface::Execute_SetInvulnerable(GetAvatarActorFromActorInfo(), false);
		}
		IPlayerInterface::Execute_UnblockAllInputs(GetAvatarActorFromActorInfo());
	}
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UAuraDodgeAbility::PerformAbility(float TimeHelded)
{
	if (!(TimeHelded < ActivationReleaseTime) ||
		!AbilityActorInfo->AvatarActor.IsValid() ||
		!CommitAbility(AbilitySpecHandle, AbilityActorInfo, AbilityActivationInfo) ||
		ICombatInterface::Execute_IsDisabled(GetAvatarActorFromActorInfo()))
	{
		FinishAbility();
		return;
	}

	AActor* Avatar = GetAvatarActorFromActorInfo();
	if (UAuraAbilitySystemLibrary::IsTargetingMode(Avatar))	UAuraAbilitySystemLibrary::SetRotationMode(Avatar, ERotationMode::ERM_OrientToMovement);
	ICombatInterface::Execute_SetInvulnerable(Avatar, true);
	IPlayerInterface::Execute_BlockAllInputs(Avatar);
	UAnimMontage* MontageToPlay;
	if (IPlayerInterface::Execute_HasDesiredRotation(Avatar))
	{
		MontageToPlay = DirectionalDodgeAnimation;
	}
	else
	{
		MontageToPlay = BackwardDodgeAnimation;
	}

	PlayAnimationAndWait(MontageToPlay);
	IPlayerInterface::Execute_SetFieldSphereCollisionEnable(GetAvatarActorFromActorInfo(), ECollisionEnabled::QueryOnly);
}

void UAuraDodgeAbility::PlayAnimationAndWait(UAnimMontage* MontageToPlay)
{
	if (AbilityActorInfo->AbilitySystemComponent.IsValid())
	{
		float Duration = AbilityActorInfo->AbilitySystemComponent.Get()->PlayMontage(this, AbilityActivationInfo, MontageToPlay, 1.0);

		FTimerHandle TimerHandle;
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &UAuraDodgeAbility::FinishDodgeAbility, Duration);
	}
}

void UAuraDodgeAbility::FinishDodgeAbility()
{
	AActor* Avatar = GetAvatarActorFromActorInfo();
	ICombatInterface::Execute_SetInvulnerable(Avatar, false);
	if (UAuraAbilitySystemLibrary::IsTargetingMode(Avatar))	UAuraAbilitySystemLibrary::SetRotationMode(Avatar, ERotationMode::ERM_OrientToCamera);
	IPlayerInterface::Execute_SetFieldSphereCollisionEnable(Avatar, ECollisionEnabled::NoCollision);

	FinishAbility();
}
