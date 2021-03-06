// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/FA_SharedStruct.h"
#include "GameFramework/SaveGame.h"
#include "FA_SG_Game.generated.h"

/**
 * 
 */
UCLASS()
class FACLIENT_API UFA_SG_Game : public USaveGame
{
	GENERATED_BODY()
	
public:
	void SGSaveData(FInfoGame& s_info_game);
public:
	UPROPERTY()
		int32 score_best = 0;
	UPROPERTY()
		int32 gem = 0;
	UPROPERTY()
		TArray<FString> code_ribbons;
};
