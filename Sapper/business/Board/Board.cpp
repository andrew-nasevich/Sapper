#include "Board.h"

Board::Board(int boardSize)
{
	cells = new Cell*[boardSize];
	this->boardSize = boardSize;
	for(int i = 0; i <= boardSize -1 ; i++)
		cells[i] = new Cell();
}

Board::~Board()
{
	for (int i = 0; i <= boardSize - 1; i++)
		delete cells[i];
}

Cell* Board::GetCell(int str, int column)
{
	if (str < 0 || str >= this->boardSize || column < 0 || column >= this->boardSize)
		return nullptr;

	return cells[(str-1) * boardSize + column - 1];
}
