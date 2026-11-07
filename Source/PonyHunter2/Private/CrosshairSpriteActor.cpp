#include "CrosshairSpriteActor.h"

#include "Kismet/GameplayStatics.h"
#include "GameFramework/PlayerController.h"

ACrosshairSpriteActor::ACrosshairSpriteActor()
{
	PrimaryActorTick.bCanEverTick = true;

}

void ACrosshairSpriteActor::Tick(float DeltaTime)
{
	FVector Location, Direction;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->DeprojectMousePositionToWorld(Location, Direction);
	//DrawDebugLine(GetWorld(), Location, Location + Direction * 100.0f, FColor::Red, true);
	SetActorLocation(Location);
}
