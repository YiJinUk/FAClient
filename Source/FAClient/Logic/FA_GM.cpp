// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/FA_GM.h"
#include "FA_GI.h"
#include "FA_PC.h"
#include "FA_FunctionLibrary.h"
#include "Manager/FA_Manager_Pool.h"
#include "Manager/FA_Manager_SaveLoad.h"
#include "Actor/Player/FA_Player.h"
#include "Actor/Object/FA_Plane.h"
#include "Actor/Object/FA_Object.h"

#include "Kismet/GameplayStatics.h"

AFA_GM::AFA_GM()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AFA_GM::DebugDeceleration(const int32 i_speed)
{
	if (_player)
	{
		_player->PlayerSetSpeed(i_speed);
	}
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
	_manager_saveload = wld->SpawnActor<AFA_Manager_SaveLoad>(s_param); // 풀링 매니저

	_manager_pool->PoolInit(_fagi);

	/*오브젝트 생성확률 초기화*/
	for (const FDataObjectProb& s_data_obj_prob : _data_game_cache->GetProbObstacles())
	{
		for (int32 i = 0, i_len = s_data_obj_prob.GetObjectProb(); i < i_len; ++i)
		{
			_prob_obstacles.Add(s_data_obj_prob.GetCode());
		}
	}
	for (const FDataObjectProb& s_data_obj_prob : _data_game_cache->GetProbChances())
	{
		for (int32 i = 0, i_len = s_data_obj_prob.GetObjectProb(); i < i_len; ++i)
		{
			_prob_chances.Add(s_data_obj_prob.GetCode());
		}
	}

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

	/*세이브파일 로드*/
	GameLoad();

	/*플레이어컨트롤러 초기화*/
	_pc->PCInit(this);
}

void AFA_GM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (_info_game.game_status == EGameStatus::TITLE && _power_progress)
	{
		if (_is_add_power_value)
		{
			_power_progress_value += DeltaTime;
			if (_power_progress_value >= 1.f)
				_is_add_power_value = false;
		}
		else
		{
			_power_progress_value -= DeltaTime;
			if (_power_progress_value <= 0.f)
				_is_add_power_value = true;
		}
		
		_power_progress->SetScalarParameterValue("Progress", _power_progress_value);
	}

	if (_info_game.game_status == EGameStatus::PLAY)
	{
		/*바닥 생성(이동) 검사*/
		TickCheckMoveFloor();

		TickCheckGameOver();
	}
}

void AFA_GM::TickCheckMoveFloor()
{
	if (_player->GetActorLocation().X - _pre_spawn_plane_loc_x >= _data_game_cache->GetPlaneLength())
	{
		/*바닥 이동*/
		++_plane_move_count;
		++_plane_index_move;

		/*이동해야할 바닥위치값을 구합니다*/
		_pre_spawn_plane_loc_x = _player->GetActorLocation().X;

		if (_plane_index_move >= _data_game_cache->GetPlaneBaseSpawnCount())
			_plane_index_move = 0;

		/*이동해야할 바닥이 오브젝트를 가지고 있다면 풀링합니다*/
		AFA_Plane* plane = _spawn_planes[_plane_index_move];
		if (plane->GetSpawnObject())
		{
			for (int32 i = _spawn_objects.Num() - 1; i >= 0; --i)
			{
				if (_spawn_objects[i]->GetInfoObject().id == plane->GetSpawnObject()->GetInfoObject().id)
					_spawn_objects.RemoveAtSwap(i);
			}
			_manager_pool->PoolInObject(plane->GetSpawnObject());
		}

		/*새로운 오브젝트 생성*/
		AFA_Object* object_spawn = _manager_pool->PoolGetObjectByCode(CalcSpawnObjectCode());
		object_spawn->ObjectInit(IdGenerator());
		_spawn_objects.Add(object_spawn);

		/*이동해야할 바닥 초기화*/
		plane->PlaneSpawn(FVector((_plane_move_count + _data_game_cache->GetPlaneBaseSpawnCount()) * _data_game_cache->GetPlaneLength(), 0.f, 0.f), object_spawn);
	}

	
}

void AFA_GM::TickCheckGameOver()
{
	if (_player->PlayerGetSpeed() <= 0 || _player->GetActorLocation().Z <= -300.f)
	{
		GameOver();
	}
}

void AFA_GM::GameRestart()
{
	/*플레이어 캐릭터 초기화*/
	_player->PlayerMovementSetActive(false);
	_player->SetActorLocation(_player_base_location);

	/*오브젝트 풀링*/
	for (AFA_Object* object : _spawn_objects)
	{
		_manager_pool->PoolInObject(object);
	}
	_spawn_objects.Empty(50);

	/*바닥 풀링*/
	PlaneInitLocation();

	/*변수 초기화*/
	_plane_index_move = -1;
	_plane_move_count = -1;
	_pre_spawn_plane_loc_x = _player_base_location.X;
	_info_game.game_status = EGameStatus::TITLE;
}
void AFA_GM::GameOver()
{
	_info_game.game_status = EGameStatus::GAMEOVER;
	if (_info_game.best_score < _player->GetActorLocation().X)
	{
		/*신기록 달성*/
		_info_game.best_score = _player->GetActorLocation().X;
		_info_game.gem += 1;
	}
	else
	{
		/*신기록 달성 실패*/
	}
	
	GameSave();
	_pc->PCGameOver();
}

void AFA_GM::ShotPlayer()
{
	_player->PlayerMovementSetActive(true);
	_player->PlayerSetVelocity(_data_game_cache->GetPlayerBaseAngle() * _power_progress_value);

	_info_game.game_status = EGameStatus::PLAY;
}

void AFA_GM::ObjectOverlap(const EObjectType e_obj_type)
{
	switch (e_obj_type)
	{
	case EObjectType::TRAP:
		_player->PlayerAddSpeed(_data_game_cache->GetObstacleTrapAddSpeed());
		break;
	case EObjectType::WALL:
		//ObstacleWallTapTimingStart();
		break;
	case EObjectType::HOLE:
		_player->PlayerAddSpeed(0.f);
		break;
	case EObjectType::JUMP:
		ChanceJumpFeverTimingStart();
		break;
	default:
		break;
	}
}

void AFA_GM::ObstacleWallTapTimingStart()
{
	//게임속도 감소
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), _data_game_cache->GetObstacleWallSlowRate());

	//피버종료 타이머 시작
	GetWorldTimerManager().SetTimer(_timer_TimerObstacleWallTapTimingEnd, this, &AFA_GM::TimerObstacleWallTapTimingEnd, _data_game_cache->GetObstacleWallTapTiming() * _data_game_cache->GetObstacleWallSlowRate(), false);

	//UI
	_pc->PCUIObstacleWallTap();
}
void AFA_GM::TimerObstacleWallTapTimingEnd()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);
}

void AFA_GM::ChanceJumpFeverTimingStart()
{
	/*피버 타이밍이 발동되었습니다*/

	//게임속도 감소
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), _data_game_cache->GetChanceJumpFeverSlotRate());

	//피버종료 타이머 시작
	GetWorldTimerManager().SetTimer(_timer_TimerChanceJumpFeverFailed, this, &AFA_GM::TimerChanceJumpFeverFailed, _data_game_cache->GetChanceJumpFeverTiming() * _data_game_cache->GetChanceJumpFeverSlotRate(), false);

	//UI
	_pc->PCUIChanceJumpFever();
}

void AFA_GM::TimerChanceJumpFeverFailed()
{
	/*피버를 작동하지 못했습니다*/

	//게임속도 원래대로
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);

	_player->PlayerMovementJump(_data_game_cache->GetChanceJumpAddSpeed(), _data_game_cache->GetChanceJumpAddVelocityZ());

	_pc->PCFeverFailed();
}

void AFA_GM::FeverSuccess()
{
	/*피버 발동에 성공했습니다*/

	//게임속도 원래대로
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);

	//피버종료타이머 취소
	GetWorldTimerManager().PauseTimer(_timer_TimerChanceJumpFeverFailed);

	_player->PlayerMovementJump(_data_game_cache->GetChanceJumpAddSpeed() * _data_game_cache->GetChanceJumpAddFever(), _data_game_cache->GetChanceJumpAddVelocityZ() * _data_game_cache->GetChanceJumpAddFever());
}

const FString AFA_GM::CalcSpawnObjectCode()
{
	//_fagi->IsPassProbByInt()
	//return FString();

	/*장애물을 설치할지 찬스를 설치할지*/
	if (_fagi->IsPassProbByInt(_data_game_cache->GetObjectProbObstacle()))
	{
		/*장애물 설치*/
		/*랜덤한 장애물의 코드를 리턴합니다*/
		return _prob_obstacles[_fagi->GetRandomByInt(0, _prob_obstacles.Num() - 1)];
	}
	else
	{
		/*찬스 설치*/
		/*랜덤한 찬스의 코드를 리턴합니다*/
		return _prob_chances[_fagi->GetRandomByInt(0, _prob_chances.Num() - 1)];
	}
}

void AFA_GM::PlaneInitLocation()
{
	_plane_move_count = -1;
	AFA_Plane* plane = nullptr;
	for (int32 i = 0, i_len = _spawn_planes.Num(); i < i_len; ++i)
	{
		++_plane_move_count;
		plane = _spawn_planes[i];
		if (i >= _data_game_cache->GetPlaneBaseSpawnObject())
		{
			/*새로운 오브젝트 생성*/
			AFA_Object* object_spawn = _manager_pool->PoolGetObjectByCode(CalcSpawnObjectCode());
			object_spawn->ObjectInit(IdGenerator());
			_spawn_objects.Add(object_spawn);

			/*이동해야할 바닥 초기화*/
			plane->PlaneSpawn(FVector(_plane_move_count * _data_game_cache->GetPlaneLength(), 0.f, 0.f), object_spawn);
		}
		else
		{
			plane->PlaneSpawn(FVector(_plane_move_count * _data_game_cache->GetPlaneLength(), 0.f, 0.f), nullptr);
		}
	}
	
	_plane_move_count = -1;
}

void AFA_GM::GameSave()
{
	_manager_saveload->SaveStart(_info_game);
}
void AFA_GM::GameLoad()
{
	_manager_saveload->LoadStart(_info_game);
}

const int64 AFA_GM::IdGenerator() { return ++_id_generator; }

void AFA_GM::SetPowerProgressMaterial(UMaterialInstanceDynamic* mid_power_progress) { _power_progress = mid_power_progress; }