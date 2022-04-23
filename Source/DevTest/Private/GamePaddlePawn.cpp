// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePaddlePawn.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AGamePaddlePawn::AGamePaddlePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	PaddleCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Collider"));
	RootComponent = PaddleCollider;

	PaddleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	PaddleMesh->SetupAttachment(PaddleCollider);

	MovementComponent = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));

	PaddleCollider->OnComponentHit.AddDynamic(this, &AGamePaddlePawn::OnBoxColliderHit);
}

// Called when the game starts or when spawned
void AGamePaddlePawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGamePaddlePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AGamePaddlePawn::CreateAndLaunchBall()
{
	BreakoutBallClass.LoadSynchronous();

	if (!IsValid(BreakoutBall))
	{
		FVector Location = GetActorLocation();
		Location += BallSpawnOffset;

		BreakoutBall = GetWorld()->SpawnActor<ABreakoutBall>(BreakoutBallClass.Get(), Location, FRotator::ZeroRotator);

		BreakoutBall->LaunchBall();

		return true;
	}

	return false;
}

void AGamePaddlePawn::DestroyBall()
{
	if (IsValid(BreakoutBall))
	{
		BreakoutBall->Destroy();
		BreakoutBall = nullptr;
	}
}

void AGamePaddlePawn::OnBoxColliderHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->IsA(ABreakoutBall::StaticClass()))
	{
		BallBounceSound.LoadSynchronous();

		UGameplayStatics::PlaySound2D(GetWorld(), BallBounceSound.Get());

		NormalImpulse.X += FMath::RandRange(-150.0f, 150.0f);
		NormalImpulse.Z = 150.0f;
		NormalImpulse.Y = 0.0f;

		ABreakoutBall* Ball = Cast<ABreakoutBall>(OtherActor);

		Ball->SetNewConstVelocity(NormalImpulse);
		
	}
}
