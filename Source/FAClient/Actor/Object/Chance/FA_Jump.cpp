// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Object/Chance/FA_Jump.h"
#include "Actor/Player/FA_Player.h"
#include "Logic/FA_GM.h"

#include "Components/BoxComponent.h"

AFA_Jump::AFA_Jump()
{
	if (_box)
	{
		_box->OnComponentBeginOverlap.AddDynamic(this, &AFA_Jump::OnBoxOverlap);
	}
}

void AFA_Jump::OnBoxOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	_fagm->ObjectOverlap(this);
}

