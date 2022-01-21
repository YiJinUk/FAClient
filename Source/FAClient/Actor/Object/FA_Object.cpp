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
}

const FInfoObject& AFA_Object::GetInfoObject() { return _info_object; }