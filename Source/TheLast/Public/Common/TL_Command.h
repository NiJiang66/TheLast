#pragma once
#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "TL_Command.generated.h"


/**
 *	主要用于测试的GM命令
 */
UCLASS()
class THELAST_API UTL_Command : public UCheatManager
{
	GENERATED_BODY()
public:
	UFUNCTION(exec)	void TestPrintCommand();


};