// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/Manager/FA_Manager_SFX.h"
#include "Logic/FA_GI.h"

#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

void AFA_Manager_SFX::SFXInit(UFA_GI* fagi)
{
	_data_sfx_cache = fagi->FindDataSFXByCode("SFX00001");


	_fever_timing_cache = UGameplayStatics::SpawnSound2D(GetWorld(), _data_sfx_cache->GetFeverTiming());
	_fever_timing_cache->SetPaused(true);
}

void AFA_Manager_SFX::SFXStart(const ESFXType e_sfx_type)
{
	switch (e_sfx_type)
	{
	case ESFXType::BACKGROUND:
		UGameplayStatics::SpawnSound2D(GetWorld(), _data_sfx_cache->GetBackGround())->SetUISound(true);
		break;
	case ESFXType::GEM:
		UGameplayStatics::SpawnSound2D(GetWorld(), _data_sfx_cache->GetObtainGem());
		break;
	case ESFXType::POWER:
		UGameplayStatics::SpawnSound2D(GetWorld(), _data_sfx_cache->GetPower());
		break;
	case ESFXType::JUMP:
		UGameplayStatics::SpawnSound2D(GetWorld(), _data_sfx_cache->GetJump());
		break;
	case ESFXType::FEVER:
		UGameplayStatics::SpawnSound2D(GetWorld(), _data_sfx_cache->GetFever());
		break;
	case ESFXType::FEVER_TIMING:
		_fever_timing_cache->SetPaused(false);
		break;
	case ESFXType::FEVER_FAILED:
		UGameplayStatics::SpawnSound2D(GetWorld(), _data_sfx_cache->GetFeverFailed());
		break;
	case ESFXType::BUY_SUCCESS:
		UGameplayStatics::SpawnSound2D(GetWorld(), _data_sfx_cache->GetBuySuccess());
		break;
	case ESFXType::BUY_FAILED:
		UGameplayStatics::SpawnSound2D(GetWorld(), _data_sfx_cache->GetBuyFailed());
		break;
	default:
		break;
	}
}

void AFA_Manager_SFX::SFXEnd(const ESFXType e_sfx_type)
{
	switch (e_sfx_type)
	{
	case ESFXType::FEVER_TIMING:
		_fever_timing_cache->SetPaused(true);
		break;
	default:
		break;
	}
}