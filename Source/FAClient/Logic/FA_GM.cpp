// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/FA_GM.h"
#include "FA_GI.h"
#include "FA_PC.h"
#include "FA_FunctionLibrary.h"
#include "Manager/FA_Manager_Pool.h"
#include "Manager/FA_Manager_SaveLoad.h"
#include "Manager/FA_Manager_SFX.h"
#include "Manager/FA_Manager_VFX.h"
#include "Actor/Player/FA_Player.h"
#include "Actor/Object/FA_Plane.h"
#include "Actor/Object/Obstacle/FA_Trap.h"
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

	_manager_pool = wld->SpawnActor<AFA_Manager_Pool>(s_param);
	_manager_saveload = wld->SpawnActor<AFA_Manager_SaveLoad>(s_param);
	_manager_sfx = wld->SpawnActor<AFA_Manager_SFX>(s_param);
	_manager_vfx = wld->SpawnActor<AFA_Manager_VFX>(s_param);

	_manager_pool->PoolInit(_fagi);
	_manager_vfx->VFXInit(_fagi);
	_manager_sfx->SFXInit(_fagi);

	///*오브젝트 생성확률 초기화*/
	//for (const FDataObjectProb& s_data_obj_prob : _data_game_cache->GetProbObstacles())
	//{
	//	for (int32 i = 0, i_len = s_data_obj_prob.GetObjectProb(); i < i_len; ++i)
	//	{
	//		_prob_obstacles.Add(s_data_obj_prob.GetCode());
	//	}
	//}
	//for (const FDataObjectProb& s_data_obj_prob : _data_game_cache->GetProbChances())
	//{
	//	for (int32 i = 0, i_len = s_data_obj_prob.GetObjectProb(); i < i_len; ++i)
	//	{
	//		_prob_chances.Add(s_data_obj_prob.GetCode());
	//	}
	//}
	/*오브젝트 RGB확률 초기화*/
	for (int32 i = 0, i_len = _data_game_cache->GetObjectProbR(); i < i_len; ++i) _prob_rgb.Add(ERGBType::R);
	for (int32 i = 0, i_len = _data_game_cache->GetObjectProbG(); i < i_len; ++i) _prob_rgb.Add(ERGBType::G);
	for (int32 i = 0, i_len = _data_game_cache->GetObjectProbB(); i < i_len; ++i) _prob_rgb.Add(ERGBType::B);
	for (int32 i = 0, i_len = _data_game_cache->GetObjectProbBlack(); i < i_len; ++i) _prob_rgb.Add(ERGBType::BLACK);
	
	

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
	_player->GetInfoPlayer().power_count_current = _data_game_cache->GetPlayerPowerCountMax();
	_player->GetInfoPlayer().max_velocity_z = _player_base_location.Z;

	/*세이브파일 로드*/
	GameLoad();

	/*SFX 초기화*/
	_manager_sfx->SFXStart(ESFXType::BACKGROUND);

	/*플레이어컨트롤러 초기화*/
	_pc->PCInit(this, _info_game);
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

		_info_game.score_current = _player->GetActorLocation().X - _player_base_location.X;

		TickUIUpdate();
	}
}

void AFA_GM::TickCheckMoveFloor()
{
	int32 i_distance_player_plane = _player->GetActorLocation().X - _pre_spawn_plane_loc_x;
	if (i_distance_player_plane >= _data_game_cache->GetPlaneLength())
	{
		int32 i_count = (i_distance_player_plane / _data_game_cache->GetPlaneLength());
		_pre_spawn_plane_loc_x += _data_game_cache->GetPlaneLength() * i_count;
		for (int32 i = 0; i < i_count; ++i)
		{
			/*바닥 이동*/
			++_plane_move_count;
			++_plane_index_move;

			/*이동해야할 바닥위치값을 구합니다*/

			if (_plane_index_move >= _data_game_cache->GetPlaneBaseSpawnCount())
				_plane_index_move = 0;

			/*이동해야할 바닥이 오브젝트를 가지고 있다면 풀링합니다*/
			AFA_Plane* plane = _spawn_planes[_plane_index_move];
			if (plane->GetSpawnObject())
			{
				_manager_pool->PoolInObject(plane->GetSpawnObject());
			}

			/*Gem이 있다면 풀링합니다*/
			TArray<AFA_Object*, TInlineAllocator<30>>& spawn_gems = plane->GetSpawnGems();
			if (spawn_gems.Num() >= 1)
			{
				for (AFA_Object* gem : spawn_gems)
				{
					_manager_pool->PoolInObject(gem);
				}
				spawn_gems.Empty(30);
			}

			/*새로운 오브젝트 생성*/
			//AFA_Object* object_spawn = _manager_pool->PoolGetObjectByCode(CalcSpawnObjectCode());
			AFA_Trap* trap_spawn = _manager_pool->PoolGetTrapByCode("OBJ00001");
			const ERGBType e_rgb_type = CalcSpawnObjectRGBType();
			FLinearColor s_object_rgb = FLinearColor();
			switch (e_rgb_type)
			{
			case ERGBType::R:
				s_object_rgb = _data_game_cache->GetObjectColorR();
				break;
			case ERGBType::G:
				s_object_rgb = _data_game_cache->GetObjectColorG();
				break;
			case ERGBType::B:
				s_object_rgb = _data_game_cache->GetObjectColorB();
				break;
			case ERGBType::BLACK:
				s_object_rgb = _data_game_cache->GetObjectColorBlack();
				break;
			default:
				break;
			}
			trap_spawn->ObjectInit(IdGenerator());
			trap_spawn->TrapInit(s_object_rgb, e_rgb_type);

			/*이동해야할 바닥 초기화*/
			plane->PlaneSpawn(FVector((_plane_move_count + _data_game_cache->GetPlaneBaseSpawnCount()) * _data_game_cache->GetPlaneLength(), 0.f, 0.f), trap_spawn);

			/*일정확률로 Gem도 생성합니다*/
			if (_fagi->IsPassProbByInt(_data_game_cache->GetGemProb()))
			{
				SpawnGem(plane);
			}
		}
	}

	
}

void AFA_GM::TickCheckGameOver()
{
	if (_player->PlayerGetSpeed() <= 0 || _player->GetActorLocation().Z <= -300.f)
	{
		GameOver();
	}
}

void AFA_GM::TickUIUpdate()
{
	_pc->PCUITickUpdate(_info_game.score_current);
}

void AFA_GM::GameRestart()
{
	/*플레이어 캐릭터 초기화*/
	_player->PlayerMovementSetActive(false);
	_player->SetActorLocation(_player_base_location);
	_player->GetInfoPlayer().power_count_current = _data_game_cache->GetPlayerPowerCountMax();
	_player->GetInfoPlayer().max_velocity_z = _player_base_location.Z;
	PlayerChangeColor(FLinearColor(FColor::FromHex("FFFFFFFF")), ERGBType::WHITE);

	/*바닥 풀링*/
	PlaneInitLocation();

	/*변수 초기화*/
	_plane_index_move = -1;
	_plane_move_count = -1;
	_pre_spawn_plane_loc_x = _player_base_location.X;
	_info_game.score_current = 0;
	_info_game.gem_add = 0;
	_info_game.game_status = EGameStatus::TITLE;
}
void AFA_GM::GameOver()
{
	_info_game.game_status = EGameStatus::GAMEOVER;
	if (_info_game.score_best < _player->GetActorLocation().X)
	{
		/*신기록 달성*/
		_info_game.score_best = _info_game.score_current;
		_info_game.gem += 1;
	}
	else
	{
		/*신기록 달성 실패*/
	}
	
	GameSave();
	_pc->PCGameOver(_info_game);
}

void AFA_GM::ShotPlayer()
{
	_player->PlayerMovementSetActive(true);
	_player->PlayerSetVelocity(_data_game_cache->GetPlayerBaseAngle() * _power_progress_value);

	_info_game.game_status = EGameStatus::PLAY;
}

void AFA_GM::PlayerPowerStart()
{
	//if (_player->GetInfoPlayer().power_count_current >= _data_game_cache->GetPlayerPowerCountMax()) return;
	if (_player->GetInfoPlayer().power_count_current <= 0) return;
	if (_info_game.gem < _data_game_cache->GetPlayerPowerCost()) return;

	--_player->GetInfoPlayer().power_count_current;
	_info_game.gem -= _data_game_cache->GetPlayerPowerCost();
	_manager_sfx->SFXStart(ESFXType::POWER);

	_player->PlayerMovementJump(_data_game_cache->GetChanceJumpFeverAddSpeed(), _data_game_cache->GetChanceJumpFeverAddVelocityZ());

	_pc->PCPowerStart(_info_game, _player->GetInfoPlayer());
}
void AFA_GM::PlayerChangeColor(const FLinearColor& s_change_color, const ERGBType e_rgb_type)
{
	_player->PlayerSetColor(s_change_color, e_rgb_type);
	switch (e_rgb_type)
	{
	case ERGBType::R:
		/*Jump : G, Slow : B*/
		_pc->PCChangeRGB(s_change_color, _data_game_cache->GetObjectColorG(), _data_game_cache->GetObjectColorB());
		break;
	case ERGBType::G:
		/*Jump : B, Slow : R*/
		_pc->PCChangeRGB(s_change_color, _data_game_cache->GetObjectColorB(), _data_game_cache->GetObjectColorR());
		break;
	case ERGBType::B:
		/*Jump : R, Slow : G*/
		_pc->PCChangeRGB(s_change_color, _data_game_cache->GetObjectColorR(), _data_game_cache->GetObjectColorG());
		break;
	case ERGBType::BLACK:
		break;
	case ERGBType::WHITE:
		_pc->PCChangeRGB(s_change_color, s_change_color, s_change_color);
		break;
	default:
		break;
	}
}

void AFA_GM::ObjectOverlap(AFA_Object* obj_overlap, const FLinearColor& s_linear_color)
{
	if (!obj_overlap) return;

	switch (obj_overlap->GetInfoObject().obj_type)
	{
	case EObjectType::TRAP:
		_player->PlayerMovementJump(_data_game_cache->GetObstacleTrapAddSpeed(), _data_game_cache->GetObstacleTrapAddSpeed());
		//_player->PlayerSetColor(s_linear_color);
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
	case EObjectType::GEM:
		_manager_vfx->VFXStart(EVFXType::GEM, obj_overlap->GetActorLocation());
		_manager_sfx->SFXStart(ESFXType::GEM);

		obj_overlap->SetActorLocation(FVector(-1000.f, 0.f, -1000.f));

		_info_game.gem += 1;
		_info_game.gem_add += 1;

		_pc->PCUIObtainGem(_info_game.gem);
		break;
	default:
		break;
	}
}
void AFA_GM::TrapOverlap(AFA_Trap* trap)
{
	if (!trap) return;

	if (trap->GetRGBType() == ERGBType::BLACK)
	{
		/*GameOver*/
		_player->PlayerAddSpeed(0.f);
		return;
	}

	switch (_player->GetInfoPlayer().rgb_type)
	{
	case ERGBType::R:
		/*Jump : G, Slow : B*/
		switch (trap->GetRGBType())
		{
		case ERGBType::R:
			ChanceJumpFeverTimingStart();
			break;
		case ERGBType::G:
			ObjectInteractJumpStart();
			break;
		case ERGBType::B:
			ObjectInteractSlowStart();
			break;
		default:
			break;
		}
		PlayerChangeColor(trap->GetColor(), trap->GetRGBType());
		break;
	case ERGBType::G:
		/*Jump : B, Slow : R*/
		switch (trap->GetRGBType())
		{
		case ERGBType::R:
			ObjectInteractSlowStart();
			break;
		case ERGBType::G:
			ChanceJumpFeverTimingStart();
			break;
		case ERGBType::B:
			ObjectInteractJumpStart();
			break;
		default:
			break;
		}
		PlayerChangeColor(trap->GetColor(), trap->GetRGBType());
		break;
	case ERGBType::B:
		/*Jump : R, Slow : G*/
		switch (trap->GetRGBType())
		{
		case ERGBType::R:
			ObjectInteractJumpStart();
			break;
		case ERGBType::G:
			ObjectInteractSlowStart();
			break;
		case ERGBType::B:
			ChanceJumpFeverTimingStart();
			break;
		default:
			break;
		}
		PlayerChangeColor(trap->GetColor(), trap->GetRGBType());
		break;
	case ERGBType::BLACK:
		//_player->PlayerAddSpeed(0.f);
		break;
	case ERGBType::WHITE:
		ObjectInteractJumpStart();
		PlayerChangeColor(trap->GetColor(), trap->GetRGBType());
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
	GetWorldTimerManager().SetTimer(_timer_interact_trap, this, &AFA_GM::TimerChanceJumpFeverFailed, _data_game_cache->GetChanceJumpFeverTiming() * _data_game_cache->GetChanceJumpFeverSlotRate(), false);

	_manager_sfx->SFXStart(ESFXType::FEVER_TIMING);

	//UI
	_pc->PCUIChanceJumpFever();
}

void AFA_GM::TimerChanceJumpFeverFailed()
{
	/*피버를 작동하지 못했습니다*/

	//게임속도 원래대로
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);

	_player->PlayerMovementJump(_data_game_cache->GetChanceJumpAddSpeed(), _data_game_cache->GetChanceJumpAddVelocityZ());

	_manager_sfx->SFXEnd(ESFXType::FEVER_TIMING);
	//_manager_sfx->SFXStart(ESFXType::JUMP);
	_manager_sfx->SFXStart(ESFXType::FEVER_FAILED);

	_pc->PCFeverFailed();
}

void AFA_GM::FeverSuccess()
{
	/*피버 발동에 성공했습니다*/

	//게임속도 원래대로
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);

	//피버종료타이머 취소
	GetWorldTimerManager().PauseTimer(_timer_interact_trap);

	_player->PlayerMovementJump(_data_game_cache->GetChanceJumpFeverAddSpeed(), _data_game_cache->GetChanceJumpFeverAddVelocityZ());

	_manager_sfx->SFXEnd(ESFXType::FEVER_TIMING);
	_manager_sfx->SFXStart(ESFXType::FEVER);
}

void AFA_GM::ObjectInteractJumpStart()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), _data_game_cache->GetChanceJumpFeverSlotRate());
	GetWorldTimerManager().SetTimer(_timer_interact_trap, this, &AFA_GM::ObjectInteractJumpEnd, _data_game_cache->GetChanceJumpFeverTiming() * _data_game_cache->GetChanceJumpFeverSlotRate(), false);

	_player->PlayerMovementJump(_data_game_cache->GetChanceJumpAddSpeed(), _data_game_cache->GetChanceJumpAddVelocityZ());
	_pc->PCUIInteractStart(EInteractType::JUMP);
}
void AFA_GM::ObjectInteractJumpEnd()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);

	_pc->PCUIInteractEnd();
}
void AFA_GM::ObjectInteractSlowStart()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), _data_game_cache->GetChanceJumpFeverSlotRate());
	GetWorldTimerManager().SetTimer(_timer_interact_trap, this, &AFA_GM::ObjectInteractSlowEnd, _data_game_cache->GetChanceJumpFeverTiming() * _data_game_cache->GetChanceJumpFeverSlotRate(), false);

	_player->PlayerMovementSlow(_data_game_cache->GetObstacleTrapAddSpeed());
	_pc->PCUIInteractStart(EInteractType::SLOW);
}
void AFA_GM::ObjectInteractSlowEnd()
{
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.f);

	_pc->PCUIInteractEnd();
}

void AFA_GM::SpawnGem(AFA_Plane* plane)
{
	AFA_Object* gem = nullptr;
	const FVector& v_loc_base = plane->GetObjectLocation();
	for (int32 i_row = 1, i_row_len = _data_game_cache->GetGemRow(); i_row <= i_row_len; ++i_row)
	{
		for (int32 i_column = 1, i_column_len = _data_game_cache->GetGemColumn(); i_column <= i_column_len; ++i_column)
		{
			gem = _manager_pool->PoolGetObjectByCode("OBJ00000");
			gem->ObjectInit(IdGenerator());
			gem->SetActorLocation(FVector(v_loc_base.X + (50 * i_column) - 200, v_loc_base.Y, _data_game_cache->GetGemLocZ()+ (50 * i_row)));
			plane->AddGem(gem);
		}
	}
}

const FString AFA_GM::CalcSpawnObjectCode()
{
	//_fagi->IsPassProbByInt()
	return FString();

	///*장애물을 설치할지 찬스를 설치할지*/
	//if (_fagi->IsPassProbByInt(_data_game_cache->GetObjectProbObstacle()))
	//{
	//	/*장애물 설치*/
	//	/*랜덤한 장애물의 코드를 리턴합니다*/
	//	return _prob_obstacles[_fagi->GetRandomByInt(0, _prob_obstacles.Num() - 1)];
	//}
	//else
	//{
	//	/*찬스 설치*/
	//	/*랜덤한 찬스의 코드를 리턴합니다*/
	//	return _prob_chances[_fagi->GetRandomByInt(0, _prob_chances.Num() - 1)];
	//}

	/*어떤 색상의 오브젝트를 생성할건지 */
}

const ERGBType AFA_GM::CalcSpawnObjectRGBType()
{
	return _prob_rgb[_fagi->GetRandomByInt(0, _prob_rgb.Num() - 1)];
}

void AFA_GM::PlaneInitLocation()
{
	_plane_move_count = -1;
	AFA_Plane* plane = nullptr;
	for (int32 i = 0, i_len = _spawn_planes.Num(); i < i_len; ++i)
	{
		++_plane_move_count;
		plane = _spawn_planes[i];

		/*바닥이 Gem을 가지고 있다면 Gem을 풀링합니다*/
		TArray<AFA_Object*, TInlineAllocator<30>>& spawn_gems = plane->GetSpawnGems();
		if (spawn_gems.Num() >= 1)
		{
			for (AFA_Object* gem : spawn_gems)
			{
				_manager_pool->PoolInObject(gem);
			}
			spawn_gems.Empty(30);
		}

		/*바닥이 오브젝트를 가지고 있다면 오브젝트를 풀링합니다*/
		if (plane->GetSpawnObject())
		{
			_manager_pool->PoolInObject(plane->GetSpawnObject());
		}

		if (i >= _data_game_cache->GetPlaneBaseSpawnObject())
		{
			/*새로운 오브젝트 생성*/
			AFA_Trap* trap_spawn = _manager_pool->PoolGetTrapByCode("OBJ00001");
			const ERGBType e_rgb_type = CalcSpawnObjectRGBType();
			FLinearColor s_object_rgb = FLinearColor();
			switch (e_rgb_type)
			{
			case ERGBType::R:
				s_object_rgb = _data_game_cache->GetObjectColorR();
				break;
			case ERGBType::G:
				s_object_rgb = _data_game_cache->GetObjectColorG();
				break;
			case ERGBType::B:
				s_object_rgb = _data_game_cache->GetObjectColorB();
				break;
			case ERGBType::BLACK:
				s_object_rgb = _data_game_cache->GetObjectColorBlack();
				break;
			default:
				break;
			}
			trap_spawn->ObjectInit(IdGenerator());
			trap_spawn->TrapInit(s_object_rgb, e_rgb_type);

			/*이동해야할 바닥 초기화*/
			plane->PlaneSpawn(FVector(_plane_move_count * _data_game_cache->GetPlaneLength(), 0.f, 0.f), trap_spawn);
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