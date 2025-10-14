// Fill out your copyright notice in the Description page of Project Settings.


#include "Room.h"
#include "TPGCharacter.h"
#include "Public/Static/MapManager.h"

// Sets default values
ARoom::ARoom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
	RootComponent = RootScene;

	Entrance = CreateDefaultSubobject<USceneComponent>(TEXT("Entrance"));
	Entrance->SetupAttachment(RootComponent);

	Exit = CreateDefaultSubobject<USceneComponent>(TEXT("Exit"));
	Exit->SetupAttachment(RootComponent);

	Structure = CreateDefaultSubobject<USceneComponent>(TEXT("Structure"));
	Structure->SetupAttachment(RootComponent);

	Door = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Door"));
	Door->SetupAttachment(RootComponent);

	DoorDetector = CreateDefaultSubobject<UBoxComponent>(TEXT("DoorDetector"));
	DoorDetector->OnComponentBeginOverlap.AddDynamic(this, &ARoom::OnOverlapBegin);
	DoorDetector->SetupAttachment(Door);

	bDoorOpen = false;
}

// Called when the game starts or when spawned
void ARoom::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARoom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ARoom::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bDoorOpen)
	{
		bDoorOpen = true;
		// Placeholder until animation implemented
		Door->DestroyComponent();

		MapManager::SpawnNextRoom(this);
	}
}

FVector ARoom::GetEntranceLocation() const
{
	// This code validates Entrance before accessing it
	// In the event of an error, the default zero vector is returned
	return Entrance ? Entrance->GetComponentLocation() : FVector::ZeroVector;
}

FVector ARoom::GetExitLocation() const
{
	return Exit ? Exit->GetComponentLocation() : FVector::ZeroVector;
}

FVector ARoom::GetRoomLocation() const
{
	return RootScene ? RootScene->GetComponentLocation() : FVector::ZeroVector;
}