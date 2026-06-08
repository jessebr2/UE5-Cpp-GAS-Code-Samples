// © 2024 Olinick Games. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AuraDamageGameplayAbility.h"
#include "AuraProjectileSpell.generated.h"

UENUM(BlueprintType)
enum class ELaunchSpeedType : uint8
{
	ELS_Constant UMETA(DisplayName = "Constant"),
	ELS_CombatTargetDistance UMETA(DisplayName = "CombatTargetDistance")
};

class AAuraProjectile;
struct FGameplayTag;
/**
 * 
 */
UCLASS()
class AURA_API UAuraProjectileSpell : public UAuraDamageGameplayAbility
{
	GENERATED_BODY()

protected:

	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	UFUNCTION(BlueprintCallable, Category = "Projectile")
	bool HasTrajectoryToLaunch();

	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void SpawnProjectile(const FVector& ProjectileTargetLocation, const FGameplayTag& SocketTag, AActor* ProjectileTarget = nullptr);

	float GetInitialVelocity(const FVector& ProjectileTargetLocation, const FVector& ProjectileInitialLocation);

	FVector CalculateProjectileVelocity(const FVector& ProjectileTargetLocation, const FVector& ProjectileInitialLocation, float GravityScale = 1.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AAuraProjectile> ProjectileClass;
	
	UPROPERTY(EditDefaultsOnly)
	int32 NumProjectiles = 5;

	UPROPERTY(EditDefaultsOnly, Category = "LaunchProperties")
	float LaunchAngle = 30.f;

	UPROPERTY(EditDefaultsOnly, Category = "LaunchProperties")
	float LaunchSpeed = 1000.f;

	UPROPERTY(EditDefaultsOnly, Category = "LaunchProperties")
	float MinLaunchSpeed = 1000.f;

	UPROPERTY(EditDefaultsOnly, Category = "LaunchProperties")
	float LaunchSpeedMultiplier = 1.f;

	UPROPERTY(EditDefaultsOnly, Category = "LaunchProperties")
	ELaunchSpeedType LaunchSpeedType = ELaunchSpeedType::ELS_Constant;



};
