#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "HorseActor.h"

#include "HuntingGameMode.generated.h"

UCLASS()
class PONYHUNTER2_API AHuntingGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AHuntingGameMode();
	
	virtual void Tick(float DeltaSeconds) override;
	
	int ticks = 0;
	
	int numHorses = 0;
	
	const int numRows = 4;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AHorseActor> BPHorse;
	
	void LeftClick();
};
