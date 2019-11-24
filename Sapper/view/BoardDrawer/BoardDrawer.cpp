#include "BoardDrawer.h"
#include <string> 

void BoardDrawer::Draw(Board* board, HWND hWnd, HDC hdc, bool finished)
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
	RECT rect;
	HFONT hFont;
	static HBRUSH hBrush = CreateSolidBrush(RGB(50, 150, 250));

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

	
	if (boardLength > 150)
	{
		x = startX;
		y = startY;
		_extraLength = extraLength;
		cellStartX = (int*)malloc(sizeof(int) * board->GetBoardSize());
		cellStartY = (int*)malloc(sizeof(int) * board->GetBoardSize());

		for (int i = 0; i < board->GetBoardSize() + 1; i++)
		{
			cellStartY[i] = y + i * cellLength;
			
			MoveToEx(hdc, x, y + i * cellLength, nullptr);
			LineTo(hdc, x + boardLength, y + i * cellLength);
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

			MoveToEx(hdc, x + i * cellLength, y, nullptr);
			LineTo(hdc, x + i * cellLength, y + boardLength);
			if (_extraLength)
			{
				x++;
				_extraLength--;
			}
		}
		
		hFont = CreateFont(cellLength / 2, cellLength / 3, 0, 0, FW_DONTCARE, FALSE, FALSE,
			FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH,
			TEXT("Times New Roman"));
		SelectObject(hdc, hFont);

		for (int row = 0; row < board->GetBoardSize(); row++)
		{
			for (int col = 0; col < board->GetBoardSize(); col++)
			{
				Cell* cell = board->GetCell(row, col);
				if (finished || true)
				{
					if(cell->IsBombed())
					{
						SetTextColor(hdc, RGB(0, 0, 0));
						TextOutA(hdc, cellStartX[row] + cellLength / 3, cellStartY[col] + cellLength / 3, "*", 1);
					}
				}
				if (cell->IsVisible())
				{
					if (cell->GetNumOfBombNearby())
					{
						SetTextColor(hdc, RGB(0, 0, 0));
						TextOutA(hdc, cellStartX[row] + cellLength / 3, cellStartY[col] + cellLength / 3, (std::to_string(cell->GetNumOfBombNearby())).c_str(), 1);
					}
					else
					{
						rect.top = cellStartY[col] + 1;
						rect.bottom = cellStartY[col + 1];
						rect.left = cellStartX[row] + 1; 
						rect.right = cellStartX[row + 1]; 

						FillRect(hdc, &rect, hBrush);
					}
				}
				else
				{
					if (cell->IsMarked() && !finished)
					{
						SetTextColor(hdc, RGB(200, 0, 0));
						TextOutA(hdc, cellStartX[row] + cellLength / 3, cellStartY[col] + cellLength / 3, "?", 1);
					}
				}
			}
		}
	}
}
