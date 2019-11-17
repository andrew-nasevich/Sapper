#pragma once
#include "../Board/Board.h"
class GameWorkItemData
{
public: 
	GameWorkItemData(Board* board, int str, int column);
	Board* board;
	int str;
	int column;
};

