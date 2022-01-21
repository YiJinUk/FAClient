// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/FA_GI.h"

#include "Kismet/KismetMathLibrary.h"

UFA_GI::UFA_GI()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_GAME(TEXT("/Game/FAContent/ReadOnly/Data/FADT_Game.FADT_Game"));
	if (DT_GAME.Succeeded())
		_dt_game = DT_GAME.Object;
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_PLANE(TEXT("/Game/FAContent/ReadOnly/Data/FADT_Plane.FADT_Plane"));
	if (DT_PLANE.Succeeded())
		_dt_plane = DT_PLANE.Object;
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_OBJECT(TEXT("/Game/FAContent/ReadOnly/Data/FADT_Object.FADT_Object"));
	if (DT_OBJECT.Succeeded())
		_dt_object = DT_OBJECT.Object;
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
FDataObject* UFA_GI::FindDataObjectByCode(const FString& str_code_object)
{
	if (!_dt_object) return nullptr;
	return _dt_object->FindRow<FDataObject>(*str_code_object, "0");
}

int32 UFA_GI::GetRandomByInt(const int32 i_min, const int32 i_max)
{
	return UKismetMathLibrary::RandomInteger(i_max - i_min + 1) + i_min;
}

bool UFA_GI::IsPassProbByInt(const int32 i_goal)
{
	const int32 i_rnd = GetRandomByInt(1, 100);
	if (i_rnd <= i_goal)
	{
		return true;
	}
	else
	{
		return false;
	}
}

FDataGame* UFA_GI::GetDataGame() { return _data_game; }