#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TL_Types.h"
#include "TL_CharacterInterface.h"
#include "Components/SceneComponent.h"
#include "TL_Weapon.generated.h"



UCLASS()
class THELAST_API ATL_Weapon : public AActor, public ITL_WeaponInterface
{
	GENERATED_BODY()
public:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintPure)
	FORCEINLINE	TEnumAsByte<EWeaponTypes> GetWeaponType() { return this->WeaponType; }
public:	
	// Sets default values for this actor's properties
	ATL_Weapon();

protected:
	TMap<int32, float> MaxCDMap;
	UPROPERTY()
	EWeaponTypes WeaponType = EWeaponTypes::E_NULLTYPE;
};

//Melee Weapons
UCLASS()
class THELAST_API ATL_MeleeWeapon : public ATL_Weapon
{
	GENERATED_BODY()

public:
	ATL_MeleeWeapon() {
		this->WeaponType = EWeaponTypes::E_MELEE;
	}

	UPROPERTY(BlueprintReadWrite)
		float TraceTickTime = .015f;
	UPROPERTY(BlueprintReadWrite)
		TArray<AActor*> Hitted;

public:
	UFUNCTION(BlueprintCallable)
		void TickTrace(FCombatSenseStruct CombatSense, TSubclassOf<UDamageType> DamageType, TArray<TEnumAsByte<EObjectTypeQuery>> ObjType, TArray<AActor*> ActorsToIgnore, int32 LineNum, USceneComponent* WeaponComponent, TArray<FVector> PrevLocs, TArray<FVector> &Prev, FName TraceStartSocket = FName("AttackTraceSocket0"), FName TraceEndSocket = FName("AttackTraceSocket1"), bool bDrawDebug = false);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void TL_ExitEquip();
	virtual void TL_ExitEquip_Implementation();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void TL_EnterEquip();
	virtual void TL_EnterEquip_Implementation();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void TL_RegisterAttack(FCombatSenseStruct CombatSense, bool bCustomizeSocket, FName TraceStartSocket0, FName TraceStartSocket1);
	virtual void TL_RegisterAttack_Implementation(FCombatSenseStruct CombatSense, bool bCustomizeSocket, FName TraceStartSocket0, FName TraceStartSocket);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void TL_UnregisterAttack();
	virtual void TL_UnregisterAttack_Implementation();
};

//Bow Weapons
UCLASS()
class THELAST_API ATL_BowWeapon : public ATL_Weapon
{
	GENERATED_BODY()

public:
	ATL_BowWeapon() {
		WeaponType = EWeaponTypes::E_BOW;
	}

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void TL_ExitEquip();
	virtual void TL_ExitEquip_Implementation();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void TL_EnterEquip();
	virtual void TL_EnterEquip_Implementation();

};

//Spec Weapons
UCLASS()
class THELAST_API ATL_SpecialWeapon : public ATL_Weapon
{
	GENERATED_BODY()

public:
	ATL_SpecialWeapon() {
		WeaponType = EWeaponTypes::E_SPECITEM;
	}

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void TL_ExitEquip();
	virtual void TL_ExitEquip_Implementation();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void TL_EnterEquip();
	virtual void TL_EnterEquip_Implementation();

};