// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BreakoutPlayerController.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class DEVTEST_API ABreakoutPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:

	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

	UFUNCTION(BlueprintCallable, Category="UI")
	bool ShowTitleWidget();

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool ShowGameOverWidget();

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool ShowGameWidget();

	UFUNCTION(BlueprintCallable, Category = "Pause")
	bool PauseBreakout();

protected:
	virtual void BeginPlay() override;
	/** Allows the PlayerController to set up custom input bindings. */
	virtual void SetupInputComponent();

	uint8 bIsGamePaused : 1;
};
