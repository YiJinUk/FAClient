// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Player/FA_Player.h"
#include "Logic/FA_FunctionLibrary.h"
#include "Logic/FA_GI.h"
#include "Logic/FA_GM.h"
#include "Actor/Object/FA_Object.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

AFA_Player::AFA_Player()
{
	PrimaryActorTick.bCanEverTick = true;

	_sphere_collision = CreateDefaultSubobject<USphereComponent>("_sphere_collision");
	if (_sphere_collision)
	{
		RootComponent = _sphere_collision;
	}

	_projectile_movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("_projectile_movement"));
	_projectile_movement->bShouldBounce = true;
	_projectile_movement->OnProjectileBounce.AddDynamic(this, &AFA_Player::PlayerOnBounce);
}

void AFA_Player::PlayerPostInit()
{
	PlayerMovementSetActive(false);

	_fagi = GetWorld()->GetGameInstance<UFA_GI>();
	_fagm = GetWorld()->GetAuthGameMode<AFA_GM>();

	PlayerSetSpeed(_fagi->GetDataGame()->GetPlayerBaseMaxPower());
}

void AFA_Player::PlayerMovementSetActive(const bool b_is_active)
{
	if (b_is_active)
	{
		_projectile_movement->SetUpdatedComponent(GetRootComponent());
		_projectile_movement->ProjectileGravityScale = _fagi->GetDataGame()->GetPlayerGravity();
	}
	else
	{
		_projectile_movement->ProjectileGravityScale = 0.f;
		_projectile_movement->SetVelocityInLocalSpace(FVector(0.f));
	}
}
void AFA_Player::PlayerSetSpeed(const int32 i_speed)
{
	_projectile_movement->MaxSpeed = i_speed;
}
void AFA_Player::PlayerSetVelocity(const FVector& v_velocity)
{
	_projectile_movement->SetVelocityInLocalSpace(v_velocity);
}
void AFA_Player::PlayerAddSpeed(const float f_speed)
{
	if (f_speed <= 0.f)
	{
		_projectile_movement->SetVelocityInLocalSpace(FVector(0.f));
	}
	else
	{
		//UFA_FunctionLibrary::GPrintString(1, 4, "velocity origin : " + _projectile_movement->Velocity.ToString());
		_projectile_movement->SetVelocityInLocalSpace(_projectile_movement->Velocity * f_speed);
		//UFA_FunctionLibrary::GPrintString(2, 4, "velocity new : " + _projectile_movement->Velocity.ToString());
		
	}
}

void AFA_Player::PlayerMovementJump(const float f_add_speed, const float f_add_velocty_z)
{
	const FVector& v_velocity = _projectile_movement->Velocity;
	//UFA_FunctionLibrary::GPrintString(5, 5, "old : "+_projectile_movement->Velocity.ToString());
	if (_info_player.max_velocity_z <= 0)
	{
		_info_player.max_velocity_z = 500;
		_projectile_movement->SetVelocityInLocalSpace(FVector(v_velocity.X, 0.f, _info_player.max_velocity_z));
	}
	else
	{
		_info_player.max_velocity_z = _info_player.max_velocity_z * f_add_velocty_z;
		if (_info_player.max_velocity_z < 500)
			_info_player.max_velocity_z = 500;
		_projectile_movement->SetVelocityInLocalSpace(FVector(v_velocity.X * f_add_speed, 0.f, _info_player.max_velocity_z));
	}
	
	//UFA_FunctionLibrary::GPrintString(2, 5, "new : "+_projectile_movement->Velocity.ToString());
}

void AFA_Player::PlayerOnBounce(const FHitResult& s_hit, const FVector& v_velocity)
{
	//UFA_FunctionLibrary::GPrintString(1, 0.1f, "Bounce");
	GetWorldTimerManager().SetTimerForNextTick(this, &AFA_Player::TimerSetMaxVelocityZ);
}

void AFA_Player::TimerSetMaxVelocityZ()
{
	_info_player.max_velocity_z = _projectile_movement->Velocity.Z;
}

FInfoPlayer& AFA_Player::GetInfoPlayer() { return _info_player; }
const int32 AFA_Player::PlayerGetSpeed() { return _projectile_movement->Velocity.Size(); }
const FVector& AFA_Player::PlayerMovementGetVelocity() { return _projectile_movement->Velocity; }