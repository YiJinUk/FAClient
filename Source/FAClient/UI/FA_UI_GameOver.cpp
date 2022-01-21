// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FA_UI_GameOver.h"
#include "Logic/FA_PC.h"

#include "Components/Button.h"

void UFA_UI_GameOver::NativeConstruct()
{
	Super::NativeConstruct();

	_pc = Cast<AFA_PC>(GetOwningPlayer());

	_restart->OnClicked.AddDynamic(this, &UFA_UI_GameOver::ClickedRestart);
}

void UFA_UI_GameOver::ClickedRestart()
{
	_pc->PCGameRestart();
}