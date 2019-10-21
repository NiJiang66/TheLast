// Fill out your copyright notice in the Description page of Project Settings.


#include "TL_LoginController.h"

ATL_LoginController::ATL_LoginController()
{
	bShowMouseCursor = true;
}

void ATL_LoginController::BeginPlay()
{
	FInputModeUIOnly InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
	SetInputMode(InputMode);
}
