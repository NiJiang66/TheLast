// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Engine/EngineTypes.h"

//#include "TL_Weapon.h"
//#include "TL_WidgetInterface.h"
//#include "TL_CharacterInterface.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "TL_Character.generated.h"

class UTL_SkillComponent;

/**
 * 所有角色的基类
 */
UCLASS(config=Game)
class ATL_Character : public ACharacter//, public ITL_CharacterInterface, public ITL_WidgetInterface
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class USpringArmComponent* CameraBoom;
	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
		class UCameraComponent* FollowCamera;
public:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "State")
		float MoveSpeed = 1.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "State")
		float XAxisInput;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "State")
		float YAxisInput;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "State")
		bool Moveable = true;

public:
	ATL_Character();
	/** Base turn rate, in deg/sec. Other scaling may affect final turn rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
		float BaseTurnRate;
	/** Base look up/down rate, in deg/sec. Other scaling may affect final rate. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=Camera)
		float BaseLookUpRate;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		UTL_SkillComponent* SkillComponnt;

//Movement
protected:
	/** Called for forwards/backward input */
	void MoveForward(float Value);
	/** Called for side to side input */
	void MoveRight(float Value);
	//Movement Input Access
	UPROPERTY()
	bool bDirUseSelfRot = false;

	void TurnAtRate(float Rate);
	void LookUpAtRate(float Rate);
protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	//BeginPlay
	virtual void BeginPlay() override;
	// End of APawn interface

private:
	void AnyKeyFunc(FKey key);
	

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }


	//
	UFUNCTION(BlueprintPure)
	void GetTargetRelativePostion(FVector TargetPositon, float& FwdOrBwd, float& LOrR);
	UFUNCTION(BlueprintCallable)
	void SetLockMeshFwd(bool bValue) { GetCharacterMovement()->bOrientRotationToMovement = !bValue;  /*bDirUseSelfRot = bValue;*/ }


	//UFUNCTION(BlueprintCallable)
		//AActor* BindWeapon(TSubclassOf<AActor> WeaponSubClass, FName SocketName, USceneComponent* ComponentToBind);
	//UFUNCTION(BlueprintCallable)
		//bool TurnToTargetAtOnceWithHitResult(FHitResult HitResult);
	//UFUNCTION(BlueprintCallable)
		//bool TurnToTargetAtOnce(USceneComponent* Target);



public:

	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	//void ACT_ApplyDamage(USceneComponent* DamageCausor, AActor* Target, UParticleSystem* ParticleTemplate, FHitReacStruct HitReact, TSubclassOf<UDamageType> DamageType, float FXScale /* = 1 */, bool bCustomizeLoc, FVector FXPos);
	//virtual void ACT_ApplyDamage_Implementation(USceneComponent* DamageCausor, AActor* Target, UParticleSystem* ParticleTemplate, FHitReacStruct HitReact, TSubclassOf<UDamageType> DamageType, float FXScale /* = 1 */, bool bCustomizeLoc, FVector FXPos) override;

	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	//void ACT_TakeDamage(USceneComponent* DamageCausor, FHitReacStruct HitReact, TSubclassOf<UDamageType> DamageType);
	//virtual void ACT_TakeDamage_Implementation(USceneComponent* DamageCausor, FHitReacStruct HitReact, TSubclassOf<UDamageType> DamageType) override;

	//UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	//void ACT_DunFrame(float TimeDilation, float Duration, float CameraBoomMin, TSubclassOf<UCameraShake> CamearaShake, UCurveFloat* CameraCurve);
	//virtual void ACT_DunFrame_Implementation(float TimeDilation, float Duration, float CameraBoomMin, TSubclassOf<UCameraShake> CamearaShake, UCurveFloat* CameraCurve) override;


	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	//void ACT_RegisterAttack(FCombatSenseStruct CombatSense, bool bCustomizeSocket, FName TraceStartSocket0, FName TraceStartSocket1);
	//virtual void ACT_RegisterAttack_Implementation(FCombatSenseStruct CombatSense, bool bCustomizeSocket, FName TraceStartSocket0, FName TraceStartSocket1);

	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	//void ACT_UnregisterAttack();
	//virtual void ACT_UnregisterAttack_Implementation();



	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	//void ACT_DealDamage(float Damage);
	//virtual void ACT_DealDamage_Implementation(float Damage) override;



	//UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	//void ACT_CharacterDie();
	//virtual void ACT_CharacterDie_Implementation() override;

	//UI
	//UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	//void ACT_UpdatePropertyUI(EACT_PropertyEnum EProperty, float Value);
	//UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	//void ACT_InitializeUI();
	//UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	//void ACT_InitializePropertyUI(EACT_PropertyEnum EProperty);
};

