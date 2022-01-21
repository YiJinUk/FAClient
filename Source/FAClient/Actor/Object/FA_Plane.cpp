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

void AFA_Plane::PlaneInit(const FVector v_loc, AFA_Object* object_spawn)
{
	SetActorLocation(v_loc);
	object_spawn->SetActorLocation(_spawn_object_location->GetComponentLocation());
	//object_spawn->SetActorLocation(FVector(10000.f, 0.f, 0.f));
}