#include "GameConfigs.h"

GameConfigs::GameConfigs(GameDifficulty difficulty)
{
	if (difficulty == easy)
	{
		boardSize = 8;
		bombsCount = 10;
		return;
	}

	if (difficulty == medium)
	{
		boardSize = 14;
		bombsCount = 40;
		return;
	}
	
	if (difficulty == hard)
	{
		boardSize = 20;
		bombsCount = 99;
		return;
	}

	throw "GameDifficulty get incorrect difficulty";
}

int GameConfigs::GetBoardSize()
{
	return boardSize;
}

int GameConfigs::GetBobmsCount()
{
	return bombsCount;
}
