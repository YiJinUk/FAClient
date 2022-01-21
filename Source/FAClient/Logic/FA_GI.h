// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/FA_SharedStruct.h"
#include "Engine/GameInstance.h"
#include "FA_GI.generated.h"

/**
 * 
 */
UCLASS()
class FACLIENT_API UFA_GI : public UGameInstance
{
	GENERATED_BODY()

protected:
	UFA_GI();
public:
	void GIInit();

#pragma region DataFind,Get
public:
	FDataPlane* FindDataPlaneByCode(const FString& str_code_plane);

	FDataGame* GetDataGame();
private:
	UPROPERTY()
		UDataTable* _dt_game = nullptr;
	UPROPERTY()
		UDataTable* _dt_plane = nullptr;

	FDataGame* _data_game = nullptr;
#pragma endregion
};
