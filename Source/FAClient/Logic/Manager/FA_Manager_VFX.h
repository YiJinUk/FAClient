// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Logic/Manager/FA_Manager_Master.h"
#include "FA_Manager_VFX.generated.h"

class UFA_GI;

/**
 * 
 */
UCLASS()
class FACLIENT_API AFA_Manager_VFX : public AFA_Manager_Master
{
	GENERATED_BODY()
	
public:
	void VFXInit(UFA_GI* fagi);
private:
	FDataVFX* _data_vfx_cache = nullptr;

public:
	void VFXStart(const EVFXType e_vfx_type, const FVector& v_loc);
};
