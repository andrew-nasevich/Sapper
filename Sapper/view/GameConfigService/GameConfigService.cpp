#include "GameConfigService.h"

GameConfigs* GameConfigService::CreateGameConfigs(GameDifficulty difficulty)
{
	return new GameConfigs(difficulty);
}