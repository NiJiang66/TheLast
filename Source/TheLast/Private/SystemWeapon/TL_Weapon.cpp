#include "TL_Weapon.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TL_CombatComponent.h"


ATL_Weapon::ATL_Weapon()
{
	PrimaryActorTick.bCanEverTick = false;	
}

void ATL_Weapon::BeginPlay()
{
	Super::BeginPlay();
}


void ATL_MeleeWeapon::TickTrace(FCombatSenseStruct CombatSense, TSubclassOf<UDamageType> DamageType, TArray<TEnumAsByte<EObjectTypeQuery>> ObjType, TArray<AActor*> ActorsToIgnore, int32 LineNum, USceneComponent* WeaponComponent, TArray<FVector> PrevLocs, TArray<FVector> &Prev, FName TraceStartSocket /*= FName("AttackTraceSocket0")*/, FName TraceEndSocket /*= FName("AttackTraceSocket1")*/, bool bDrawDebug /*= false*/)
{
	FVector StartSoc = WeaponComponent->GetSocketLocation(TraceStartSocket);
	FVector EndSoc = WeaponComponent->GetSocketLocation(TraceEndSocket);
	TArray<FVector> CurrentLocs;
	for (int i = 0; i <= LineNum; i++) {
		CurrentLocs.Add((((EndSoc - StartSoc) / LineNum) * i + StartSoc));
	}
	if (PrevLocs.Num() > 0) {
		for (int i = 0; i < PrevLocs.Num(); i++) {
			TArray<FHitResult> HitReses;
			if (UKismetSystemLibrary::LineTraceMultiForObjects(Cast<UObject>(GetGameInstance()), PrevLocs[i], CurrentLocs[i], ObjType, false, ActorsToIgnore, bDrawDebug ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None, HitReses, true)) {
				for (auto& HitRes : HitReses) {
					if( (Hitted.Num() == 0 || !Hitted.Contains(HitRes.GetActor())) && GetOwner() && HitRes.GetActor() != GetOwner()) {
						ITL_CharacterInterface* _Owner = Cast<ITL_CharacterInterface>(GetOwner());
						TSubclassOf<UActorComponent> CombatClass = UTL_CombatComponent::StaticClass();
						((UTL_CombatComponent*)(GetOwner()->GetComponentByClass(CombatClass)))->TL_HitTarget(CombatSense, HitRes.GetActor());
						Hitted.Add(HitRes.GetActor());
					}
				}
			}
		}
	}
	Prev = CurrentLocs;
}

void ATL_MeleeWeapon::TL_ExitEquip_Implementation()
{

}

void ATL_MeleeWeapon::TL_EnterEquip_Implementation()
{

}

void ATL_MeleeWeapon::TL_UnregisterAttack_Implementation()
{

}

void ATL_MeleeWeapon::TL_RegisterAttack_Implementation(FCombatSenseStruct CombatSense, bool bCustomizeSocket, FName TraceStartSocket0, FName TraceStartSocket1)
{

}

void ATL_BowWeapon::TL_ExitEquip_Implementation()
{

}

void ATL_BowWeapon::TL_EnterEquip_Implementation()
{

}

void ATL_SpecialWeapon::TL_ExitEquip_Implementation()
{

}

void ATL_SpecialWeapon::TL_EnterEquip_Implementation()
{

}
