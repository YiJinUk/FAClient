// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Object/FA_Object.h"
#include "FA_Gem.generated.h"

/**
 * 
 */
UCLASS()
class FACLIENT_API AFA_Gem : public AFA_Object
{
	GENERATED_BODY()

protected:
	AFA_Gem();

	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* _sm = nullptr;
private:
	UFUNCTION()
		void OnBoxOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
