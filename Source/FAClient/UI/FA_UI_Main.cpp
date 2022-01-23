// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FA_UI_Main.h"
#include "FA_UI_GameStart.h"
#include "FA_UI_Fever.h"

#include "Components/WidgetSwitcher.h"

void UFA_UI_Main::UIMainInit()
{
	_game_start->UIGameStartInit();
	_switcher->SetActiveWidgetIndex(1);
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
}
void UFA_UI_Main::UIMainGameOver()
{
	_switcher->SetActiveWidgetIndex(2);
}