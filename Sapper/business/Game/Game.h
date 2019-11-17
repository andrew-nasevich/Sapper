#pragma once
#include"GameConfigs.h"
#include "../Board/Board.h"
#include <iostream>

class Game
{
public:
	Game(GameConfigs* configs);
	
	void MakeStep(int str, int column);
	void RestardGame(GameConfigs* configs);

	Board* GetBoard();
	int GetBombCount();

private:
	void MakeInitStep(int str, int column);
	void NotifyCellsBombIsNear(int str, int column);

	Board* board;
	bool isItinStepMade;
	int bombCount;
};

