#pragma once
#include "CoreMinimal.h"
#include "TL_DataAssetBase.h"
#include "Animation/AnimMontage.h"
#include "TL_MotionDataAsset.generated.h"

/**
 * 动作数据资产
 */
UCLASS()
class THELAST_API UTL_MotionDataAsset : public UTL_DataAssetBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Motion")
		UAnimMontage* MotionMontage;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Motion")
		float MontagePlayRate = 1.f;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Motion")
		FName MontageStartingSection = FName("None");
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Motion")
		float MontageStartingPosition = 0.f;
};
