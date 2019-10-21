#include "BaseDamageBox.h"

ABaseDamageBox::ABaseDamageBox()
{
	DamgeCheckBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Dmg Check"));
	
}

TArray<AActor*> ABaseDamageBox::BoxCheck(FVector CausorLocation,FVector FwdLocationOffset, FVector BoundsScale, TSubclassOf<AActor> ClassToCheck)
{
	DamgeCheckBox->SetWorldTransform(this->GetTransform());
	DamgeCheckBox->SetWorldLocation(CausorLocation + FwdLocationOffset);
	DamgeCheckBox->SetWorldScale3D(BoundsScale);
	DamgeCheckBox->SetBoxExtent(FVector(120.f, 120.f, 160.f));
	TArray<AActor*> Res;
	DamgeCheckBox->GetOverlappingActors(Res, ClassToCheck);
	
	DelayedDestory();
	return Res;
}

void ABaseDamageBox::DelayedDestory()
{
	if (GetWorld()) {
		GetWorld()->GetTimerManager().SetTimer(DestoryHandle, this, &ABaseDamageBox::DestoryThis, .2f, false);
	}
}

void ABaseDamageBox::DestoryThis()
{
	GetWorld()->GetTimerManager().ClearTimer(DestoryHandle);
	this->Destroy();
}

ABaseDamageSphere::ABaseDamageSphere()
{
	DamgeCheckSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Dmg Check"));
}

TArray<AActor*> ABaseDamageSphere::SphereCheck(FVector CausorLocation, FVector FwdLocationOffset, FVector BoundsScale, TSubclassOf<AActor> ClassToCheck)
{
	DamgeCheckSphere->SetWorldTransform(this->GetTransform());
	DamgeCheckSphere->SetWorldLocation(CausorLocation + FwdLocationOffset);
	DamgeCheckSphere->SetWorldScale3D(BoundsScale);
	DamgeCheckSphere->SetSphereRadius(60.f);
	TArray<AActor*> Res;
	DamgeCheckSphere->GetOverlappingActors(Res, ClassToCheck);

	DelayedDestory();
	return Res;
}

void ABaseDamageSphere::DelayedDestory()
{
	if (GetWorld()) {
		GetWorld()->GetTimerManager().SetTimer(DestoryHandle, this, &ABaseDamageSphere::DestoryThis, .2f, false);
	}
}

void ABaseDamageSphere::DestoryThis()
{
	GetWorld()->GetTimerManager().ClearTimer(DestoryHandle);
	this->Destroy();
}
