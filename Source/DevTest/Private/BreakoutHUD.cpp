// Fill out your copyright notice in the Description page of Project Settings.


#include "BreakoutHUD.h"

void ABreakoutHUD::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	GameWidgetClass.LoadSynchronous();
	MainMenuWidgetClass.LoadSynchronous();
	GameOverWidgetClass.LoadSynchronous();
	PauseMenuWidgetClass.LoadSynchronous();

	if (IsValid(PlayerOwner))
	{
		GameWidget = CreateWidget(PlayerOwner, GameWidgetClass.Get());
		MainMenuWidget = CreateWidget(PlayerOwner, MainMenuWidgetClass.Get());
		GameOverWidget = CreateWidget(PlayerOwner, GameOverWidgetClass.Get());
		PauseMenuWidget = CreateWidget(PlayerOwner, PauseMenuWidgetClass.Get());
	}
}

bool ABreakoutHUD::ShowTitleWidget(bool show)
{
	if (IsValid(MainMenuWidget))
	{
		if (show)
		{
			MainMenuWidget->AddToViewport();
		}
		else
		{
			MainMenuWidget->RemoveFromViewport();
		}

		return true;
	}

	return false;
}

bool ABreakoutHUD::ShowGameOverWidget(bool show)
{
	if (IsValid(GameOverWidget))
	{
		if (show)
		{
			GameOverWidget->AddToViewport();
		}
		else
		{
			GameOverWidget->RemoveFromViewport();
		}
		return true;
	}

	return false;
}

bool ABreakoutHUD::ShowGameWidget(bool show)
{
	if (IsValid(GameWidget))
	{
		if (show)
		{
			GameWidget->AddToViewport();
		}
		else
		{
			GameWidget->RemoveFromViewport();
		}
		return true;
	}

	return false;
}

bool ABreakoutHUD::ShowPauseWidget(bool show)
{
	if (IsValid(PauseMenuWidget))
	{
		if (show)
		{
			PauseMenuWidget->AddToViewport();
		}
		else
		{
			PauseMenuWidget->RemoveFromViewport();
		}

		return true;
	}

	return false;
}
