#include "GameWorkItem.h"
#include "WorkQueue.h"

void GameWorkItem::Work(void* _queue)
{
	if ((data != nullptr) || (_queue != nullptr))
	{
		WorkQueue* queue = static_cast<WorkQueue*>(_queue);
		Board* board = data->board;
		int str = data->str;
		int column = data->column;
		int boardSize = board->GetBoardSize();

		Cell* currentCell = board->GetCell(str, column);
		currentCell->SetVisible(true);

		// processing steps
		//	+----+----+----+
		//  |  2 |  3 |  4 |
		//	+----+----+----+
		//  |  1 |here|  5 |
		//	+----+----+----+
		//  |  8 |  7 |  6 |
		//	+----+----+----+

		if (currentCell->GetNumOfBombNearby() == 0)
		{
			if (column - 1 >= 0)
			{
				Cell* cell = board->GetCell(str, column - 1);
				if (!cell->IsVisible())
				{
					cell->SetVisible(true);
					if (cell->GetNumOfBombNearby() == 0)
					{
						queue->addWorkItem(new GameWorkItem(new GameWorkItemData(board, str, column - 1)));
					}
				}
			}

			if (column - 1 >= 0 && str - 1 >= 0)
			{
				Cell* cell = board->GetCell(str - 1, column - 1);
				if (!cell->IsVisible())
				{
					cell->SetVisible(true);
					if (cell->GetNumOfBombNearby() == 0)
					{
						queue->addWorkItem(new GameWorkItem(new GameWorkItemData(board, str - 1, column - 1)));
					}
				}
			}

			if (str - 1 >= 0)
			{
				Cell* cell = board->GetCell(str - 1, column);
				if (!cell->IsVisible())
				{
					cell->SetVisible(true);
					if (cell->GetNumOfBombNearby() == 0)
					{
						queue->addWorkItem(new GameWorkItem(new GameWorkItemData(board, str - 1, column)));
					}
				}
			}

			if (str - 1 >= 0 && column + 1 < boardSize)
			{
				Cell* cell = board->GetCell(str - 1, column + 1);
				if (!cell->IsVisible())
				{
					cell->SetVisible(true);
					if (cell->GetNumOfBombNearby() == 0)
					{
						queue->addWorkItem(new GameWorkItem(new GameWorkItemData(board, str - 1, column + 1)));
					}
				}
			}

			if (column + 1 < boardSize)
			{
				Cell* cell = board->GetCell(str, column + 1);
				if (!cell->IsVisible())
				{
					cell->SetVisible(true);
					if (cell->GetNumOfBombNearby() == 0)
					{
						queue->addWorkItem(new GameWorkItem(new GameWorkItemData(board, str, column + 1)));
					}
				}
			}

			if (str + 1 < boardSize && column + 1 < boardSize)
			{
				Cell* cell = board->GetCell(str + 1, column + 1);
				if (!cell->IsVisible())
				{
					cell->SetVisible(true);
					if (cell->GetNumOfBombNearby() == 0)
					{
						queue->addWorkItem(new GameWorkItem(new GameWorkItemData(board, str + 1, column + 1)));
					}
				}
			}

			if (str + 1 < boardSize)
			{
				Cell* cell = board->GetCell(str + 1, column);
				if (!cell->IsVisible())
				{
					cell->SetVisible(true);
					if (cell->GetNumOfBombNearby() == 0)
					{
						queue->addWorkItem(new GameWorkItem(new GameWorkItemData(board, str + 1, column)));
					}
				}
			}

			if (str + 1 < boardSize && column - 1 >= 0)
			{
				Cell* cell = board->GetCell(str + 1, column - 1);
				if (!cell->IsVisible())
				{
					cell->SetVisible(true);
					if (cell->GetNumOfBombNearby() == 0)
					{
						queue->addWorkItem(new GameWorkItem(new GameWorkItemData(board, str + 1, column - 1)));
					}
				}
			}
		}
	}
}

GameWorkItem::GameWorkItem(GameWorkItemData* ptr)
{
	data = ptr;
}

GameWorkItem::~GameWorkItem()
{
	delete data;
}

