// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FA_UI_GamePlay.h"
#include "Logic/FA_GM.h"
#include "Logic/FA_GI.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

void UFA_UI_GamePlay::UIGamePlayPostInit()
{
	_fagm = GetWorld()->GetAuthGameMode<AFA_GM>();
	_fagi = GetWorld()->GetGameInstance<UFA_GI>();

	_power_cost->SetText(FText::AsNumber(_fagi->GetDataGame()->GetPlayerPowerCost()));
	_power_count->SetText(FText::AsNumber(_fagi->GetDataGame()->GetPlayerPowerCountMax()));

	_power->OnClicked.AddDynamic(this, &UFA_UI_GamePlay::ClickedPower);
}

void UFA_UI_GamePlay::UIGamePlayInit()
{
	_power_count->SetText(FText::AsNumber(_fagi->GetDataGame()->GetPlayerPowerCountMax()));
}

void UFA_UI_GamePlay::UIGamePlayPowerStart(const FInfoPlayer& s_info_player)
{
	_power_count->SetText(FText::AsNumber(s_info_player.power_count_current));
}

void UFA_UI_GamePlay::ClickedPower()
{
	_fagm->PlayerPowerStart();
}