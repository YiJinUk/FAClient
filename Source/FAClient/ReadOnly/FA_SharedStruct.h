// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Runtime/CoreUObject/Public/Templates/SubclassOf.h"
#include "UObject/NoExportTypes.h"
#include "FA_SharedStruct.generated.h"

class AFA_Plane;
class AFA_Object;

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

UENUM()
enum class EObjectType : uint8
{
	NO,
	TRAP,
	HOLE,
};

USTRUCT(BlueprintType)
struct FDataObjectProb
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, Category = "General")
		FString _code = "0";
	UPROPERTY(EditAnywhere, Category = "General")
		int32 _obj_prob = 0;

public:
	FORCEINLINE const FString& GetCode() const { return _code; }
	FORCEINLINE const int32 GetObjectProb() const { return _obj_prob; }
};

USTRUCT(BlueprintType)
struct FDataGame : public FTableRowBase
{
	GENERATED_BODY()
protected:	
	UPROPERTY(EditAnywhere, Category = "Player")
		float _player_gravity = 0.5f;
	UPROPERTY(EditAnywhere, Category = "Player")
		FVector _player_base_angle = FVector::ZeroVector;
	UPROPERTY(EditAnywhere, Category = "Player")
		int32 _player_base_max_power = 10000;

	UPROPERTY(EditAnywhere, Category = "Plane")
		int32 _plane_base_spawn_count = 5;
	UPROPERTY(EditAnywhere, Category = "Plane")
		int32 _plane_length = 5000;

	UPROPERTY(EditAnywhere, Category = "ObjectProb")
		int32 _object_prob_obstacle = 50;
	UPROPERTY(EditAnywhere, Category = "ObjectProb")
		int32 _object_prob_chance = 50;
	UPROPERTY(EditAnywhere, Category = "ObjectProb")
		TArray<FDataObjectProb> _prob_obstacles;
	UPROPERTY(EditAnywhere, Category = "ObjectProb")
		TArray<FDataObjectProb> _prob_chances;

	UPROPERTY(EditAnywhere, Category = "Obstacle")
		float _obstacle_trap_add_speed = 0.f;
public:
	FORCEINLINE const float GetPlayerGravity() const { return _player_gravity; }
	FORCEINLINE const FVector GetPlayerBaseAngle() const { return _player_base_angle; }
	FORCEINLINE const int32 GetPlayerBaseMaxPower() const { return _player_base_max_power; }

	FORCEINLINE const int32 GetPlaneBaseSpawnCount() const { return _plane_base_spawn_count; }
	FORCEINLINE const int32 GetPlaneLength() const { return _plane_length; }

	FORCEINLINE const int32 GetObjectProbObstacle() const { return _object_prob_obstacle; }
	FORCEINLINE const int32 GetObjectProbChance() const { return _object_prob_chance; }
	FORCEINLINE const TArray<FDataObjectProb>& GetProbObstacles() const { return _prob_obstacles; }
	FORCEINLINE const TArray<FDataObjectProb>& GetProbChances() const { return _prob_chances; }

	FORCEINLINE const float GetObstacleTrapAddSpeed() const { return _obstacle_trap_add_speed; }
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
struct FDataObject : public FTableRowBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General")
		TSubclassOf<AFA_Object> _class_object;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General")
		FString _code = "0";
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General")
		bool _is_obstacle = false;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General")
		EObjectType _obj_type = EObjectType::NO;
public:
	FORCEINLINE const TSubclassOf<AFA_Object>& GetClassObject() const { return _class_object; }
	FORCEINLINE const FString GetCode() const { return _code; }
	FORCEINLINE const bool GetIsObstacle() const { return _is_obstacle; }
	FORCEINLINE const EObjectType GetObjectType() const { return _obj_type; }
};


USTRUCT(BlueprintType)
struct FInfoGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
		EGameStatus game_status = EGameStatus::TITLE;
};

USTRUCT(BlueprintType)
struct FInfoObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
		FString code = "0";
	UPROPERTY()
		EObjectType obj_type = EObjectType::NO;
};