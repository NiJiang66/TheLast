// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TL_DataAssetBase.h"
#include "InputCoreTypes.h"
#include "TL_Types.h"
#include "TL_SkillDataAsset.generated.h"

class ATL_Skill;
class ATL_Character;

/**
 * 技能数据资产
 */
UCLASS()
class THELAST_API UTL_SkillDataAsset : public UTL_DataAssetBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Input")
		TArray<FInputStruct> InputKeysAndTimes;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Skill")
		FName SkillName;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Skill")
		bool Active = true;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Skill")
		int32 SkillPriority = 0;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Skill")
		TSubclassOf<ATL_Skill> SkillSubClass;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		TSubclassOf<ATL_Character> Owner;	

};
