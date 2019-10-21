// Fill out your copyright notice in the Description page of Project Settings.


#include "TL_LoginGameMode.h"
#include "TL_LoginWidget.h"
#include "TL_LoginController.h"

ATL_LoginGameMode::ATL_LoginGameMode()
{
	PlayerControllerClass = ATL_LoginController::StaticClass();
	HUDClass = UTL_LoginWidget::StaticClass();
}
