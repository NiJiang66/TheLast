#pragma once
#include "CoreMinimal.h"
#include "TL_DataAssetBase.h"
#include "TL_ItemDataAsset.generated.h"

/**
 * 物品数据资产
 */
UCLASS()
class THELAST_API UTL_ItemDataAsset : public UTL_DataAssetBase
{
	GENERATED_BODY()	
public:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		FName ItemName;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		FString ItemDescription;
	
};
 
/**
 * 武器数据资产
 */
UCLASS()
class THELAST_API UTL_WeaponDataAsset : public UTL_ItemDataAsset
{
	GENERATED_BODY()	
public:

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		TSubclassOf<class ATL_Weapon> WeaponSubClass;
	
};
