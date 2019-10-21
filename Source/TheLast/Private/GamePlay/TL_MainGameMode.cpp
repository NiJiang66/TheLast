// Fill out your copyright notice in the Description page of Project Settings.


#include "TL_MainGameMode.h"
#include "TL_ArchiveDataHandle.h"
#include "TestSaveGame.h"

#include "TL_MainWidget.h"
#include "TL_MainController.h"

#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

ATL_MainGameMode::ATL_MainGameMode()
{	
	//允许开启tick函数
	PrimaryActorTick.bCanEverTick = true;

	PlayerControllerClass = ATL_MainController::StaticClass();
	HUDClass = UTL_MainWidget::StaticClass();

	//开始设置不能够加载存档
	bEnableLoadRecord = true;
}

void ATL_MainGameMode::SaveGame()
{
	//如果存档名是Default,不进行保存
	if (FTL_ArchiveDataHandle::Get()->CurrentRecordName.Equals(FString("Default"))) return;

	//创建一个新存档
	UTestSaveGame* NewRecord = Cast<UTestSaveGame>(UGameplayStatics::CreateSaveGameObject(UTestSaveGame::StaticClass()));
	NewRecord->TestString = "woyeshizuile";

	//保存存档
	UGameplayStatics::SaveGameToSlot(NewRecord, FTL_ArchiveDataHandle::Get()->CurrentRecordName, 0);

	//查看json是否已经有这个存档
	bool IsRecordExist = false;
	for (TArray<FString>::TIterator It(FTL_ArchiveDataHandle::Get()->CurrentRecordData.RecordNameList); It; ++It)
	{
		//只要有一个相同,就跳出
		if ((*It).Equals(FTL_ArchiveDataHandle::Get()->CurrentRecordName)) {
			IsRecordExist = true;
			break;
		}
	}
	//如果存档不存在,让数据管理类添加存档到json
	if (!IsRecordExist) FTL_ArchiveDataHandle::Get()->AddNewRecord();
}

void ATL_MainGameMode::BeginPlay()
{
	//初始化游戏数据
	FTL_ArchiveDataHandle::Get()->InitializeGameData();

	//播放音乐


	//加载存档
	LoadRecord();
}

void ATL_MainGameMode::LoadRecord()
{
	if (FTL_ArchiveDataHandle::Get()->CurrentRecordName.IsEmpty() || FTL_ArchiveDataHandle::Get()->CurrentRecordName.Equals(FString("Default")))
	{
		return;
	}

	//遍历存档是否存在
	for (TArray<FString>::TIterator It(FTL_ArchiveDataHandle::Get()->CurrentRecordData.RecordNameList); It; ++It)
	{
		//存在一个相同的就设置可以加载存档，并跳出
		if ((*It).Equals(FTL_ArchiveDataHandle::Get()->CurrentRecordName))
		{
			bEnableLoadRecord = true;
			break;
		}
	}

	//如果可以加载，并且存档存在，进行加载
	if (bEnableLoadRecord && UGameplayStatics::DoesSaveGameExist(FTL_ArchiveDataHandle::Get()->CurrentRecordName, 0))
	{
		GameRecord = Cast<UTestSaveGame>(UGameplayStatics::LoadGameFromSlot(FTL_ArchiveDataHandle::Get()->CurrentRecordName, 0));
	}
	else
	{
		bEnableLoadRecord = false;
	}

	//如果可以加载，并且存档加载成功，进行游戏内容设置
	if (bEnableLoadRecord && GameRecord)
	{
		//设置玩家位置和血量

		//循环设置敌人

		//循环设置资源

		//测试用
		FString testt = GameRecord->TestString;
		GEngine->AddOnScreenDebugMessage(-1, 30, FColor::Black, testt);

	}
}
