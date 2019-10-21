#pragma once
#include "CoreMinimal.h"
#include "TL_MotionDataAsset.h"
#include "TL_ComboMotionDataAsset.generated.h"

/**
 * 连招动作数据资产
 */
UCLASS()
class THELAST_API UTL_ComboMotionDataAsset : public UTL_MotionDataAsset
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Combo")
		bool Branch = false;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Combo")
		UTL_ComboMotionDataAsset* NextCombo;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Combo")
		UTL_ComboMotionDataAsset* BranchCombo;
};
