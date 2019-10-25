#include "TL_CombatComponent.h"
#include "TL_SkillDataAsset.h"
#include "Engine.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TL_DamageTypes.h"
#include "Kismet/KismetMathLibrary.h"

#define bMotioning (CurrentStateType == EStateTypes::E_MOTION)

// Sets default values for this component's properties
UTL_CombatComponent::UTL_CombatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UTL_CombatComponent::BeginPlay()
{
	//Try Get player character
	if (GetOwner()) {
		PlayerCharacter = Cast<ATL_Character>(GetOwner());
		ChangeStateAndWeaponOnHand(nullptr);
	}
	Super::BeginPlay();
}


// Called every frame
void UTL_CombatComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


//Loc And Dir
FVector UTL_CombatComponent::GetControlFwd()
{
	if (AController* M_Controller = PlayerCharacter->GetController()) {
		FVector Ori = UKismetMathLibrary::GetForwardVector(M_Controller->GetControlRotation());
		Ori.Z = 0;
		Ori.Normalize();
		return Ori;
	}
	return FVector(1, 0, 0);
}

FVector UTL_CombatComponent::GetControlRight()
{
	if (AController* M_Controller = PlayerCharacter->GetController()) {
		FVector Ori = UKismetMathLibrary::GetRightVector(M_Controller->GetControlRotation());
		Ori.Z = 0;
		Ori.Normalize();
		return Ori;
	}
	return FVector(0, 1, 0);
}

AActor* UTL_CombatComponent::CheckTurn(TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes, bool TraceComplex, TArray<AActor*> ActorsToIgnore, bool& bSuccess, float Length /*= 200.f*/, int LineNum /*= 5*/, float OffsetDegree /*= 60*/, bool SphereCheck /*= true*/, bool DebugDraw /*= false*/, float Rot, int RadNum)
{
	if (UWorld* World = GetWorld()) {
		FHitResult HitRes;
		FVector UpVector = GetOwner()->GetActorUpVector();
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Purple, TEXT("CheckTurn"));
		if (LineNum % 2 == 0) LineNum += 1;
		if (SphereCheck) {
			for (int i = 0; i < RadNum * LineNum; i++) {
				//Line Trace
				if (UKismetSystemLibrary::LineTraceSingleForObjects(World,
					GetOwner()->GetActorLocation(),
					(GetControlFwd().RotateAngleAxis(((360.f / (RadNum * LineNum - 1)) * ((i + 1) / 2) * FMath::Pow(-1, i + 1) + Rot), UpVector)) * Length + GetOwner()->GetActorLocation(),
					ObjectTypes, TraceComplex, ActorsToIgnore, DebugDraw ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None, HitRes, true))
				{
					bSuccess = PlayerCharacter? PlayerCharacter->TurnToTargetAtOnceWithHitResult(HitRes) : false;
					return PlayerCharacter;
				}
			}
		}
		else {
			for (int i = 0; i < LineNum; i++) {
				//Line Trace
				if (UKismetSystemLibrary::LineTraceSingleForObjects(World,
					GetOwner()->GetActorLocation(),
					(GetControlFwd().RotateAngleAxis(((OffsetDegree / (LineNum - 1)) * ((i + 1) / 2) * FMath::Pow(-1, i + 1) + Rot), UpVector)) * Length + GetOwner()->GetActorLocation(),
					ObjectTypes, TraceComplex, ActorsToIgnore, DebugDraw ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None, HitRes, true))
				{
					bSuccess = PlayerCharacter ? PlayerCharacter->TurnToTargetAtOnceWithHitResult(HitRes) : false;
					return PlayerCharacter;
				}
			}
		}
		return false;
	}
	return false;
}

//Motion
void UTL_CombatComponent::ExChangeComboState()
{
	CurrentComboState = NextComboState ? NextComboState : CurrentCombo->StartState;
	NextComboState = nullptr;
	OnComboStateExChange();
}

void UTL_CombatComponent::OnComboStateExChange()
{
	
}


bool UTL_CombatComponent::CanEnterMotion()
{
	return (!bMotioning);
}

bool UTL_CombatComponent::CanEnterAttack()
{
	return (!bMotioning && bAttackable); 
}

bool UTL_CombatComponent::SimpleMotionEnter(UTL_MotionDataAsset* MotionToEnter)
{
	if (!bMotioning && MotionToEnter) {
		CurrentStateType = EStateTypes::E_MOTION;
		PlayerCharacter->Moveable = false;
		ResetNextComboState();
		if (MotionToEnter) {
			CharacterPlayMontage(MotionToEnter->MotionMontage, MotionToEnter->MontagePlayRate, MotionToEnter->MontageStartingSection, MotionToEnter->MontageStartingPosition);
			return true;
		}
		else return false;
	}
	return false;
}
bool UTL_CombatComponent::SimpleMotionMontageEnter(UAnimMontage* MotionToEnter, float Rate, FName MontageSection, float EnterPos)
{
	if (!bMotioning && MotionToEnter) {
		CurrentStateType = EStateTypes::E_MOTION;
		PlayerCharacter->Moveable = false;
		ResetNextComboState();
		if (MotionToEnter) {
			CharacterPlayMontage(MotionToEnter, Rate, MontageSection, EnterPos);
			return true;
		}
		else return false;
	}
	return false;
}
bool UTL_CombatComponent::MotionEnter()
{
	if (!bMotioning && NextComboState) {
		CurrentStateType = EStateTypes::E_MOTION;
		PlayerCharacter->Moveable = false;
		ExChangeComboState();
		CharacterPlayMontage(CurrentComboState->MotionMontage, CurrentComboState->MontagePlayRate, CurrentComboState->MontageStartingSection, CurrentComboState->MontageStartingPosition);
		return true;
	}
	else return false;
}

bool UTL_CombatComponent::AttackEnter()
{
	if (!CurrentComboState && CurrentCombo) {
		CurrentComboState = CurrentCombo->StartState;
		NextComboState = CurrentCombo->StartState;
	} 
	if ((CurrentStateType != EStateTypes::E_MOTION) && NextComboState && bAttackable && CurrentComboState) {
		CurrentStateType = EStateTypes::E_MOTION;
		bAttackable = false;
		PlayerCharacter->Moveable = false;
		ExChangeComboState();
		CharacterPlayMontage(CurrentComboState->MotionMontage, CurrentComboState->MontagePlayRate, CurrentComboState->MontageStartingSection, CurrentComboState->MontageStartingPosition);
		return true;
	}
	else return false;
}

void UTL_CombatComponent::MotionEnd()
{
	PlayerCharacter->Moveable = true;
	CurrentStateType = EStateTypes::E_IDLE;
	bAttackable = true;
	//CurrentComboState = nullptr;
	ResetNextComboState();
}

void UTL_CombatComponent::OnHit(USceneComponent* DamageCausor, FHitReacStruct HitReact, TSubclassOf<UDamageType> DamageType)
{
	PlayerCharacter->Moveable = false;
	CurrentStateType = EStateTypes::E_MOTION;
	bAttackable = false;
	float FOB, LOR;
	PlayerCharacter->GetTargetRelativePostion(DamageCausor->GetComponentLocation(), FOB, LOR);
	if (!CurrentMotionList) {
		GEngine->AddOnScreenDebugMessage(-1, 12.f, FColor::Red, TEXT("ERROR: NO HIT MOTION LIST"));
		return;
	}
	if (DamageType.Get()) {
		if (DamageType.Get() == UTL_DamageType_ShockDown::StaticClass()) {
			PlayMontageWithMotionType((UTL_MotionDataAsset*)CurrentMotionList->HitDown);
		}
		else DefaultHittedReaction.Broadcast();
	}
	else {
	if (FOB >= 0 && HitReact.bTurnToDmgCauser) {
		PlayerCharacter->TurnToTargetAtOnce(DamageCausor);
	}
	if (FOB >= 0.f) {
		if (LOR > 0.5f) {
			if (CurrentMotionList->FwdRight)
				PlayMontageWithMotionType((UTL_MotionDataAsset*)CurrentMotionList->FwdRight);
			else DefaultHittedReaction.Broadcast();
			return;
		}
		if (LOR < -0.5f) {
			if (CurrentMotionList->FwdLeft)
				PlayMontageWithMotionType((UTL_MotionDataAsset*)CurrentMotionList->FwdLeft);
			else DefaultHittedReaction.Broadcast();
			return;
		}
		else {
			if (CurrentMotionList->Fwd)
				PlayMontageWithMotionType((UTL_MotionDataAsset*)CurrentMotionList->Fwd);
			else DefaultHittedReaction.Broadcast();
			return;
		}
	}
	else if (FOB < 0.f) {
		if (LOR > 0.5f) {
			if (CurrentMotionList->BwdRight)
				PlayMontageWithMotionType((UTL_MotionDataAsset*)CurrentMotionList->BwdRight);
			else DefaultHittedReaction.Broadcast();
			return;
		}
		if (LOR < -0.5f) {
			if (CurrentMotionList->BwdLeft)
				PlayMontageWithMotionType((UTL_MotionDataAsset*)CurrentMotionList->BwdLeft);
			else DefaultHittedReaction.Broadcast();
			return;
		}
		else {
			if (CurrentMotionList->Bwd)
				PlayMontageWithMotionType((UTL_MotionDataAsset*)(CurrentMotionList->Bwd));
			else DefaultHittedReaction.Broadcast();
			return;
		}
	}
}
	
}

void UTL_CombatComponent::MotionForceBlendOut()
{
	if (PlayerCharacter) PlayerCharacter->StopAnimMontage();
	MotionEnd();
}

void UTL_CombatComponent::PlayMontageWithMotionType(UTL_MotionDataAsset* Motion)
{
	if (Motion && Motion->MotionMontage) {
		UAnimMontage* MontageToPlay;
		float MontagePlayRate;
		FName MontageStartSection;
		MontageToPlay = Motion->MotionMontage;
		MontagePlayRate = Motion->MontagePlayRate;
		MontageStartSection = Motion->MontageStartingSection;
		CharacterPlayMontage(MontageToPlay, MontagePlayRate, MontageStartSection, Motion->MontageStartingPosition);
	}
}


void UTL_CombatComponent::PreExchangeComboState(bool ToBranch)
{
	if (CurrentComboState) {
		if (ToBranch) {
			if (CurrentComboState->BranchCombo) {
				NextComboState = CurrentComboState->BranchCombo;
			}
			else if(CurrentCombo) NextComboState = CurrentCombo->StartState;
			else return;
		}
		else {
			if (CurrentComboState->NextCombo) {
				NextComboState = CurrentComboState->NextCombo;
			}
			else if(CurrentCombo) NextComboState = CurrentCombo->StartState;
			else return;
		}
		CurrentStateType = EStateTypes::E_IDLE;
		bAttackable = true;
	}
}

void UTL_CombatComponent::ResetNextComboState()
{
	NextComboState = CurrentCombo?CurrentCombo->StartState:nullptr;
}

void UTL_CombatComponent::ChangeStateAndWeaponOnHand(ATL_Weapon* Weapon)
{
	if(WeaponOnHand) WeaponOnHand->Execute_TL_ExitEquip(WeaponOnHand);
	WeaponOnHand = Weapon;
	if(WeaponOnHand) WeaponOnHand->Execute_TL_EnterEquip(WeaponOnHand);
	ResetNextComboState();
	FCharacterStateStruct CurrentState;
	CurrentState = WeaponOnHand ? FindCharacterStateForWeapon(WeaponOnHand) : MainState;
	CurrentCombo = CurrentState.Combo;
	CurrentMotionList = CurrentState.MotionList;
	if (CurrentCombo) {
		CurrentComboState = CurrentCombo->StartState;
		NextComboState = CurrentCombo->StartState;
	}
}

void UTL_CombatComponent::ChangeStateToSpecificWeaponType(TEnumAsByte<EWeaponTypes> WeaponType)
{
	if (!CanEnterMotion()) return;
	ResetNextComboState();
	//No Weapon, Equip WeaponType Type Weapon
	if (!WeaponOnHand) {
		if (CurrentWeapon.Find(WeaponType)) {
			//Locate Weapon To Change to
			ATL_Weapon* TargetWeapon = CurrentWeapon[WeaponType];
			if (TargetWeapon) {
				//Find Mapped State and prepare to play the Equip Montage
				FCharacterStateStruct State = FindCharacterStateForWeapon(TargetWeapon);
				if (State.MotionList && State.MotionList->EquipMotion) SimpleMotionEnter(State.MotionList->EquipMotion);
				else ChangeStateAndWeaponOnHand(GetCurrentWeaponOfType(WeaponType));
			}
			else GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, TEXT("ERROR: CAN NOT FIND TARGET WEAPON TO CHANGE"));
		}
		else GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, TEXT("ERROR: CAN NOT FIND STATE OF WEAPON TYPE"));
	}
	else {
		//if same type with Input type
		//Unequip Weapon
		if (WeaponOnHand->GetWeaponType() == WeaponType) {
			FCharacterStateStruct State = FindCharacterStateForWeapon(WeaponOnHand);
			if (State.MotionList && State.MotionList->EquipMotion) SimpleMotionEnter(State.MotionList->UnequipMotion);
			else ChangeStateAndWeaponOnHand(nullptr);
		}
		//else if not equal with Input type, Equip to Target Type
		//And Before it unequip 
		else
		{
			WeaponOnHand->Execute_TL_ExitEquip(WeaponOnHand);
			WeaponOnHand = nullptr;
			if (CurrentWeapon.Find(WeaponType)) {
				//Locate Weapon To Change to
				ATL_Weapon* TargetWeapon = CurrentWeapon[WeaponType];
				if (TargetWeapon) {
					//Find Mapped State and prepare to play the Equip Montage
					FCharacterStateStruct State = FindCharacterStateForWeapon(TargetWeapon);
					if(State.MotionList && State.MotionList->EquipMotion) SimpleMotionEnter(State.MotionList->EquipMotion);
					else ChangeStateAndWeaponOnHand(GetCurrentWeaponOfType(WeaponType));
				}
				else GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, TEXT("ERROR: CAN NOT FIND TARGET WEAPON TO CHANGE"));
			}
			else GEngine->AddOnScreenDebugMessage(-1, 15.f, FColor::Red, TEXT("ERROR: CAN NOT FIND STATE OF WEAPON TYPE"));
		}
	}
}

//State Depended with Weapon
bool UTL_CombatComponent::SetCurrentWeaponOfType(TEnumAsByte<EWeaponTypes> TypeInput, ATL_Weapon* WeaponToSet)
{
	if (!WeaponToSet) {
		CurrentWeapon.Add(TypeInput, nullptr);
		return true;
	}
	else if (WeaponToSet->GetWeaponType() == TypeInput)
	{
		CurrentWeapon.Add(TypeInput, WeaponToSet);
		return true;
	}
	return false;
}

ATL_Weapon* UTL_CombatComponent::GetCurrentWeaponOfType(TEnumAsByte<EWeaponTypes> TypeInput)
{
	EWeaponTypes Type = TypeInput.GetValue();
	return CurrentWeapon[Type];
}

FCharacterStateStruct UTL_CombatComponent::FindCharacterStateForWeapon(ATL_Weapon* Weapon)
{
	if (!Weapon) return MainState;
	for (auto& iter : CharacterStates) {
		if ((Weapon->GetClass()->IsChildOf(iter.Key.Get())) | (Weapon->GetClass() == iter.Key.Get())) {
			return iter.Value;
		}
	}
	return MainState;
}




//Trace 
TArray<AActor*> UTL_CombatComponent::TL_BoxCheck_Implementation(float FwdLocationOffset, FVector NewScale /* = FVector(1, 1, 1) */, bool bFalseFaceAttacker)
{
	TArray<AActor*> BugArray;
	BugArray.Add(PlayerCharacter);
	return BugArray;
}
TArray<AActor*> UTL_CombatComponent::TL_SphereCheck_Implementation(float FwdLocationOffset, FVector NewScale /* = FVector(1, 1, 1) */, bool bFalseFaceAttacker /*= false*/)
{
	TArray<AActor*> BugArray;
	BugArray.Add(PlayerCharacter);
	return BugArray;
}
void UTL_CombatComponent::TL_HitTarget_Implementation(FCombatSenseStruct CombatSense, AActor* Hitted, bool bCustomizeLoc, FVector Loc)
{
	if (UTL_CombatComponent* TargetComp = Cast<UTL_CombatComponent>(Hitted->GetComponentByClass(UTL_CombatComponent::StaticClass()))) {
		if (TargetComp->bInvincible) {
			return;
		} 
	}
	PlayerCharacter->TL_ApplyDamage(PlayerCharacter->GetRootComponent(), Hitted, CombatSense.EmitterTemplate, CombatSense.HitReact, CombatSense.HitReact.DamageType, CombatSense.FXScale, bCustomizeLoc, Loc);
	PlayerCharacter->TL_DunFrame(CombatSense.TimeDilation, CombatSense.Duration, CombatSense.CameraBloomMin, CombatSense.CameraShake, CombatSense.CameraCurve);
}

void UTL_CombatComponent::TickTrace(FCombatSenseStruct CombatSense, TArray<TEnumAsByte<EObjectTypeQuery>> ObjType, TArray<AActor*> ActorsToIgnore, int32 LineNum, USceneComponent* WeaponComponent, TArray<FVector> PrevLocs, TArray<FVector> &Prev, FName TraceStartSocket /*= FName("AttackTraceSocket0")*/, FName TraceEndSocket /*= FName("AttackTraceSocket1")*/, bool bDrawDebug /*= false*/, float ProtectionTime /*= 0.2f*/)
{
	//Clear Hitted Map
	float sec = PlayerCharacter->GetWorld()->GetTimeSeconds();
	for (auto& iter : HittedEne) {
		if (sec - iter.Value >= ProtectionTime) {
			HittedEne.Remove(iter.Key);
		}
	}
	//Trace
	FVector StartSoc = WeaponComponent->GetSocketLocation(TraceStartSocket);
	FVector EndSoc = WeaponComponent->GetSocketLocation(TraceEndSocket);
	TArray<FVector> CurrentLocs;
	for (int i = 0; i <= LineNum; i++) {
		CurrentLocs.Add((((EndSoc - StartSoc) / LineNum) * i + StartSoc));
	}
	if (PrevLocs.Num() > 0) {
		for (int i = 0; i < PrevLocs.Num(); i++) {
			TArray<FHitResult> HitReses;
			if (UKismetSystemLibrary::LineTraceMultiForObjects(Cast<UObject>(this), PrevLocs[i], CurrentLocs[i], ObjType, false, ActorsToIgnore, bDrawDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None, HitReses, true)) {
				for (auto& HitRes : HitReses) {
					if ((HittedEne.Num() == 0 || !HittedEne.Contains(HitRes.GetActor())) && HitRes.GetActor() != GetOwner()) {
						GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("_TRACE_TARGET_"));
						TL_HitTarget(CombatSense, HitRes.GetActor());
						HittedEne.Add(HitRes.GetActor(), PlayerCharacter->GetWorld()->GetTimeSeconds());
					}
				}
			}
		}
	}
	Prev = CurrentLocs;
}

//Phys
void UTL_CombatComponent::ResetGroundFiction()
{
	UWorld* World = PlayerCharacter->GetWorld();
	UCharacterMovementComponent* Movement = PlayerCharacter->GetCharacterMovement();
	if (Movement && World) {
		Movement->GroundFriction = 8.f;
		World->GetTimerManager().ClearTimer(ForceTimerHandle);
	}
}
void UTL_CombatComponent::TL_HitForce_Implementation(FHitForceStruct HitForce, USceneComponent* DamageCausor)
{
	UWorld* World = GetWorld();
	UCharacterMovementComponent* Movement = PlayerCharacter->GetCharacterMovement();
	if (Movement && World) {
		Movement->GroundFriction = 0;
		FVector DistanceXY = DamageCausor->GetComponentLocation() - PlayerCharacter->GetActorLocation();
		DistanceXY.Z = 0;
		FVector Force = DistanceXY;
		Force.Normalize();
		Force.X *= (-1.f) * (HitForce.ForceStruct.ForceStrength);
		Force.Y *= (-1.f) * (HitForce.ForceStruct.ForceStrength);
		Force.Z = HitForce.UpForce + 5.f;
		Movement->AddImpulse(Force, true);
		World->GetTimerManager().SetTimer(ForceTimerHandle, this, &UTL_CombatComponent::ResetGroundFiction, HitForce.ForceStruct.ForceDuration + .01f, false);
	}
}

void UTL_CombatComponent::TL_AddMovementImpulse_Implementation(FForceStruct ForceStruct, bool VelChange /*= true*/)
{
	UWorld* World = PlayerCharacter->GetWorld();
	UCharacterMovementComponent* Movement = PlayerCharacter->GetCharacterMovement();
	if (Movement && World) {
		Movement->GroundFriction = 0;
		FVector Fwd = PlayerCharacter->GetActorForwardVector();
		Fwd.Normalize();
		Movement->AddImpulse(ForceStruct.ForceStrength * (FVector(PlayerCharacter->GetActorForwardVector().X, PlayerCharacter->GetActorForwardVector().Y, 0)), VelChange);
		World->GetTimerManager().SetTimer(ForceTimerHandle, this, &UTL_CombatComponent::ResetGroundFiction, ForceStruct.ForceDuration + .01f, false);
	}
	
}








//void UTL_CombatComponent::Change(TSubclassOf<ATL_Weapon> ChangeTo)
//{
//	if (CurrentCombo && CurrentCombo->SkillChangeOut && CurrentCombo->SkillChangeOut->SkillSubClass && GetWorld()) {
//		ATL_Skill* Skill = GetWorld()->SpawnActor<ATL_Skill>(CurrentCombo->SkillChangeOut->SkillSubClass.Get(), PlayerCharacter->GetTransform());
//		Skill->Perform(CurrentCombo->SkillChangeOut, PlayerCharacter);
//	}
//	ResetNextComboState();
//	if (!ChangeTo) {
//		CurrentCombo = MainState.Combo;
//		CurrentMotionList = MainState.MotionList;
//		if (!CurrentCombo) return;
//		NextComboState = CurrentCombo->StartState;
//		CurrentComboState = CurrentCombo->StartState;
//		if (CurrentCombo->SkillBlendIn && CurrentCombo->SkillBlendIn->SkillSubClass && GetWorld()) {
//			ATL_Skill* Skill = GetWorld()->SpawnActor<ATL_Skill>(CurrentCombo->SkillBlendIn->SkillSubClass.Get(), PlayerCharacter->GetTransform());
//			Skill->Perform(CurrentCombo->SkillBlendIn, PlayerCharacter);
//		}
//		return;
//	}
//	for (auto& iter : CharacterStates) {
//		if ((ChangeTo.Get()->IsChildOf(iter.Key.Get())) | (ChangeTo.Get() == iter.Key.Get())) {
//			CurrentCombo = iter.Value.Combo;
//			CurrentMotionList = iter.Value.MotionList;
//			if (!CurrentCombo) break;
//			NextComboState = CurrentCombo->StartState;
//			CurrentComboState = CurrentCombo->StartState;
//
//			if (CurrentCombo->SkillBlendIn && CurrentCombo->SkillBlendIn->SkillSubClass && GetWorld()) {
//				ATL_Skill* Skill = GetWorld()->SpawnActor<ATL_Skill>(CurrentCombo->SkillBlendIn->SkillSubClass.Get(), PlayerCharacter->GetTransform());
//				Skill->Perform(CurrentCombo->SkillBlendIn, PlayerCharacter);
//			}
//			break;
//		}
//	}
//
//}