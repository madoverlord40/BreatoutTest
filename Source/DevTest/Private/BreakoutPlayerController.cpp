// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakoutPlayerController.h"
#include "BreakoutHUD.h"

void ABreakoutPlayerController::OnPossess(APawn* aPawn)
{

}

void ABreakoutPlayerController::OnUnPossess()
{

}

bool ABreakoutPlayerController::ShowTitleWidget()
{
	if (IsValid(MyHUD))
	{
		ABreakoutHUD* HUD = Cast<ABreakoutHUD>(MyHUD);

		if (IsValid(HUD))
		{
			return HUD->ShowTitleWidget();
		}
	}

	return false;
}

bool ABreakoutPlayerController::ShowGameOverWidget()
{
	if (IsValid(MyHUD))
	{
		ABreakoutHUD* HUD = Cast<ABreakoutHUD>(MyHUD);

		if (IsValid(HUD))
		{
			return HUD->ShowGameOverWidget();
		}
	}

	return false;
}

bool ABreakoutPlayerController::ShowGameWidget()
{
	if (IsValid(MyHUD))
	{
		ABreakoutHUD* HUD = Cast<ABreakoutHUD>(MyHUD);

		if (IsValid(HUD))
		{
			return HUD->ShowGameWidget();
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

void ABreakoutPlayerController::BeginPlay()
{
	Super::BeginPlay();

}

void ABreakoutPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

}
