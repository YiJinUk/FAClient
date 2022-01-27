// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/FA_PC.h"
#include "FA_GM.h"
#include "UI/FA_UI_Main.h"

AFA_PC::AFA_PC()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AFA_PC::PCInit(AFA_GM* fagm, const FInfoGame& s_info_game)
{
	_fagm = fagm;

	PCBPInit();

	_ui_main = PCCreateWidgetMain();
	_ui_main->UIMainInit(s_info_game);
}

void AFA_PC::PCUIObstacleWallTap()
{
	_ui_main->UIMainObstacleWallTap();
}

void AFA_PC::PCUITickUpdate(const int32 i_score_current)
{
	_ui_main->UIMainTickUpdate(i_score_current);
}

void AFA_PC::PCUIChanceJumpFever()
{
	_ui_main->UIMainChanceJumpFever();
}
void AFA_PC::PCFeverSuccess()
{
	_ui_main->UIMainFeverSuccess();
	_fagm->FeverSuccess();
}
void AFA_PC::PCFeverFailed()
{
	_ui_main->UIMainFeverFailed();
}
void AFA_PC::PCUIInteract(const EInteractType e_interact_type)
{
	_ui_main->UIMainInteract(e_interact_type);
}

void AFA_PC::PCShotStart()
{
	_ui_main->UIMainShotStart();
	_fagm->ShotPlayer();
}
void AFA_PC::PCPowerStart(const FInfoGame& s_info_game, const FInfoPlayer& s_info_player)
{
	_ui_main->UIMainPowerStart(s_info_game, s_info_player);
}
void AFA_PC::PCChangeRGB(const FLinearColor& s_fever, const FLinearColor& s_jump, const FLinearColor& s_slow)
{
	_ui_main->UIMainChangeRGB(s_fever, s_jump, s_slow);
}

void AFA_PC::PCGameRestart()
{
	_fagm->GameRestart();
	_ui_main->UIMainGameRestart();
}
void AFA_PC::PCGameOver(const FInfoGame& s_info_game)
{
	_ui_main->UIMainGameOver(s_info_game);
}

void AFA_PC::PCUIObtainGem(const int32 i_gem)
{
	_ui_main->UIMainObtainGem(i_gem);
}