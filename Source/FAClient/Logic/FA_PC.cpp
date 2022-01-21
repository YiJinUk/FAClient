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
}