// Fill out your copyright notice in the Description page of Project Settings.

#include "EventManager.h"
#include "Engine.h"
#include "EventDataBase.h"

TMap<FString, TArray<UObject*>> UEventManager::AllListener;

void UEventManager::AddEventListener(FString EventName, UObject* Listener)
{
	if (EventName.IsEmpty() || Listener == nullptr) {
		return;
	}

	Listener->AddToRoot();

	if (UEventManager::AllListener.Contains(EventName)) {
		UEventManager::AllListener[EventName].Emplace(Listener);
	}
	else {
		TArray<UObject*> arrTmp = { Listener };
		UEventManager::AllListener.Emplace(EventName, arrTmp);
	}
}

void UEventManager::RemoveEventListener(FString EventName, UObject* Listener)
{
	if (UEventManager::AllListener.Contains(EventName)) {
		UEventManager::AllListener[EventName].Remove(Listener);
		Listener->RemoveFromRoot();
	}
}

FString UEventManager::DispatchEvent(FString EventName, UObject* Datas)
{
	FString errorInfo = TEXT("");
	if (EventName.IsEmpty()) errorInfo += "EventName Is Empty!";
	if (Datas == nullptr) errorInfo += "Datas is nullptr!";
	if (EventName.IsEmpty() || Datas == nullptr) {
		if (Datas != nullptr) Datas->RemoveFromRoot();
		return errorInfo;
	}

	if (UEventManager::AllListener.Contains(EventName) && UEventManager::AllListener[EventName].Num() > 0) {
		for (UObject*& obj : UEventManager::AllListener[EventName]) {
			UFunction* fun = obj->FindFunction("ExecuteFun");
			if (fun == nullptr) {
				errorInfo += "'" + obj->GetName() + "'No 'ExecuteFun' Function. \n";
			}
			else {
				obj->ProcessEvent(fun, &Datas);
			}
		}
	}
	else {
		errorInfo = "'" + EventName + "'No Listener.";
	}
	if(Datas->IsRooted()){
		Datas->RemoveFromRoot();
	}	
	return errorInfo;
}

UEventDataBase* UEventManager::NewDataObj(TSubclassOf<UEventDataBase> ClassType)
{
	UEventDataBase* obj = NewObject<UEventDataBase>((UClass*)GetTransientPackage(), ClassType);
	if (obj) {
		obj->AddToRoot();
	}
	return obj;
}
