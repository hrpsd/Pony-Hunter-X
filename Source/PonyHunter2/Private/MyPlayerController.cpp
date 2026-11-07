#include "MyPlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"
#include "EnhancedInputComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"

#include "HorseActor.h"

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	EnableInput(this);
	
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		for (UInputMappingContext* CurrentContext : DefaultMappingContexts)
		{
			Subsystem->AddMappingContext(CurrentContext, 0);
		}
	}
}

void AMyPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent)) {
		EnhancedInputComponent->BindAction(fireAction, ETriggerEvent::Started, this, &AMyPlayerController::OnLeftMouseButtonClicked);
	}
}

void AMyPlayerController::OnLeftMouseButtonClicked()
{
	UE_LOG(LogTemp, Display, TEXT("FIRE"));
	
	
	// FHitResult will hold all data returned by our line collision query
	FHitResult Hit;
	 
	
	FVector Location, Direction;
	UGameplayStatics::GetPlayerController(GetWorld(), 0)->DeprojectMousePositionToWorld(Location, Direction);
	//DrawDebugLine(GetWorld(), Location, Location + Direction * 100.0f, FColor::Red, true);
	
	
	// We set up a line trace from our current location to a point 1000cm ahead of us
	FVector TraceStart = Location;
	FVector TraceEnd = Location + Direction * 10000.0f;
	 
	// You can use FCollisionQueryParams to further configure the query
	// Here we add ourselves to the ignored list so we won't block the trace
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this);
	 
	// To run the query, you need a pointer to the current level, which you can get from an Actor with GetWorld()
	// UWorld()->LineTraceSingleByChannel runs a line trace and returns the first actor hit over the provided collision channel.
	GetWorld()->LineTraceSingleByChannel(Hit, TraceStart, TraceEnd, TraceChannelProperty, QueryParams);
	 
	// You can use DrawDebug helpers and the log to help visualize and debug your trace queries.
	//DrawDebugLine(GetWorld(), TraceStart, TraceEnd, Hit.bBlockingHit ? FColor::Blue : FColor::Red, false, 5.0f, 0, 10.0f);
	UE_LOG(LogTemp, Log, TEXT("Tracing line: %s to %s"), *TraceStart.ToCompactString(), *TraceEnd.ToCompactString());
	 
	// If the trace hit something, bBlockingHit will be true,
	// and its fields will be filled with detailed info about what was hit
	if (Hit.bBlockingHit && IsValid(Hit.GetActor()))
	{
		UE_LOG(LogTemp, Log, TEXT("Trace hit actor: %s"), *Hit.GetActor()->GetName());
		
		if (AHorseActor *horse = Cast<AHorseActor>(Hit.GetActor()))
		{
			horse->Hit();
		}
		else {
			UE_LOG(LogTemp, Log, TEXT("Not a horse!"));
		}
	}
	else {
		UE_LOG(LogTemp, Log, TEXT("No Actors were hit"));
	}

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), rifleSound, FVector::ZeroVector);
}

