// Fill out your copyright notice in the Description page of Project Settings.


#include "Public/Pickup.h"
#include "TPGGameMode.h"

// Sets default values
APickup::APickup()
{
	// Set this actor to call Tick() every frame. You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Collectable Mesh"));
	MyMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	RootComponent = MyMesh;
	MyCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collect Box"));
	MyCollider->AddRelativeLocation(FVector(0, -48, 0));
	MyCollider->SetupAttachment(RootComponent);
	MyCollider->OnComponentBeginOverlap.AddDynamic(this, &APickup::OnOverlapBegin);
}
// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
}
// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void APickup::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GEngine)
	{
		FString Message = FString::Printf(TEXT("Overlapped"));
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Emerald, Message);
	}
	ATPGGameMode* MyGameMode = Cast<ATPGGameMode>(GetWorld()->GetAuthGameMode());
	if (MyGameMode)
	{
		MyGameMode->AddScore(Value);
	}
	Destroy();
}