// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/FA_PC.h"
#include "FA_GM.h"
#include "UI/FA_UI_Main.h"

AFA_PC::AFA_PC()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AFA_PC::PCInit(AFA_GM* fagm)
{
	_fagm = fagm;

	PCBPInit();

	_ui_main = PCCreateWidgetMain();
	_ui_main->UIMainInit();
}

void AFA_PC::PCUIObstacleWallTap()
{
	_ui_main->UIMainObstacleWallTap();
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

void AFA_PC::PCShotStart()
{
	_ui_main->UIMainShotStart();
	_fagm->ShotPlayer();
}
void AFA_PC::PCGameRestart()
{
	_fagm->GameRestart();
	_ui_main->UIMainGameRestart();
}
void AFA_PC::PCGameOver()
{
	_ui_main->UIMainGameOver();
}