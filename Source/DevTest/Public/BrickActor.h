// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Sound/SoundCue.h"
#include "Particles/ParticleEmitter.h"
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
	void OnBoxColliderOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void SetBrickID(const FString& Id);

	const FString GetBrickId() const { return BrickId; }

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* BrickMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components")
	UBoxComponent* BrickBoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configuration")
	int32 HitsToBreak = 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configuration")
	FLinearColor MaterialColor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configuration")
	TSoftObjectPtr<USoundCue> HitSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configuration")
	TSoftObjectPtr<USoundCue> BreakSound;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configuration")
	TSoftObjectPtr<UParticleEmitter> HitParticleFX;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configuration")
	TSoftObjectPtr<UParticleEmitter> BreakParticleFX;

	UPROPERTY(BlueprintReadOnly, Category = "BrickId")
	FString BrickId;

};
