// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Object/Obstacle/FA_Wall.h"
#include "Actor/Player/FA_Player.h"
#include "Logic/FA_GM.h"

#include "Components/BoxComponent.h"

AFA_Wall::AFA_Wall()
{
	if (_box)
	{
		_box->OnComponentBeginOverlap.AddDynamic(this, &AFA_Wall::OnBoxOverlap);
	}
}

void AFA_Wall::WallInitSMCsLocation()
{
	for (UStaticMeshComponent* smc : _smcs)
	{
		_smcs_location.Add(smc->GetRelativeLocation());
	}
}
void AFA_Wall::ObjectSetPoolActiveChild(const bool b_is_active)
{
	if (b_is_active)
	{
		GetWorldTimerManager().SetTimer(_timer_TimerSetPhysicsSMCS, this, &AFA_Wall::TimerSetPhysicsSMCS, 1.f, false);
	}
	else
	{
		UStaticMeshComponent* smc = nullptr;
		for (int32 i = 0, i_len = _smcs.Num(); i < i_len; ++i)
		{
			smc = _smcs[i];
			smc->SetSimulatePhysics(false);
			smc->SetRelativeLocation(_smcs_location[i]);
		}
	}
}

void AFA_Wall::TimerSetPhysicsSMCS()
{
	for (UStaticMeshComponent* smc : _smcs)
	{
		smc->SetSimulatePhysics(true);
	}
}

void AFA_Wall::OnBoxOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AFA_Player* player = Cast<AFA_Player>(OtherActor);
	if (!player) return;

	_fagm->ObjectOverlap(EObjectType::WALL);
}
