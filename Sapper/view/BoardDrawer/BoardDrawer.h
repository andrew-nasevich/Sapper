#pragma once

#include "../../business/Board/Board.h"
#include "../../framework.h"
class BoardDrawer
{
public:
	void Draw(Board* board, HWND hWnd, HDC hdc, bool finished);
};

