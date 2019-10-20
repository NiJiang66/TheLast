// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TL_SkillFsmState.h"
#include "TimerManager.h"
#include "TL_SkillFsm.generated.h"

/**
 * 技能状态机
 */
UCLASS()
class THELAST_API UTL_SkillFsm : public UObject
{
	GENERATED_BODY()
	
public:
	/**	states mapped to valid input key list */
	UPROPERTY()
		TMap<int, UTL_SkillFsmState*> states;
	/**	保存当前状态节点 */
	UPROPERTY()
		UTL_SkillFsmState* CurrentState;

	/**	技能是否搓招完毕，是否可以使用 */
	bool IsSkillReady = false;

	/**	Add State with State Key Value */
	bool AddState(UTL_SkillFsmState* StateToAdd);
	/**	更改状态机状态节点 */
	bool ChangeState(int32 InStateID);

	/**	检查按键 */
	void Check(int32 InputKeyHash);

	/**	搓招计时 */
	FTimerHandle ResetTimer;
	void SetTimer(float TimerDelay);
	void ResetFSM();
};
