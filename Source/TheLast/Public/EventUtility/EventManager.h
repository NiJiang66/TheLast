// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "EventManager.generated.h"

/**
 * 
 */
UCLASS()
class THELAST_API UEventManager : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()


private:
	static TMap<FString, TArray<UObject*>> AllListener;
	
public:
	UFUNCTION(BlueprintCallable, Category = "EventDistributionUtility")
	static void AddEventListener(FString EventName, UObject* Listener);
	UFUNCTION(BlueprintCallable, Category = "EventDistributionUtility")
	static void RemoveEventListener(FString EventName, UObject* Listener);
	UFUNCTION(BlueprintCallable, Category = "EventDistributionUtility")
	static FString DispatchEvent(FString EventName, UObject* Datas);
	
	UFUNCTION(BlueprintCallable, Category = "EventDistributionUtility")
	static UObject* NewAsset(UClass* ClassType);
};
