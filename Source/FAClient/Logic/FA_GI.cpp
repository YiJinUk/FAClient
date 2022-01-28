// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/FA_GI.h"

#include "Kismet/KismetMathLibrary.h"

UFA_GI::UFA_GI()
{
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_GAME(TEXT("/Game/FAContent/ReadOnly/Data/FADT_Game.FADT_Game"));
	if (DT_GAME.Succeeded()) _dt_game = DT_GAME.Object;
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_PLANE(TEXT("/Game/FAContent/ReadOnly/Data/FADT_Plane.FADT_Plane"));
	if (DT_PLANE.Succeeded()) _dt_plane = DT_PLANE.Object;
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_OBJECT(TEXT("/Game/FAContent/ReadOnly/Data/FADT_Object.FADT_Object"));
	if (DT_OBJECT.Succeeded()) _dt_object = DT_OBJECT.Object;
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_RIBBON(TEXT("/Game/FAContent/ReadOnly/Data/FADT_Ribbon.FADT_Ribbon"));
	if (DT_RIBBON.Succeeded()) _dt_ribbon = DT_RIBBON.Object;
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_VFX(TEXT("/Game/FAContent/ReadOnly/Data/FADT_VFX.FADT_VFX"));
	if (DT_VFX.Succeeded()) _dt_vfx = DT_VFX.Object;
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_SFX(TEXT("/Game/FAContent/ReadOnly/Data/FADT_SFX.FADT_SFX"));
	if (DT_SFX.Succeeded()) _dt_sfx = DT_SFX.Object;
}

void UFA_GI::GIInit()
{
	_data_game = _dt_game->FindRow<FDataGame>("GAME00001", "0");

	_dt_ribbon->GetAllRows("0", _data_ribbons);
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
FDataVFX* UFA_GI::FindDataVFXByCode(const FString& str_code_vfx)
{
	if (!_dt_vfx) return nullptr;
	return _dt_vfx->FindRow<FDataVFX>(*str_code_vfx, "0");
}
FDataSFX* UFA_GI::FindDataSFXByCode(const FString& str_code_sfx)
{
	if (!_dt_sfx) return nullptr;
	return _dt_sfx->FindRow<FDataSFX>(*str_code_sfx, "0");
}
FDataRibbon* UFA_GI::FindDataRibbonByCode(const FString& str_code_ribbon)
{
	if (!_dt_ribbon) return nullptr;
	return _dt_ribbon->FindRow<FDataRibbon>(*str_code_ribbon, "0");
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
TArray<FDataRibbon*>& UFA_GI::GetDataRibbons() { return _data_ribbons; }