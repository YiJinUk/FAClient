// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/FA_UI_Master.h"
#include "FA_UI_Main.generated.h"

class UFA_UI_GameStart;
class UFA_UI_Fever;
class UWidgetSwitcher;

/**
 * 
 */
UCLASS()
class FACLIENT_API UFA_UI_Main : public UFA_UI_Master
{
	GENERATED_BODY()
	
public:
	void UIMainInit();
private:
	/*
	* index 0 : empty
	* index 1 : GameStart
	* index 2 : GameOver
	* index 3 : JumpFever
	*/
	UPROPERTY(Meta = (BindWidget))
		UWidgetSwitcher* _switcher = nullptr;
	UPROPERTY(Meta = (BindWidget))
		UFA_UI_GameStart* _game_start = nullptr;
	UPROPERTY(Meta = (BindWidget))
		UFA_UI_Fever* _fever = nullptr;

public:
	void UIMainChanceJumpFever();
	void UIMainFeverSuccess();
	void UIMainFeverFailed();

	void UIMainShotStart();
	void UIMainGameRestart();
	void UIMainGameOver();
};
