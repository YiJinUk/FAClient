// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Object/FA_Object.h"
#include "Logic/FA_GM.h"

#include "Components/BoxComponent.h"

AFA_Object::AFA_Object()
{
	_root_scene = CreateDefaultSubobject<USceneComponent>("_root_scene");
	if (_root_scene)
	{
		RootComponent = _root_scene;
	}

	_box = CreateDefaultSubobject<UBoxComponent>("_box");
	if (_box)
	{
		_box->SetupAttachment(GetRootComponent());
		_box->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
		_box->SetGenerateOverlapEvents(false);
	}
}


void AFA_Object::BeginPlay()
{
	Super::BeginPlay();
	_fagm = GetWorld()->GetAuthGameMode<AFA_GM>();
}
void AFA_Object::ObjectPostInit(const FDataObject* s_data_object)
{
	_info_object.code = s_data_object->GetCode();
	_info_object.obj_type = s_data_object->GetObjectType();

	ObjectPostInitChild(s_data_object);
}
void AFA_Object::ObjectPostInitChild(const FDataObject* s_data_object)
{
	//override
}

void AFA_Object::ObjectInit(const int64 i_id)
{
	_info_object.id = i_id;
	ObjectSetPoolActive(true);
}

void AFA_Object::ObjectSetPoolActive(const bool b_is_active)
{
	_box->SetGenerateOverlapEvents(b_is_active);

	if (!b_is_active)
	{
		SetActorLocation(FVector(-1000.f, 0.f, 0.f));
	}

	ObjectSetPoolActiveChild(b_is_active);
}

void AFA_Object::ObjectSetPoolActiveChild(const bool b_is_active)
{
	//override
}

const FInfoObject& AFA_Object::GetInfoObject() { return _info_object; }