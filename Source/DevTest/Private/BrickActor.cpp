// Fill out your copyright notice in the Description page of Project Settings.


#include "BrickActor.h"

// Sets default values
ABrickActor::ABrickActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BrickMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Brich Mesh"));
	BrickMeshComponent->SetupAttachment(RootComponent);

	BrickBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Brich Collider"));
	BrickBoxComponent->SetupAttachment(BrickBoxComponent);

	BrickBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ABrickActor::OnBoxColliderOverlap);

}

// Called when the game starts or when spawned
void ABrickActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABrickActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABrickActor::OnBoxColliderOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

}

