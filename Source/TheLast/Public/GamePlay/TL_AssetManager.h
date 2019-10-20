// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "TL_AssetManager.generated.h"

class UTL_DataAssetBase;

/**
 * 资产管理器
 */
UCLASS()
class THELAST_API UTL_AssetManager : public UAssetManager
{
	GENERATED_BODY()
public:	
	UTL_AssetManager() {}

	//Static Types of items
	static const FPrimaryAssetType GameItemType;
	static const FPrimaryAssetType SkillType;
	static const FPrimaryAssetType ComboTreeType;
	static const FPrimaryAssetType MotionType;
	static const FPrimaryAssetType MotionListType;
	static const FPrimaryAssetType NullType;


	/**	获得当前 AssetManager 单例 */
	static UTL_AssetManager& Get();

	/**
	 * Synchronously loads an RPGItem subclass, this can hitch but is useful when you cannot wait for an async load
	 * This does not maintain a reference to the item so it will garbage collect if not loaded some other way
	 *
	 * @param PrimaryAssetId The asset identifier to load
	 * @param bDisplayWarning If true, this will log a warning if the item failed to load
	 */
	UTL_DataAssetBase* ForceLoadItem(const FPrimaryAssetId& PrimaryAssetId, bool bLogWarning = true);
};
