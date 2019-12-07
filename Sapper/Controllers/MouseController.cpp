#include "MouseController.h"
#include "../business/Game/Game.h"

GameDifficulty MouseController::ProcessChossingDifficulty(HWND hWnd, POINT cp)
{
	int boardLength;
	int startX;
	int startY;

	PAINTSTRUCT ps;
	LPRECT workingSpace = new RECT();
	HFONT hFont;

	GetClientRect(hWnd, workingSpace);

	if (workingSpace->bottom - workingSpace->top < workingSpace->right - workingSpace->left)
	{
		boardLength = workingSpace->bottom - workingSpace->top;
		startX = (workingSpace->right - workingSpace->left - boardLength) / 2;
		startY = 0;
	}
	else
	{
		boardLength = workingSpace->right - workingSpace->left;
		startX = 0;
		startY = (workingSpace->bottom - workingSpace->top - boardLength) / 2;
	}

	if (boardLength > 150)
	{
		if ((cp.x > startX + boardLength / 4) && (cp.x < startX + boardLength / 2 + boardLength / 4) &&
			(cp.y > startY + boardLength / 7) && (cp.y < startY + boardLength / 7 + boardLength / 6))
		{
			return easy;
		}
		if (cp.x > startX + boardLength / 4 && cp.x < startX + boardLength / 2 + boardLength / 4 &&
			cp.y > startY + 3 * boardLength / 7 && cp.y < startY + 3 * boardLength / 7 + boardLength / 6)
		{
			return medium;
		}
		if (cp.x > startX + boardLength / 4 && cp.x < startX + boardLength / 2 + boardLength / 4 &&
			cp.y > startY + 5 * boardLength / 7 && cp.y < startY + 5 * boardLength / 7 + boardLength / 6)
		{
			return hard;
		}
	}
		return (GameDifficulty)100;
}

void MouseController::ProcessClick(HWND hWnd, POINT p, Game* game, MouseButton mouseButton, GameStatesEnum* gameState)
{
	int boardLength;
	int cellLength;
	int extraLength;
	int _extraLength;

	int startX;
	int startY;
	int x, y;
	int* cellStartX;
	int* cellStartY;
	
	bool bottom_top;
	
	LPRECT workingSpace = new RECT();
	HFONT hFont;
	Board* board = game->GetBoard();

	GetClientRect(hWnd, workingSpace);

	bottom_top = (workingSpace->bottom - workingSpace->top < workingSpace->right - workingSpace->left);
	if (bottom_top)
	{
		boardLength = workingSpace->bottom - workingSpace->top;
		startX = (workingSpace->right - workingSpace->left - boardLength) / 2;
		startY = 0;
	}
	else
	{
		boardLength = workingSpace->right - workingSpace->left;
		startX = 0;
		startY = (workingSpace->bottom - workingSpace->top - boardLength) / 2;
	}


	cellLength = boardLength / board->GetBoardSize();
	extraLength = boardLength - cellLength * board->GetBoardSize();


	if (boardLength > 150 )
	{
		x = startX;
		y = startY;
		_extraLength = extraLength;

		cellStartX = (int*)malloc(sizeof(int) * board->GetBoardSize());
		cellStartY = (int*)malloc(sizeof(int) * board->GetBoardSize());

		for (int i = 0; i < board->GetBoardSize() + 1; i++)
		{
			cellStartY[i] = y + i * cellLength;
			if (_extraLength)
			{
				y++;
				_extraLength--;
			}
		}

		x = startX;
		y = startY;
		_extraLength = extraLength;

		for (int i = 0; i < board->GetBoardSize() + 1; i++)
		{
			cellStartX[i] = x + i * cellLength;
			if (_extraLength)
			{
				x++;
				_extraLength--;
			}
		}

		for (int row = 0; row < board->GetBoardSize(); row++)
		{
			for (int col = 0; col < board->GetBoardSize(); col++)
			{
				if (p.x > cellStartX[row] && p.x < cellStartX[row] + cellLength &&
					p.y > cellStartY[col] && p.y < cellStartY[col] + cellLength)
				{
					switch (mouseButton)
					{
					case LButton:
						game->MakeStep(row, col);
						break;
					case RButton:
						game->GetBoard()->GetCell(row, col)->ChangeMarked();
					}
					
					if (game->IsFinished())
					{
						if (game->IsWon())
						{
							*gameState = Won;
						}
						else
						{
							*gameState = Lost;
						}
					}

					InvalidateRect(hWnd, NULL, true);
					UpdateWindow(hWnd);

					return;
				}
			}
		}
	}
}