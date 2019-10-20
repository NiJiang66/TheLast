// Copyright Crystal Boy/Hika

#pragma once

#include "CoreMinimal.h"
#include "Particles/ParticleSystem.h"
#include "InputCoreTypes.h"
#include "Camera/CameraShake.h"
#include "TL_Types.generated.h"

//Property
UENUM(BlueprintType)
enum class EACT_PropertyEnum : uint8
{
	E_None      UMETA(DisplayName = "None"),
	E_Health     UMETA(DisplayName = "Health"),
	E_Attack     UMETA(DisplayName = "Attack"),
	E_MotionSpeed UMETA(DisplayName = "MotionSpeed"),
	E_Stamina UMETA(DisplayName = "Stamina")
};

USTRUCT(BlueprintType)
struct FACT_PropertyStruct
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Min = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Current = 100;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Max = 100;
};

/**
 * 按键输入结构
 */
USTRUCT(BlueprintType)
struct FInputStruct
{
	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		FKey Key;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		float InputTime = .5f;
};

//Hit
USTRUCT(Blueprintable, BlueprintType)
struct FForceStruct {

	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ForceStrength;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ForceDuration;
};

USTRUCT(Blueprintable, BlueprintType)
struct FHitForceStruct {

	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FForceStruct ForceStruct;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float UpForce;
};

USTRUCT(Blueprintable, BlueprintType)
struct FHitReacStruct {

	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bTurnToDmgCauser = true;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage = 25.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float KnockBackIntensity = 250.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float KnockUpIntensity = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HitForceDuration = .2f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TargetFXScale = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UDamageType> DamageType;
};

USTRUCT(Blueprintable, BlueprintType)
struct FCombatSenseStruct {

	GENERATED_USTRUCT_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Duration = .01f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeDilation = .15f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float CameraBloomMin = 0.75f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UParticleSystem* EmitterTemplate;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FXScale = 1.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UCurveFloat* CameraCurve;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UCameraShake> CameraShake;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FHitReacStruct HitReact;
};

UENUM(BlueprintType)
enum class EStateTypes : uint8
{
	E_IDLE UMETA(DisplayName = "Idle"),
	E_WALK UMETA(DisplayName = "Walk"),
	E_SPRINT UMETA(DisplayName = "Sprint"),
	E_MOTION UMETA(DisplayName = "Motioning"),
	E_CROUCH UMETA(DisplayName = "Crouch"),
	E_NULLTYPE,
};

UENUM(BlueprintType)
enum class EWeaponTypes : uint8
{
	E_MELEE UMETA(DisplayName = "MeleeWeapon"),
	E_BOW UMETA(DisplayName = "BowWeapon"),
	E_SPECITEM UMETA(DisplayName = "SpecialWeapon"),
	E_NULLTYPE,
};