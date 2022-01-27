// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Object/Obstacle/FA_Trap.h"
#include "Actor/Player/FA_Player.h"
#include "Logic/FA_GM.h"

//#include "Materials/MaterialInstanceDynamic.h"
#include "Components/BoxComponent.h"

AFA_Trap::AFA_Trap()
{
	if (_box)
	{
		_box->OnComponentBeginOverlap.AddDynamic(this, &AFA_Trap::OnBoxOverlap);
	}
}

void AFA_Trap::OnBoxOverlap(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	_fagm->ObjectOverlap(this, _color);
}

void AFA_Trap::ObjectPostInitChild(const FDataObject* s_data_object)
{
	_mid_color = GetMID();
}

void AFA_Trap::ObjectInitChild(const FLinearColor& s_linear_color)
{
	_color = s_linear_color;
	_mid_color->SetVectorParameterValue("Color_1", _color);
	_mid_color->SetVectorParameterValue("Fresnel_Color", _color);
}

void AFA_Trap::ObjectSetPoolActiveChild(const bool b_is_active)
{

}