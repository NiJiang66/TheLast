// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EventInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UEventInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 事件分发机制接口
 */
class THELAST_API IEventInterface
{
	GENERATED_BODY()
public:
	/** 当事件发送时调用观察者(监听者)的ExecuteFun函数，实体对象通过实现该接口就成为观察者(监听者) */
	UFUNCTION(BlueprintImplementableEvent, Category = "EventDistributionUtility")
		void ExecuteFun(UObject* Datas);
};
