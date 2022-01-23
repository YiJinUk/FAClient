// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ReadOnly/FA_SharedStruct.h"
#include "Actor/FA_Actor.h"
#include "FA_Object.generated.h"

/**
 * 
 */
UCLASS()
class FACLIENT_API AFA_Object : public AFA_Actor
{
	GENERATED_BODY()
	
protected:
	AFA_Object();
	virtual void BeginPlay() override;
protected:
	UPROPERTY(EditAnywhere)
		class USceneComponent* _root_scene = nullptr;
	UPROPERTY(EditAnywhere)
		class UBoxComponent* _box = nullptr;

	UPROPERTY()
		class AFA_GM* _fagm = nullptr;
private:
	


public:
	/*���� 1ȸ�� ȣ��. Ǯ���� ���� ȣ������ ����*/
	void ObjectPostInit(const FDataObject* s_data_object);
	virtual void ObjectPostInitChild(const FDataObject* s_data_object);

	/*Ǯ������ ���� �� ȣ��*/
	void ObjectInit(const int64 i_id);

	void ObjectSetPoolActive(const bool b_is_active);
	virtual void ObjectSetPoolActiveChild(const bool b_is_active);
public:
	const FInfoObject& GetInfoObject();
private:
	UPROPERTY()
		FInfoObject _info_object;
};
