// © 2024 Olinick Games. All rights reserved.


#include "AbilitySystem/AuraAbilitySystemLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/Data/LevelUpInfo.h"
#include "AbilitySystem/Data/MagicInfo.h"
#include "AuraAbilityTypes.h"
#include "AuraGameplayTags.h"
#include "Character/AuraCharacter.h"
#include "Game/AuraGameModeBase.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameplayEffectTypes.h"
#include "Engine/OverlapResult.h"
#include "Interaction/CombatInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Player/AuraPlayerState.h"
#include "Player/AuraPlayerController.h"
#include "UI/HUD/AuraHUD.h"
#include "UI/Widget/AuraUserWidget.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"
#include "UI/WidgetController/AuraWidgetController.h"
#include "UI/WidgetController/MenuWidgetController.h"


bool UAuraAbilitySystemLibrary::MakeWidgetControllerParams(const UObject* WorldContextObject, FWidgetControllerParams& OutWCParams, AAuraHUD*& OutAuraHUD)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		OutAuraHUD = Cast<AAuraHUD>(PC->GetHUD());
		if (OutAuraHUD)
		{
			AAuraPlayerState* PS = PC->GetPlayerState<AAuraPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();

			OutWCParams.AbilitySystemComponent = ASC;
			OutWCParams.AttributeSet = AS;
			OutWCParams.PlayerController = PC;
			OutWCParams.PlayerState = PS;
			return true;
		}
	}
	return false;
}

UOverlayWidgetController* UAuraAbilitySystemLibrary::GetOverlayWidgetController(const UObject* WorldContextObject)
{
	FWidgetControllerParams WCParams;
	AAuraHUD* AuraHUD = nullptr;
	if (MakeWidgetControllerParams(WorldContextObject, WCParams, AuraHUD))
	{
		return AuraHUD->GetOverlayWidgetController(WCParams);
	}
	return nullptr;
}

UMenuWidgetController* UAuraAbilitySystemLibrary::GetMenuWidgetController(const UObject* WorldContextObject)
{
	FWidgetControllerParams WCParams;
	AAuraHUD* AuraHUD = nullptr;
	if (MakeWidgetControllerParams(WorldContextObject, WCParams, AuraHUD))
	{
		return AuraHUD->GetMenuWidgetController(WCParams);
	}
	return nullptr;
}

UAttributeMenuWidgetController* UAuraAbilitySystemLibrary::GetAttributeMenuWidgetController(const UObject* WorldContextObject)
{
	FWidgetControllerParams WCParams;
	AAuraHUD* AuraHUD = nullptr;
	if (MakeWidgetControllerParams(WorldContextObject, WCParams, AuraHUD))
	{
		return AuraHUD->GetAttributeMenuWidgetController(WCParams);
	}
	return nullptr;
}

USpellMenuWidgetController* UAuraAbilitySystemLibrary::GetSpellMenuWidgetController(const UObject* WorldContextObject)
{
	FWidgetControllerParams WCParams;
	AAuraHUD* AuraHUD = nullptr;
	if (MakeWidgetControllerParams(WorldContextObject, WCParams, AuraHUD))
	{
		return AuraHUD->GetSpellMenuWidgetController(WCParams);
	}
	return nullptr;
}

void UAuraAbilitySystemLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject, ECharacterClass CharacterClass, float Level, UAbilitySystemComponent* ASC)
{
	AActor* AvatarActor = ASC->GetAvatarActor();

	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	FCharacterClassDefaultInfo ClassDefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);

	FGameplayEffectContextHandle PrimaryAttributesContextHandle = ASC->MakeEffectContext();
	PrimaryAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle PrimaryAttributesSpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.PrimaryAttributes, Level, PrimaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributesSpecHandle.Data.Get());

	FGameplayEffectContextHandle SecondaryAttributesContextHandle = ASC->MakeEffectContext();
	SecondaryAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle SecondaryAttributesSpecHandle = ASC->MakeOutgoingSpec(ClassDefaultInfo.SecondaryAttributes, Level, SecondaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributesSpecHandle.Data.Get());

	FGameplayEffectContextHandle VitalAttributesContextHandle = ASC->MakeEffectContext();
	VitalAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle VitalAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterClassInfo->VitalAttributes, Level, VitalAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*VitalAttributesSpecHandle.Data.Get());
}

void UAuraAbilitySystemLibrary::GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC, ECharacterClass CharacterClass)
{
	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	if (!CharacterClassInfo) return;

	for (TSubclassOf<UGameplayAbility> AbilityClass : CharacterClassInfo->CommonAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		ASC->GiveAbility(AbilitySpec);
	}
	if (ASC->GetAvatarActor()->Implements<UCombatInterface>())
	{
		const FCharacterClassDefaultInfo& DefaultInfo = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
		for (TSubclassOf<UGameplayAbility> AbilityClass : DefaultInfo.StartupAbilities)
		{
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, ICombatInterface::Execute_GetPlayerLevel(ASC->GetAvatarActor()));
			ASC->GiveAbility(AbilitySpec);
		}
		TArray<TSubclassOf<UGameplayAbility>> SpecificStartupAbilities = ICombatInterface::Execute_GetStartupAbilities(ASC->GetAvatarActor());
		for (TSubclassOf<UGameplayAbility> AbilityClass : SpecificStartupAbilities)
		{
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, ICombatInterface::Execute_GetPlayerLevel(ASC->GetAvatarActor()));
			ASC->GiveAbility(AbilitySpec);
		}
	}
	
}

int32 UAuraAbilitySystemLibrary::GetXPRewardForClassAndLevel(const UObject* WorldContextObject, ECharacterClass CharacterClass, int32 CharacterLevel)
{
	UCharacterClassInfo* CharacterClassInfo = GetCharacterClassInfo(WorldContextObject);
	if (!CharacterClassInfo) return 0;

	const FCharacterClassDefaultInfo& Info = CharacterClassInfo->GetClassDefaultInfo(CharacterClass);
	const float XPReward = Info.XPReward.GetValueAtLevel(CharacterLevel);

	return static_cast<int32>(XPReward);
}

int32 UAuraAbilitySystemLibrary::GetXPToNextLevel(const UObject* WorldContextObject, int32 CharacterLevel)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (AAuraPlayerState* PS = PC->GetPlayerState<AAuraPlayerState>())
		{
			return PS->LevelUpInfo->GetXPToLevel(CharacterLevel + 1);
		}
	}
	return 0;
}

bool UAuraAbilitySystemLibrary::CanLevelUp(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		float PlayerLevel = ICombatInterface::Execute_GetPlayerLevel(PC->GetPawn());
		float XpNeeded = GetXPToNextLevel(WorldContextObject, PlayerLevel);
		AAuraPlayerState* PS = PC->GetPlayerState<AAuraPlayerState>();
		return PS->GetXP() >= XpNeeded;
	}
	return false;
}

bool UAuraAbilitySystemLibrary::PrimaryAttributeUpgrade(const UObject* WorldContextObject, FGameplayTag AttributeTag, int32 IncrementValue)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		PC->GetPlayerState<AAuraPlayerState>()->GetAuraAttributeSet()->IncrementPrimaryAttribte(AttributeTag, IncrementValue);
		return true;
	}
	return false;
}

float UAuraAbilitySystemLibrary::GetAvatarAngleToLocation(AActor* AvatarActor, FVector InstigatorLocation)
{
	if (!AvatarActor) return 0.f;

	const FVector Forward = AvatarActor->GetActorForwardVector();
	// Lower Impact Point to the Enemy's Actor Location Z
	const FVector ImpactLowered(InstigatorLocation.X, InstigatorLocation.Y, AvatarActor->GetActorLocation().Z);
	const FVector ToHit = (ImpactLowered - AvatarActor->GetActorLocation()).GetSafeNormal();

	// Forward * ToHit = |Forward||ToHit| * cos(theta)
	// |Forward| = 1, |ToHit| = 1, so Forward * ToHit = cos(theta)
	const float CosTheta = FVector::DotProduct(Forward, ToHit);
	float Theta = FMath::Acos(CosTheta);
	Theta = FMath::RadiansToDegrees(Theta);

	// if CrossProduct points down, Theta should be negative
	const FVector CrossProduct = FVector::CrossProduct(Forward, ToHit);
	if (CrossProduct.Z < 0)
	{
		Theta *= -1.f;
	}
	return Theta;

}

TSubclassOf<UAuraUserWidget> UAuraAbilitySystemLibrary::GetBossOverlayClass(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		AAuraHUD* AuraHUD = Cast<AAuraHUD>(PC->GetHUD());
		if (AuraHUD)
		{
			return AuraHUD->GetBossOverlayClass();
		}

	}
	return TSubclassOf<UAuraUserWidget>();
}

bool UAuraAbilitySystemLibrary::HandleWeaponEquipType(AWeapon* InWeapon, EEquipType& EquipType, AAuraCharacter* AuraCharacter)
{
	if (!InWeapon || !AuraCharacter) return false;
	TArray<EEquipType> WeaponEquipTypes = IWeaponInterface::Execute_GetWeaponEquipTypes(InWeapon);
	if (WeaponEquipTypes.Num() < 1) return false;
	AShield* EquippedShield = ICombatInterface::Execute_GetEquippedShield(AuraCharacter);
	if (EquippedShield && EquippedShield->IsEquipped())
	{
		if (WeaponEquipTypes.Contains(EEquipType::EET_WeaponAndShield) || WeaponEquipTypes.Contains(EEquipType::EET_OneHandedWeapon))
		{
			EquipType = EEquipType::EET_WeaponAndShield;
			return true;
		}
		else if (WeaponEquipTypes.Contains(EEquipType::EET_MagicStickAndShield) || WeaponEquipTypes.Contains(EEquipType::EET_MagicStick))
		{
			EquipType = EEquipType::EET_MagicStickAndShield;
			return true;
		}
		else
		{
			EquippedShield->AttachShieldOnBack();
		}
	}
	EquipType = WeaponEquipTypes[0];
	return true;
}

bool UAuraAbilitySystemLibrary::EquipNewWeapon(AWeapon* InWeapon, AAuraCharacter* AuraCharacter)
{
	if (!InWeapon || !AuraCharacter) return false;
	EEquipType NewEquipState;
	bool Success = HandleWeaponEquipType(InWeapon, NewEquipState, AuraCharacter);
	if (!Success) return false;
	FName SocketName = IPlayerInterface::Execute_GetSocketNameFromEquipType(AuraCharacter, NewEquipState, InWeapon);
	InWeapon->Equip(AuraCharacter->GetMesh(), SocketName, AuraCharacter);
	AAuraPlayerState* AuraPS = IPlayerInterface::Execute_GetAuraPlayerState(AuraCharacter);
	FEquippedWeapon& EquippedWeapon = AuraPS->GetEquippedWeapon();
	if (EquippedWeapon.EquippedWeaponLeft) EquippedWeapon.EquippedWeaponLeft->Destroy();
	if (EquippedWeapon.EquippedWeaponRight) EquippedWeapon.EquippedWeaponRight->Destroy();
	EquippedWeapon.EquippedWeaponRight = InWeapon;
	IPlayerInterface::Execute_SetEquipState(AuraCharacter, NewEquipState);
	return true;
}


UCharacterClassInfo* UAuraAbilitySystemLibrary::GetCharacterClassInfo(const UObject* WorldContextObject)
{
	const AAuraGameModeBase* AuraGameMode = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (!AuraGameMode) return nullptr;
	return AuraGameMode->CharacterClassInfo;
}

UMagicInfo* UAuraAbilitySystemLibrary::GetMagicInfo(const UObject* WorldContextObject)
{
	const AAuraGameModeBase* AuraGameMode = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (!AuraGameMode)	return nullptr;
	return AuraGameMode->MagicInfo;
}

FAuraMagicInfo UAuraAbilitySystemLibrary::GetAuraMagicInfoForTag(const UObject* WorldContextObject, const FGameplayTag& MagicTag)
{
	const UMagicInfo* MagicInfo = GetMagicInfo(WorldContextObject);
	if (MagicInfo)
	{
		return MagicInfo->FindMagicInfoForTag(MagicTag);
	}
	return FAuraMagicInfo();
}

UAbilityInfo* UAuraAbilitySystemLibrary::GetAbilityInfo(const UObject* WorldContextObject)
{
	const AAuraGameModeBase* AuraGameMode = Cast<AAuraGameModeBase>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (!AuraGameMode) return nullptr;
	return AuraGameMode->AbilityInfo;
}

bool UAuraAbilitySystemLibrary::IsBlockedHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FAuraGameplayEffectContext* AuraEffectContext = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return AuraEffectContext->IsBlockedHit();
	}
	return false;
}

bool UAuraAbilitySystemLibrary::IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FAuraGameplayEffectContext* AuraEffectContext = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return AuraEffectContext->IsCriticalHit();
	}
	return false;
}

bool UAuraAbilitySystemLibrary::IsStabHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FAuraGameplayEffectContext* AuraEffectContext = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return AuraEffectContext->IsStabHit();
	}
	return false;
}

bool UAuraAbilitySystemLibrary::IsSuccessfulDebuff(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FAuraGameplayEffectContext* AuraEffectContext = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return AuraEffectContext->IsSuccessfulDebuff();
	}
	return false;
}

float UAuraAbilitySystemLibrary::GetDebuffDamage(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FAuraGameplayEffectContext* AuraEffectContext = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return AuraEffectContext->GetDebuffDamage();
	}
	return 0.0f;
}

float UAuraAbilitySystemLibrary::GetDebuffDuration(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FAuraGameplayEffectContext* AuraEffectContext = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return AuraEffectContext->GetDebuffDuration();
	}
	return 0.0f;
}

float UAuraAbilitySystemLibrary::GetDebuffFrequency(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FAuraGameplayEffectContext* AuraEffectContext = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return AuraEffectContext->GetDebuffFrequency();
	}
	return 0.0f;
}

FGameplayTag UAuraAbilitySystemLibrary::GetDamageType(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FAuraGameplayEffectContext* AuraEffectContext = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		if (AuraEffectContext->GetDamageType().IsValid())
		{
			return *AuraEffectContext->GetDamageType();
		}
	}
	return FGameplayTag();
}

FVector UAuraAbilitySystemLibrary::GetDeathImpulse(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FAuraGameplayEffectContext* AuraEffectContext = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return AuraEffectContext->GetDeahtImpulse();
	}
	return FVector::ZeroVector;
}

FVector UAuraAbilitySystemLibrary::GetImpactPoint(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FAuraGameplayEffectContext* AuraEffectContext = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return AuraEffectContext->GetImpactPoint();
	}
	return FVector::ZeroVector;
}

FVector UAuraAbilitySystemLibrary::GetKnockbackForce(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FAuraGameplayEffectContext* AuraEffectContext = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return AuraEffectContext->GetKnockbackForce();
	}
	return FVector::ZeroVector;
}

AActor* UAuraAbilitySystemLibrary::GetDamageCauser(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FAuraGameplayEffectContext* AuraEffectContext = static_cast<const FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return AuraEffectContext->GetDamageCauser();
	}
	return nullptr;
}

void UAuraAbilitySystemLibrary::SetIsBlockedHit(UPARAM(ref)FGameplayEffectContextHandle& EffectContextHandle, bool bInIsBlockedHit)
{
	if (FAuraGameplayEffectContext* AuraEffectContext = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		AuraEffectContext->SetIsBlockedHit(bInIsBlockedHit);
	}
}

void UAuraAbilitySystemLibrary::SetIsCriticalHit(UPARAM(ref)FGameplayEffectContextHandle& EffectContextHandle, bool bInIsCriticalHit)
{
	if (FAuraGameplayEffectContext* AuraEffectContext = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		AuraEffectContext->SetIsCriticalHit(bInIsCriticalHit);
	}
}

void UAuraAbilitySystemLibrary::SetIsStabHit(UPARAM(ref)FGameplayEffectContextHandle& EffectContextHandle, bool bInIsStabHit)
{
	if (FAuraGameplayEffectContext* AuraEffectContext = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		AuraEffectContext->SetIsStabHit(bInIsStabHit);
	}
}

void UAuraAbilitySystemLibrary::SetIsSuccessfullDebuff(UPARAM(ref)FGameplayEffectContextHandle& EffectContextHandle, bool bInIsSuccessfulDebuff)
{
	if (FAuraGameplayEffectContext* AuraEffectContext = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		AuraEffectContext->SetIsSuccessfulDebuff(bInIsSuccessfulDebuff);
	}
}

void UAuraAbilitySystemLibrary::SetDebuffDamage(UPARAM(ref)FGameplayEffectContextHandle& EffectContextHandle, float InDamage)
{
	if (FAuraGameplayEffectContext* AuraEffectContext = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		AuraEffectContext->SetDebuffDamage(InDamage);
	}
}

void UAuraAbilitySystemLibrary::SetDebuffDuration(UPARAM(ref)FGameplayEffectContextHandle& EffectContextHandle, float InDuration)
{
	if (FAuraGameplayEffectContext* AuraEffectContext = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		AuraEffectContext->SetDebuffDuration(InDuration);
	}
}

void UAuraAbilitySystemLibrary::SetDebuffFrequency(UPARAM(ref)FGameplayEffectContextHandle& EffectContextHandle, float InFrequency)
{
	if (FAuraGameplayEffectContext* AuraEffectContext = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		AuraEffectContext->SetDebuffFrequency(InFrequency);
	}
}

void UAuraAbilitySystemLibrary::SetDamageType(UPARAM(ref)FGameplayEffectContextHandle& EffectContextHandle, const FGameplayTag& InDamageType)
{
	if (FAuraGameplayEffectContext* AuraEffectContext = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		TSharedPtr<FGameplayTag> DamageType = MakeShared<FGameplayTag>(InDamageType);
		AuraEffectContext->SetDamageType(DamageType);
	}
}

void UAuraAbilitySystemLibrary::SetDeathImpulse(UPARAM(ref)FGameplayEffectContextHandle& EffectContextHandle, const FVector& InImpulse)
{
	if (FAuraGameplayEffectContext* AuraEffectContext = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		AuraEffectContext->SetDeathImpulse(InImpulse);
	}
}

void UAuraAbilitySystemLibrary::SetImpactPoint(UPARAM(ref)FGameplayEffectContextHandle& EffectContextHandle, const FVector& InImpactPoint)
{
	if (FAuraGameplayEffectContext* AuraEffectContext = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		AuraEffectContext->SetImpactPoint(InImpactPoint);
	}
}

void UAuraAbilitySystemLibrary::SetKnockbackForce(UPARAM(ref)FGameplayEffectContextHandle& EffectContextHandle, const FVector& InForce)
{
	if (FAuraGameplayEffectContext* AuraEffectContext = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		AuraEffectContext->SetKnockbackForce(InForce);
	}
}

void UAuraAbilitySystemLibrary::SetDamageCauser(UPARAM(ref)FGameplayEffectContextHandle& EffectContextHandle, AActor* InDamageCauser)
{
	if (FAuraGameplayEffectContext* AuraEffectContext = static_cast<FAuraGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		AuraEffectContext->SetDamageCauser(InDamageCauser);
	}
}

void UAuraAbilitySystemLibrary::GetLivePlayersWithinRadius(const UObject* WorldContextObject, TArray<AActor*>& OutOverlappingActors, const TArray<AActor*>& ActorsToIgnore, float Radius, const FVector& SphereOrigin)
{
	FCollisionQueryParams SphereParams;
	SphereParams.AddIgnoredActors(ActorsToIgnore);

	// query scene to see what we hit
	TArray<FOverlapResult> Overlaps;
	if (UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		World->OverlapMultiByObjectType(Overlaps, SphereOrigin, FQuat::Identity, FCollisionObjectQueryParams(FCollisionObjectQueryParams::InitType::AllDynamicObjects), FCollisionShape::MakeSphere(Radius), SphereParams);
		for (FOverlapResult& Overlap : Overlaps)
		{
			if (Overlap.GetActor()->Implements<UCombatInterface>() && !ICombatInterface::Execute_IsDead(Overlap.GetActor()))
			{
				OutOverlappingActors.AddUnique(ICombatInterface::Execute_GetAvatar(Overlap.GetActor()));
			}
		}
	}
}

void UAuraAbilitySystemLibrary::GetClosestTargets(int32 MaxTargets, const TArray<AActor*>& Actors, TArray<AActor*>& OutClosestTargets, const FVector& Origin)
{
	if (Actors.Num() <= MaxTargets)
	{
		OutClosestTargets = Actors;
		return;
	}
	
	TArray<AActor*> ActorsToCheck = Actors;
	int32 NumTargetsFound = 0;

	while (NumTargetsFound < MaxTargets)
	{
		if (ActorsToCheck.Num() < 1) return;
		double ClosestDistance = TNumericLimits<double>::Max();
		AActor* ClosestActor;
		for (AActor* PotentialTarget : ActorsToCheck)
		{
			const double Distance = (PotentialTarget->GetActorLocation() - Origin).Length();
			if (Distance < ClosestDistance)
			{
				ClosestDistance = Distance;
				ClosestActor = PotentialTarget;
			}
		}
		ActorsToCheck.Remove(ClosestActor);
		OutClosestTargets.AddUnique(ClosestActor);
		NumTargetsFound++;
	}
}

bool UAuraAbilitySystemLibrary::IsNotFriend(AActor* FirstActor, AActor* SecondActor)
{
	return	
		!(
			(FirstActor->ActorHasTag(FName("Player")) && SecondActor->ActorHasTag(FName("Player"))) ||
			(FirstActor->ActorHasTag(FName("Enemy")) && SecondActor->ActorHasTag(FName("Enemy")))
		);
}

FActiveGameplayEffectHandle UAuraAbilitySystemLibrary::ApplyDamageEffect(const FDamageEffectParams& DamageEffectParams)
{
	if (!DamageEffectParams.TargetAbilitySystemComponent) return FActiveGameplayEffectHandle();

	const FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();
	AActor* SourceAvatarActor = DamageEffectParams.SourceActor;
	UAbilitySystemComponent* ASC;
	if (DamageEffectParams.SourceAbilitySystemComponent) ASC = DamageEffectParams.SourceAbilitySystemComponent;
	else if (DamageEffectParams.TargetAbilitySystemComponent) ASC = DamageEffectParams.TargetAbilitySystemComponent;
	else return FActiveGameplayEffectHandle();
	
	if (!SourceAvatarActor && DamageEffectParams.SourceAbilitySystemComponent)
	{
		SourceAvatarActor = DamageEffectParams.SourceAbilitySystemComponent->GetAvatarActor();
	}

	FAuraGameplayEffectContext AuraEffectContext = FAuraGameplayEffectContext();
	AuraEffectContext;

	FGameplayEffectContextHandle EffectContextHandle = ASC->MakeEffectContext();

	EffectContextHandle.AddSourceObject(SourceAvatarActor);
	SetDeathImpulse(EffectContextHandle, DamageEffectParams.DeathImpulse);
	SetKnockbackForce(EffectContextHandle, DamageEffectParams.KnockbackForce);
	SetImpactPoint(EffectContextHandle, DamageEffectParams.ImpactPoint);
	SetIsStabHit(EffectContextHandle, DamageEffectParams.bIsStabHit);
	SetDamageType(EffectContextHandle, DamageEffectParams.DamageType);
	SetDebuffDamage(EffectContextHandle, DamageEffectParams.DebuffDamage);
	SetDebuffDuration(EffectContextHandle, DamageEffectParams.DebuffDuration);
	SetDebuffFrequency(EffectContextHandle, DamageEffectParams.DebuffFrequency);
	SetDamageCauser(EffectContextHandle, DamageEffectParams.DamageCauser);
	
	check(DamageEffectParams.DamageGameplayEffectClass);

	const FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(DamageEffectParams.DamageGameplayEffectClass, DamageEffectParams.AbilityLevel, EffectContextHandle);

	for (auto& Pair : DamageEffectParams.DamageByType)
	{
		UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle,Pair.Key, Pair.Value);
	}
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, DamageEffectParams.DamageType, DamageEffectParams.BaseDamage);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Debuff_Chance, DamageEffectParams.DebuffChance);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Debuff_Damage, DamageEffectParams.DebuffDamage);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Debuff_Duration, DamageEffectParams.DebuffDuration);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Debuff_Frequency, DamageEffectParams.DebuffFrequency);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.DamageBonus, DamageEffectParams.DamageBonus);

	return DamageEffectParams.TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data);
}

//FActiveGameplayEffectHandle UAuraAbilitySystemLibrary::ApplyDamageEffectAndGetActiveEffectHandle(const FDamageEffectParams& DamageEffectParams)
//{
//	const FAuraGameplayTags& GameplayTags = FAuraGameplayTags::Get();
//	AActor* SourceAvatarActor = DamageEffectParams.SourceActor;
//	UAbilitySystemComponent* ASC;
//	if (DamageEffectParams.SourceAbilitySystemComponent) ASC = DamageEffectParams.SourceAbilitySystemComponent;
//	else if (DamageEffectParams.TargetAbilitySystemComponent) ASC = DamageEffectParams.TargetAbilitySystemComponent;
//	else return FActiveGameplayEffectHandle();
//
//	if (!SourceAvatarActor && DamageEffectParams.SourceAbilitySystemComponent)
//	{
//		SourceAvatarActor = DamageEffectParams.SourceAbilitySystemComponent->GetAvatarActor();
//	}
//
//	FGameplayEffectContextHandle EffectContextHandle = ASC->MakeEffectContext();
//	EffectContextHandle.AddSourceObject(SourceAvatarActor);
//	SetDeathImpulse(EffectContextHandle, DamageEffectParams.DeathImpulse);
//	SetKnockbackForce(EffectContextHandle, DamageEffectParams.KnockbackForce);
//	SetImpactPoint(EffectContextHandle, DamageEffectParams.ImpactPoint);
//	SetIsStabHit(EffectContextHandle, DamageEffectParams.bIsStabHit);
//	const FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(DamageEffectParams.DamageGameplayEffectClass, DamageEffectParams.AbilityLevel, EffectContextHandle);
//
//	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, DamageEffectParams.DamageType, DamageEffectParams.BaseDamage);
//	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Debuff_Chance, DamageEffectParams.DebuffChance);
//	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Debuff_Damage, DamageEffectParams.DebuffDamage);
//	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Debuff_Duration, DamageEffectParams.DebuffDuration);
//	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Debuff_Frequency, DamageEffectParams.DebuffFrequency);
//	return DamageEffectParams.TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data);
//}

TArray<FRotator> UAuraAbilitySystemLibrary::EvenlySpacedRotators(const FVector& Forward, float SpreadAngle, int32 NumRotators, const FVector& Axis)
{
	TArray<FRotator> Rotators;

	const FVector LeftOfSpread = Forward.RotateAngleAxis(-SpreadAngle / 2.f, Axis);
	const float DeltaSpread = SpreadAngle / FMath::Max((NumRotators - 1), 1);
	for (int32 i = 0; i < NumRotators; i++)
	{
		const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i, Axis);
		Rotators.Add(Direction.Rotation());
	}
	return Rotators;
}

TArray<FVector> UAuraAbilitySystemLibrary::EvenlyRotateVectors(const FVector& Forward, float SpreadAngle, int32 NumVectors, const FVector& Axis)
{
	TArray<FVector> Vectors;

	const FVector LeftOfSpread = Forward.GetSafeNormal().RotateAngleAxis(-SpreadAngle / 2.f, Axis);
	const float DeltaSpread = SpreadAngle / FMath::Max((NumVectors - 1), 1);
	for (int32 i = 0; i < NumVectors; i++)
	{
		const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i, Axis);
		Vectors.Add(Direction);
	}
	return Vectors;
}

AAuraPlayerController* UAuraAbilitySystemLibrary::GetAuraPlayerController(AActor* Avatar)
{
	AAuraCharacter* AuraCharacter = static_cast<AAuraCharacter*>(Avatar);
	if (AuraCharacter) return static_cast<AAuraPlayerController*>(AuraCharacter->GetController());
	else return nullptr;
}

void UAuraAbilitySystemLibrary::SetRotationMode(AActor* Avatar, ERotationMode RotationMode)
{
	ACharacter* Character = static_cast<ACharacter*>(Avatar);
	if (!Character || !Character->GetCharacterMovement()) return;
	switch (RotationMode)
	{
	case ERotationMode::ERM_OrientToCamera:
		//Character->bUseControllerRotationYaw = false; 
		Character->GetCharacterMovement()->bUseControllerDesiredRotation = true;
		Character->GetCharacterMovement()->bOrientRotationToMovement = false;
		break;
	case ERotationMode::ERM_OrientToMovement:
		//Character->bUseControllerRotationYaw = false;
		Character->GetCharacterMovement()->bUseControllerDesiredRotation = false;
		Character->GetCharacterMovement()->bOrientRotationToMovement = true;
		break;
	}
}

void UAuraAbilitySystemLibrary::DisableTargeting(AActor* Avatar)
{
	AAuraPlayerController* AuraPlayerController = UAuraAbilitySystemLibrary::GetAuraPlayerController(Avatar);
	if (!AuraPlayerController) return;
	AuraPlayerController->DisableTargeting();
}

bool UAuraAbilitySystemLibrary::IsTargetingMode(AActor* Avatar)
{
	AAuraPlayerController* AuraPlayerController = UAuraAbilitySystemLibrary::GetAuraPlayerController(Avatar);
	if (AuraPlayerController)
		return AuraPlayerController->IsTargeting();
	else
		return false;
}

AActor* UAuraAbilitySystemLibrary::GetEnemyToStab(AActor* Avatar, float StabRadius)
{
	TArray<AActor*> CloseActors = TArray<AActor*>();
	TArray<AActor*> IgnoreActors = TArray<AActor*>();

	IgnoreActors.Add(Avatar);
	UAuraAbilitySystemLibrary::GetLivePlayersWithinRadius(Avatar, CloseActors, IgnoreActors, StabRadius, Avatar->GetActorLocation());

	if (CloseActors.Num() < 1) return nullptr;

	TArray<AActor*> FromBackActors = TArray<AActor*>();
	for (AActor* OtherActor : CloseActors)
	{
		if (OtherActor->Implements<UCombatInterface>())
		{
			if (!ICombatInterface::Execute_IsParryImmune(OtherActor))
			{
				if (ICombatInterface::Execute_IsStunned(OtherActor)) return OtherActor;

				const float StabbedAngle = ICombatInterface::Execute_GetStabbedAngle(OtherActor);
				if (UAuraAbilitySystemLibrary::GetAngleToOpponentBack(Avatar, OtherActor) < StabbedAngle && GetOrientationsAngle(Avatar, OtherActor) < StabbedAngle)
				{
					FromBackActors.AddUnique(OtherActor);
				}
			}
		}
	}
	if (FromBackActors.Num() < 1) return nullptr;
	if (FromBackActors.Num() == 1) return FromBackActors[0];
	if (FromBackActors.Num() > 1)
	{
		return GetClosestActor(Avatar, FromBackActors);
	}
	return nullptr;
}

UAuraUserMessageData* UAuraAbilitySystemLibrary::GetAuraUserMessageData(APlayerController* PC)
{
	AAuraHUD* AuraHUD = Cast<AAuraHUD>(PC->GetHUD());
	if(AuraHUD) return AuraHUD->GetAuraUserMessageData();
	return nullptr;
}

float UAuraAbilitySystemLibrary::GetAngleToOpponentBack(AActor* Avatar, AActor* OtherActor)
{
	const FVector AvatarToOtherActor = (OtherActor->GetActorLocation() - Avatar->GetActorLocation()).GetSafeNormal2D();
	const FVector OpponentFowardVector = OtherActor->GetActorForwardVector().GetSafeNormal2D();
	const float DotProduct = FVector::DotProduct(AvatarToOtherActor, OpponentFowardVector);
	const float AngleInRadians = FMath::Acos(DotProduct);
	return FMath::Abs(FMath::RadiansToDegrees(AngleInRadians));
}

float UAuraAbilitySystemLibrary::GetOrientationsAngle(AActor* Avatar, AActor* OtherActor)
{
	const FVector AvatarFowardVector = Avatar->GetActorForwardVector().GetSafeNormal2D();
	const FVector OpponentFowardVector = OtherActor->GetActorForwardVector().GetSafeNormal2D();
	const float DotProduct = FVector::DotProduct(AvatarFowardVector, OpponentFowardVector);
	const float AngleInRadians = FMath::Acos(DotProduct);
	return FMath::Abs(FMath::RadiansToDegrees(AngleInRadians));
}

AActor* UAuraAbilitySystemLibrary::GetClosestActor(AActor* Avatar, const TArray<AActor*>& OtherActors)
{
	AActor* ClosestActor = nullptr;
	float MinDistance = 10000.f;
	for (AActor* OtherActor : OtherActors)
	{
		const float CurrentDistance = OtherActor->GetDistanceTo(Avatar);
		if (CurrentDistance < MinDistance)
		{
			MinDistance = CurrentDistance;
			ClosestActor = OtherActor;
		}
	}
	return ClosestActor;
}


