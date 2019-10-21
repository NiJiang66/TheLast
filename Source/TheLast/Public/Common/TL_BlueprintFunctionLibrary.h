#pragma once
#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TL_BlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class THELAST_API UTL_BPFLib_Transform : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "BPF_Lib_Transform")
	static bool BPF_World2Screen(UObject* Context, FVector InWorldPos, FVector2D& OutScreenPos);
	UFUNCTION(BlueprintCallable, Category = "BPF_Lib_Transform")
	static bool BPF_Screen2World(UObject* Context, FVector2D InScreenPos, FVector& OutWorldPos, FVector& OutWorldDir);
	UFUNCTION(BlueprintPure, Category = "BPF_Lib_Transform")
	static bool BPF_ActorInViewPort(AActor* InActor);
	UFUNCTION(BlueprintPure, Category = "BPF_Lib_Transform", meta = (ToolTip = "输入的顶点必须顺次"))
	static bool BPF_IsPointInRect(FVector2D p, FVector2D p1, FVector2D p2, FVector2D p3, FVector2D p4);
private:
	UFUNCTION()
	static float GetCross(FVector2D& p1, FVector2D& p2, FVector2D& p) {
		return (p2.X - p1.X) * (p.Y - p1.Y) - (p.X - p1.X) * (p2.Y - p1.Y);
	};
};
