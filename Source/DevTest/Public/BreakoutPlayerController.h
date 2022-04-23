// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GamePaddlePawn.h"
#include "BreakoutGameState.h"
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
	bool ShowTitleWidget(bool show = true);

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool ShowGameOverWidget(bool show = true);

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool ShowGameWidget(bool show = true);

	UFUNCTION(BlueprintCallable, Category = "Pause")
	bool PauseBreakout();

	UFUNCTION(BlueprintCallable, Category = "Ball")
	bool SpawnAndLaunchBall();

	UFUNCTION(BlueprintCallable, Category = "Start")
	void StartGame();

	UFUNCTION(BlueprintCallable, Category = "Quit")
	void QuitGame();

	UFUNCTION(BlueprintCallable, Category = "Quit")
	void ResumeGame();

	UFUNCTION(BlueprintCallable, Category="Movement")
	void OnInputMoveHorizontal(const float delta);

	UFUNCTION(BlueprintCallable, Category = "Launch")
	void OnInputLaunch();

	UFUNCTION(BlueprintCallable, Category = "Pause")
	void OnInputPauseGame();

	UFUNCTION(BlueprintImplementableEvent, Category="Events")
	void UpdateGameUI(const int32 Score, const int32 Level, const int32 HighScore, const int32 Lives);

protected:
	virtual void BeginPlay() override;

	uint8 bIsGamePaused : 1;

	UPROPERTY()
	ABreakoutGameState* GameState;

	UPROPERTY()
	AGamePaddlePawn* PaddlePawn;
};
