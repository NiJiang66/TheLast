#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "TL_Types.h"
#include "TL_AnimNotifies.generated.h"

/**
 * 
 */
UCLASS()
class THELAST_API UTL_AnimNotifies : public UAnimNotify
{
	GENERATED_BODY()
	
};

UCLASS()
class THELAST_API UTL_AnimNotifyStates : public UTL_AnimNotifies
{
	GENERATED_BODY()

};

UCLASS()
class THELAST_API UTL_AN_FwdForce : public UTL_AnimNotifies
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FForceStruct Force;

};

UCLASS()
class THELAST_API UTL_ANS_BoxTraceCheckHit : public UTL_AnimNotifyStates
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FVector4 RangeAndFwdOffset = FVector4(1.f, 1.f, 1.f, 60.f);
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FCombatSenseStruct CombatSenseStruct;

};

UCLASS()
class THELAST_API UTL_ANS_LineTraceCheckHit : public UTL_AnimNotifyStates
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 LineNums = 5;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FCombatSenseStruct CombatSenseStruct;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bCustomizeTraceSocket = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FName TraceSocket0;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FName TraceSocket1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float ProtectionSeconds = 0.2f;
};

UCLASS()
class THELAST_API UTL_AN_CheckTurn : public UTL_AnimNotifies
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float CheckTurnRadius = 200.f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 LineNum = 5;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float OffsetDegree = 60.f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bSphereCheckTwice = false;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Rot = 60.f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 RadNumMultiplier = 4;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool DebugDraw = false;
};

