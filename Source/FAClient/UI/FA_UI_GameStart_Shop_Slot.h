// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/FA_SharedStruct.h"
#include "UI/FA_UI_Master.h"
#include "FA_UI_GameStart_Shop_Slot.generated.h"

class AFA_GM;
class UFA_UI_GameStart;
class UTextBlock;
class UImage;
class UWidgetSwitcher;
class UButton;

/**
 * 
 */
UCLASS()
class FACLIENT_API UFA_UI_GameStart_Shop_Slot : public UFA_UI_Master
{
	GENERATED_BODY()
	
public:
	void SlotPostInit(FDataRibbon* s_data_ribbon, UFA_UI_GameStart* w_game_start);
	void SlotSetBuy(const bool b_is_buy);
	void SlotSetSelected(const bool b_is_selected);

	const FString& GetCode() const;
	int32 GetPrice() const;
private:
	UPROPERTY(Meta = (BindWidget))
		UImage* _portrait = nullptr;
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* _price_text = nullptr;
	/*
	* index 0 : price
	* index 1 : check
	*/
	UPROPERTY(Meta = (BindWidget))
		UWidgetSwitcher* _switcher = nullptr;

	/*
	* index 0 : unselect
	* index 1 : selected
	*/
	UPROPERTY(Meta = (BindWidget))
		UWidgetSwitcher* _switcher_background = nullptr;

	UPROPERTY(Meta = (BindWidget))
		UButton* _buy = nullptr;

	UPROPERTY()
		AFA_GM* _fagm = nullptr;
	UPROPERTY()
		UFA_UI_GameStart* _game_start = nullptr;

	UPROPERTY()
		FString _code = "0";
	UPROPERTY()
		int32 _price = 0;
	UPROPERTY()
		bool _is_buy = false;

public:
	void SlotEquiped();
private:
	UFUNCTION()
		void ClickedBuy();
};
