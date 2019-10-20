// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TL_Character.h"
#include "TL_SkillDataAsset.h"
#include "TL_SkillFsm.h"
#include "TL_SkillComponent.generated.h"

/**
 * 技能组件
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class THELAST_API UTL_SkillComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	/**	Sets default values for this component's properties */
	UTL_SkillComponent();

	/**	保存 Map: Skill and FSM(To Check Input and Spawn Mapped Skill) */
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Skills")
		TMap<UTL_SkillDataAsset*, UTL_SkillFsm*> SkillsMap;

	/**	技能组件拥有者 */
	UPROPERTY(BlueprintReadOnly)
		ATL_Character* PlayerCharacter;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	//
	void KeyInput(FKey key);

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/**	批量创建技能状态机 */
	UFUNCTION(BlueprintCallable)
		void ConstructFSM4Skills();

	/**	创建一个技能状态机 */
	bool ConstructFSM4Skill(UTL_SkillDataAsset* Skill);

private:
	int32 SkillCounter = 0;

		
	
};
