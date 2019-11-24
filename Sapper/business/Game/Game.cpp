#include "Game.h"

Game::Game(GameConfigs* configs)
{
	if (configs == nullptr ||
		configs->GetBoardSize() <= 0 ||
		configs->GetBobmsCount() <= 0 ||
		configs->GetBobmsCount() >= configs->GetBoardSize() * configs->GetBoardSize())
	{
		throw "Invalid input data";
	}

	workQueue = new WorkQueue();
	board = new Board(configs->GetBoardSize());
	isItinStepMade = false;
	finished = false;
	won = false;
	bombCount = configs->GetBobmsCount();
}

Game::~Game()
{
	delete this->workQueue;
	delete this->board;
}

void Game::MakeStep(int str, int column)
{
	if (!isItinStepMade)
	{
		MakeInitStep(str, column);
	}
	else
	{
		if (str < 0 || str >= board->GetBoardSize() || column < 0 || column >= board->GetBoardSize())
		{
			return;
		}
		
		Cell* currentCell = board->GetCell(str, column);
		
		if (currentCell->IsBombed())
		{
			finished = true;
		}
		else
		{
			workQueue->addWorkItem(new GameWorkItem(new GameWorkItemData(board, str, column)));
			workQueue->ProcessItems();
		}
	}

	int visibleCells = 0;
	int boardSize = board->GetBoardSize();
	for (int i = 0; i < boardSize; i++)
	{
		for (int j = 0; j < boardSize; j++)
		{
			Cell* cell = board->GetCell(i, j);

			if (cell->IsVisible())
			{
				visibleCells++;
			}
		}
	}

	if (visibleCells == boardSize * boardSize - bombCount)
	{
		won = true;
		finished = true;
	}
}

void Game::RestardGame(GameConfigs* configs)
{
	finished = false;
	isItinStepMade = false;
	bombCount = configs->GetBobmsCount();

	delete board;

	board = new Board(configs->GetBoardSize());
}

Board* Game::GetBoard()
{
	return board;
}

int Game::GetBombCount()
{
	return bombCount;
}

bool Game::IsFinished()
{
	return finished;
}

bool Game::IsWon()
{
	return won;
}

void Game::MakeInitStep(int str, int column)
{
	if (!isItinStepMade)
	{
		isItinStepMade = true;
		int _str, _column;

		for (int i = 0; i < bombCount; i++)
		{
			//TODO srand
			while (true) 
			{
				_str = rand() % board->GetBoardSize();
				_column = rand() % board->GetBoardSize();

				if (!(_str == str && (_column == column || _column == column - 1 || _column == column - 2 || _column == column  + 1 || _column == column  + 2)) &&
					!(_str == str + 1 && (_column == column || _column == column - 1 || _column == column - 2 || _column == column + 1 || _column == column + 2))&&
					!(_str == str - 1 && (_column == column || _column == column - 1 || _column == column - 2 || _column == column + 1 || _column == column + 2))&&
					!(_str == str + 2 && (_column == column || _column == column - 1 || _column == column - 2 || _column == column + 1 || _column == column + 2))&&
					!(_str == str - 2 && (_column == column || _column == column - 1 || _column == column - 2 || _column == column + 1 || _column == column + 2)))
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

		workQueue->addWorkItem(new GameWorkItem(new GameWorkItemData(board, str, column)));
		workQueue->ProcessItems();
	}
}

void Game::NotifyCellsBombIsNear(int str, int column)
{
	int boardSize = board->GetBoardSize();
	// processing steps
	//	+----+----+----+
	//  |  2 |  3 |  4 |
	//	+----+----+----+
	//  |  1 |here|  5 |
	//	+----+----+----+
	//  |  8 |  7 |  6 |
	//	+----+----+----+

	if (column - 1 >= 0)
	{
		Cell* cell = board->GetCell(str, column - 1);
		cell->IncNumOfBombNearby();
	}

	if (column - 1 >= 0 && str - 1 >= 0)
	{
		Cell* cell = board->GetCell(str - 1, column - 1);
		cell->IncNumOfBombNearby();
	}

	if (str - 1 >= 0)
	{
		Cell* cell = board->GetCell(str - 1, column);
		cell->IncNumOfBombNearby();
	}

	if (str - 1 >= 0 && column + 1 < boardSize)
	{
		Cell* cell = board->GetCell(str - 1, column + 1);
		cell->IncNumOfBombNearby();
	}

	if (column + 1 < boardSize)
	{
		Cell* cell = board->GetCell(str, column + 1);
		cell->IncNumOfBombNearby();
	}

	if (str + 1 < boardSize && column + 1 < boardSize)
	{
		Cell* cell = board->GetCell(str + 1, column + 1);
		cell->IncNumOfBombNearby();
	}

	if (str + 1 < boardSize)
	{
		Cell* cell = board->GetCell(str + 1, column);
		cell->IncNumOfBombNearby();
	}

	if (str + 1 < boardSize && column - 1 >= 0)
	{
		Cell* cell = board->GetCell(str + 1, column - 1);
		cell->IncNumOfBombNearby();
	}
}
