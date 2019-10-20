// Fill out your copyright notice in the Description page of Project Settings.

#include "TL_SkillFsmState.h"
#include "InputCoreTypes.h"

UTL_SkillFsmState::UTL_SkillFsmState()
{
}

void UTL_SkillFsmState::Init_SkillFsmStateInfo(int32 InStateID, int32 InKeyHash, float InTinputTime, int32 InMaxStateID)
{
	StateID = InStateID;
	KeyHash = InKeyHash;
	InputTime = InTinputTime;
	MaxStateID = InMaxStateID;
}

void UTL_SkillFsmState::Init_SkillFsmStateInfo(int32 InStateID, FKey InKeyCode, float InTinputTime, int32 InMaxStateID)
{
	StateID = InStateID;
	KeyHash = GetTypeHash(InKeyCode.GetFName());
	InputTime = InTinputTime;
	MaxStateID = InMaxStateID;
}

