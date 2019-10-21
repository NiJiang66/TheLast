// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TL_LoginController.generated.h"

/**
 * 开始关卡的角色控制类
 */
UCLASS()
class THELAST_API ATL_LoginController : public APlayerController
{
	GENERATED_BODY()

public:
	ATL_LoginController();

protected:

	virtual void BeginPlay() override;
};
