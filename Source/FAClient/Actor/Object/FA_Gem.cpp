// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Object/FA_Gem.h"
#include "Logic/FA_FunctionLibrary.h"
#include "Actor/Player/FA_Player.h"
#include "Logic/FA_GM.h"

#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/RotatingMovementComponent.h"

AFA_Gem::AFA_Gem()
{
	if (_box)
	{
		_box->OnComponentBeginOverlap.AddDynamic(this, &AFA_Gem::OnBoxOverlap);
	}

	_sm = CreateDefaultSubobject<UStaticMeshComponent>("_sm");
	if (_sm)
	{
		_sm->SetupAttachment(_box);
		_sm->SetGenerateOverlapEvents(false);
		_sm->CanCharacterStepUpOn = ECanBeCharacterBase::ECB_No;
		_sm->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	}

	_rotating_movement = CreateDefaultSubobject<URotatingMovementComponent>("_rotating_movement");
}

void AFA_Gem::OnBoxOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	_fagm->ObjectOverlap(this);
}

void AFA_Gem::ObjectSetPoolActiveChild(const bool b_is_active)
{
	_rotating_movement->SetActive(b_is_active);
}