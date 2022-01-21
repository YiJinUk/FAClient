// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/FA_GM.h"
#include "FA_GI.h"
#include "FA_PC.h"
#include "FA_FunctionLibrary.h"
#include "Manager/FA_Manager_Pool.h"
#include "Actor/Player/FA_Player.h"
#include "Actor/Object/FA_Plane.h"

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

	/*�ٴ�Ÿ�� �ʱ�ȭ*/
	for (int32 i = 0, i_len = _data_game_cache->GetStartPlaneCount(); i < i_len; ++i)
	{
		AFA_Plane* plane = _manager_pool->PoolGetPlaneByCode("PLANE00001");
		plane->SetActorLocation(FVector(_data_game_cache->GetPlaneLength() * _spawn_planes.Num() + 1, 0.f, 0.f));
		_spawn_planes.Add(plane);
	}

	/*�÷��̾���Ʈ�ѷ� �ʱ�ȭ*/
	_pc->PCInit(this);
}

void AFA_GM::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (UFA_FunctionLibrary::GetDistanceByV2(_pre_spawn_plane_loc, _player->GetActorLocation2D()) >= 5000.f)
	{
		_pre_spawn_plane_loc = _player->GetActorLocation2D();

		AFA_Plane* plane = _manager_pool->PoolGetPlaneByCode("PLANE00001");
		plane->SetActorLocation(FVector(_data_game_cache->GetPlaneLength() * _spawn_planes.Num() + 1, 0.f, 0.f));
		_spawn_planes.Add(plane);
	}
}

void AFA_GM::ShotPlayer()
{
	_player->PlayerMovementSetActive(true);
	_player->PlayerSetSpeed(5000);
	_player->PlayerSetVelocity(FVector(3000, 0, 1000));
}