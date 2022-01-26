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
	FDataObject* FindDataObjectByCode(const FString& str_code_object);
	FDataVFX* FindDataVFXByCode(const FString& str_code_vfx);
	FDataSFX* FindDataSFXByCode(const FString& str_code_sfx);

	FDataGame* GetDataGame();
private:
	UPROPERTY()
		UDataTable* _dt_game = nullptr;
	UPROPERTY()
		UDataTable* _dt_plane = nullptr;
	UPROPERTY()
		UDataTable* _dt_object = nullptr;
	UPROPERTY()
		UDataTable* _dt_vfx = nullptr;
	UPROPERTY()
		UDataTable* _dt_sfx = nullptr;

	FDataGame* _data_game = nullptr;
#pragma endregion

#pragma region Math
public:
	int32 GetRandomByInt(const int32 i_min, const int32 i_max);
	bool IsPassProbByInt(const int32 i_goal);
#pragma endregion
};
