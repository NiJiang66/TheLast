#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TL_Types.h"
#include "TL_PropertyComponent.generated.h"

UENUM(BlueprintType)
enum class E_PropertySetStatus : uint8
{
	E_SUCCESS UMETA(DisplayName = "Success"),
	E_OVERFLOW UMETA(DisplayName = "Overflow"),
	E_BOTTOM UMETA(DisplayName = "Bottom")
};


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable, BlueprintType)
class THELAST_API UTL_PropertyComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTL_PropertyComponent();

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, Category = "Property")
	TMap<ETL_PropertyEnum, FTL_PropertyStruct> PropertiesMaps;

public:
	//Get the value map to the enum
	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetMappedProperty(ETL_PropertyEnum MapEnum) { return PropertiesMaps.Find(MapEnum) ? PropertiesMaps.Find(MapEnum)->Current : 0.f; }
	//Get the whole struct
	UFUNCTION(BlueprintPure)
	FORCEINLINE bool GetMappedPropertyStruct(ETL_PropertyEnum MapEnum, FTL_PropertyStruct& PropertyStruct) 
	{ 
		if (!PropertiesMaps.Find(MapEnum)) return false;
		PropertyStruct = PropertiesMaps[MapEnum]; 
		return true; 
	}
	
	UFUNCTION(BlueprintCallable)
	void SetMappedProperty(ETL_PropertyEnum MapEnum, float NewValue, E_PropertySetStatus& Status, bool bUpdateInUI = true);
	UFUNCTION(BlueprintCallable)
	bool ModifyMappedPropertyBy(ETL_PropertyEnum MapEnum, float By, E_PropertySetStatus& Status, bool bUpdateInUI = true, bool bCheck = true);
	UFUNCTION(BlueprintPure)
	bool CheckProperty(ETL_PropertyEnum MapEnum, float By);

//UI
	UFUNCTION()
	virtual void UpdatePropertyUI(ETL_PropertyEnum MapEnum);
	UFUNCTION(BlueprintImplementableEvent)
	void BP_UpdatePropertyUI(ETL_PropertyEnum MapEnum);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

		
};
