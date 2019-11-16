#pragma once
#include "../../business/Game/GameConfigs.h"
class GameConfigService
{
public:
	GameConfigs* CreateGameConfigs(GameDifficulty difficulty);
};

