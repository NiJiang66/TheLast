// Copyright Crystal Boy/Hika

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TL_Skill.generated.h"

class ATL_Character; 
class UTL_SkillDataAsset;

/**
 * 技能类
 */
UCLASS(Abstract, Blueprintable)
class THELAST_API ATL_Skill : public AActor
{
	GENERATED_BODY()

public:
	/**	施展技能 */
	UFUNCTION(BlueprintCallable)
		void Perform(UTL_SkillDataAsset* SkillData, ATL_Character* InPlayerCharacter);

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float LifeTime = 8.f;

	/**	计时器 */
	FTimerHandle DestoryTimer;

protected:
	//Override this
	UFUNCTION()
		void SkillDestory();
	UFUNCTION()
		virtual void MainProcess(UTL_SkillDataAsset* SkillData, ATL_Character* InPlayerCharacter);
	UFUNCTION(BlueprintImplementableEvent)
		void BP_SkillProcess(UTL_SkillDataAsset* SkillData, ATL_Character* InPlayerCharacter);
	
};
