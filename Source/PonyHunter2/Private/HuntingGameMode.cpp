#include "HuntingGameMode.h"

#include "HorseActor.h"

AHuntingGameMode::AHuntingGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	
}

void AHuntingGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	if (ticks++ % 120 == 0)
	{
		AHorseActor *NewHorse = Cast<AHorseActor>(GetWorld()->SpawnActor(BPHorse, NULL, NULL, FActorSpawnParameters()));
		
		if (NewHorse)
		{
			
			int row = FMath::RandRange(0, numRows - 1);
			float rowY = row * 300.0f - 300.0f;
			
			bool flipped = (bool)(row % 2);
			
			NewHorse->SetActorLocation(FVector(flipped ? -2000.0f : 2000.0f, 0.0f, rowY));
			NewHorse->SetSortPriority(++numHorses);
			
			NewHorse->rowY = rowY;
			NewHorse->scale = 1.25f / FMath::Log2((row + 1) * 3.5f);
			NewHorse->flipped = flipped;
			
			if (flipped)
				NewHorse->xSpeed *= -1.0f;
			
		}
	}
	
	
}

