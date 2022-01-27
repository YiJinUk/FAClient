// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Object/Obstacle/FA_Obstacle.h"
#include "FA_Trap.generated.h"

class UMaterialInstanceDynamic;

/**
 * 
 */
UCLASS()
class FACLIENT_API AFA_Trap : public AFA_Obstacle
{
	GENERATED_BODY()

protected:
	AFA_Trap();
	
private:
	UFUNCTION()
		void OnBoxOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	void ObjectPostInitChild(const FDataObject* s_data_object) override;
	void ObjectInitChild(const FLinearColor& s_linear_color) override;
	void ObjectSetPoolActiveChild(const bool b_is_active) override;

	UFUNCTION(BlueprintImplementableEvent)
		UMaterialInstanceDynamic* GetMID();
private:
	UPROPERTY()
		UMaterialInstanceDynamic* _mid_color = nullptr;
	UPROPERTY()
		FLinearColor _color = FLinearColor();
};
