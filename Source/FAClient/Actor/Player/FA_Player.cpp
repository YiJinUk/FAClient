// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Player/FA_Player.h"

#include "GameFramework/ProjectileMovementComponent.h"

AFA_Player::AFA_Player()
{
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
}

void AFA_Player::PlayerMovementSetActive(const bool b_is_active)
{
	_projectile_movement->SetActive(b_is_active);
}

void AFA_Player::PlayerSetSpeed(const int32 i_speed)
{
	_projectile_movement->MaxSpeed = i_speed;
}

void AFA_Player::PlayerSetVelocity(const FVector v_velocity)
{
	_projectile_movement->SetVelocityInLocalSpace(v_velocity);
}