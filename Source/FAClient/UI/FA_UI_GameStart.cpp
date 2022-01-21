// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FA_UI_GameStart.h"
#include "Logic/FA_GM.h"
#include "Logic/FA_PC.h"

#include "Components/Image.h"
#include "Components/Button.h"

void UFA_UI_GameStart::NativeConstruct()
{
	Super::NativeConstruct();

	_pc = Cast<AFA_PC>(GetOwningPlayer());

	_shot_start->OnClicked.AddDynamic(this, &UFA_UI_GameStart::ClickedShotStart);
}
void UFA_UI_GameStart::UIGameStartInit()
{
	AFA_GM* fagm = GetWorld()->GetAuthGameMode<AFA_GM>();
	fagm->SetPowerProgressMaterial(_power_progress->GetDynamicMaterial());
}

void UFA_UI_GameStart::ClickedShotStart()
{
	_pc->PCShotStart();
}