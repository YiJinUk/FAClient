// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FA_UI_Fever.h"
#include "Logic/FA_PC.h"

#include "Components/Button.h"

void UFA_UI_Fever::NativeConstruct()
{
	Super::NativeConstruct();

	_pc = Cast<AFA_PC>(GetOwningPlayer());

	_fever->OnClicked.AddDynamic(this, &UFA_UI_Fever::ClickedFever);
}

void UFA_UI_Fever::UIFeverInit()
{

}

void UFA_UI_Fever::ClickedFever()
{
	_pc->PCFeverSuccess();
}