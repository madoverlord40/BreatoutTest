// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakoutBall.h"

// Sets default values
ABreakoutBall::ABreakoutBall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("Ball Collider"));
	SphereCollider->SetupAttachment(RootComponent);

	BallMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ball Mesh"));
	BallMeshComp->SetupAttachment(SphereCollider);

	
}

// Called when the game starts or when spawned
void ABreakoutBall::BeginPlay()
{
	Super::BeginPlay();
	

}

// Called every frame
void ABreakoutBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABreakoutBall::LaunchBall()
{
	const float X = FMath::RandRange(-50.f, 50.f);

	SphereCollider->AddImpulse(FVector(X, 0.0f, -150.0f));
}

void ABreakoutBall::SetNewConstVelocity(const FVector& NewVelocity)
{
	CurrentVelocity = NewVelocity;
	const FVector Velocity = CurrentVelocity * VelocityMultiplier;

	SphereCollider->SetAllPhysicsLinearVelocity(Velocity);
}

void ABreakoutBall::SetVelocityMultiplier(const float multiplier)
{
	VelocityMultiplier = multiplier;
	const FVector Velocity = CurrentVelocity * VelocityMultiplier;

	SphereCollider->SetAllPhysicsLinearVelocity(Velocity);
}

