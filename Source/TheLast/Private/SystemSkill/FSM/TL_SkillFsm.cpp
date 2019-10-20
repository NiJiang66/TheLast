// Fill out your copyright notice in the Description page of Project Settings.

#include "TL_SkillFsm.h"
#include "TL_Helper.h"

bool UTL_SkillFsm::AddState(UTL_SkillFsmState* StateToAdd)
{
	if (StateToAdd && !states.Contains(StateToAdd->StateID)) {
		states.Add(StateToAdd->StateID, StateToAdd);
		return true;
	}
	return false;
}

bool UTL_SkillFsm::ChangeState(int32 InStateID)
{
	if (states.Contains(InStateID)) {
		UTL_SkillFsmState* FsmState = states[InStateID];
		if (FsmState) {
			CurrentState = FsmState;
			return true;
		}
	}
	return false;
}


void UTL_SkillFsm::Check(int32 InputKeyHash)
{
	if (CurrentState == nullptr && states[0]) {
		ResetFSM();
	}
	if (CurrentState && InputKeyHash == CurrentState->KeyHash) {
		//TL_Helper::Debug(TEXT("Check One FSM"));
		SetTimer(CurrentState->InputTime);
		if (CurrentState->StateID == CurrentState->MaxStateID) {
			TL_Helper::Debug(TEXT("Skill is ready, Change State to 0"), 5);
			IsSkillReady = true;
			ChangeState(0);
			return;
		}
		else ChangeState(CurrentState->StateID + 1);
	}
	else {
		ResetFSM();
	}
}

void UTL_SkillFsm::SetTimer(float TimerDelay)
{
	if (GetWorld()) {
		GetWorld()->GetTimerManager().SetTimer(ResetTimer, this, &UTL_SkillFsm::ResetFSM, TimerDelay + 0.001f,false);
	}
}

void UTL_SkillFsm::ResetFSM()
{
	IsSkillReady = false;
	GetWorld()->GetTimerManager().ClearTimer(ResetTimer);
	ChangeState(0);
}
