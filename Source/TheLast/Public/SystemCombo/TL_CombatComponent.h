#pragma once
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TL_Character.h"
#include "TL_ComboTreeDataAsset.h"
#include "TL_MotionListDataAsset.h"
#include "TL_ComboMotionDataAsset.h"
#include "TL_ItemDataAsset.h"
#include "Animation/AnimBlueprint.h"
#include "TL_CombatComponent.generated.h"

/**	 */
USTRUCT(BlueprintType)
struct FCharacterStateStruct
{
	GENERATED_USTRUCT_BODY()
public:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		UTL_ComboTreeDataAsset* Combo;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly)
		UTL_WeaponMotionListDataAsset* MotionList;
};	

/**
 * 战斗组件
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class THELAST_API UTL_CombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTL_CombatComponent();

	UPROPERTY(BlueprintReadWrite)
	ATL_Character* PlayerCharacter;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	TArray<UTL_WeaponDataAsset*> WeaponItems;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	ATL_Weapon* WeaponOnHand;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapon")
	TMap<EWeaponTypes, ATL_Weapon*> CurrentWeapon;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TArray<TEnumAsByte<EObjectTypeQuery>> EnemyObjectTypes;
	UPROPERTY(BlueprintReadWrite)
	bool bAiming = false;
	UPROPERTY(BlueprintReadWrite)
	bool bAttackable = true;
	UPROPERTY(BlueprintReadWrite)
	EStateTypes CurrentStateType = EStateTypes::E_IDLE;
	UPROPERTY(BlueprintReadWrite)
	bool bInvincible = false;

	UPROPERTY(BlueprintReadWrite)
	TMap<AActor*,float> HittedEne;
	 
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	FCharacterStateStruct MainState;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	TMap<TSubclassOf<ATL_Weapon>, FCharacterStateStruct> CharacterStates;

	UPROPERTY(BlueprintReadWrite, VisibleInstanceOnly)
	UTL_WeaponMotionListDataAsset* CurrentMotionList;
	UPROPERTY(BlueprintReadWrite, VisibleInstanceOnly)
	UTL_ComboTreeDataAsset* CurrentCombo;
	UPROPERTY(BlueprintReadWrite, VisibleInstanceOnly)
	UTL_ComboMotionDataAsset* CurrentComboState;
	UPROPERTY(BlueprintReadWrite, VisibleInstanceOnly)
	UTL_ComboMotionDataAsset* NextComboState;

	//Delegates
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAttackExitDelegate);
	UPROPERTY(BlueprintAssignable)
	FAttackExitDelegate DelegateAttackExit;
	UFUNCTION(BlueprintCallable)
	void BroadCastAttackExitDelegate() { DelegateAttackExit.Broadcast(); }
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAttackEnterDelegate);
	UPROPERTY(BlueprintAssignable)
	FAttackEnterDelegate DelegateAttackEnter;
	UFUNCTION(BlueprintCallable)
	void BroadCastAttackDelegate() { DelegateAttackEnter.Broadcast(); }
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAimEnterDelegate);
	UPROPERTY(BlueprintAssignable)
	FAttackEnterDelegate DelegateAimEnter;
	UFUNCTION(BlueprintCallable)
	void BroadCastAimDelegate() { DelegateAimEnter.Broadcast(); }
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAimExitDelegate);
	UPROPERTY(BlueprintAssignable)
	FAimExitDelegate DelegateAimExit;
	UFUNCTION(BlueprintCallable)
	void BroadCastAimExitDelegate() { DelegateAimExit.Broadcast(); }
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FDefaultHittedReactionDelegate);
	UPROPERTY(BlueprintAssignable)
	FDefaultHittedReactionDelegate DefaultHittedReaction;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	FTimerHandle ForceTimerHandle;
	void ResetGroundFiction();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION(BlueprintPure)
	bool CanEnterMotion();
	UFUNCTION(BlueprintPure)
	bool CanEnterAttack();


	//Loc and Dir
	UFUNCTION(BlueprintPure)
	FVector GetControlFwd();
	UFUNCTION(BlueprintPure)
	FVector GetControlRight();
	UFUNCTION(BlueprintCallable)
	AActor* CheckTurn(TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes, bool TraceComplex, TArray<AActor*> ActorsToIgnore, bool& bSuccess, float Length = 200.f, int LineNum = 5, float OffsetDegree = 60, bool SphereCheck = true, bool DebugDraw = false, float Rot = 60, int RadNum = 4);


	//Anim
	UFUNCTION(BlueprintImplementableEvent)
	void CharacterPlayMontage(UAnimMontage* MontageToPlay, float PlayRate, FName StartSection, float StartingPos);
	UFUNCTION(BlueprintCallable)
	void MotionForceBlendOut();
	UFUNCTION(BlueprintCallable)
	void PlayMontageWithMotionType(UTL_MotionDataAsset* Motion);
	UFUNCTION(BlueprintCallable)
	void ExChangeComboState();
	UFUNCTION(BlueprintCallable)
	virtual void OnComboStateExChange();
	UFUNCTION(BlueprintCallable)
	bool SimpleMotionEnter(UTL_MotionDataAsset* MotionToEnter);
	UFUNCTION(BlueprintCallable)
	bool SimpleMotionMontageEnter(UAnimMontage* MotionToEnter, float Rate, FName MontageSection, float EnterPos);
	UFUNCTION(BlueprintCallable)
	bool MotionEnter();
	UFUNCTION(BlueprintCallable)
	bool AttackEnter();
	UFUNCTION(BlueprintCallable)
	void MotionEnd();
	UFUNCTION(BlueprintCallable)
	void OnHit(USceneComponent* DamageCausor, FHitReacStruct HitReact, TSubclassOf<UDamageType> DamageType);
	UFUNCTION(BlueprintCallable)
	void PreExchangeComboState(bool ToBranch);	
	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
	void DealMontageAndNotify(USkeletalMeshComponent* InSkeletalMesh, UAnimMontage* MontageToPlay, float PlayRate = 1.f, float StartingPositon = 0.f, FName StartingSection = FName("None"));
	UFUNCTION(BlueprintCallable)
	void ResetNextComboState();


	//Check
	UFUNCTION(BlueprintCallable)
		void TickTrace(FCombatSenseStruct CombatSense, TArray<TEnumAsByte<EObjectTypeQuery>> ObjType, TArray<AActor*> ActorsToIgnore, int32 LineNum, USceneComponent* WeaponComponent, TArray<FVector> PrevLocs, TArray<FVector> &Prev, FName TraceStartSocket = FName("AttackTraceSocket0"), FName TraceEndSocket = FName("AttackTraceSocket1"), bool bDrawDebug = false, float ProtectionTime = 0.2f);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		TArray<AActor*> TL_SphereCheck(float FwdLocationOffset, FVector NewScale /* = FVector(1, 1, 1) */, bool bFalseFaceAttacker = false);
	virtual TArray<AActor*> TL_SphereCheck_Implementation(float FwdLocationOffset, FVector NewScale /* = FVector(1, 1, 1) */, bool bFalseFaceAttacker = false);
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		TArray<AActor*> TL_BoxCheck(float FwdLocationOffset, FVector NewScale /* = FVector(1, 1, 1) */, bool bFalseFaceAttacker = false);
	virtual TArray<AActor*> TL_BoxCheck_Implementation(float FwdLocationOffset, FVector NewScale /* = FVector(1, 1, 1) */, bool bFalseFaceAttacker = false);
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void TL_HitTarget(FCombatSenseStruct CombatSense, AActor* Hitted, bool bCustomizeLoc = false, FVector Loc = FVector(0, 0, 0));
	virtual void TL_HitTarget_Implementation(FCombatSenseStruct CombatSense, AActor* Hitted, bool bCustomizeLoc = false, FVector Loc = FVector(0, 0, 0));


	//Weapon
	UFUNCTION(BlueprintCallable)
		bool SetCurrentWeaponOfType(TEnumAsByte<EWeaponTypes> TypeInput, ATL_Weapon* WeaponToSet);
	UFUNCTION(BlueprintPure)
		ATL_Weapon* GetCurrentWeaponOfType(TEnumAsByte<EWeaponTypes> TypeInput);
	UFUNCTION(BlueprintCallable)
		void ChangeStateAndWeaponOnHand(ATL_Weapon* Weapon);
	UFUNCTION(BlueprintCallable)
		void ChangeStateToSpecificWeaponType(TEnumAsByte<EWeaponTypes> WeaponType);
	UFUNCTION(BlueprintPure)
		FCharacterStateStruct FindCharacterStateForWeapon(ATL_Weapon* Weapon);

	//Phys
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void TL_AddMovementImpulse(FForceStruct ForceStruct, bool VelChange  /*= true*/);
	virtual void TL_AddMovementImpulse_Implementation(FForceStruct ForceStruct, bool VelChange /*= true*/);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void TL_HitForce(FHitForceStruct HitForce, USceneComponent* DamageCausor);
	virtual void TL_HitForce_Implementation(FHitForceStruct HitForce, USceneComponent* DamageCausor);







	/*
	UFUNCTION(BlueprintCallable)
	void Change(TSubclassOf<ATLWeapon> ChangeTo);*/
};
