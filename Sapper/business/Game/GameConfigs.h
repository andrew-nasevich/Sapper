#pragma once
#include "GameConfigsEnum.h"
class GameConfigs
{
public:
	GameConfigs(GameDifficulty difficulty);
	int GetBoardSize();
	int GetBobmsCount();

private:
	int boardSize;
	int bombsCount;
};



