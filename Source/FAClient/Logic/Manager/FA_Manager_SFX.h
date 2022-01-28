// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Logic/Manager/FA_Manager_Master.h"
#include "FA_Manager_SFX.generated.h"

class UFA_GI;

/**
 * 
 */
UCLASS()
class FACLIENT_API AFA_Manager_SFX : public AFA_Manager_Master
{
	GENERATED_BODY()

public:
	void SFXInit(UFA_GI* fagi);
private:
	FDataSFX* _data_sfx_cache = nullptr;
	UPROPERTY()
		UAudioComponent* _fever_timing_cache = nullptr;

public:
	void SFXStart(const ESFXType e_sfx_type);
	void SFXEnd(const ESFXType e_sfx_type);
};
