// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/FA_UI_GameStart.h"
#include "FA_UI_GameStart_Shop_Slot.h"
#include "Logic/FA_GM.h"
#include "Logic/FA_PC.h"
#include "Logic/FA_GI.h"

#include "Components/Image.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"

void UFA_UI_GameStart::NativeConstruct()
{
	Super::NativeConstruct();

	_pc = Cast<AFA_PC>(GetOwningPlayer());

	_shot_start->OnClicked.AddDynamic(this, &UFA_UI_GameStart::ClickedShotStart);
}
void UFA_UI_GameStart::UIGameStartInit()
{
	AFA_GM* fagm = GetWorld()->GetAuthGameMode<AFA_GM>();
	UFA_GI* fagi = GetWorld()->GetGameInstance<UFA_GI>();

	for (FDataRibbon* s_data_ribbon : fagi->GetDataRibbons())
	{
		UFA_UI_GameStart_Shop_Slot* w_slot = CreateWidgetShopSlot();
		w_slot->SlotPostInit(s_data_ribbon, this);
		if (fagm->IsBuyRibbonByCode(s_data_ribbon->GetCode()))
		{
			w_slot->SlotSetBuy(true);
			if (w_slot->GetCode() == "RB00001")
			{
				w_slot->SlotSetSelected(true);
			}
			_shop_slots_buy.Add(w_slot);
		}
		else
		{
			w_slot->SlotSetBuy(false);
			_shop_slots_not_buy.Add(w_slot);
		}
	}
	_shop_slots_not_buy.Sort([](const UFA_UI_GameStart_Shop_Slot& A, const UFA_UI_GameStart_Shop_Slot& B)
		{
			return A.GetPrice() < B.GetPrice();
		});

	SortShopSlot();

	fagm->SetPowerProgressMaterial(_power_progress->GetDynamicMaterial());

}

void UFA_UI_GameStart::UIGameStartChangeSelectedSlot(UFA_UI_GameStart_Shop_Slot* _selected_slot)
{
	if (_slot_selected)
	{
		_slot_selected->SlotSetSelected(false);
	}

	_slot_selected = _selected_slot;
	_slot_selected->SlotSetSelected(true);
}

void UFA_UI_GameStart::UIGameStartRibbonBuy(const FString& str_code_ribbon_buy)
{
	UFA_UI_GameStart_Shop_Slot* w_slot = nullptr;
	for (int32 i = 0, i_len = _shop_slots_not_buy.Num(); i < i_len; ++i)
	{
		w_slot = _shop_slots_not_buy[i];
		if (w_slot->GetCode() == str_code_ribbon_buy)
		{
			/**/
			w_slot->SlotSetBuy(true);
			_shop_slots_buy.Add(w_slot);
			_shop_slots_not_buy.RemoveAt(i);
			break;
		}
	}

	SortShopSlot();
}

void UFA_UI_GameStart::SortShopSlot()
{
	_shop_box->ClearChildren();
	_shop_slots_buy.Sort([](const UFA_UI_GameStart_Shop_Slot& A, const UFA_UI_GameStart_Shop_Slot& B)
		{
			return A.GetPrice() < B.GetPrice();
		});


	for (UFA_UI_GameStart_Shop_Slot* w_slot : _shop_slots_buy)
	{
		_shop_box->AddChild(w_slot);
	}
	for (UFA_UI_GameStart_Shop_Slot* w_slot : _shop_slots_not_buy)
	{
		_shop_box->AddChild(w_slot);
	}
}

void UFA_UI_GameStart::ClickedShotStart()
{
	_pc->PCShotStart();
}