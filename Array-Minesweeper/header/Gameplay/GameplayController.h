#pragma once
#include "../../header/Gameplay/Board/BoardService.h"
#include "../../header/UI/UIElement/ButtonView.h"
#include <SFML/Graphics.hpp>

namespace Gameplay
{
	using namespace Gameplay::Board;
	class GameplayController
	{
		enum class GameResult
		{
			NONE,
			WON,
			LOST
		};

	private:
		const float max_level_duration = 301.0f;
		const float game_over_time = 11.f;
		BoardService* board_service;
		float remaining_time;

		GameResult game_result;

		void updateRemainingTime();

		void beginGameOverTimer();

	public:
		~GameplayController();

		void initialize();
		void update();
		bool isTimeOver();
		void endGame(GameResult result);
		void gameLost();
		void gameWon();
		void render();

		void restart();
		

		void showCredits();

		int getMinesCount();
		float getRemainingTime();
	};
}