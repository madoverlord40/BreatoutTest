// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Sound/SoundCue.h"
#include "Particles/ParticleSystem.h"
#include "BrickActor.generated.h"

/*
Red Brick – One hit to break
Green Brick – Two hits to break, ball moves at 125% base speed
Blue Brick – Three hits to break, ball moves at 150% base speed
*/

UCLASS()
class DEVTEST_API ABrickActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABrickActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnBoxColliderHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void SetBrickID(const FString& Id) { BrickId = Id; }

	const FString GetBrickId() const { return BrickId; }

	void DestroyBrick();

	virtual void PostInitializeComponents() override;

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* BrickMeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* BrickBoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configuration")
	int32 HitsToBreak = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configuration")
	uint8 bModifyVelocityOnHit : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configuration")
	float BallSpeedModifier;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configuration")
	TSoftObjectPtr<USoundCue> HitSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configuration")
	TSoftObjectPtr<USoundCue> BreakSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configuration")
	TSoftObjectPtr<UParticleSystem> HitParticleFX;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configuration")
	TSoftObjectPtr<UParticleSystem> BreakParticleFX;

	UPROPERTY(BlueprintReadOnly, Category = "BrickId")
	FString BrickId;

	UPROPERTY(BlueprintReadOnly, Category = "BrickId")
	class ABreakoutGameState* GameState;

};
