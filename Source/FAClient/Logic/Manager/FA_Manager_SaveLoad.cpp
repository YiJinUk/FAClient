// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/Manager/FA_Manager_SaveLoad.h"
#include "Logic/SaveLoad/FA_SG_Game.h"

#include "Kismet/GameplayStatics.h"

void AFA_Manager_SaveLoad::SaveStart(FInfoGame& s_info_game)
{
	UFA_SG_Game* save_file = Cast<UFA_SG_Game>(UGameplayStatics::CreateSaveGameObject(UFA_SG_Game::StaticClass()));
	if (!save_file) return;

	save_file->SGSaveData(s_info_game);

	UGameplayStatics::SaveGameToSlot(save_file, "SG_Game", 0);
}
void AFA_Manager_SaveLoad::LoadStart(FInfoGame& s_info_game)
{
	UFA_SG_Game* save_file_game = Cast<UFA_SG_Game>(UGameplayStatics::LoadGameFromSlot("SG_Game", 0));
	if (save_file_game)
	{
		s_info_game.score_best = save_file_game->score_best;
		s_info_game.gem = save_file_game->gem;
	}
	else
	{
		///*세이브데이터를 불러오지 못했습니다 기본값으로 변경합니다*/
		//USA_GI* sagi = GetWorld()->GetGameInstance<USA_GI>();
		//const FDataGame* s_data_game = sagi->GetDataGame();

		s_info_game.score_best = 0;
		s_info_game.gem = 0;
	}
}