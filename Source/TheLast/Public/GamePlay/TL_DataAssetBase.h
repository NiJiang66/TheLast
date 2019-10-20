// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "TL_DataAssetBase.generated.h"

/**
 * 数据资产基类
 */
UCLASS()
class THELAST_API UTL_DataAssetBase : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:
	UTL_DataAssetBase();

	/** Type of this item, set in native parent class */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Item)
		FPrimaryAssetType ItemType;

	/** Overridden to use saved type */
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

	/** Returns the logical name, equivalent to the primary asset id */
	UFUNCTION(BlueprintCallable, Category = Item)
		FString GetIdentifierString() const;
};
