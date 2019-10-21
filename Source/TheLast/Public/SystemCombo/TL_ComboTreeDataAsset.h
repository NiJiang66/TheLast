#pragma once
#include "CoreMinimal.h"
#include "TL_DataAssetBase.h"
#include "TL_ComboTreeDataAsset.generated.h"

class UTL_ComboMotionDataAsset;
class UTL_SkillDataAsset;
class UTexture2D;

/**
 * 组合连招树数据资产
 */
UCLASS()
class THELAST_API UTL_ComboTreeDataAsset : public UTL_DataAssetBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		UTexture2D* Icon;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		UTL_ComboMotionDataAsset* StartState;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		UTL_ComboMotionDataAsset* DodgeMotion;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		UTL_ComboMotionDataAsset* ChangeMotion;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		UTL_SkillDataAsset* SkillChangeOut;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		UTL_SkillDataAsset* SkillBlendIn;

};
