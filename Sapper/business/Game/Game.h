	#pragma once
	#include"GameConfigs.h"
	#include "../Board/Board.h"
	#include <iostream>
	#include "../WorkQueue/WorkQueue.h"
	#include "../WorkQueue/GameWorkItem.h"

	class Game
	{
	public:
		Game(GameConfigs* configs);

		~Game();

		void MakeStep(int str, int column);

		void RestardGame(GameConfigs* configs);

		Board* GetBoard();

		int GetBombCount();

		bool IsFinished();

		bool IsWon();

	private:
		void MakeInitStep(int str, int column);

		void NotifyCellsBombIsNear(int str, int column);

		Board* board;

		WorkQueue* workQueue;

		bool isItinStepMade;

		bool finished;

		bool won;

		int bombCount;
	};

