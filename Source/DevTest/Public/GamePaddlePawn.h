// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BreakoutBall.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Sound/SoundCue.h"
#include "GamePaddlePawn.generated.h"

UCLASS()
class DEVTEST_API AGamePaddlePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AGamePaddlePawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* PaddleMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* PaddleCollider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UFloatingPawnMovement* MovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ball")
	TSoftClassPtr<ABreakoutBall> BreakoutBallClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ball")
	TSoftObjectPtr<USoundCue> BallBounceSound;

	UPROPERTY(BlueprintReadOnly, Category = "Launch Ball")
	ABreakoutBall* BreakoutBall;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ball")
	FVector BallSpawnOffset;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual UPawnMovementComponent* GetMovementComponent() const override { return MovementComponent; }

	bool CreateAndLaunchBall();

	void DestroyBall();

	UFUNCTION()
	void OnBoxColliderHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);


};
