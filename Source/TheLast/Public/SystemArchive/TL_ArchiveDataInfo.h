// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TL_ArchiveDataInfo.generated.h"


//存档相对路径
#define ARCHIVEFILE_RELATIVEPATH		TEXT("Resource/ConfigData/")
//存档文件名
#define RECORDDATAFILENAME				TEXT("RecordData.json")


/** 语言 */
UENUM()
enum class ECultureTeam : uint8 
{
	EN = 0,
	ZH
};


/** 游戏存档数据 */
USTRUCT()
struct FTL_ArchiveData
{
	GENERATED_BODY()
public:
	FTL_ArchiveData() {}
	FTL_ArchiveData(ECultureTeam c, float m, float s, TArray<FString>* r)
		: Culture(c), MusicVolume(m), SoundVolume(s), RecordNameList(*r)
	{}

public:

	UPROPERTY()
	ECultureTeam Culture;

	UPROPERTY()
	float MusicVolume;

	UPROPERTY()
	float SoundVolume;

	UPROPERTY()
	TArray<FString> RecordNameList;
};
