// Fill out your copyright notice in the Description page of Project Settings.


#include "TL_ArchiveDataHandle.h"
#include "TL_ArchiveJsonHandle.h"
#include "TL_Singleton.h"
#include "Engine/Engine.h"


TSharedPtr<FTL_ArchiveDataHandle> FTL_ArchiveDataHandle::DataInstance = NULL;


TSharedPtr<FTL_ArchiveDataHandle> FTL_ArchiveDataHandle::Get()
{
	Initialize();
	return DataInstance;
}

void FTL_ArchiveDataHandle::InitializeGameData()
{

}

void FTL_ArchiveDataHandle::ChangeLocalizationCulture(ECultureTeam Culture)
{
	//切换语言
	switch (Culture)
	{
	case ECultureTeam::EN:
		FInternationalization::Get().SetCurrentCulture(TEXT("en"));
		break;
	case ECultureTeam::ZH:
		FInternationalization::Get().SetCurrentCulture(TEXT("zh"));
		break;
	}
	//修改当前存档语言
	CurrentRecordData.Culture = Culture;
	//更新存档文件数据
	UpdateRecordData();
}

void FTL_ArchiveDataHandle::SetMenuVolume(float MusicVol, float SoundVol)
{

}

void FTL_ArchiveDataHandle::SetGameVolume(float MusicVol, float SoundVol)
{

}

void FTL_ArchiveDataHandle::AddNewRecord()
{
	//添加新的存档名
	CurrentRecordData.RecordNameList.Emplace(CurrentRecordName);
	//更新存档文件数据
	UpdateRecordData();
}

void FTL_ArchiveDataHandle::UpdateRecordData()
{
	FTL_Singleton<FTL_ArchiveJsonHandle>::Get()->SaveArchiveFile<FTL_ArchiveData>(RECORDDATAFILENAME, CurrentRecordData);
}

void FTL_ArchiveDataHandle::InitRecordData()
{
	//初始化当前存档名
	CurrentRecordName = "";

	//加载本地存档文件，并缓存数据到CurrentRecordData
	FTL_Singleton<FTL_ArchiveJsonHandle>::Get()->LoadArchiveFile<FTL_ArchiveData>(RECORDDATAFILENAME, CurrentRecordData);

	//初始化语言
	ChangeLocalizationCulture(CurrentRecordData.Culture);
}

void FTL_ArchiveDataHandle::InitMenuAudio()
{

}

FTL_ArchiveDataHandle::FTL_ArchiveDataHandle()
{
	//初始化存档数据
	InitRecordData();
	//初始化菜单音乐
	InitMenuAudio();
}

void FTL_ArchiveDataHandle::Initialize()
{
	if (!DataInstance.IsValid())
	{
		DataInstance = Create();
	}
}

TSharedRef<FTL_ArchiveDataHandle> FTL_ArchiveDataHandle::Create()
{
	TSharedRef<FTL_ArchiveDataHandle> DataRef = MakeShareable(new FTL_ArchiveDataHandle());
	return DataRef;
}

