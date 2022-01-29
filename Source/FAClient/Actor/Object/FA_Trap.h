// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Object/FA_Object.h"
#include "FA_Trap.generated.h"

class UMaterialInstanceDynamic;

/**
 * 
 */
UCLASS()
class FACLIENT_API AFA_Trap : public AFA_Object
{
	GENERATED_BODY()

protected:
	AFA_Trap();
	
private:
	UFUNCTION()
		void OnBoxOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	void TrapInit(const FLinearColor& s_linear_color, const ERGBType e_rgb_type);

	const FLinearColor& GetColor();
	const ERGBType GetRGBType();
protected:

	void ObjectPostInitChild(const FDataObject* s_data_object) override;

	UFUNCTION(BlueprintImplementableEvent)
		UMaterialInstanceDynamic* GetMID();
private:
	UPROPERTY()
		UMaterialInstanceDynamic* _mid_color = nullptr;
	UPROPERTY()
		FLinearColor _color = FLinearColor();
	UPROPERTY()
		ERGBType _rgb_type = ERGBType::R;
};
