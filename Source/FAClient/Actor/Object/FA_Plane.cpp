// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Object/FA_Plane.h"
#include "FA_Object.h"

AFA_Plane::AFA_Plane()
{
	PrimaryActorTick.bCanEverTick = false;

	_spawn_object_location = CreateDefaultSubobject<USceneComponent>("_spawn_object_location");
	if (_spawn_object_location)
	{
		_spawn_object_location->SetupAttachment(GetRootComponent());
	}
}

void AFA_Plane::PlaneInit(const FVector& v_loc)
{
	SetActorLocation(v_loc);
	_spawn_object = nullptr;
}
void AFA_Plane::PlaneSpawn(const FVector& v_loc, AFA_Object* object_spawn)
{
	SetActorLocation(v_loc);
	if (object_spawn)
	{
		object_spawn->SetActorLocation(_spawn_object_location->GetComponentLocation());
		_spawn_object = object_spawn;
	}
}

void AFA_Plane::AddGem(AFA_Object* gem)
{
	_spawn_gems.Add(gem);
}

AFA_Object* AFA_Plane::GetSpawnObject() { return _spawn_object; }
const FVector AFA_Plane::GetObjectLocation() { return _spawn_object_location->GetComponentLocation(); }
TArray<AFA_Object*, TInlineAllocator<30>>& AFA_Plane::GetSpawnGems() { return _spawn_gems; }