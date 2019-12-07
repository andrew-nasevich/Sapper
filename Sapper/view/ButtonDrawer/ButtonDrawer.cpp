#include "ButtonDrawer.h"
void ButtonDrawer::Draw(HWND hWnd, HDC hdc)
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
		hFont = CreateFont(boardLength / 15, boardLength / 35, 0, 0, FW_DONTCARE, FALSE, FALSE,
			FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH,
			TEXT("Times New Roman"));
		SelectObject(hdc, hFont);

		Rectangle(hdc, startX +  boardLength / 4, startY + boardLength / 7, startX + boardLength / 2 + boardLength / 4, startY + boardLength / 7 + boardLength / 6);
		TextOut(hdc, startX + 1.65 * boardLength / 4, startY + 1.35 * boardLength / 7, L"Легко", 5);
		
		Rectangle(hdc, startX + boardLength / 4, startY + 3 * boardLength / 7, startX + boardLength / 2 + boardLength / 4, startY + 3 * boardLength / 7 + boardLength / 6);
		TextOut(hdc, startX + 1.6 * boardLength / 4, startY + 3.35 * boardLength / 7, L"Средне", 6);
		
		Rectangle(hdc, startX + boardLength / 4, startY + 5 * boardLength / 7, startX + boardLength / 2 + boardLength / 4, startY + 5 * boardLength / 7 + boardLength / 6);
		TextOut(hdc, startX + 1.6 * boardLength / 4, startY + 5.35 * boardLength / 7, L"Сложно", 6);
	}
}