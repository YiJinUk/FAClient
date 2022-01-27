// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/FA_SharedStruct.h"
#include "Actor/FA_Actor.h"
#include "FA_Player.generated.h"

class UProjectileMovementComponent;
class UFA_GI;
class AFA_GM;

/**
 * 
 */
UCLASS()
class FACLIENT_API AFA_Player : public AFA_Actor
{
	GENERATED_BODY()

#pragma region Init
protected:
	AFA_Player();
	/*게임 실행시 최초 1회만 호출됩니다*/
public:
	void PlayerPostInit();
protected:
	UPROPERTY(EditAnywhere)
		class USphereComponent* _sphere_collision = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly) 
		UProjectileMovementComponent* _projectile_movement = nullptr;

	UPROPERTY(BlueprintReadWrite)
		UMaterialInstanceDynamic* _mid_color = nullptr;

	UPROPERTY()
		UFA_GI* _fagi = nullptr;
	UPROPERTY()
		AFA_GM* _fagm = nullptr;
#pragma endregion

#pragma region Movement
public:
	void PlayerMovementSetActive(const bool b_is_active);
	void PlayerSetSpeed(const int32 i_speed);
	void PlayerSetVelocity(const FVector& v_velocity);
	void PlayerAddSpeed(const float f_speed);
	void PlayerMovementJump(const float f_add_speed, const float f_add_velocty_z);

	const int32 PlayerGetSpeed();
	const FVector& PlayerMovementGetVelocity();
private:
	UFUNCTION()
		void PlayerOnBounce(const FHitResult& s_hit, const FVector& v_velocity);
#pragma endregion

#pragma region Color
public:
	void PlayerSetColor(const FLinearColor& s_linear_color, const ERGBType e_rgb_type);
#pragma endregion

#pragma region Stat
public:
	void TimerSetMaxVelocityZ();

	FInfoPlayer& GetInfoPlayer();
private:
	UPROPERTY()
		FInfoPlayer _info_player;
#pragma endregion

};
