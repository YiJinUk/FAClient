// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FA_UI_GameStart_Shop_Slot.h"
#include "Logic/FA_GM.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"

void UFA_UI_GameStart_Shop_Slot::SlotPostInit(FDataRibbon* s_data_ribbon)
{
	if (!s_data_ribbon) return;

	_fagm = GetWorld()->GetAuthGameMode<AFA_GM>();

	_portrait->SetBrushFromTexture(s_data_ribbon->GetPortrait());
	_price_text->SetText(FText::AsNumber(s_data_ribbon->GetPrice()));

	_code = s_data_ribbon->GetCode();
	_price = s_data_ribbon->GetPrice();

	_switcher->SetActiveWidgetIndex(0);

	_buy->OnClicked.AddDynamic(this, &UFA_UI_GameStart_Shop_Slot::ClickedBuy);
}

void UFA_UI_GameStart_Shop_Slot::SlotSetBuy(const bool b_is_buy)
{
	_is_buy = b_is_buy;
	if (b_is_buy)
	{
		_switcher->SetActiveWidgetIndex(1);
	}
	else
	{
		_switcher->SetActiveWidgetIndex(0);
	}
}

void UFA_UI_GameStart_Shop_Slot::ClickedBuy()
{
	if (_is_buy)
	{
		_fagm->PlayerChangeRibbonByCode(_code);
	}
	else
	{
		_fagm->RibbonBuyByCode(_code);
	}
}

const FString& UFA_UI_GameStart_Shop_Slot::GetCode() const { return _code; }
int32 UFA_UI_GameStart_Shop_Slot::GetPrice() const { return _price; }