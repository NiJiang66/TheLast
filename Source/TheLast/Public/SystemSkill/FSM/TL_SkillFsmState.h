// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InputCoreTypes.h"
#include "TL_SkillFsmState.generated.h"

struct FKey;

/**
 * 技能状态机的节点
 */
UCLASS()
class THELAST_API UTL_SkillFsmState : public UObject
{
	GENERATED_BODY()
public:
	/**	State ID */
	int32 StateID = 0;

	/**	Key Mapped */
	int32 KeyHash = 0;

	/**	Time */
	float InputTime = 1.f;

	/**	max */
	int32 MaxStateID = 0;
	
	/**	初始化状态机节点信息 */
	void Init_SkillFsmStateInfo(int32 InStateID, int32 InKeyHash, float InTinputTime, int32 InMaxStateID);
	void Init_SkillFsmStateInfo(int32 InStateID, FKey InKeyCode, float InTinputTime, int32 InMaxStateID);

	UTL_SkillFsmState();

};
