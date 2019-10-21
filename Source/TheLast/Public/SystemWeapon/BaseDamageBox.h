#pragma once
#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "BaseDamageBox.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class THELAST_API ABaseDamageBox : public AActor
{
	GENERATED_BODY()

public:

	ABaseDamageBox();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	UBoxComponent* DamgeCheckBox;

	FTimerHandle DestoryHandle;

	UFUNCTION(BlueprintCallable)
	virtual TArray<AActor*> BoxCheck(FVector CausorLocation, FVector FwdLocationOffset, FVector BoundsScale, TSubclassOf<AActor> ClassToCheck);
	UFUNCTION(BlueprintCallable)
	void DelayedDestory();

private:
	void DestoryThis();
};

UCLASS(Blueprintable)
class THELAST_API ABaseDamageSphere : public AActor
{
	GENERATED_BODY()

public:

	ABaseDamageSphere();

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
	USphereComponent* DamgeCheckSphere;

	FTimerHandle DestoryHandle;

	UFUNCTION(BlueprintCallable)
	virtual TArray<AActor*> SphereCheck(FVector CausorLocation, FVector FwdLocationOffset, FVector BoundsScale, TSubclassOf<AActor> ClassToCheck);
	UFUNCTION(BlueprintCallable)
	void DelayedDestory();

private:
	void DestoryThis();
};
