#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteActor.h"
#include "CrosshairSpriteActor.generated.h"

UCLASS()
class PONYHUNTER2_API ACrosshairSpriteActor : public APaperSpriteActor
{
	GENERATED_BODY()
	
public:
	ACrosshairSpriteActor();

	virtual void Tick(float DeltaTime) override;
};
