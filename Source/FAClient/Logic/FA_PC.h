// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FA_PC.generated.h"

class AFA_GM;
class UFA_UI_Main;

/**
 * 
 */
UCLASS()
class FACLIENT_API AFA_PC : public APlayerController
{
	GENERATED_BODY()

#pragma region Init
protected:
	AFA_PC();
public:
	void PCInit(AFA_GM* fagm);
private:
	UPROPERTY()
		AFA_GM* _fagm = nullptr;
#pragma endregion

#pragma region Game
public:
	void PCUIObstacleWallTap();

	void PCFeverSuccess();
	void PCFeverFailed();

	void PCShotStart();
	void PCGameRestart();
#pragma endregion

#pragma region UI
public:
	void PCGameOver();

	void PCUIChanceJumpFever();
protected:
	UFUNCTION(BlueprintImplementableEvent)
		void PCBPInit();
	UFUNCTION(BlueprintImplementableEvent)
		UFA_UI_Main* PCCreateWidgetMain();
private:
	UFA_UI_Main* _ui_main = nullptr;
#pragma endregion
};
