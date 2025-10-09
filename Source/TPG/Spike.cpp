// Fill out your copyright notice in the Description page of Project Settings.


#include "Spike.h"

// Sets default values
ASpike::ASpike()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spike Mesh"));
	MyMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MyMesh;

	MyCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("DamageBox"));
	MyCollider->SetupAttachment(RootComponent);
	MyCollider->OnComponentBeginOverlap.AddDynamic(this, &ASpike::OnOverlapBegin);
}

// Called when the game starts or when spawned
void ASpike::BeginPlay()
{
	Super::BeginPlay();
	
	Super::BeginPlay();
	UE_LOG(LogTemp, Display, TEXT("HELLO CPP!"));
}

// Called every frame
void ASpike::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpike::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Display, TEXT("OUCH!"));
}