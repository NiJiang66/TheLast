// Fill out your copyright notice in the Description page of Project Settings.
#include "TLActorTool.h"
#include "Engine/Engine.h"
#include "GameFramework/Actor.h"
#include "EngineUtils.h"

bool UTLActorTool::GetFirstActor_BP(UObject* WObj, TSubclassOf<AActor> AClass, AActor*& Actor)
{
	Actor = NULL;
	if (!WObj)return false;
	UWorld* World = GEngine->GetWorldFromContextObjectChecked(WObj);
	if (!World)return false;

	for (TActorIterator<AActor> It(World, AClass); It; ++It)
	{
		Actor = *It;
		if (Actor && !Actor->IsPendingKill())
		{
			return true;
		}

	}
	return false;
}
