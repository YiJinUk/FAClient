// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Object/Obstacle/FA_Obstacle.h"

#include "Components/BoxComponent.h"

AFA_Obstacle::AFA_Obstacle()
{
	PrimaryActorTick.bCanEverTick = true;

	if (_box)
	{
		_box->SetCollisionResponseToChannel(ECollisionChannel::ECC_Vehicle, ECollisionResponse::ECR_Overlap);
	}
}