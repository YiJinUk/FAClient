// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/FA_UI_Master.h"
#include "FA_UI_GameStart.generated.h"

class AFA_PC;
class UImage;
class UButton;

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
private:
	UPROPERTY(Meta = (BindWidget))
		UButton* _shot_start = nullptr;
	UPROPERTY(Meta = (BindWidget))
		UImage* _power_progress = nullptr;

	UPROPERTY()
		AFA_PC* _pc = nullptr;

private:
	UFUNCTION()
		void ClickedShotStart();
};
