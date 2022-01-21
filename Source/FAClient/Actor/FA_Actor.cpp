// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/FA_Actor.h"

AFA_Actor::AFA_Actor()
{
	PrimaryActorTick.bCanEverTick = true;
}

FVector2D AFA_Actor::GetActorLocation2D()
{
	return FVector2D(GetActorLocation().X, GetActorLocation().Y);
}