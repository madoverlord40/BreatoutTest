// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "BrickActor.h"
#include "TimerManager.h"
#include "BreakoutGameState.generated.h"

//Main flow states, for the game state so we can keep track of what the game is doing, or supposed to be doing
//Also allows the game state to be in charge of what the game is doing
UENUM(BlueprintType)
enum class EGameFlowStates : uint8
{
	EGAME_FLOW_STATE_NONE,
	EGAME_FLOW_STATE_FADE_IN,
	EGAME_FLOW_STATE_FADE_OUT,
	EGAME_FLOW_STATE_TITLESCREEN,
	EGAME_FLOW_STATE_LOAD_LEVEL,
	EGAME_FLOW_STATE_IN_GAME,
	EGAME_FLOW_STATE_GAME_WIN,
	EGAME_FLOW_STATE_GAME_OVER,
	EGAME_FLOW_STATE_GAME_PAUSED
};


/**
 * 
 */
UCLASS(Blueprintable)
class DEVTEST_API ABreakoutGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:

	/** Called by game mode to set the started play bool */
	virtual void HandleBeginPlay() override;

	void StartNewGame();

	void PauseGamePlay();

	void ResumeGamePlay();

	void ExitGamePlay();

	bool DestroyBrickId(const FString& BrickId);

	void ResetGame();

	int32 GetLivesRemaining() const { return LivesRemaining; }

	EGameFlowStates GetCurrentState() const { return CurrentState; }

	int32 GetCurrentScore() const { return CurrentScore; }

	void LaunchBreakoutBall();

	UFUNCTION(BlueprintCallable, Category="Win")
	void WinGame();

	UFUNCTION(BlueprintCallable, Category = "Lose")
	void LoseGame();

	UFUNCTION(BlueprintCallable, Category = "Lose")
	void NotifyBallLost();

	UFUNCTION(BlueprintImplementableEvent, Category="Events")
	void OnGamePlayHasStarted();

	UFUNCTION()
	void TransitionCompleted();

protected:
	void ChangeToState(EGameFlowStates NewState);

	bool SwitchToSubLevelById(const FName& SublevelId);

	void UnloadCurrentLevel();

	void LoadNextLevel();

	UFUNCTION()
	void FinishedLoadingMap();

	UFUNCTION()
	void FinishedUnLoadingMap();

	void DestroyAllBricks();

	void FindAllBricks();

	void StartFadeOut();

	void StartFadeIn();

	void DestroyBreakoutBall();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game Config")
	int32 MaxNumberLives = 3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game Config")
	TMap<int32, FName> LevelsMap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game Config")
	TSoftObjectPtr<UParticleSystem> Fireworks;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game Config")
	uint8 bUseFadingTransitions : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game Config")
	float TransitionTime = 2.0f;

	UPROPERTY(BlueprintReadOnly, Category = "References")
	TArray<ABrickActor*> BricksInLevel;

	UPROPERTY(BlueprintReadOnly, Category = "References")
	int32 LivesRemaining = 3;

	UPROPERTY(BlueprintReadOnly, Category = "References")
	int32 CurrentLevel = 0;

	UPROPERTY(BlueprintReadOnly, Category = "References")
	int32 CurrentScore = 0;

	UPROPERTY(BlueprintReadOnly, Category = "References")
	int32 HighestScore = 0;

	UPROPERTY(BlueprintReadOnly, Category = "References")
	EGameFlowStates CurrentState;

	UPROPERTY(BlueprintReadOnly, Category = "References")
	EGameFlowStates NextState;

	UPROPERTY(BlueprintReadOnly, Category = "References")
	class ABreakoutPlayerController* BreakoutController;

	UPROPERTY(BlueprintReadOnly, Category = "References")
	FName CurrentStreamedLevelName;

	UPROPERTY(BlueprintReadOnly, Category = "References")
	FName NextStreamedLevelName;

	FTimerHandle TimerHandle;
};
