// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TL_GameInstance.generated.h"

/**
 * 
 */
UCLASS()
class THELAST_API UTL_GameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	/**	指定需要加载的资源类型 */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "AutoLoadPrimary")
		TArray<FPrimaryAssetType> AutoLoadTypes;

	/**	重写初始化 */
	virtual void Init() override;

protected:
	/**	自动加载所有资产 */
	void AutoLoadDataAssets();

};
