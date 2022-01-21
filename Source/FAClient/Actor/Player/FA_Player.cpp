// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Player/FA_Player.h"
#include "Logic/FA_GI.h"

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
	//_projectile_movement->InitialSpeed = 3000.0f; 
	//_projectile_movement->MaxSpeed = 3000.0f; 
	//_projectile_movement->bRotationFollowsVelocity = true; 
	_projectile_movement->bShouldBounce = true; 
	//_projectile_movement->Bounciness = 0.3f;
}

void AFA_Player::PlayerPostInit()
{
	PlayerMovementSetActive(false);

	_fagi = GetWorld()->GetGameInstance<UFA_GI>();
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
	const FVector& v_velocity = _projectile_movement->Velocity;
	_projectile_movement->SetVelocityInLocalSpace(FVector(v_velocity.X * f_speed, 0.f, v_velocity.Z));
}

const int32 AFA_Player::PlayerGetSpeed() { return _projectile_movement->Velocity.Size(); }