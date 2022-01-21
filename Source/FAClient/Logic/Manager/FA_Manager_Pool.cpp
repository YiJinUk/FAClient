// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/Manager/FA_Manager_Pool.h"
#include "Logic/FA_GI.h"
#include "Actor/Object/FA_Plane.h"

void AFA_Manager_Pool::PoolInit(UFA_GI* fagi)
{
	_fagi = fagi;
	_spawn_param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
}

AFA_Plane* AFA_Manager_Pool::PoolGetPlaneByCode(const FString& str_code_plane)
{
	return PoolOutPlane(str_code_plane);
}

void AFA_Manager_Pool::PoolInPlane(AFA_Plane* plane)
{
	//monster->MOBSetPoolActive(false);
	//_pool_monster.FindOrAdd(monster->GetInfoMonster().code).Add(monster);
	_pool_plane.FindOrAdd("PLANE00001").Add(plane);
}

AFA_Plane* AFA_Manager_Pool::PoolOutPlane(const FString& str_code_plane)
{
	TArray<AFA_Plane*>* arr_pool_plane = _pool_plane.Find(str_code_plane);

	if (!arr_pool_plane || arr_pool_plane->Num() <= 0)
	{
		const FDataPlane* s_data_monster = _fagi->FindDataPlaneByCode(str_code_plane);
		AFA_Plane* plane_spawn = GetWorld()->SpawnActor<AFA_Plane>(s_data_monster->GetClassPlane(), _spawn_param); // 풀링 매니저
		//monster_spawn->MOBPostInit(s_data_monster);
		return plane_spawn;
	}
	else
	{
		return arr_pool_plane->Pop();
	}
}