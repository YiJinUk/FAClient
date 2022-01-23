// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/FA_UI_Master.h"
#include "FA_UI_Fever.generated.h"

class AFA_PC;
class UButton;

/**
 * 
 */
UCLASS()
class FACLIENT_API UFA_UI_Fever : public UFA_UI_Master
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
public:
	void UIFeverInit();
private:
	UPROPERTY(Meta = (BindWidget))
		UButton* _fever = nullptr;

	UPROPERTY()
		AFA_PC* _pc = nullptr;

private:
	UFUNCTION()
		void ClickedFever();
};
