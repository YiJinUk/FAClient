// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FA_Actor.generated.h"

UCLASS()
class FACLIENT_API AFA_Actor : public AActor
{
	GENERATED_BODY()
	
public:	
	AFA_Actor();

	FVector2D GetActorLocation2D();

};
