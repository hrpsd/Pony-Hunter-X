#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PaperSpriteActor.h"

#include "MyPlayerController.generated.h"

class UInputAction;
class UInputMappingContext;

UCLASS()
class PONYHUNTER2_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void SetupInputComponent() override;
	
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category ="Input", meta = (AllowPrivateAccess = "true"))
	TArray<UInputMappingContext*> DefaultMappingContexts;
	
public:
	void OnLeftMouseButtonClicked();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* fireAction;
	
	UPROPERTY(EditAnywhere, Category="Collision")
	TEnumAsByte<ECollisionChannel> TraceChannelProperty = ECC_WorldDynamic;

	UPROPERTY(EditAnywhere)
	USoundBase *rifleSound;
};
