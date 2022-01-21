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


UENUM()
enum class EGameStatus : uint8
{
	TITLE, // ���ӽ����� UIȭ�� �Դϴ�
	PLAY, // ���̺���
	CLEAR, // ���̺�Ŭ����
	GAMEOVER, // ���ӿ���
};

USTRUCT(BlueprintType)
struct FDataGame : public FTableRowBase
{
	GENERATED_BODY()
protected:	
	UPROPERTY(EditAnywhere, Category = "Plane")
		int32 _plane_base_spawn_count = 5;
	UPROPERTY(EditAnywhere, Category = "Plane")
		int32 _plane_length = 5000;

public:
	FORCEINLINE const int32 GetPlaneBaseSpawnCount() const { return _plane_base_spawn_count; }
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

USTRUCT(BlueprintType)
struct FInfoGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
		EGameStatus game_status = EGameStatus::TITLE;
};