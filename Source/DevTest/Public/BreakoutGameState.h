// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "BrickActor.h"
#include "BreakoutGameState.generated.h"

//Main flow states, for the game state so we can keep track of what the game is doing, or supposed to be doing
//Also allows the game state to be in charge of what the game is doing
UENUM(BlueprintType)
enum class EGameFlowStates : uint8
{
	EGAME_FLOW_STATE_TITLESCREEN,
	EGAME_FLOW_STATE_IN_GAME,
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

	void ChangeToState(EGameFlowStates NewState);

	bool SwitchToSubLevelById(const FName& SublevelId);

	bool DestroyBrickId(const FString& BrickId);

	void ResetBricks();

	void ResetGame();

	int32 GetLivesRemaining() const { return LivesRemaining; }

protected:

	void UnloadCurrentLevel();

	void LoadNextLevel();

	UFUNCTION()
	void FinishedLoadingMap();

	UFUNCTION()
	void FinishedUnLoadingMap();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game Config")
	int32 MaxNumberLives = 3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game Config")
	int32 RowsOfBricks = 5;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game Config")
	int32 ColumnsOfBricks = 15;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game Config")
	TSoftClassPtr<ABrickActor> BrickBlueprintClass;

	UPROPERTY(BlueprintReadOnly, Category = "References")
	TArray<ABrickActor*> CreatedBricks;

	UPROPERTY(BlueprintReadOnly, Category = "References")
	int32 LivesRemaining = 3;

};
