// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/FA_SharedStruct.h"
#include "UI/FA_UI_Master.h"
#include "FA_UI_GamePlay.generated.h"

class UFA_GI;
class AFA_GM;
class UFA_GI;
class UButton;
class UTextBlock;

/**
 * 
 */
UCLASS()
class FACLIENT_API UFA_UI_GamePlay : public UFA_UI_Master
{
	GENERATED_BODY()
	
public:
	void UIGamePlayPostInit();
private:
	UPROPERTY(Meta = (BindWidget))
		UButton* _power = nullptr;
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* _power_count = nullptr;
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* _power_cost = nullptr;

	UPROPERTY()
		UFA_GI* _fagi = nullptr;
	UPROPERTY()
		AFA_GM* _fagm = nullptr;

public:
	void UIGamePlayInit();

	void UIGamePlayPowerStart(const FInfoPlayer& s_info_player);
	
protected:
	
private:
	UFUNCTION()
		void ClickedPower();
};
