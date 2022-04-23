// Fill out your copyright notice in the Description page of Project Settings.


#include "BrickActor.h"
#include "BreakoutGameState.h"
#include "BreakoutBall.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABrickActor::ABrickActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BrickMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Brich Mesh"));
	BrickMeshComponent->SetupAttachment(RootComponent);

	BrickBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Brich Collider"));
	BrickBoxComponent->SetupAttachment(BrickMeshComponent);

}

// Called when the game starts or when spawned
void ABrickActor::BeginPlay()
{
	Super::BeginPlay();
	HitSound.LoadSynchronous();
	BreakSound.LoadSynchronous();
	HitParticleFX.LoadSynchronous();
	BreakParticleFX.LoadSynchronous();
}

// Called every frame
void ABrickActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABrickActor::OnBoxColliderHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->IsA(ABreakoutBall::StaticClass()))
	{
		UGameplayStatics::PlaySound2D(GetWorld(), HitSound.LoadSynchronous());
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticleFX.LoadSynchronous(), OtherActor->GetActorTransform());

		HitsToBreak--;

		UGameplayStatics::PlaySound2D(this, HitSound.Get());
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitParticleFX.Get(), OtherActor->GetActorTransform());

		if (HitsToBreak == 0)
		{
			GameState = Cast<ABreakoutGameState>(GetWorld()->GetGameState());

			if (IsValid(GameState))
			{
				GameState->DestroyBrickId(BrickId);
			}
		}
		
		NormalImpulse.X += FMath::RandRange(-150.0f, 150.0f);
		NormalImpulse.Z = -150.0f;
		NormalImpulse.Y = 0.0f;

		ABreakoutBall* Ball = Cast<ABreakoutBall>(OtherActor);

		if (IsValid(Ball))
		{
			Ball->SetNewConstVelocity(NormalImpulse);

			if (bModifyVelocityOnHit)
			{
				Ball->SetVelocityMultiplier(BallSpeedModifier);
			}
		}
	}
}

void ABrickActor::DestroyBrick()
{
	UGameplayStatics::PlaySound2D(GetWorld(), BreakSound.Get());
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BreakParticleFX.Get(), GetActorTransform());

	Destroy();
}

void ABrickActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	BrickBoxComponent->OnComponentHit.AddDynamic(this, &ABrickActor::OnBoxColliderHit);
}

