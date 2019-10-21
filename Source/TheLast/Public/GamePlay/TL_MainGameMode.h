// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TL_MainGameMode.generated.h"

/**
 * 主关卡的游戏模式类
 */
UCLASS()
class THELAST_API ATL_MainGameMode : public AGameModeBase
{
	GENERATED_BODY()
public:
	ATL_MainGameMode();

	/** 保存游戏 */
	//UFUNCTION(BlueprintCallable)
	void SaveGame();

protected:

	virtual void BeginPlay() override;

	/** 加载存档 */
	void LoadRecord();

private:

	/** 是否能够加载存档 */
	bool bEnableLoadRecord;

	/** 游戏存档指针 */
	class UTestSaveGame* GameRecord;
};
