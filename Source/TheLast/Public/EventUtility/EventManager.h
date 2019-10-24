// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EventManager.generated.h"

class UEventDataBase;

/**
 * 事件分发机制管理器
 */
UCLASS()
class THELAST_API UEventManager : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	/** 注册观察者(监听者) */
	UFUNCTION(BlueprintCallable, Category = "EventDistributionUtility")
		static void AddEventListener(FString EventName, UObject* Listener);
	/** 移除观察者(监听者) */
	UFUNCTION(BlueprintCallable, Category = "EventDistributionUtility")
		static void RemoveEventListener(FString EventName, UObject* Listener);
	/** 发送事件 */
	UFUNCTION(BlueprintCallable, Category = "EventDistributionUtility")
		static FString DispatchEvent(FString EventName, UObject* Datas);

public:
	/** 蓝图调用，根据类型创建数据类对象，并返回该对象指针 */
	UFUNCTION(BlueprintCallable, Category = "EventDistributionUtility", meta = (DeterminesOutputType = "ClassType"))
		static UEventDataBase* NewDataObj(TSubclassOf<UEventDataBase> ClassType);
	/**	C++调用，根据类型创建数据类对象，并返回该对象指针 */
	template<typename T>
	static T* NewDataObj() {
		NewDataObj(T::StaticClass());
	}

private:
	/** 存放所有观察者对象的列表，仅由EventManager自己管理 */
	static TMap<FString, TArray<UObject*>> AllListener;
};
