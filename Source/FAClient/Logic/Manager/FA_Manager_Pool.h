// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Logic/Manager/FA_Manager_Master.h"
#include "FA_Manager_Pool.generated.h"

class AFA_Plane;
class UFA_GI;

/**
 * 
 */
UCLASS()
class FACLIENT_API AFA_Manager_Pool : public AFA_Manager_Master
{
	GENERATED_BODY()
public:
	void PoolInit(UFA_GI* fagi);

public:
	AFA_Plane* PoolGetPlaneByCode(const FString& str_code_plane);
public:
	void PoolInPlane(AFA_Plane* plane);
private:
	AFA_Plane* PoolOutPlane(const FString& str_code_plane);

private:
	UPROPERTY()
		UFA_GI* _fagi = nullptr;

	FActorSpawnParameters _spawn_param = FActorSpawnParameters();

	TMap<FString, TArray<AFA_Plane*>> _pool_plane;
};
