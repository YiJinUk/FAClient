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
	//_projectile_movement->OnProjectileBounce.AddDynamic(this, &AFA_Player::PlayerOnBounce);
}

void AFA_Player::PlayerPostInit()
{
	PlayerMovementSetActive(false);

	_fagi = GetWorld()->GetGameInstance<UFA_GI>();
	_fagm = GetWorld()->GetAuthGameMode<AFA_GM>();
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
	if (f_speed <= 0.f)
	{
		_projectile_movement->SetVelocityInLocalSpace(FVector(0.f));
	}
	else
	{
		_projectile_movement->SetVelocityInLocalSpace(FVector(v_velocity.X * f_speed, 0.f, v_velocity.Z));
	}
	
	//_projectile_movement->SetVelocityInLocalSpace(FVector(v_velocity.X * f_speed, 0.f, 4000.f));
}

//void AFA_Player::PlayerOnBounce(const FHitResult& s_hit, const FVector& v_velocity)
//{
//	//UFA_FunctionLibrary::GPrintString(1, 3, "PlayerOnBounce. hit name : " + s_hit.GetActor()->GetName() + " // velocity : "+v_velocity.ToString());
//	AFA_Object* obj_hit = Cast<AFA_Object>(s_hit.GetActor());
//	if (!obj_hit) return;
//	_fagm->ObjectOverlap(obj_hit->GetInfoObject().obj_type);
//}

const int32 AFA_Player::PlayerGetSpeed() { return _projectile_movement->Velocity.Size(); }