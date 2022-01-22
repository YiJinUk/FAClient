// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

	const int32 PlayerGetSpeed();
private:
	//UFUNCTION()
		//void PlayerOnBounce(const FHitResult& s_hit, const FVector& v_velocity);
#pragma endregion

};
