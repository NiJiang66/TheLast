// Fill out your copyright notice in the Description page of Project Settings.


#include "TL_AssetManager.h"
#include "TL_DataAssetBase.h"
#include "TL_Helper.h"

const FPrimaryAssetType UTL_AssetManager::GameItemType = TEXT("GameItemType");
const FPrimaryAssetType UTL_AssetManager::SkillType = TEXT("SkillType");
const FPrimaryAssetType UTL_AssetManager::ComboTreeType = TEXT("ComboTreeType");
const FPrimaryAssetType UTL_AssetManager::MotionType = TEXT("MotionType");
const FPrimaryAssetType UTL_AssetManager::MotionListType = TEXT("MotionListType");
const FPrimaryAssetType UTL_AssetManager::NullType = TEXT("NullType");

UTL_AssetManager& UTL_AssetManager::Get()
{
	UTL_AssetManager* This = Cast<UTL_AssetManager>(GEngine->AssetManager);

	if (This) {
		return *This;
	}
	else{
		FString err = "Invalid AssetManager in DefaultEngine.ini, must be TL_AssetManager!!!";
		TL_Helper::Debug(err, 999, FColor::Red, ELogVerbosity::Fatal);
		return *NewObject<UTL_AssetManager>(); // never calls this
	}
}

UTL_DataAssetBase* UTL_AssetManager::ForceLoadItem(const FPrimaryAssetId& PrimaryAssetId, bool bLogWarning /*= true*/)
{
	FSoftObjectPath ItemPath = GetPrimaryAssetPath(PrimaryAssetId);

	// This does a synchronous load and may hitch
	UTL_DataAssetBase* LoadedItem = Cast<UTL_DataAssetBase>(ItemPath.TryLoad());

	if (bLogWarning && LoadedItem == nullptr){
		UE_LOG(LogTemp, Warning, TEXT("Failed to load item for identifier %s!"), *PrimaryAssetId.ToString());
	}
	return LoadedItem;
}

