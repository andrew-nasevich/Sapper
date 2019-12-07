#include "GameWorkItemData.h"

GameWorkItemData::GameWorkItemData(Board* board, int str, int column)
{
	this->board = board;
	this->column = column;
	this->str = str;
}