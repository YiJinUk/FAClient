// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/FA_GM.h"
#include "FA_GI.h"
#include "FA_PC.h"
#include "FA_FunctionLibrary.h"
#include "Manager/FA_Manager_Pool.h"
#include "Actor/Player/FA_Player.h"
#include "Actor/Object/FA_Plane.h"
#include "Actor/Object/FA_Object.h"

#include "Kismet/GameplayStatics.h"

AFA_GM::AFA_GM()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AFA_GM::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
	/*앱을 최초로 실행시켰습니다 초기화를 진행합니다*/
	_pc = Cast<AFA_PC>(NewPlayer);
}

void AFA_GM::BeginPlay()
{
	Super::BeginPlay();

	GMInit();
}

void AFA_GM::GMInit()
{
	UWorld* wld = GetWorld();

	/*게임 인스턴스 초기화*/
	_fagi = GetWorld()->GetGameInstance<UFA_GI>();
	_fagi->GIInit();

	/*자주 사용하는 게임데이터를 캐싱합니다*/
	_data_game_cache = _fagi->GetDataGame();

	TArray<AActor*> arr_found_actor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFA_Player::StaticClass(), arr_found_actor);
	if (arr_found_actor.Num() >= 1)
	{
		_player = Cast<AFA_Player>(arr_found_actor[0]);
		_player->PlayerPostInit();
	}

	/*매니저클래스 생성*/
	FActorSpawnParameters s_param;
	s_param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	_manager_pool = wld->SpawnActor<AFA_Manager_Pool>(s_param); // 풀링 매니저

	_manager_pool->PoolInit(_fagi);

	/*바닥 초기화*/
	for (int32 i = 0, i_len = _data_game_cache->GetPlaneBaseSpawnCount(); i < i_len; ++i)
	{
		AFA_Plane* plane = _manager_pool->PoolGetPlaneByCode("PLANE00001");
		_spawn_planes.Add(plane);
	}
	PlaneInitLocation();

	/*플레이어 초기화*/
	_player_base_location = _player->GetActorLocation();
	_pre_spawn_plane_loc_x = _player_base_location.X;

	/*플레이어컨트롤러 초기화*/
	_pc->PCInit(this);
}

void AFA_GM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_info_game.game_status == EGameStatus::PLAY)
	{
		/*바닥 생성 검사*/
		if (_player->GetActorLocation().X - _pre_spawn_plane_loc_x >= _data_game_cache->GetPlaneLength())
		{
			++_plane_move_count;
			++_plane_index_move;

			/*바닥 생성*/
			_pre_spawn_plane_loc_x = _player->GetActorLocation().X;

			if (_plane_index_move >= _data_game_cache->GetPlaneBaseSpawnCount())
				_plane_index_move = 0;

			//_spawn_planes[_plane_index_move]->SetActorLocation(FVector((_plane_move_count + _data_game_cache->GetPlaneBaseSpawnCount()) * _data_game_cache->GetPlaneLength(), 0.f, 0.f));
			AFA_Object* object_spawn = _manager_pool->PoolGetObjectByCode(CalcSpawnObjectCode());
			_spawn_planes[_plane_index_move]->PlaneInit(FVector((_plane_move_count + _data_game_cache->GetPlaneBaseSpawnCount()) * _data_game_cache->GetPlaneLength(), 0.f, 0.f), object_spawn);
		}

		if (_player->PlayerGetSpeed() <= 0)
		{
			//GameOver
			_info_game.game_status = EGameStatus::GAMEOVER;
			_pc->PCGameOver();
		}
	}
}

void AFA_GM::GameRestart()
{
	/*플레이어 캐릭터 초기화*/
	_player->PlayerMovementSetActive(false);
	_player->SetActorLocation(_player_base_location);

	/*바닥 풀링*/
	PlaneInitLocation();

	/*변수 초기화*/
	_plane_index_move = -1;
	_plane_move_count = -1;
	_pre_spawn_plane_loc_x = _player_base_location.X;
	_info_game.game_status = EGameStatus::TITLE;
}

void AFA_GM::ShotPlayer()
{
	_player->PlayerMovementSetActive(true);
	_player->PlayerSetSpeed(5000);
	_player->PlayerSetVelocity(FVector(3000, 0, 1000));

	_info_game.game_status = EGameStatus::PLAY;
}

void AFA_GM::ObjectOverlap(const EObjectType e_obj_type)
{
	switch (e_obj_type)
	{
	case EObjectType::TRAP:
		_player->PlayerAddSpeed(_data_game_cache->GetObstacleTrapAddSpeed());
		break;
	default:
		break;
	}
}

const FString AFA_GM::CalcSpawnObjectCode()
{
	//_fagi->IsPassProbByInt()
	//return FString();
	return "OBJ00001";
}

void AFA_GM::PlaneInitLocation()
{
	_plane_index_move = -1;
	for (AFA_Plane* plane : _spawn_planes)
	{
		plane->SetActorLocation(FVector(_data_game_cache->GetPlaneLength() * ++_plane_index_move, 0.f, 0.f));
	}
	_plane_index_move = -1;
}