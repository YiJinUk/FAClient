// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Object/Chance/FA_Chance.h"
#include "FA_Jump.generated.h"

/**
 * 
 */
UCLASS()
class FACLIENT_API AFA_Jump : public AFA_Chance
{
	GENERATED_BODY()

protected:
	AFA_Jump();

private:
	UFUNCTION()
		void OnBoxOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
