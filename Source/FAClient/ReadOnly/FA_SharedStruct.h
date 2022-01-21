// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Runtime/CoreUObject/Public/Templates/SubclassOf.h"
#include "UObject/NoExportTypes.h"
#include "FA_SharedStruct.generated.h"

class AFA_Plane;

/**
 * 
 */
UCLASS()
class FACLIENT_API UFA_SharedStruct : public UObject
{
	GENERATED_BODY()
	
};

USTRUCT(BlueprintType)
struct FDataGame : public FTableRowBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, Category = "Stage")
		int32 _start_plane_count = 3;
	UPROPERTY(EditAnywhere, Category = "Stage")
		int32 _spawn_plane_distance = 5000;
	
	UPROPERTY(EditAnywhere, Category = "Plane")
		int32 _plane_length = 5000;

public:
	FORCEINLINE const int32 GetStartPlaneCount() const { return _start_plane_count; }
	FORCEINLINE const int32 GetSpawnPlaneDistance() const { return _spawn_plane_distance; }

	FORCEINLINE const int32 GetPlaneLength() const { return _plane_length; }
};

USTRUCT(BlueprintType)
struct FDataPlane : public FTableRowBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General")
		TSubclassOf<AFA_Plane> _class_plane;

public:
	FORCEINLINE const TSubclassOf<AFA_Plane>& GetClassPlane() const { return _class_plane; }
};