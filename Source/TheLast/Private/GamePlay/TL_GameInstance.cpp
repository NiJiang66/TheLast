// Fill out your copyright notice in the Description page of Project Settings.


#include "TL_GameInstance.h"
#include "TL_AssetManager.h"

void UTL_GameInstance::Init()
{
	Super::Init();
	AutoLoadDataAssets();
}

void UTL_GameInstance::AutoLoadDataAssets()
{
	UTL_AssetManager& Manager = UTL_AssetManager::Get();
	for (auto& Type : AutoLoadTypes) {
		FPrimaryAssetType CurrentType = Type;
		TArray<FPrimaryAssetId> AssetIds;
		if (Manager.GetPrimaryAssetIdList(CurrentType, AssetIds)) {
			Manager.LoadPrimaryAssets(AssetIds/*, TArray<FName>(), FStreamableDelegate(), 0*/);
		}
	}
}
