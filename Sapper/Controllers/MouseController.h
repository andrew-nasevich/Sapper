#pragma once
#include"../business/Game/GameConfigsEnum.h"
#include"../framework.h"
#include "MouseController.h"
#include "../business/Game/Game.h"
#include "MouseButton/MouseButton.h"
#include "../business/States/GameStatesEnum.h"

class MouseController
{
public:
	GameDifficulty ProcessChossingDifficulty(HWND hWnd, POINT cp);
	void ProcessClick(HWND hWnd, POINT p, Game* game, MouseButton mouseButton, GameStatesEnum* gameState);
};