// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Object/Obstacle/FA_Hole.h"
#include "Actor/Player/FA_Player.h"
#include "Logic/FA_GM.h"

#include "Components/BoxComponent.h"

AFA_Hole::AFA_Hole()
{
	if (_box)
	{
		_box->OnComponentBeginOverlap.AddDynamic(this, &AFA_Hole::OnBoxOverlap);
	}
}

void AFA_Hole::OnBoxOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	_fagm->ObjectOverlap(this);
}
