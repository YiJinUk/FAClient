// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/FA_SharedStruct.h"
#include "UI/FA_UI_Master.h"
#include "FA_UI_Main.generated.h"

class UFA_UI_GameStart;
class UFA_UI_GameOver;
class UFA_UI_Fever;
class UWidgetSwitcher;
class UTextBlock;

/**
 * 
 */
UCLASS()
class FACLIENT_API UFA_UI_Main : public UFA_UI_Master
{
	GENERATED_BODY()
	
public:
	void UIMainInit(const FInfoGame& s_info_game);
private:
	/*
	* index 0 : empty
	* index 1 : GameStart
	* index 2 : GameOver
	* index 3 : JumpFever
	* index 4 : WallTap
	*/
	UPROPERTY(Meta = (BindWidget))
		UWidgetSwitcher* _switcher = nullptr;
	UPROPERTY(Meta = (BindWidget))
		UFA_UI_GameStart* _game_start = nullptr;
	UPROPERTY(Meta = (BindWidget))
		UFA_UI_GameOver* _game_over = nullptr;
	UPROPERTY(Meta = (BindWidget))
		UFA_UI_Fever* _fever = nullptr;

	UPROPERTY(Meta = (BindWidget))
		UTextBlock* _gem = nullptr;
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* _score_best = nullptr;
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* _score_current = nullptr;

public:
	void UIMainTickUpdate(const int32 i_score_current);

	void UIMainObstacleWallTap();

	void UIMainChanceJumpFever();
	void UIMainFeverSuccess();
	void UIMainFeverFailed();

	void UIMainShotStart();
	void UIMainGameRestart();
	void UIMainGameOver(const FInfoGame& s_info_game);

	void UIMainSetScoreBest(const int32 i_score_best);
	void UIMainObtainGem(const int32 i_gem);
};
