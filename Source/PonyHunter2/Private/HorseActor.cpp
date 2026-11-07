// Fill out your copyright notice in the Description page of Project Settings.


#include "HorseActor.h"

AHorseActor::AHorseActor()
{
	PrimaryActorTick.bCanEverTick = true;

	
	rotationSpeed = 0.0f;
	
	horseRace = FMath::RandRange(0, 1);
	horseGender = FMath::RandRange(0, 1);
	
	//scale = FMath::RandRange(0.4f, 1.0f);
	
	xSpeed = -100.0f;
	
	bgFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Background Flipbook"));
	SetRootComponent(bgFlipbook);
	
	fgFlipbook = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Foreground Flipbook"));
	fgFlipbook->SetupAttachment(bgFlipbook);
		
}

void AHorseActor::BeginPlay()
{
	Super::BeginPlay();
	
	
	if (flipbooks.Num() > 0)
	{
		bgFlipbook->SetFlipbook(flipbooks[horseRace * 8 + horseGender * 4 + WALK * 2 + BG]);
		fgFlipbook->SetFlipbook(flipbooks[horseRace * 8 + horseGender * 4 + WALK * 2 + FG]);
	}
	
	if (horseRace == UNICORN)
	{
		fgFlipbook->SetRelativeLocation(FVector(-45.0f, 0.0f, 40.0f));
	}
	
	spawnTime = GetWorld()->GetTimeSeconds();
	
	bgFlipbook->SetSpriteColor(FLinearColor::MakeRandomColor());
	
}

void AHorseActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorScale3D(FVector(scale * FMath::Sign(-xSpeed), 1.0f, scale));
	
	FRotator rotation = GetActorRotation();
	rotation.Yaw += rotationSpeed * 30.0f * DeltaTime;
	SetActorRotation(rotation);
	rotationSpeed *= 0.99f;
	
	if (moving)
	{
		float sin, cos;
		FMath::SinCos(&sin, &cos, (GetWorld()->GetTimeSeconds() - spawnTime) * 3.0f);
		
		FVector location = GetActorLocation();
		location.X += xSpeed * DeltaTime;
		location.Z = rowY + sin * scale * 300.0f;
		SetActorLocation(location);
		
		if (!flipped && location.X < -2000.0f || flipped && location.X > 2000.0f)
		{
			Destroy();
		}
	}
	else {
		if (rotationSpeed > -5.0f && ((int)rotation.Yaw % 360 > 90 || (int)rotation.Yaw % 360 > 270))
		{
			Destroy();
		}
	}
}

void AHorseActor::SetSortPriority(int priority)
{
	bgFlipbook->SetTranslucentSortPriority(priority * 2);
	fgFlipbook->SetTranslucentSortPriority(priority * 2 + 1);
}

void AHorseActor::Hit()
{
	rotationSpeed = -60.0f;
	moving = false;
}
