// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakoutGameState.h"
#include "BreakoutPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/LevelStreaming.h"
#include "Kismet/GameplayStatics.h"


void ABreakoutGameState::HandleBeginPlay()
{
	Super::HandleBeginPlay();

	BreakoutController = GetWorld()->GetFirstPlayerController<ABreakoutPlayerController>();

	if (IsValid(BreakoutController))
	{
		ExitGamePlay();
	}
}

void ABreakoutGameState::StartNewGame()
{
	if (IsValid(BreakoutController))
	{
		DestroyBreakoutBall();

		LivesRemaining = MaxNumberLives;
		if (CurrentScore > HighestScore)
		{
			HighestScore = CurrentScore;
		}
		CurrentScore = 0;
		CurrentLevel = 1;

		NextState = EGameFlowStates::EGAME_FLOW_STATE_IN_GAME;
		ChangeToState(EGameFlowStates::EGAME_FLOW_STATE_FADE_OUT);
	}
}

void ABreakoutGameState::PauseGamePlay()
{
	if (CurrentState == EGameFlowStates::EGAME_FLOW_STATE_IN_GAME)
	{
		ChangeToState(EGameFlowStates::EGAME_FLOW_STATE_GAME_PAUSED);
	}
}

void ABreakoutGameState::ResumeGamePlay()
{
	if (CurrentState == EGameFlowStates::EGAME_FLOW_STATE_GAME_PAUSED)
	{
		CurrentState = EGameFlowStates::EGAME_FLOW_STATE_IN_GAME;
		if (IsValid(BreakoutController))
		{
			//un-pause the game, acts like a toggle
			BreakoutController->PauseBreakout();
		}
	}
}

void ABreakoutGameState::ExitGamePlay()
{
	if (CurrentState == EGameFlowStates::EGAME_FLOW_STATE_GAME_PAUSED)
	{
		DestroyBreakoutBall();

		if (IsValid(BreakoutController))
		{
			//un-pause the game, acts like a toggle
			BreakoutController->PauseBreakout();
		}
	}
	CurrentLevel = 0;

	NextState = EGameFlowStates::EGAME_FLOW_STATE_TITLESCREEN;
	ChangeToState(EGameFlowStates::EGAME_FLOW_STATE_FADE_OUT);
}

void ABreakoutGameState::ChangeToState(EGameFlowStates NewState)
{
	if (IsValid(BreakoutController))
	{
		CurrentState = NewState;

		switch (CurrentState)
		{
		case EGameFlowStates::EGAME_FLOW_STATE_NONE:
			break;
		case EGameFlowStates::EGAME_FLOW_STATE_FADE_IN:
		{
			BreakoutController->DisableInput(BreakoutController);
			StartFadeIn();
			break;
		}
		case EGameFlowStates::EGAME_FLOW_STATE_FADE_OUT:
		{
			BreakoutController->DisableInput(BreakoutController);
			BreakoutController->ShowTitleWidget(false);
			BreakoutController->ShowGameWidget(false);
			BreakoutController->ShowGameOverWidget(false);
			StartFadeOut();

			break;
		}
		case EGameFlowStates::EGAME_FLOW_STATE_TITLESCREEN:
		{
			BreakoutController->ShowTitleWidget();
			BreakoutController->ShowGameWidget(false);
			BreakoutController->ShowGameOverWidget(false);

			StartFadeIn();

			OnGamePlayHasStarted();
			break;
		}
		case EGameFlowStates::EGAME_FLOW_STATE_LOAD_LEVEL:
		{
			FName* LevelId = LevelsMap.Find(CurrentLevel);
			if (LevelId != nullptr)
			{
				SwitchToSubLevelById(*LevelId);
			}
			break;
		}
		case EGameFlowStates::EGAME_FLOW_STATE_GAME_WIN:
		{
			BreakoutController->DisableInput(BreakoutController);
			BreakoutController->ShowTitleWidget(false);
			BreakoutController->ShowGameWidget(false);
			BreakoutController->ShowGameOverWidget(true);
			Fireworks.LoadSynchronous();

			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Fireworks.Get(), BreakoutController->GetPawn()->GetActorTransform());
			break;
		}
		case EGameFlowStates::EGAME_FLOW_STATE_IN_GAME:

			BreakoutController->EnableInput(BreakoutController);
			BreakoutController->ShowTitleWidget(false);
			BreakoutController->ShowGameOverWidget(false);
			BreakoutController->ShowGameWidget();
			
			FindAllBricks();
			
			BreakoutController->UpdateGameUI(CurrentScore, CurrentLevel, HighestScore, LivesRemaining);

			StartFadeIn();

			OnGamePlayHasStarted();
			break;
		case EGameFlowStates::EGAME_FLOW_STATE_GAME_OVER:
			BreakoutController->ShowTitleWidget(false);
			BreakoutController->ShowGameWidget(false);
			BreakoutController->ShowGameOverWidget(true);
			break;
		case EGameFlowStates::EGAME_FLOW_STATE_GAME_PAUSED:
			BreakoutController->PauseBreakout();
			break;
		default:
			break;

		}
	}
}

bool ABreakoutGameState::SwitchToSubLevelById(const FName& SublevelId)
{
	bool success = false;

	ULevelStreaming* Level = UGameplayStatics::GetStreamingLevel(this, SublevelId);

	if (IsValid(Level))
	{
		NextStreamedLevelName = SublevelId;
		UnloadCurrentLevel();
	}

	return success;
}

bool ABreakoutGameState::DestroyBrickId(const FString& BrickId)
{
	bool success = false;
	ABrickActor* BrickToDestroy = nullptr;

	for (ABrickActor* Brick : BricksInLevel)
	{
		if (IsValid(Brick))
		{
			if (Brick->GetBrickId() == BrickId)
			{
				BrickToDestroy = &(*Brick);
				break;
			}
		}
	}

	if (IsValid(BrickToDestroy))
	{
		BricksInLevel.Remove(BrickToDestroy);

		BrickToDestroy->DestroyBrick();
		CurrentScore++;

		if (CurrentScore > HighestScore)
		{
			HighestScore = CurrentScore;
		}

		if (BricksInLevel.Num() == 0)
		{
			DestroyBreakoutBall();

			CurrentLevel++;
			LivesRemaining++;

			if (CurrentLevel < 4)
			{
				ChangeToState(EGameFlowStates::EGAME_FLOW_STATE_FADE_OUT);
			}
			else
			{
				WinGame();
			}
		}

		BreakoutController->UpdateGameUI(CurrentScore, CurrentLevel, HighestScore, LivesRemaining);
	}

	return success;
}

void ABreakoutGameState::ResetGame()
{
	DestroyAllBricks();
	LivesRemaining = MaxNumberLives;
	CurrentLevel = 1;

	if (CurrentScore > HighestScore)
	{
		HighestScore = CurrentScore;
	}

	CurrentScore = 0;
	ChangeToState(EGameFlowStates::EGAME_FLOW_STATE_LOAD_LEVEL);
}

void ABreakoutGameState::LaunchBreakoutBall()
{
	if (IsValid(BreakoutController) && CurrentState == EGameFlowStates::EGAME_FLOW_STATE_IN_GAME)
	{
		if (LivesRemaining > 0)
		{

			if (BricksInLevel.Num() == 0)
			{
				FindAllBricks();
			}
			if (BreakoutController->SpawnAndLaunchBall())
			{
				LivesRemaining--;
			}
		}
	}
}

void ABreakoutGameState::WinGame()
{
	if (CurrentState == EGameFlowStates::EGAME_FLOW_STATE_IN_GAME)
	{
		ChangeToState(EGameFlowStates::EGAME_FLOW_STATE_GAME_WIN);
	}
}

void ABreakoutGameState::LoseGame()
{
	if (CurrentState == EGameFlowStates::EGAME_FLOW_STATE_IN_GAME)
	{
		ChangeToState(EGameFlowStates::EGAME_FLOW_STATE_GAME_OVER);
	}
}

void ABreakoutGameState::NotifyBallLost()
{
	if (CurrentState == EGameFlowStates::EGAME_FLOW_STATE_IN_GAME)
	{
		if (LivesRemaining == 0)
		{
			BreakoutController->DisableInput(BreakoutController);

			LoseGame();
		}
	}

}

void ABreakoutGameState::UnloadCurrentLevel()
{
	ULevelStreaming* Level = UGameplayStatics::GetStreamingLevel(this, CurrentStreamedLevelName);
	if (IsValid(Level))
	{
		if (Level->IsLevelLoaded())
		{
			FLatentActionInfo LatentInfo;

			LatentInfo.CallbackTarget = this;
			LatentInfo.ExecutionFunction = "FinishedUnLoadingMap";
			LatentInfo.Linkage = 1;
			LatentInfo.UUID = 1;

			UGameplayStatics::UnloadStreamLevel(this, CurrentStreamedLevelName, LatentInfo, true);
		}
		else
		{
			LoadNextLevel();
		}
	}
	else
	{
		LoadNextLevel();
	}
}

void ABreakoutGameState::LoadNextLevel()
{
	ULevelStreaming* Level = UGameplayStatics::GetStreamingLevel(this, NextStreamedLevelName);

	if (IsValid(Level))
	{
		if (!Level->IsLevelLoaded())
		{
			FLatentActionInfo LatentInfo;

			LatentInfo.CallbackTarget = this;
			LatentInfo.ExecutionFunction = FName("FinishedLoadingMap");
			LatentInfo.Linkage = 0;
			LatentInfo.UUID = 1;

			UGameplayStatics::LoadStreamLevel(this, NextStreamedLevelName, false, true, LatentInfo);
		}
		else
		{
			FinishedLoadingMap();
		}
	}
		
}

void ABreakoutGameState::FinishedLoadingMap()
{
	if (IsValid(BreakoutController))
	{
		ULevelStreaming* Level = UGameplayStatics::GetStreamingLevel(this, NextStreamedLevelName);

		if (IsValid(Level))
		{
			if (Level->IsLevelLoaded())
			{
				Level->SetShouldBeVisible(true);

				CurrentStreamedLevelName = NextStreamedLevelName;

				BreakoutController->PlayerCameraManager->StartCameraFade(1.0f, 0.0f, 1.0f, FLinearColor::Black, true, true);

				
				ChangeToState( EGameFlowStates::EGAME_FLOW_STATE_FADE_IN);
			}
		}
	}
}

void ABreakoutGameState::FinishedUnLoadingMap()
{
	LoadNextLevel();
}

void ABreakoutGameState::DestroyAllBricks()
{
	for (ABrickActor* Brick : BricksInLevel)
	{
		if (IsValid(Brick))
		{
			Brick->DestroyBrick();
		}
	}

	BricksInLevel.Empty();
}

void ABreakoutGameState::FindAllBricks()
{
	DestroyAllBricks();

	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABrickActor::StaticClass(), OutActors);

	for (AActor* Actor : OutActors)
	{
		ABrickActor* Brick = Cast<ABrickActor>(Actor);
		if (IsValid(Brick))
		{
			const FString BrickId = Brick->GetFName().ToString();
			Brick->SetBrickID(BrickId);

			BricksInLevel.Add(Brick);
		}
	}
}

void ABreakoutGameState::StartFadeOut()
{
	if (IsValid(BreakoutController) && CurrentState == EGameFlowStates::EGAME_FLOW_STATE_FADE_OUT)
	{
		BreakoutController->PlayerCameraManager->StartCameraFade(0.0f, 1.0f, TransitionTime, FLinearColor::Black, true, true);

		FTimerManager* TimerManager = &GetWorld()->GetTimerManager();

		if (TimerManager != nullptr)
		{			
			TimerManager->SetTimer(TimerHandle, this, &ABreakoutGameState::TransitionCompleted, TransitionTime, true);
		}
	}
}

void ABreakoutGameState::StartFadeIn()
{
	if (IsValid(BreakoutController) && CurrentState == EGameFlowStates::EGAME_FLOW_STATE_FADE_IN)
	{
		BreakoutController->PlayerCameraManager->StartCameraFade(1.0f, 0.0f, TransitionTime, FLinearColor::Black, true, true);

		FTimerManager* TimerManager = &GetWorld()->GetTimerManager();

		if (TimerManager != nullptr)
		{
			TimerManager->SetTimer(TimerHandle, this, &ABreakoutGameState::TransitionCompleted, TransitionTime, true);
		}
	}
}

void ABreakoutGameState::DestroyBreakoutBall()
{
	AGamePaddlePawn* Paddle = BreakoutController->GetPawn<AGamePaddlePawn>();
	if (IsValid(Paddle))
	{
		Paddle->DestroyBall();
	}
}

void ABreakoutGameState::TransitionCompleted()
{
	if (CurrentState == EGameFlowStates::EGAME_FLOW_STATE_FADE_IN)
	{
		ChangeToState(NextState);
	}
	else if (CurrentState == EGameFlowStates::EGAME_FLOW_STATE_FADE_OUT)
	{
		ChangeToState(EGameFlowStates::EGAME_FLOW_STATE_LOAD_LEVEL);
	}
		
	
}

