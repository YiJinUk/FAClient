// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/FA_GI.h"

UFA_GI::UFA_GI()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_GAME(TEXT("/Game/FAContent/ReadOnly/Data/FADT_Game.FADT_Game"));
	if (DT_GAME.Succeeded())
		_dt_game = DT_GAME.Object;
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_PLANE(TEXT("/Game/FAContent/ReadOnly/Data/FADT_Plane.FADT_Plane"));
	if (DT_PLANE.Succeeded())
		_dt_plane = DT_PLANE.Object;
}

void UFA_GI::GIInit()
{
	_data_game = _dt_game->FindRow<FDataGame>("GAME00001", "0");
}

FDataPlane* UFA_GI::FindDataPlaneByCode(const FString& str_code_plane)
{
	if (!_dt_plane) return nullptr;
	return _dt_plane->FindRow<FDataPlane>(*str_code_plane, "0");
}

FDataGame* UFA_GI::GetDataGame() { return _data_game; }