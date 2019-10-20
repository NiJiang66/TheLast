// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TL_ActorTool.generated.h"

/**
 * 获取Actor引用的工具
 */
UCLASS()
class THELAST_API UTL_ActorTool : public UObject
{
	GENERATED_BODY()
	
public:
	/**
	 * 获取第一个Actor，蓝图调用
	 * @param		WorldContextObject			世界上下文对象
	 * @param		AClass						Actor类型
	 * @param		Actor						输出第一个Actor指针引用
	 * @return		是否成功找到
	 */
	UFUNCTION(BlueprintCallable, Category = "TLActorTool", meta = (WorldContextObject = "WObj", DeterminesOutputType = "AClass", DynamicOutputParam = "Actor"))
	static bool GetFirstActor_BP(UObject* WorldContextObject, TSubclassOf<AActor> AClass, AActor*& Actor);

	/**
	 * 获取第一个Actor
	 * @param		WorldContextObject			世界上下文对象
	 * @param		OutActor					输出第一个Actor指针引用
	 * @return		是否成功找到
	 * @return
	 */
	template<typename ActorTyp>
	static bool GetFirstActor(UWorld* WorldContextObject, ActorTyp*& OutActor)
	{
		OutActor = nullptr;
		if (!WorldContextObject) return false;

		for (TActorIterator<AActor> It(WorldContextObject); It; ++It)
		{
			AActor* MidActor = *It;
			if (!MidActor->IsPendingKill())
			{
				if (MidActor->IsA<ActorTyp>())
				{
					OutActor = Cast<ActorTyp>(MidActor);
					MidActor = nullptr;
					if (OutActor)
					{
						return true;
					}
				}
			}
		}
		return false;
	}	 

};
