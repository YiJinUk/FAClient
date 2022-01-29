// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/FA_UI_Master.h"
#include "FA_UI_GameStart.generated.h"

class AFA_PC;
class UFA_UI_GameStart_Shop_Slot;
class UImage;
class UButton;
class UScrollBox;

/**
 * 
 */
UCLASS()
class FACLIENT_API UFA_UI_GameStart : public UFA_UI_Master
{
	GENERATED_BODY()
	
public:
	virtual void NativeConstruct() override;
	void UIGameStartInit();
protected:
	UFUNCTION(BlueprintImplementableEvent)
		UFA_UI_GameStart_Shop_Slot* CreateWidgetShopSlot();
private:
	UPROPERTY(Meta = (BindWidget))
		UButton* _shot_start = nullptr;
	UPROPERTY(Meta = (BindWidget))
		UImage* _power_progress = nullptr;
	UPROPERTY(Meta = (BindWidget))
		UScrollBox* _shop_box = nullptr;

	UPROPERTY()
		AFA_PC* _pc = nullptr;

	UPROPERTY()
		TArray<UFA_UI_GameStart_Shop_Slot*> _shop_slots_buy;
	UPROPERTY()
		TArray<UFA_UI_GameStart_Shop_Slot*> _shop_slots_not_buy;
	UPROPERTY()
		UFA_UI_GameStart_Shop_Slot* _slot_selected = nullptr;

public:
	void UIGameStartRibbonBuy(const FString& str_code_ribbon_buy);
	void UIGameStartChangeSelectedSlot(UFA_UI_GameStart_Shop_Slot* _selected_slot);
private:
	void SortShopSlot();

private:
	UFUNCTION()
		void ClickedShotStart();
};
