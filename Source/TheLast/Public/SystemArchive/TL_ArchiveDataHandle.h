// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TL_ArchiveDataInfo.h"



/**
 * 数据管理类
 */
class THELAST_API FTL_ArchiveDataHandle
{
public:
	static TSharedPtr<FTL_ArchiveDataHandle> Get();

	/** 初始化游戏数据 */
	void InitializeGameData();

public:
	/** 修改本地语言 */
	void ChangeLocalizationCulture(ECultureTeam Culture);
	/** 修改菜单音量 */
	void SetMenuVolume(float MusicVol, float SoundVol);
	/** 修改游戏音量 */
	void SetGameVolume(float MusicVol, float SoundVol);
	/** 添加新存档名 */
	void AddNewRecord();
private:
	/** 更新存档文件数据 */
	void UpdateRecordData();

public:

	/** 当前存档名列表 */
	FString CurrentRecordName;

	/** 当前存档数据 */
	FTL_ArchiveData CurrentRecordData;



private:

	/** 根据Enum类型获取字符串 */
	template<typename TEnum>
	FString GetEnumValueAsString(const FString& Name, TEnum Value);
	/** 根据字符串获取Enum值 */
	template<typename TEnum>
	TEnum GetEnumValueFromString(const FString& Name, FString Value);


	/** 初始化存档数据 */
	void InitRecordData();
	/** 初始化Menu声音数据 */
	void InitMenuAudio();



public:
	FTL_ArchiveDataHandle();
private:
	static void Initialize();
	static TSharedRef<FTL_ArchiveDataHandle> Create();
private:
	static TSharedPtr<FTL_ArchiveDataHandle> DataInstance;
};


template<typename TEnum>
FString FTL_ArchiveDataHandle::GetEnumValueAsString(const FString& Name, TEnum Value)
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, *Name, true);
	if (!EnumPtr) 
	{
		return FString("InValid");
	}
	return EnumPtr->GetEnumName((int32)Value);
}

template<typename TEnum>
TEnum FTL_ArchiveDataHandle::GetEnumValueFromString(const FString& Name, FString Value)
{
	const UEnum* EnumPtr = FindObject<UEnum>(ANY_PACKAGE, *Name, true);
	if (!EnumPtr) 
	{
		return TEnum(0);
	}
	return (TEnum)EnumPtr->GetIndexByName(FName(*FString(Value)));
}

