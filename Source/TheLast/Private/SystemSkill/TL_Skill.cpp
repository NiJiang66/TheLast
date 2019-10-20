// Copyright Crystal Boy/Hika

#include "TL_Skill.h"
#include "TL_SkillComponent.h"



void ATL_Skill::Perform(UTL_SkillDataAsset* SkillData, ATL_Character* InPlayerCharacter)
{
	if (SkillData) {
		MainProcess(SkillData, InPlayerCharacter);
		BP_SkillProcess(SkillData, InPlayerCharacter);
	}	
}

void ATL_Skill::SkillDestory()
{
	GetWorld()->GetTimerManager().ClearTimer(DestoryTimer);
	Destroy();
}

void ATL_Skill::MainProcess(UTL_SkillDataAsset* SkillData, ATL_Character* InPlayerCharacter)
{
	if (GetWorld()) {
		GetWorld()->GetTimerManager().SetTimer(DestoryTimer, this, &ATL_Skill::SkillDestory, LifeTime + 0.001f, false);
	}
}


