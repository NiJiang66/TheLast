// Fill out your copyright notice in the Description page of Project Settings.


#include "TL_MainController.h"

ATL_MainController::ATL_MainController()
{
	//允许每帧运行
	PrimaryActorTick.bCanEverTick = true;
}

void ATL_MainController::BeginPlay()
{
	Super::BeginPlay();

	//设置鼠标不显示
	bShowMouseCursor = false;
	//设置输入模式
	FInputModeGameOnly InputMode;
	InputMode.SetConsumeCaptureMouseDown(true);
	SetInputMode(InputMode);
}
