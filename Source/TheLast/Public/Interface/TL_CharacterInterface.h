// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Particles/ParticleSystem.h"
#include "TL_Types.h"
#include "TL_CharacterInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTL_CharacterInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 角色接口
 */
class THELAST_API ITL_CharacterInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void TL_TakeDamage(USceneComponent* DamageCausor, FHitReacStruct HitReact, TSubclassOf<UDamageType> DamageType);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void TL_ApplyDamage(USceneComponent* DamageCausor, AActor* Target, UParticleSystem* ParticleTemplate, FHitReacStruct HitReact, TSubclassOf<UDamageType> DamageType, float FXScale = 1, bool bCustomizeLoc = false, FVector FXPos = FVector(0, 0, 0));

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void TL_DunFrame(float TimeDilation, float Duration, float CameraBoomMin, TSubclassOf<UCameraShake> CamearaShake, UCurveFloat* CameraCurve);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void TL_RegisterAttack(FCombatSenseStruct CombatSense, bool bCustomizeSocket, FName TraceStartSocket0, FName TraceStartSocket1);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void TL_UnregisterAttack();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void TL_CharacterDie();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void TL_DealDamage(float Damage);
};


// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTL_WeaponInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 武器接口
 */
class THELAST_API ITL_WeaponInterface
{
	GENERATED_BODY()

		// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void TL_RegisterAttack(FCombatSenseStruct CombatSense, bool bCustomizeSocket, FName TraceStartSocket0, FName TraceStartSocket1);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void TL_EnterEquip();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void TL_ExitEquip();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void TL_UnregisterAttack();
};