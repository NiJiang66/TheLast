#pragma once
#include "CoreMinimal.h"
#include "TL_DataAssetBase.h"
#include "TL_MotionDataAsset.h"
#include "TL_MotionListDataAsset.generated.h"

class UTL_HitMotionDataAsset;

/**
 * 动作列表数据资产
 */
UCLASS(Abstract)
class THELAST_API UTL_MotionListDataAsset : public UTL_DataAssetBase
{
	GENERATED_BODY()

};

/**
 * 武器动作列表数据资产
 */
UCLASS()
class THELAST_API UTL_WeaponMotionListDataAsset : public UTL_MotionListDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		UTL_MotionDataAsset* EquipMotion;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		UTL_MotionDataAsset* UnequipMotion;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		UTL_MotionDataAsset* Fwd;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		UTL_MotionDataAsset* FwdLeft;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		UTL_MotionDataAsset* FwdRight;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		UTL_MotionDataAsset* Bwd;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		UTL_MotionDataAsset* BwdLeft;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		UTL_MotionDataAsset* BwdRight;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		UTL_MotionDataAsset* HitDown;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		UTL_MotionDataAsset* HitDown_Loop;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		UTL_MotionDataAsset* HitDown_Exit;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		UTL_MotionDataAsset* Fwd_KnockBack;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		UTL_MotionDataAsset* Bwd_KnockBack;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		UTL_MotionDataAsset* DeadMotion;
};
