#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TL_Types.h"
#include "TL_WidgetInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UTL_WidgetInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class THELAST_API ITL_WidgetInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void TL_InitializeUI();
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void TL_InitializePropertyUI(ETL_PropertyEnum EProperty);
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
		void TL_UpdatePropertyUI(ETL_PropertyEnum EProperty, float Value);
};
