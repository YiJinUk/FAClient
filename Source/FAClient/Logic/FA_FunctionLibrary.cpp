// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/FA_FunctionLibrary.h"

float UFA_FunctionLibrary::GetDistanceByV2(const FVector2D& v_loc_owner, const FVector2D& v_loc_target)
{
	return (v_loc_owner - v_loc_target).Size();
}

void UFA_FunctionLibrary::GPrintString(int i_key, float f_time, const FString& str_message, const FColor& s_color)
{
	GEngine->AddOnScreenDebugMessage(i_key, f_time, s_color, str_message);
}