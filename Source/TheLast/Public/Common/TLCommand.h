#pragma once
#include "CoreMinimal.h"
#include "GameFramework/CheatManager.h"
#include "TLCommand.generated.h"


/**
 *	主要用于测试的GM命令
 */
UCLASS()
class THELAST_API UTLCommand : public UCheatManager
{
	GENERATED_BODY()
public:
	UFUNCTION(exec)	void TestPrintCommand();


};