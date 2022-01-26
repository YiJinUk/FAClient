// Fill out your copyright notice in the Description page of Project Settings.


#include "Logic/SaveLoad/FA_SG_Game.h"

void UFA_SG_Game::SGSaveData(FInfoGame& s_info_game)
{
	score_best = s_info_game.score_best;
	gem = s_info_game.gem;
}