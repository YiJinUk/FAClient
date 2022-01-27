// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/Manager/FA_Manager_Pool.h"
#include "Logic/FA_GI.h"
#include "Actor/Object/FA_Plane.h"
#include "Actor/Object/FA_Object.h"

void AFA_Manager_Pool::PoolInit(UFA_GI* fagi)
{
	_fagi = fagi;
	_spawn_param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
}

AFA_Plane* AFA_Manager_Pool::PoolGetPlaneByCode(const FString& str_code_plane)
{
	return PoolOutPlane(str_code_plane);
}
AFA_Object* AFA_Manager_Pool::PoolGetObjectByCode(const FString& str_code_object)
{
	return PoolOutObject(str_code_object);
}

void AFA_Manager_Pool::PoolInPlane(AFA_Plane* plane)
{
	if (!plane) return;
	_pool_plane.FindOrAdd("PLANE00001").Add(plane);
}
void AFA_Manager_Pool::PoolInObject(AFA_Object* object)
{
	if (!object) return;
	object->ObjectSetPoolActive(false);
	_pool_object.FindOrAdd(object->GetInfoObject().code).Add(object);
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
AFA_Object* AFA_Manager_Pool::PoolOutObject(const FString& str_code_object)
{
	TArray<AFA_Object*>* arr_pool_object = _pool_object.Find(str_code_object);

	if (!arr_pool_object || arr_pool_object->Num() <= 0)
	{
		const FDataObject* s_data_object = _fagi->FindDataObjectByCode(str_code_object);
		AFA_Object* object_spawn = GetWorld()->SpawnActor<AFA_Object>(s_data_object->GetClassObject(), _spawn_param); // 풀링 매니저
		object_spawn->ObjectPostInit(s_data_object);
		return object_spawn;
	}
	else
	{
		return arr_pool_object->Pop();
	}
}