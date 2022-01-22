// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Object/Obstacle/FA_Trap.h"
#include "Actor/Player/FA_Player.h"
#include "Logic/FA_GM.h"

#include "Components/BoxComponent.h"

AFA_Trap::AFA_Trap()
{
	if (_box)
	{
		_box->SetCollisionResponseToChannel(ECollisionChannel::ECC_Vehicle, ECollisionResponse::ECR_Overlap);
		_box->OnComponentBeginOverlap.AddDynamic(this, &AFA_Trap::OnBoxOverlap);
	}
}

void AFA_Trap::OnBoxOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AFA_Player* player = Cast<AFA_Player>(OtherActor);
	if (!player) return;

	_fagm->ObjectOverlap(EObjectType::TRAP);
}

void AFA_Trap::ObjectSetPoolActiveChild(const bool b_is_active)
{

}