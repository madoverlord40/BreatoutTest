// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakoutPlayerController.h"
#include "BreakoutHUD.h"
#include "BreakoutGameState.h"

void ABreakoutPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	PaddlePawn = Cast<AGamePaddlePawn>(aPawn);

	GameState = GetWorld()->GetGameState<ABreakoutGameState>();
}

void ABreakoutPlayerController::OnUnPossess()
{
	Super::OnUnPossess();

	PaddlePawn = nullptr;
}

bool ABreakoutPlayerController::ShowTitleWidget(bool show)
{
	if (IsValid(MyHUD))
	{
		ABreakoutHUD* HUD = Cast<ABreakoutHUD>(MyHUD);

		if (IsValid(HUD))
		{
			return HUD->ShowTitleWidget(show);
		}
	}

	return false;
}

bool ABreakoutPlayerController::ShowGameOverWidget(bool show)
{
	if (IsValid(MyHUD))
	{
		ABreakoutHUD* HUD = Cast<ABreakoutHUD>(MyHUD);

		if (IsValid(HUD))
		{
			return HUD->ShowGameOverWidget(show);
		}
	}

	return false;
}

bool ABreakoutPlayerController::ShowGameWidget(bool show)
{
	if (IsValid(MyHUD))
	{
		ABreakoutHUD* HUD = Cast<ABreakoutHUD>(MyHUD);

		if (IsValid(HUD))
		{
			return HUD->ShowGameWidget(show);
		}
	}

	return false;
}

bool ABreakoutPlayerController::PauseBreakout()
{
	if (IsValid(MyHUD))
	{
		ABreakoutHUD* HUD = Cast<ABreakoutHUD>(MyHUD);

		if (IsValid(HUD))
		{
			bIsGamePaused = !bIsGamePaused;

			if (bIsGamePaused)
			{
				HUD->ShowPauseWidget();
				return SetPause(true);
			}
			else
			{
				HUD->ShowPauseWidget(false);
				return SetPause(false);
			}
		}
	}

	return false;
}

void ABreakoutPlayerController::OnInputMoveHorizontal(const float delta)
{
	if (IsValid(GameState) && IsValid(PaddlePawn))
	{
		if (GameState->GetCurrentState() == EGameFlowStates::EGAME_FLOW_STATE_IN_GAME)
		{
			const FVector Direction = FVector::ForwardVector;

			PaddlePawn->AddMovementInput(Direction, delta);
		}
	}
}



bool ABreakoutPlayerController::SpawnAndLaunchBall()
{
	if (IsValid(PaddlePawn))
	{
		return PaddlePawn->CreateAndLaunchBall();
	}

	return false;
}

void ABreakoutPlayerController::StartGame()
{
	if (IsValid(GameState) && IsValid(PaddlePawn))
	{
		GameState->StartNewGame();
		EnableInput(this);
	}
}

void ABreakoutPlayerController::QuitGame()
{
	if (IsValid(GameState) && IsValid(PaddlePawn))
	{
		PaddlePawn->DestroyBall();
		GameState->ExitGamePlay();
	}
}

void ABreakoutPlayerController::ResumeGame()
{
	if (IsValid(GameState) && IsValid(PaddlePawn) && bIsGamePaused)
	{
		GameState->ResumeGamePlay();
	}
}

void ABreakoutPlayerController::OnInputLaunch()
{
	if (IsValid(GameState) && IsValid(PaddlePawn))
	{
		if (GameState->GetCurrentState() == EGameFlowStates::EGAME_FLOW_STATE_IN_GAME)
		{
			GameState->LaunchBreakoutBall();
		}
	}
}

void ABreakoutPlayerController::OnInputPauseGame()
{
	if (IsValid(GameState))
	{	
		EGameFlowStates CurrentState = GameState->GetCurrentState();

		if (CurrentState == EGameFlowStates::EGAME_FLOW_STATE_IN_GAME )
		{
			GameState->PauseGamePlay();
		}
		else if (CurrentState == EGameFlowStates::EGAME_FLOW_STATE_GAME_PAUSED)
		{
			GameState->ResumeGamePlay();
		}
	}
}

void ABreakoutPlayerController::BeginPlay()
{
	Super::BeginPlay();
}
