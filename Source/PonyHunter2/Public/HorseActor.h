#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "PaperFlipbookComponent.h"

#include "HorseActor.generated.h"

UCLASS()
class PONYHUNTER2_API AHorseActor : public AActor
{
	GENERATED_BODY()
	
public:
	AHorseActor();

protected:
	virtual void BeginPlay() override;

public:
	const int
		PONY = 0, UNICORN = 1,
		BOY = 0, GIRL = 1,
		WALK = 0, JUMP = 1,
		BG = 0, FG = 1;
	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	UPaperFlipbookComponent *bgFlipbook;
	
	UPROPERTY(EditAnywhere)
	UPaperFlipbookComponent *fgFlipbook;

	double spawnTime;
	
	int horseRace;
	int horseGender;
	
	float scale = 1.0f;
	float rowY = 0.0f;
	bool flipped;
	bool moving = true;
	float xSpeed;
	float rotationSpeed;
	
	UPROPERTY(EditAnywhere)
	TArray<UPaperFlipbook*> flipbooks;
	
	void SetSortPriority(int priority);
	void Hit();
};
