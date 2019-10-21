// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JsonUtilities/Public/JsonObjectConverter.h"
#include "TL_ArchiveDataInfo.h"

/**
 * Json管理类
 */
class THELAST_API FTL_ArchiveJsonHandle
{
public:

	/** 加载存档文件 */
	template<typename StructType>
	void LoadArchiveFile(FString FileName, StructType& Data);

	/** 保存存档文件 */
	template<typename StructType>
	void SaveArchiveFile(FString FileName, const StructType& Data);

private:

	/** 读取Json文件到字符串 */
	bool LoadStringFromFile(const FString& FileName, const FString& RelaPath, FString& ResultString);

	/** 保存字符串到Json文件 */
	bool SaveStringToFile(const FString& FileName, const FString& RelaPath, const FString& JsonString);
};



template<typename StructType>
void FTL_ArchiveJsonHandle::LoadArchiveFile(FString FileName, StructType& Data)
{
	FString JsonString = "";
	if (LoadStringFromFile(FileName, ARCHIVEFILE_RELATIVEPATH, JsonString))
	{
		FJsonObjectConverter::JsonObjectStringToUStruct(JsonString, &Data, 0, 0);
	}
}

template<typename StructType>
void FTL_ArchiveJsonHandle::SaveArchiveFile(FString FileName, const StructType& Data)
{
	FString JsonString = "";
	if (FJsonObjectConverter::UStructToJsonObjectString(Data, JsonString))
	{
		SaveStringToFile(FileName, ARCHIVEFILE_RELATIVEPATH, JsonString);
	}
}
