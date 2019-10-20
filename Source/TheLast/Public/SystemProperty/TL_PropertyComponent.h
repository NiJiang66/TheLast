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
	TMap<EACT_PropertyEnum, FACT_PropertyStruct> PropertiesMaps;

public:
	//Get the value map to the enum
	UFUNCTION(BlueprintPure)
	FORCEINLINE float GetMappedProperty(EACT_PropertyEnum MapEnum) { return PropertiesMaps.Find(MapEnum) ? PropertiesMaps.Find(MapEnum)->Current : 0.f; }
	//Get the whole struct
	UFUNCTION(BlueprintPure)
	FORCEINLINE bool GetMappedPropertyStruct(EACT_PropertyEnum MapEnum, FACT_PropertyStruct& PropertyStruct) 
	{ 
		if (!PropertiesMaps.Find(MapEnum)) return false;
		PropertyStruct = PropertiesMaps[MapEnum]; 
		return true; 
	}
	
	UFUNCTION(BlueprintCallable)
	void SetMappedProperty(EACT_PropertyEnum MapEnum, float NewValue, E_PropertySetStatus& Status, bool bUpdateInUI = true);
	UFUNCTION(BlueprintCallable)
	bool ModifyMappedPropertyBy(EACT_PropertyEnum MapEnum, float By, E_PropertySetStatus& Status, bool bUpdateInUI = true, bool bCheck = true);
	UFUNCTION(BlueprintPure)
	bool CheckProperty(EACT_PropertyEnum MapEnum, float By);

//UI
	UFUNCTION()
	virtual void UpdatePropertyUI(EACT_PropertyEnum MapEnum);
	UFUNCTION(BlueprintImplementableEvent)
	void BP_UpdatePropertyUI(EACT_PropertyEnum MapEnum);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

		
};
