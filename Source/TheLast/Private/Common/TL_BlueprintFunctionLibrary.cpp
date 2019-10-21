#include "TL_BlueprintFunctionLibrary.h"
#include "Object.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"


bool UTL_BPFLib_Transform::BPF_World2Screen(UObject* Context, FVector InWorldPos, FVector2D& OutScreenPos)
{
	UWorld* World = Context->GetWorld();
	if (World)
	{
		APlayerController* PlayerCC;
		PlayerCC = World->GetFirstPlayerController();
		if (PlayerCC) {
			return UGameplayStatics::ProjectWorldToScreen(PlayerCC, InWorldPos, OutScreenPos);
		}
		return false;
	}
	return false;
}

bool UTL_BPFLib_Transform::BPF_Screen2World(UObject* Context, FVector2D InScreenPos, FVector& OutWorldPos, FVector& OutWorldDir)
{
	UWorld* World = Context->GetWorld();
	if (World)
	{
		APlayerController* PlayerCC;
		PlayerCC = World->GetFirstPlayerController();
		if (PlayerCC) {
			UGameplayStatics::DeprojectScreenToWorld(PlayerCC, InScreenPos, OutWorldPos, OutWorldDir);
			return true;
		} 
		return false;
	}
	return false;
}

bool UTL_BPFLib_Transform::BPF_ActorInViewPort(AActor* InActor)
{
	UWorld* World = InActor->GetWorld();
	if (!World) return false;
	//FVector LL, LR, HL, HR;
	FVector LLD, LRD, HLD, HRD;
	FVector2D VPSize;
	GEngine->GameViewport->GetViewportSize(VPSize);
	FVector2D LL, LR, HL, HR;
	LL = FVector2D(0, VPSize.Y);
	LR = FVector2D(VPSize.X, VPSize.Y);
	HL = FVector2D(0, 0);
	HR = FVector2D(VPSize.X, 0);
	FVector2D ActLoc;
	if (!BPF_World2Screen(InActor, InActor->GetActorLocation(), ActLoc)) return false;
	return BPF_IsPointInRect(ActLoc, HL, LL, LR, HR);
}

bool UTL_BPFLib_Transform::BPF_IsPointInRect(FVector2D p, FVector2D p1, FVector2D p2, FVector2D p3, FVector2D p4)
{
	//顶点必须顺次排布
	return (GetCross(p1, p2, p) * GetCross(p3, p4, p) >= 0) && (GetCross(p2, p3, p) * GetCross(p4, p1, p) >= 0);
}
