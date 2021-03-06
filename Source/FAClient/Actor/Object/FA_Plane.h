// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Actor/Object/FA_Object.h"
#include "FA_Plane.generated.h"

class AFA_Object;

/**
 * 
 */
UCLASS()
class FACLIENT_API AFA_Plane : public AFA_Object
{
	GENERATED_BODY()
	
protected:
	AFA_Plane();

protected:
	UPROPERTY(EditAnywhere)
		class USceneComponent* _spawn_object_location = nullptr;

public:
	void PlaneInit(const FVector& v_loc);
	void PlaneSpawn(const FVector& v_loc, AFA_Object* object_spawn);

	void AddGem(AFA_Object* gem);

	AFA_Object* GetSpawnObject();
	const FVector GetObjectLocation();
	TArray<AFA_Object*, TInlineAllocator<30>>& GetSpawnGems();
private:
	UPROPERTY()
		AFA_Object* _spawn_object = nullptr;

	TArray<AFA_Object*, TInlineAllocator<30>> _spawn_gems;
};
