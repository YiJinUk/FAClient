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
	/*���� ���ʷ� ������׽��ϴ� �ʱ�ȭ�� �����մϴ�*/
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

	/*���� �ν��Ͻ� �ʱ�ȭ*/
	_fagi = GetWorld()->GetGameInstance<UFA_GI>();
	_fagi->GIInit();

	/*���� ����ϴ� ���ӵ����͸� ĳ���մϴ�*/
	_data_game_cache = _fagi->GetDataGame();

	TArray<AActor*> arr_found_actor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFA_Player::StaticClass(), arr_found_actor);
	if (arr_found_actor.Num() >= 1)
	{
		_player = Cast<AFA_Player>(arr_found_actor[0]);
		_player->PlayerPostInit();
	}

	/*�Ŵ���Ŭ���� ����*/
	FActorSpawnParameters s_param;
	s_param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	_manager_pool = wld->SpawnActor<AFA_Manager_Pool>(s_param); // Ǯ�� �Ŵ���

	_manager_pool->PoolInit(_fagi);

	/*�ٴ� �ʱ�ȭ*/
	for (int32 i = 0, i_len = _data_game_cache->GetPlaneBaseSpawnCount(); i < i_len; ++i)
	{
		AFA_Plane* plane = _manager_pool->PoolGetPlaneByCode("PLANE00001");
		_spawn_planes.Add(plane);
	}
	PlaneInitLocation();

	/*������Ʈ ����Ȯ�� �ʱ�ȭ*/
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

	/*�÷��̾� �ʱ�ȭ*/
	_player_base_location = _player->GetActorLocation();
	_pre_spawn_plane_loc_x = _player_base_location.X;

	/*�÷��̾���Ʈ�ѷ� �ʱ�ȭ*/
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
		/*�ٴ� ���� �˻�*/
		if (_player->GetActorLocation().X - _pre_spawn_plane_loc_x >= _data_game_cache->GetPlaneLength())
		{
			++_plane_move_count;
			++_plane_index_move;

			/*�ٴ� ����*/
			_pre_spawn_plane_loc_x = _player->GetActorLocation().X;

			if (_plane_index_move >= _data_game_cache->GetPlaneBaseSpawnCount())
				_plane_index_move = 0;

			AFA_Object* object_spawn = _manager_pool->PoolGetObjectByCode(CalcSpawnObjectCode());
			object_spawn->ObjectInit();
			AFA_Plane* plane = _spawn_planes[_plane_index_move];
			_manager_pool->PoolInObject(plane->GetSpawnObject());
			plane->PlaneSpawn(FVector((_plane_move_count + _data_game_cache->GetPlaneBaseSpawnCount()) * _data_game_cache->GetPlaneLength(), 0.f, 0.f), object_spawn);
			_spawn_objects.Add(object_spawn);
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
	/*�÷��̾� ĳ���� �ʱ�ȭ*/
	_player->PlayerMovementSetActive(false);
	_player->SetActorLocation(_player_base_location);

	/*�ٴ� Ǯ��*/
	PlaneInitLocation();

	/*������Ʈ Ǯ��*/
	for (AFA_Object* object : _spawn_objects)
	{
		_manager_pool->PoolInObject(object);
	}
	_spawn_objects.Empty(50);

	/*���� �ʱ�ȭ*/
	_plane_index_move = -1;
	_plane_move_count = -1;
	_pre_spawn_plane_loc_x = _player_base_location.X;
	_info_game.game_status = EGameStatus::TITLE;
}

void AFA_GM::ShotPlayer()
{
	_player->PlayerMovementSetActive(true);
	_player->PlayerSetSpeed(_data_game_cache->GetPlayerBaseMaxPower() * _power_progress_value);
	_player->PlayerSetVelocity(_data_game_cache->GetPlayerBaseAngle());

	_info_game.game_status = EGameStatus::PLAY;
}

void AFA_GM::ObjectOverlap(const EObjectType e_obj_type)
{
	switch (e_obj_type)
	{
	case EObjectType::TRAP:
		_player->PlayerAddSpeed(_data_game_cache->GetObstacleTrapAddSpeed());
		break;
	case EObjectType::HOLE:
		_player->PlayerAddSpeed(0.f);
		break;
	default:
		break;
	}
}

const FString AFA_GM::CalcSpawnObjectCode()
{
	//_fagi->IsPassProbByInt()
	//return FString();

	/*��ֹ��� ��ġ���� ������ ��ġ����*/
	if (_fagi->IsPassProbByInt(_data_game_cache->GetObjectProbObstacle()))
	{
		/*��ֹ� ��ġ*/
		/*������ ��ֹ��� �ڵ带 �����մϴ�*/
		return _prob_obstacles[_fagi->GetRandomByInt(0, _prob_obstacles.Num() - 1)];
	}
	else
	{
		/*���� ��ġ*/
		/*������ ������ �ڵ带 �����մϴ�*/
		return _prob_chances[_fagi->GetRandomByInt(0, _prob_chances.Num() - 1)];
	}
}

void AFA_GM::PlaneInitLocation()
{
	_plane_index_move = -1;
	for (AFA_Plane* plane : _spawn_planes)
	{
		plane->PlaneInit(FVector(_data_game_cache->GetPlaneLength() * ++_plane_index_move, 0.f, 0.f));
	}
	_plane_index_move = -1;
}

void AFA_GM::SetPowerProgressMaterial(UMaterialInstanceDynamic* mid_power_progress) { _power_progress = mid_power_progress; }