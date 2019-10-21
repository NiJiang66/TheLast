// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

/**
 * 单例模板类
 */
template<class T>
class THELAST_API FTL_Singleton
{
public:
	
	static TSharedPtr<T> Get();

private:

	static void Initialize();

	static TSharedPtr<T> Create();

private:

	static TSharedPtr<T> TInstance;
};



template<class T>
TSharedPtr<T> FTL_Singleton<T>::TInstance = NULL;

template<class T>
TSharedPtr<T> FTL_Singleton<T>::Create()
{
	TSharedPtr<T> TRef = MakeShareable(new T());
	return TRef;
}

template<class T>
void FTL_Singleton<T>::Initialize()
{
	if (!TInstance.IsValid())
	{
		TInstance = Create();
	}
}

template<class T>
TSharedPtr<T> FTL_Singleton<T>::Get()
{
	Initialize();
	return TInstance;
}


