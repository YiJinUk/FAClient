// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/Manager/FA_Manager_VFX.h"
#include "Logic/FA_GI.h"

#include "Kismet/GameplayStatics.h"

void AFA_Manager_VFX::VFXInit(UFA_GI* fagi)
{
	_data_vfx_cache = fagi->FindDataVFXByCode("VFX00001");
}

void AFA_Manager_VFX::VFXStart(const EVFXType e_vfx_type, const FVector& v_loc)
{
	switch (e_vfx_type)
	{
	case EVFXType::GEM:
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), _data_vfx_cache->GetObtainGem(), v_loc);
		break;
	default:
		break;
	}
}