// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "FA_FunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class FACLIENT_API UFA_FunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	static float GetDistanceByV2(const FVector2D& v_loc_owner, const FVector2D& v_loc_target);

	static void GPrintString(int i_key, float f_time, const FString& str_message, const FColor& s_color = FColor::Magenta);
};
