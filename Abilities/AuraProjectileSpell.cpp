// © 2024 Olinick Games. All rights reserved.


#include "AbilitySystem/Abilities/AuraProjectileSpell.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Actor/AuraProjectile.h"
#include "AuraGameplayTags.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/GameplayStatics.h"

#include "DrawDebugHelpers.h"

void UAuraProjectileSpell::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	switch (LaunchSpeedType)
	{
	case ELaunchSpeedType::ELS_Constant:
		break;
	case ELaunchSpeedType::ELS_CombatTargetDistance:
		CombatTarget = ICombatInterface::Execute_GetCombatTarget(GetAvatarActorFromActorInfo());
		if (CombatTarget)
		{
			LaunchSpeed = FMath::Max(MinLaunchSpeed, GetAvatarActorFromActorInfo()->GetDistanceTo(CombatTarget) * LaunchSpeedMultiplier);
		}
		break;
	}
}

bool UAuraProjectileSpell::HasTrajectoryToLaunch()
{
	const AActor* Avatar = GetAvatarActorFromActorInfo();
	if(!CombatTarget) CombatTarget = ICombatInterface::Execute_GetCombatTarget(Avatar);
	if (!CombatTarget) return false;
	const FVector LaunchVelocity = CalculateProjectileVelocity(CombatTarget->GetActorLocation(), Avatar->GetActorLocation());
	if (LaunchVelocity.IsNearlyZero())
	{
		return false;
	}
	return true;
}

void UAuraProjectileSpell::SpawnProjectile(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag, AActor* ProjectileTarget)
{
	const bool bIsServer = GetAvatarActorFromActorInfo()->HasAuthority();
	if (!bIsServer) return;

	const FVector SocketLocation = ICombatInterface::Execute_GetCombatSocketLocation(
		GetAvatarActorFromActorInfo(),
		SocketTag);

	check(ProjectileClass);
	AAuraProjectile* Projectile = GetWorld()->SpawnActorDeferred<AAuraProjectile>(
		ProjectileClass,
		FTransform(),
		GetOwningActorFromActorInfo(),
		Cast<APawn>(GetOwningActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn);

	FVector LaunchVelocity = CalculateProjectileVelocity(ProjectileTargetLocation, SocketLocation, Projectile->ProjectileMovement->ProjectileGravityScale);
	if (LaunchVelocity.IsNearlyZero())
	{
		LaunchVelocity = ((ProjectileTargetLocation - SocketLocation).GetSafeNormal() * LaunchSpeed) + FVector(0.f, 0.f, LaunchSpeed * .2f);
	}

	FRotator Rotation = LaunchVelocity.Rotation();

	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SocketLocation);
	SpawnTransform.SetRotation(Rotation.Quaternion());

	Projectile->DamageEffectParams = MakeDamageEffectParamsFromClassDefaults();
	
	Projectile->SetProjectileSpeed(LaunchVelocity.Length());

	if (ProjectileTarget) Projectile->SetProjectileTarget(ProjectileTarget);

	Projectile->FinishSpawning(SpawnTransform);
}

float UAuraProjectileSpell::GetInitialVelocity(const FVector& ProjectileTargetLocation, const FVector& ProjectileInitialLocation)
{
	LaunchAngle = FMath::Clamp(LaunchAngle, 10.f, 80.f);
	float Distance = (ProjectileTargetLocation - ProjectileInitialLocation).Length();
	return FMath::Sqrt(Distance * FMath::Abs((GetWorld()->GetGravityZ()) / (FMath::Sin(2*LaunchAngle))));
}

FVector UAuraProjectileSpell::CalculateProjectileVelocity(const FVector& ProjectileTargetLocation, const FVector& ProjectileInitialLocation, float GravityScale)
{
	FVector LaunchVelocity;

	if (GravityScale == 0.f)
	{
		return (ProjectileTargetLocation - ProjectileInitialLocation).GetSafeNormal() * LaunchSpeed;
	}

	if (!GetWorld()) K2_EndAbility();

	UGameplayStatics::FSuggestProjectileVelocityParameters SuggestParams = UGameplayStatics::FSuggestProjectileVelocityParameters(GetWorld(), ProjectileInitialLocation, ProjectileTargetLocation, LaunchSpeed);
	SuggestParams.bAcceptClosestOnNoSolutions = true;
	if(GravityScale != 1.f)	SuggestParams.OverrideGravityZ = GetWorld()->GetGravityZ() * GravityScale;
	//SuggestParams.bDrawDebug = true;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetAvatarActorFromActorInfo());
	if (!CombatTarget) CombatTarget = ICombatInterface::Execute_GetCombatTarget(GetAvatarActorFromActorInfo());
	if (CombatTarget)
	{
		ActorsToIgnore.Add(CombatTarget);
	}
	SuggestParams.ActorsToIgnore = ActorsToIgnore;

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(SuggestParams, LaunchVelocity);
	if (bHaveAimSolution)
	{
		return LaunchVelocity;
	}
	return FVector::ZeroVector;
}
