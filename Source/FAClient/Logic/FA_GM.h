// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/FA_SharedStruct.h"
#include "GameFramework/GameModeBase.h"
#include "FA_GM.generated.h"

class UFA_GI;
class AFA_PC;
class AFA_Player;
class AFA_Manager_Pool;
class AFA_Plane;
class AFA_Object;

/**
 * 
 */
UCLASS()
class FACLIENT_API AFA_GM : public AGameModeBase
{
	GENERATED_BODY()

#pragma region Debug
public:
	UFUNCTION(BlueprintCallable)
		void DebugDeceleration(const int32 i_speed);
#pragma endregion
	
#pragma region Init
protected:
	AFA_GM();
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void BeginPlay() override;
private:
	void GMInit();
#pragma endregion

#pragma region General
private:
	const int64 IdGenerator();
private:
	UPROPERTY()
		UFA_GI* _fagi = nullptr;

	FDataGame* _data_game_cache = nullptr;

	UPROPERTY()
		int64 _id_generator = 0;
#pragma endregion

#pragma region Tick
protected:
	virtual void Tick(float DeltaTime) override;
private:
	void TickCheckMoveFloor();
	void TickCheckGameOver();
#pragma endregion

#pragma region Manager
private:
	UPROPERTY()
		AFA_Manager_Pool* _manager_pool = nullptr;
#pragma endregion

#pragma region Game,Stage
public:
	void GameRestart();
private:
	//플레이어캐릭터 위치의 X값 입니다
	UPROPERTY()
		int32 _pre_spawn_plane_loc_x = 0;
	UPROPERTY()
		FInfoGame _info_game;
#pragma endregion

#pragma region Plane
private:
	void PlaneInitLocation();
private:
	UPROPERTY()
		TArray<AFA_Plane*> _spawn_planes;
	//옮겨야할 바닥 인덱스
	UPROPERTY()
		int32 _plane_index_move = -1;
	//바닥이 옮겨진 횟수
	UPROPERTY()
		int32 _plane_move_count = -1;
#pragma endregion

#pragma region Object
public:
	void ObjectOverlap(const EObjectType e_obj_type);

private:
	const FString CalcSpawnObjectCode();
private:
	UPROPERTY()
		TArray<AFA_Object*> _spawn_objects;

	UPROPERTY()
		TArray<FString> _prob_obstacles;
	UPROPERTY()
		TArray<FString> _prob_chances;
#pragma endregion

#pragma region Player
public:
	/*게임초반 플레이어를 날립니다*/
	UFUNCTION(BlueprintCallable)
		void ShotPlayer();

	void SetPowerProgressMaterial(UMaterialInstanceDynamic* mid_power_progress);
private:
	UPROPERTY()
		AFA_PC* _pc = nullptr;
	UPROPERTY()
		AFA_Player* _player = nullptr;

	UPROPERTY()
		FVector _player_base_location = FVector::ZeroVector;

	UPROPERTY()
		UMaterialInstanceDynamic* _power_progress = nullptr;
	UPROPERTY()
		float _power_progress_value = 0.f;
	UPROPERTY()
		bool _is_add_power_value = true;
#pragma endregion

};
