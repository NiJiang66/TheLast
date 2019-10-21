// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TL_MainController.generated.h"

/**
 * 主关卡的角色控制类
 */
UCLASS()
class THELAST_API ATL_MainController : public APlayerController
{
	GENERATED_BODY()

public:
	ATL_MainController();

protected:

	virtual void BeginPlay() override;

};
