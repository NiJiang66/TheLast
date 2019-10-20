// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "TL_Character.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/Engine.h"

//#include "BaseDamageBox.h"
#include "TL_SkillComponent.h"
#include "TL_Helper.h"

//#include "ACT_CombatComponent.h"


ATL_Character::ATL_Character()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// set our turn rates for input
	BaseTurnRate = 45.f;
	BaseLookUpRate = 45.f;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
	GetCharacterMovement()->SetComponentTickEnabled(true);

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 500.0f; // The camera follows at this distance behind the character	
	CameraBoom->RelativeRotation = FRotator(-17.f, 0, 0);
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Note: The skeletal mesh and anim blueprint references on the Mesh component (inherited from Character) 
	// are set in the derived blueprint asset named MyCharacter (to avoid direct content references in C++)

}

//////////////////////////////////////////////////////////////////////////
// Input

void ATL_Character::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	// Set up gameplay key bindings
	check(PlayerInputComponent);
	
	PlayerInputComponent->BindAxis("MoveForward", this, &ATL_Character::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ATL_Character::MoveRight);
	PlayerInputComponent->BindAction("AnyKey", IE_Pressed, this, &ATL_Character::AnyKeyFunc);

	// We have 2 versions of the rotation bindings to handle different kinds of devices differently
	// "turn" handles devices that provide an absolute delta, such as a mouse.
	// "turnrate" is for devices that we choose to treat as a rate of change, such as an analog joystick
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis("TurnRate", this, &ATL_Character::TurnAtRate);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpRate", this, &ATL_Character::LookUpAtRate);

	//AbilitySystem->BindAbilityActivationToInputComponent(PlayerInputComponent, FGameplayAbilityInputBinds("ConfirmInput", "CancelInput", "AbilityInput"));
}

void ATL_Character::BeginPlay()
{
	Super::BeginPlay();

	//获取技能组件
	if (GetComponentByClass(UTL_SkillComponent::StaticClass())) {
		SkillComponnt = Cast<UTL_SkillComponent>(GetComponentByClass(UTL_SkillComponent::StaticClass()));
	}	
	else {
		TL_Helper::Debug(TEXT("Character: Failed To Get Combo Component"), 20, FColor::Red);
	}

	//TL_InitializeUI();
}

void ATL_Character::AnyKeyFunc(FKey key)
{
	if(SkillComponnt) SkillComponnt->KeyInput(key);
}

void ATL_Character::GetTargetRelativePostion(FVector TargetPositon, float& FwdOrBwd, float& LOrR)
{
	FVector Forward = GetActorForwardVector();
	FVector Right = GetActorRightVector();
	FVector Dis = TargetPositon - GetActorLocation();
	Forward.Z = 0;
	Right.Z = 0;
	Dis.Z = 0;
	Forward.Normalize();
	Right.Normalize();
	FwdOrBwd = FVector::DotProduct(Forward, Dis);
	LOrR = FVector::DotProduct(Right, Dis);
}



//AActor* ATL_Character::BindWeapon(TSubclassOf<AActor> WeaponSubClass, FName SocketName, USceneComponent* ComponentToBind)
//{
//	if (GetWorld() && WeaponSubClass && ComponentToBind) {
//		AActor* WeaponToBind = GetWorld()->SpawnActor<AActor>(WeaponSubClass, ComponentToBind->GetSocketTransform(SocketName));
//		WeaponToBind->AttachToComponent(ComponentToBind, FAttachmentTransformRules::SnapToTargetIncludingScale, SocketName);
//		WeaponToBind->SetOwner(this);
//		return WeaponToBind;
//	}																		
//	return nullptr;
//}
//
//bool ATL_Character::TurnToTargetAtOnceWithHitResult(FHitResult HitResult)
//{
//	//Quick Turn With a HitResult 
//	AActor* OtherActor = HitResult.GetActor();
//	return TurnToTargetAtOnce(OtherActor->GetRootComponent());
//}
//
//bool ATL_Character::TurnToTargetAtOnce(USceneComponent* Target)
//{
//	//Immediately Turn To An Actor Target
//	if (Target) {
//		FVector SelfLocation = GetActorLocation();
//		FVector TargetLocation = Target->GetComponentLocation();
//		FRotator NewRotator = UKismetMathLibrary::FindLookAtRotation(SelfLocation, TargetLocation);
//		NewRotator.Pitch = 0;
//		return SetActorRotation(NewRotator);
//	}
//	return false;
//}

void ATL_Character::TurnAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerYawInput(Rate * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void ATL_Character::LookUpAtRate(float Rate)
{
	// calculate delta for this frame from the rate information
	AddControllerPitchInput(Rate * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

void ATL_Character::MoveForward(float Value)
{
	XAxisInput = Value;
	if ((Controller != NULL) && (Value != 0.0f) && Moveable)
	{
		if (!bDirUseSelfRot) {
			// find out which way is forward                                                                                                                                         
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get forward vector
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction, Value * MoveSpeed);
		}
		else {
			// find out which way is forward                                                                                                                                         
			const FRotator Rotation = GetActorRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get forward vector
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
			AddMovementInput(Direction, Value * MoveSpeed);
		}
	}
}

void ATL_Character::MoveRight(float Value)
{
	YAxisInput = Value;
	if ( (Controller != NULL) && (Value != 0.0f) && Moveable)
	{
		if (!bDirUseSelfRot) {
			// find out which way is right
			const FRotator Rotation = Controller->GetControlRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get right vector 
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			// add movement in that direction
			AddMovementInput(Direction, Value * MoveSpeed);
		}
		else {
			// find out which way is right
			//Use Self Rot Here
			const FRotator Rotation = GetActorRotation();
			const FRotator YawRotation(0, Rotation.Yaw, 0);

			// get right vector 
			const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
			// add movement in that direction
			AddMovementInput(Direction, Value * MoveSpeed);
		}
	}
}


//Character Interface(Could Be Overrided By BP Implements)

//void ATL_Character::ACT_ApplyDamage_Implementation(USceneComponent* DamageCausor, AActor* Target, UParticleSystem* ParticleTemplate, FHitReacStruct HitReact, TSubclassOf<UDamageType> DamageType, float FXScale /* = 1 */, bool bCustomizeLoc, FVector FXPos)
//{
//
//}
//
//void ATL_Character::ACT_TakeDamage_Implementation(USceneComponent* DamageCausor, FHitReacStruct HitReact, TSubclassOf<UDamageType> DamageType)
//{
//
//}
//
//void ATL_Character::ACT_DunFrame_Implementation(float TimeDilation, float Duration, float CameraBoomMin, TSubclassOf<UCameraShake> CamearaShake, UCurveFloat* CameraCurve)
//{
//
//}
//
//
//void ATL_Character::ACT_RegisterAttack_Implementation(FCombatSenseStruct CombatSense, bool bCustomizeSocket, FName TraceStartSocket0, FName TraceStartSocket1)
//{
//	if (UACT_CombatComponent* CombatComponent = Cast<UACT_CombatComponent>(GetComponentByClass(UACT_CombatComponent::StaticClass())))
//		if(AACTWeapon* MeleeWeapon = CombatComponent->GetCurrentWeaponOfType(EWeaponTypes::E_MELEE))
//			MeleeWeapon->Execute_ACT_RegisterAttack(MeleeWeapon, CombatSense, bCustomizeSocket, TraceStartSocket0, TraceStartSocket1);
//}
//
//void ATL_Character::ACT_UnregisterAttack_Implementation()
//{
//	if(UACT_CombatComponent* CombatComponent = Cast<UACT_CombatComponent>(GetComponentByClass(UACT_CombatComponent::StaticClass())))
//		if(AACTWeapon* MeleeWeapon = CombatComponent->GetCurrentWeaponOfType(EWeaponTypes::E_MELEE))
//			MeleeWeapon->Execute_ACT_UnregisterAttack(MeleeWeapon);
//}
//
//
//
//void ATL_Character::ACT_DealDamage_Implementation(float Damage)
//{
//	
//}
//
//
//
//void ATL_Character::ACT_CharacterDie_Implementation()
//{
//
//}



