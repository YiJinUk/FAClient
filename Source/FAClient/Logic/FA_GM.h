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
	UPROPERTY()
		UFA_GI* _fagi = nullptr;

	FDataGame* _data_game_cache = nullptr;
#pragma endregion

#pragma region Tick
protected:
	virtual void Tick(float DeltaTime) override;
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
		TArray<AFA_Object*> _spawn_object;
#pragma endregion

#pragma region Player
public:
	/*게임초반 플레이어를 날립니다*/
	UFUNCTION(BlueprintCallable)
		void ShotPlayer();
private:
	UPROPERTY()
		AFA_PC* _pc = nullptr;
	UPROPERTY()
		AFA_Player* _player = nullptr;

	UPROPERTY()
		FVector _player_base_location = FVector::ZeroVector;
#pragma endregion

};
