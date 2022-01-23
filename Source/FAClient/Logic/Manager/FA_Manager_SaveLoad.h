// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/FA_SharedStruct.h"
#include "Logic/Manager/FA_Manager_Master.h"
#include "FA_Manager_SaveLoad.generated.h"

/**
 * 
 */
UCLASS()
class FACLIENT_API AFA_Manager_SaveLoad : public AFA_Manager_Master
{
	GENERATED_BODY()
public:
	void SaveStart(FInfoGame& s_info_game);
	void LoadStart(FInfoGame& s_info_game);
};
