// Fill out your copyright notice in the Description page of Project Settings.

#include "TL_SkillComponent.h"
#include "Engine/Engine.h"
#include "TL_DataAssetBase.h"
#include "TL_Skill.h"
#include "TL_AssetManager.h"
#include "TL_Helper.h"

// Sets default values for this component's properties
UTL_SkillComponent::UTL_SkillComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UTL_SkillComponent::BeginPlay()
{
	Super::BeginPlay();

	check(GetOwner());
	PlayerCharacter = Cast<ATL_Character>(GetOwner());

	ConstructFSM4Skills();//批量创建技能状态机
}

void UTL_SkillComponent::KeyInput(FKey key)
{
	TL_Helper::Debug(FString("KeyHash:") + FString::FromInt(GetTypeHash(key.GetFName())));

	int32 KeyHash = GetTypeHash(key.GetFName());
	if (SkillsMap.Num() > 0) {
		for (auto& SkillMap : SkillsMap) {
			UTL_SkillFsm* CurrentFsm = SkillMap.Value;
			CurrentFsm->Check(KeyHash);
			if (CurrentFsm->IsSkillReady) {
				CurrentFsm->ResetFSM();
				//Perform Skill
				UTL_SkillDataAsset* SkillToPerform = SkillMap.Key;
				ATL_Skill* NewSkill;
				UClass* SkillClass = SkillToPerform->SkillSubClass.Get();
				NewSkill = GetWorld()->SpawnActor<ATL_Skill>(SkillClass, PlayerCharacter->GetTransform());
				if (SkillToPerform && NewSkill) {
					NewSkill->Perform(SkillToPerform, PlayerCharacter);
					return;
				}
			}
		}
	}
}

// Called every frame
void UTL_SkillComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UTL_SkillComponent::ConstructFSM4Skills()
{
	UTL_AssetManager& Manager = UTL_AssetManager::Get();
	TArray<FPrimaryAssetId> SkillIds;
	Manager.GetPrimaryAssetIdList(Manager.SkillType, SkillIds);
	for (auto& _Id : SkillIds) {
		UTL_SkillDataAsset* TempData = Cast<UTL_SkillDataAsset>(Manager.GetPrimaryAssetObject(_Id));
		if (!TempData) {
			TempData = Cast<UTL_SkillDataAsset>(Manager.ForceLoadItem(_Id));
		}
		if (TempData && TempData->Owner && this->GetOwner()->IsA(TempData->Owner.Get())) {
			ConstructFSM4Skill(TempData);
		}
	}
	//Sort the map with Skill Priority
	SkillsMap.KeySort([](const UTL_SkillDataAsset& A, const UTL_SkillDataAsset& B) {
		return (A.SkillPriority) < (B.SkillPriority);
	});
}

bool UTL_SkillComponent::ConstructFSM4Skill(UTL_SkillDataAsset* Skill)
{	
	if (Skill && Skill->InputKeysAndTimes.Num() > 0) {
		UTL_SkillFsm* CurrentFSM = NewObject<UTL_SkillFsm>(this);
		if (CurrentFSM) {
			for (int i = 0; i < Skill->InputKeysAndTimes.Num(); i++) {
				FString SkillFsmStateStr("State");
				SkillFsmStateStr.Append(FString::FromInt(i));
				FName SkillName = FName(*SkillFsmStateStr);
				UTL_SkillFsmState* NewState = NewObject<UTL_SkillFsmState>(CurrentFSM);
				NewState->Init_SkillFsmStateInfo(i, Skill->InputKeysAndTimes[i].Key, Skill->InputKeysAndTimes[i].InputTime, Skill->InputKeysAndTimes.Num() - 1);
				CurrentFSM->AddState(NewState);
				TL_Helper::Debug(Skill->InputKeysAndTimes[i].Key.GetFName().ToString());
			}
			//CurrentFSM->AddToRoot();
			SkillsMap.Add(Skill, CurrentFSM);
			return true;
		}
		else return false;
	}
	else {
		TL_Helper::Debug(TEXT("Skill System Find illegal Skill Input!"), 20, FColor::Red);
		return false;
	}
	
}

