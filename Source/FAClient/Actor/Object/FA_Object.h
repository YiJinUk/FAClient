// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/FA_SharedStruct.h"
#include "Actor/FA_Actor.h"
#include "FA_Object.generated.h"

/**
 * 
 */
UCLASS()
class FACLIENT_API AFA_Object : public AFA_Actor
{
	GENERATED_BODY()
	
protected:
	AFA_Object();
	virtual void BeginPlay() override;
protected:
	UPROPERTY(EditAnywhere)
		class USceneComponent* _root_scene = nullptr;
	UPROPERTY(EditAnywhere)
		class UBoxComponent* _box = nullptr;

	UPROPERTY()
		class AFA_GM* _fagm = nullptr;
private:
	


public:
	void ObjectPostInit(const FDataObject* s_data_object);

public:
	const FInfoObject& GetInfoObject();
private:
	UPROPERTY()
		FInfoObject _info_object;
};
