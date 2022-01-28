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
	TITLE, // 게임시작전 UI화면 입니다
	PLAY, // 웨이브중
	CLEAR, // 웨이브클리어
	GAMEOVER, // 게임오버
};

UENUM()
enum class EObjectType : uint8
{
	NO,
	GEM,
	TRAP,
	WALL,
	HOLE,
	JUMP,
};

UENUM()
enum class ERGBType : uint8
{
	R = 0,
	G = 1,
	B = 2,
	BLACK = 3,
	WHITE = 4,
};

UENUM()
enum class EInteractType : uint8
{
	FEVER,
	JUMP,
	SLOW,
};

UENUM()
enum class EVFXType : uint8
{
	GEM,
};
UENUM()
enum class ESFXType : uint8
{
	BACKGROUND,
	GEM,
	POWER,
	JUMP,
	FEVER,
	FEVER_TIMING,
	FEVER_FAILED,
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
	UPROPERTY(EditAnywhere, Category = "Player")
		int32 _player_camera_max_location_z = 0;

	UPROPERTY(EditAnywhere, Category = "PlayerPower")
		int32 _player_power_cost = 0;
	UPROPERTY(EditAnywhere, Category = "PlayerPower")
		int32 _player_power_count_max = 0;

	UPROPERTY(EditAnywhere, Category = "Plane")
		int32 _plane_base_spawn_count = 5;
	UPROPERTY(EditAnywhere, Category = "Plane")
		int32 _plane_base_spawn_object = 5;
	UPROPERTY(EditAnywhere, Category = "Plane")
		int32 _plane_length = 5000;

	UPROPERTY(EditAnywhere, Category = "ObjectProb")
		int32 _object_prob_r = 25;
	UPROPERTY(EditAnywhere, Category = "ObjectProb")
		int32 _object_prob_g = 25;
	UPROPERTY(EditAnywhere, Category = "ObjectProb")
		int32 _object_prob_b = 25;
	UPROPERTY(EditAnywhere, Category = "ObjectProb")
		int32 _object_prob_black = 25;

	UPROPERTY(EditAnywhere, Category = "GemProb")
		int32 _gem_prob = 20;

	UPROPERTY(EditAnywhere, Category = "ObjectColor")
		FLinearColor _object_color_r = FLinearColor();
	UPROPERTY(EditAnywhere, Category = "ObjectColor")
		FLinearColor _object_color_g = FLinearColor();
	UPROPERTY(EditAnywhere, Category = "ObjectColor")
		FLinearColor _object_color_b = FLinearColor();
	UPROPERTY(EditAnywhere, Category = "ObjectColor")
		FLinearColor _object_color_black = FLinearColor();


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
	UPROPERTY(EditAnywhere, Category = "Obstacle")
		float _obstacle_wall_tap_timing = 0.f;
	UPROPERTY(EditAnywhere, Category = "Obstacle")
		float _obstacle_wall_tap_slow_rate = 0.f;

	UPROPERTY(EditAnywhere, Category = "Chance")
		float _chance_jump_add_speed = 0.f;
	UPROPERTY(EditAnywhere, Category = "Chance")
		float _chance_jump_add_velocity_z = 0.f;
	UPROPERTY(EditAnywhere, Category = "Chance")
		float _chance_jump_fever_add_speed = 0.f;
	UPROPERTY(EditAnywhere, Category = "Chance")
		float _chance_jump_fever_add_velocity_z = 0.f;
	//점프대에 닿았을때 변수시간안에 탭해야 피버가 발동합니다
	UPROPERTY(EditAnywhere, Category = "Chance")
		float _chance_jump_fever_timing = 2.f;
	//피버타이밍때 게임속도가 해당 값만큼 느려집니다
	UPROPERTY(EditAnywhere, Category = "Chance")
		float _chance_jump_fever_slow_rate = 0.1f;

	UPROPERTY(EditAnywhere, Category = "Gem")
		int32 _gem_row = 3;
	UPROPERTY(EditAnywhere, Category = "Gem")
		int32 _gem_column = 9;
	UPROPERTY(EditAnywhere, Category = "Gem")
		int32 _gem_loc_z = 300;
public:
	FORCEINLINE const float GetPlayerGravity() const { return _player_gravity; }
	FORCEINLINE const FVector GetPlayerBaseAngle() const { return _player_base_angle; }
	FORCEINLINE const int32 GetPlayerBaseMaxPower() const { return _player_base_max_power; }
	FORCEINLINE const int32 GetPlayerCameraMaxLocationZ() const { return _player_camera_max_location_z; }
	FORCEINLINE const int32 GetPlayerPowerCost() const { return _player_power_cost; }
	FORCEINLINE const int32 GetPlayerPowerCountMax() const { return _player_power_count_max; }
	
	FORCEINLINE const int32 GetPlaneBaseSpawnCount() const { return _plane_base_spawn_count; }
	FORCEINLINE const int32 GetPlaneBaseSpawnObject() const { return _plane_base_spawn_object; }
	FORCEINLINE const int32 GetPlaneLength() const { return _plane_length; }

	FORCEINLINE const int32 GetObjectProbR() const { return _object_prob_r; }
	FORCEINLINE const int32 GetObjectProbG() const { return _object_prob_g; }
	FORCEINLINE const int32 GetObjectProbB() const { return _object_prob_b; }
	FORCEINLINE const int32 GetObjectProbBlack() const { return _object_prob_black; }

	FORCEINLINE const int32 GetGemProb() const { return _gem_prob; }

	FORCEINLINE const FLinearColor GetObjectColorR() const { return _object_color_r; }
	FORCEINLINE const FLinearColor GetObjectColorG() const { return _object_color_g; }
	FORCEINLINE const FLinearColor GetObjectColorB() const { return _object_color_b; }
	FORCEINLINE const FLinearColor GetObjectColorBlack() const { return _object_color_black; }

	




	FORCEINLINE const int32 GetObjectProbObstacle() const { return _object_prob_obstacle; }
	FORCEINLINE const int32 GetObjectProbChance() const { return _object_prob_chance; }
	FORCEINLINE const TArray<FDataObjectProb>& GetProbObstacles() const { return _prob_obstacles; }
	FORCEINLINE const TArray<FDataObjectProb>& GetProbChances() const { return _prob_chances; }

	FORCEINLINE const float GetObstacleTrapAddSpeed() const { return _obstacle_trap_add_speed; }
	FORCEINLINE const float GetObstacleWallTapTiming() const { return _obstacle_wall_tap_timing; }
	FORCEINLINE const float GetObstacleWallSlowRate() const { return _obstacle_wall_tap_slow_rate; }

	FORCEINLINE const float GetChanceJumpAddSpeed() const { return _chance_jump_add_speed; }
	FORCEINLINE const float GetChanceJumpAddVelocityZ() const { return _chance_jump_add_velocity_z; }
	FORCEINLINE const float GetChanceJumpFeverAddSpeed() const { return _chance_jump_fever_add_speed; }
	FORCEINLINE const float GetChanceJumpFeverAddVelocityZ() const { return _chance_jump_fever_add_velocity_z; }
	FORCEINLINE const float GetChanceJumpFeverTiming() const { return _chance_jump_fever_timing; }
	FORCEINLINE const float GetChanceJumpFeverSlotRate() const { return _chance_jump_fever_slow_rate; }

	FORCEINLINE const int32 GetGemRow() const { return _gem_row; }
	FORCEINLINE const int32 GetGemColumn() const { return _gem_column; }
	FORCEINLINE const int32 GetGemLocZ() const { return _gem_loc_z; }
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
	FORCEINLINE const FString& GetCode() const { return _code; }
	FORCEINLINE const bool GetIsObstacle() const { return _is_obstacle; }
	FORCEINLINE const EObjectType GetObjectType() const { return _obj_type; }
};

USTRUCT(BlueprintType)
struct FDataRibbon : public FTableRowBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General")
		FString _code = "0";
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General")
		UParticleSystem* _ribbon = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General")
		UTexture2D* _portrait = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General")
		int32 _price = 0;

public:
	FORCEINLINE const FString& GetCode() const { return _code; }
	FORCEINLINE UParticleSystem* GetRibbon() { return _ribbon; }
	FORCEINLINE UTexture2D* GetPortrait() { return _portrait; }
	FORCEINLINE const int32 GetPrice() const { return _price; }

};

USTRUCT(BlueprintType)
struct FDataVFX : public FTableRowBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "General")
		UParticleSystem* _obtain_gem = nullptr;

public:
	FORCEINLINE UParticleSystem* GetObtainGem() { return _obtain_gem; }
};

USTRUCT(BlueprintType)
struct FDataSFX : public FTableRowBase
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level")
		USoundBase* _background = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game")
		USoundBase* _obtain_gem = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game")
		USoundBase* _power = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game")
		USoundBase* _jump = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game")
		USoundBase* _fever = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game")
		USoundBase* _fever_timing = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Game")
		USoundBase* _fever_failed = nullptr;

public:
	FORCEINLINE USoundBase* GetBackGround() { return _background; }

	FORCEINLINE USoundBase* GetObtainGem() { return _obtain_gem; }
	FORCEINLINE USoundBase* GetPower() { return _power; }
	FORCEINLINE USoundBase* GetJump() { return _jump; }
	FORCEINLINE USoundBase* GetFever() { return _fever; }
	FORCEINLINE USoundBase* GetFeverTiming() { return _fever_timing; }
	FORCEINLINE USoundBase* GetFeverFailed() { return _fever_failed; }
};

//USTRUCT(BlueprintType)
//struct FInfoRibbon
//{
//	GENERATED_BODY()
//
//public:
//	UPROPERTY()
//		FString code = "0";
//	UPROPERTY()
//		bool is_buy = false;
//};
//


USTRUCT(BlueprintType)
struct FInfoGame
{
	GENERATED_BODY()

public:
	UPROPERTY()
		EGameStatus game_status = EGameStatus::TITLE;
	UPROPERTY()
		int32 score_best = 0;
	UPROPERTY()
		int32 score_current = 0;
	UPROPERTY()
		int32 gem = 0;
	//이번 게임에서 얻은 gem갯수 입니다
	UPROPERTY()
		int32 gem_add = 0;

	UPROPERTY()
		TArray<FString> code_ribbons;
};

USTRUCT(BlueprintType)
struct FInfoPlayer
{
	GENERATED_BODY()

public:
	UPROPERTY()
		int32 max_velocity_z = 0;
	UPROPERTY()
		int32 power_count_current = 0;
	UPROPERTY()
		ERGBType rgb_type = ERGBType::WHITE;
};

USTRUCT(BlueprintType)
struct FInfoObject
{
	GENERATED_BODY()

public:
	UPROPERTY()
		int64 id = 0;
	UPROPERTY()
		FString code = "0";
	UPROPERTY()
		EObjectType obj_type = EObjectType::NO;
};