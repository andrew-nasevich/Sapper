#pragma once
#include "..\Cell\Cell.h"
class Board
{
public:
	Board(int boardSize);
	~Board();
	Cell* GetCell(int str, int column);
	int GetBoardSize() { return boardSize; }
private:
	Cell** cells;
	int boardSize;
};

