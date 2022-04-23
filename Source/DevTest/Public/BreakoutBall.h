// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "BreakoutBall.generated.h"

UCLASS()
class DEVTEST_API ABreakoutBall : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABreakoutBall();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	USphereComponent* SphereCollider;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Components")
	UStaticMeshComponent* BallMeshComp;

	UPROPERTY()
	float VelocityMultiplier = 1.0f;

	UPROPERTY()
	FVector CurrentVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Velocity")
	FVector BaseVelocity = FVector(50.0f, 0.0f, 150.0f);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void LaunchBall();

	UFUNCTION(BlueprintCallable, Category="Velocity")
	void SetNewConstVelocity(const FVector& NewVelocity);

	UFUNCTION(BlueprintCallable, Category = "Velocity")
	void SetVelocityMultiplier(const float multiplier);


};
