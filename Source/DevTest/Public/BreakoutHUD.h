// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "BreakoutHUD.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class DEVTEST_API ABreakoutHUD : public AHUD
{
	GENERATED_BODY()
	

public:
	virtual void PostInitializeComponents() override;

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool ShowTitleWidget(bool show = true);

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool ShowGameOverWidget(bool show = true);

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool ShowGameWidget(bool show = true);

	UFUNCTION(BlueprintCallable, Category = "UI")
	bool ShowPauseWidget(bool show = true);

protected:

	//Sets the user widget to be displayed as the main HUD for the player
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget Classes")
	TSoftClassPtr<UUserWidget> GameWidgetClass;

	//Sets the user widget to be displayed as the main menu widget
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget Classes")
	TSoftClassPtr<UUserWidget> MainMenuWidgetClass;

	//Sets the user widget to be displayed as the game over widget
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget Classes")
	TSoftClassPtr<UUserWidget> GameOverWidgetClass;

	//Sets the user widget to be displayed as the main pause menu widget
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Widget Classes")
	TSoftClassPtr<UUserWidget> PauseMenuWidgetClass;

	//Holds the user widget to be displayed as the game menu
	UPROPERTY(BlueprintReadOnly, Category = "References")
	UUserWidget* GameWidget;

	//Holds the user widget to be displayed as the main menu
	UPROPERTY(BlueprintReadOnly, Category = "References")
	UUserWidget* MainMenuWidget;

	//Holds the user widget to be displayed as the game over widget
	UPROPERTY(BlueprintReadOnly, Category = "References")
	UUserWidget* GameOverWidget;

	//Holds the user widget to be displayed as the pause menu widget
	UPROPERTY(BlueprintReadOnly, Category = "References")
	UUserWidget* PauseMenuWidget;
};
