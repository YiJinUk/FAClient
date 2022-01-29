// Fill out your copyright notice in the Description page of Project Settings.


#include "Actor/Object/FA_Trap.h"
#include "Actor/Player/FA_Player.h"
#include "Logic/FA_GM.h"

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
	_fagm->TrapOverlap(this);
}

void AFA_Trap::ObjectPostInitChild(const FDataObject* s_data_object)
{
	_mid_color = GetMID();
}

void AFA_Trap::TrapInit(const FLinearColor& s_linear_color, const ERGBType e_rgb_type)
{
	_color = s_linear_color;
	_rgb_type = e_rgb_type;
	_mid_color->SetVectorParameterValue("Color_1", _color);
	_mid_color->SetVectorParameterValue("Fresnel_Color", _color);
}

const FLinearColor& AFA_Trap::GetColor() { return _color; }
const ERGBType AFA_Trap::GetRGBType() { return _rgb_type; }