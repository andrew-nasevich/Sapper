#include "Game.h"
Game::Game(GameConfigs* configs)
{
	if (configs == nullptr ||
		configs->GetBoardSize() <= 0 ||
		configs->GetBobmsCount() <= 0 ||
		configs->GetBobmsCount() >= configs->GetBoardSize() * configs->GetBoardSize())
		throw "Invalid input data";

	board = new Board(configs->GetBoardSize());
	this->isItinStepMade = false;
	bombCount = 0;
}

void Game::MakeStep(int str, int column)
{
	if (!isItinStepMade)
	{
		MakeInitStep(str, column);
	}
	else
	{
		//TODO
	}
}

void Game::RestardGame(GameConfigs* configs)
{
}

Board* Game::GetBoard()
{
	return board;
}

int Game::GetBombCount()
{
	return bombCount;
}

void Game::MakeInitStep(int str, int column)
{
	if (!isItinStepMade)
	{
		isItinStepMade = true;
		int _str, _column;

		for (int i = 1; i <= bombCount; i++)
		{
			//TODO srand
			while (true) 
			{
				_str = rand() % board->GetBoardSize();
				_column = rand() % board->GetBoardSize();

				if (_str != str && _column != column)
				{
					Cell* cell = board->GetCell(_str, _column);
					
					if (!cell->IsBombed())
					{
						cell->SetBombed(true);
						NotifyCellsBombIsNear(_str, _column);

						break;
					}
				}
			}
		}

		Cell* cell = board->GetCell(str, column);
		cell->SetVisible(true);
		//TODO processing visibility
	}
}

void Game::NotifyCellsBombIsNear(int str, int column)
{
	//TODO
}
