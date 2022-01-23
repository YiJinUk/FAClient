// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/FA_SharedStruct.h"
#include "Actor/Object/Obstacle/FA_Obstacle.h"
#include "FA_Wall.generated.h"

class UInstancedStaticMeshComponent;

/**
 * 
 */
UCLASS()
class FACLIENT_API AFA_Wall : public AFA_Obstacle
{
	GENERATED_BODY()
protected:
	AFA_Wall();
	void ObjectSetPoolActiveChild(const bool b_is_active) override;
protected:
	UPROPERTY(BlueprintReadWrite)
		TArray<UStaticMeshComponent*> _smcs;
	UPROPERTY()
		TArray<FVector> _smcs_location;
private:
	void TimerSetPhysicsSMCS();
	UFUNCTION(BlueprintCallable)
		void WallInitSMCsLocation();

	UFUNCTION()
		void OnBoxOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	UPROPERTY()
		FTimerHandle _timer_TimerSetPhysicsSMCS;

};
