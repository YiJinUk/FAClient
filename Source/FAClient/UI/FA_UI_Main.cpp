// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FA_UI_Main.h"
#include "FA_UI_GameStart.h"
#include "FA_UI_GameOver.h"
#include "FA_UI_Fever.h"

#include "Components/WidgetSwitcher.h"
#include "Components/TextBlock.h"

void UFA_UI_Main::UIMainInit(const FInfoGame& s_info_game)
{
	_game_start->UIGameStartInit();
	_switcher->SetActiveWidgetIndex(1);

	_score_best->SetText(FText::AsNumber(s_info_game.score_best));
	_gem->SetText(FText::AsNumber(s_info_game.gem));
}

void UFA_UI_Main::UIMainTickUpdate(const int32 i_score_current)
{
	_score_current->SetText(FText::AsNumber(i_score_current));
}

void UFA_UI_Main::UIMainObstacleWallTap()
{
	_switcher->SetActiveWidgetIndex(4);
}

void UFA_UI_Main::UIMainChanceJumpFever()
{
	_fever->UIFeverInit();
	_switcher->SetActiveWidgetIndex(3);
}
void UFA_UI_Main::UIMainFeverSuccess()
{
	_switcher->SetActiveWidgetIndex(0);
}
void UFA_UI_Main::UIMainFeverFailed()
{
	_switcher->SetActiveWidgetIndex(0);
}

void UFA_UI_Main::UIMainShotStart()
{
	_switcher->SetActiveWidgetIndex(0);
}
void UFA_UI_Main::UIMainGameRestart()
{
	_switcher->SetActiveWidgetIndex(1);
	_score_current->SetText(FText::AsNumber(0));
}
void UFA_UI_Main::UIMainGameOver(const FInfoGame& s_info_game)
{
	_game_over->UIGameOverUpdate(s_info_game);
	_switcher->SetActiveWidgetIndex(2);
	_score_best->SetText(FText::AsNumber(s_info_game.score_best));
}

void UFA_UI_Main::UIMainSetScoreBest(const int32 i_score_best)
{
	_score_best->SetText(FText::AsNumber(i_score_best));
}
void UFA_UI_Main::UIMainObtainGem(const int32 i_gem)
{
	_gem->SetText(FText::AsNumber(i_gem));
}