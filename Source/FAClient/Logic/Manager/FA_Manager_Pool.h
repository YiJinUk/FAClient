// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Logic/Manager/FA_Manager_Master.h"
#include "FA_Manager_Pool.generated.h"

class UFA_GI;
class AFA_Plane;
class AFA_Object;

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
	AFA_Object* PoolGetObjectByCode(const FString& str_code_object);
public:
	void PoolInPlane(AFA_Plane* plane);
	void PoolInObject(AFA_Object* object);
private:
	AFA_Plane* PoolOutPlane(const FString& str_code_plane);
	AFA_Object* PoolOutObject(const FString& str_code_object);

private:
	UPROPERTY()
		UFA_GI* _fagi = nullptr;

	FActorSpawnParameters _spawn_param = FActorSpawnParameters();

	TMap<FString, TArray<AFA_Plane*>> _pool_plane;
	TMap<FString, TArray<AFA_Object*>> _pool_object;
};
