// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/FA_SharedStruct.h"
#include "UI/FA_UI_Master.h"
#include "FA_UI_GameOver.generated.h"

class AFA_PC;
class UButton;
class UTextBlock;

/**
 * 
 */
UCLASS()
class FACLIENT_API UFA_UI_GameOver : public UFA_UI_Master
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
private:
	UPROPERTY(Meta = (BindWidget))
		UButton* _restart = nullptr;
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* _score = nullptr;
	UPROPERTY(Meta = (BindWidget))
		UTextBlock* _gem = nullptr;
	UPROPERTY(Meta = (BindWidgetAnim), Transient, Meta = (AllowPrivateAccess = true))
		UWidgetAnimation* _game_over = nullptr;

	UPROPERTY()
		AFA_PC* _pc = nullptr;

public:
	void UIGameOverUpdate(const FInfoGame& s_info_game);
private:
	UFUNCTION()
		void ClickedRestart();
};
