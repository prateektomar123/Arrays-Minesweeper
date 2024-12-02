#pragma once
#include "../../header/Gameplay/GameplayController.h"
#include "../../header/Gameplay/Cell/CellController.h"
#include "../../header/UI/UIElement/ButtonView.h"

namespace Gameplay
{
	class GameplayService
	{
	private:
		GameplayController* gameplay_controller;

		void createController();
		void destroy();

	public:
		GameplayService();
		~GameplayService();

		void initialize();
		void update();
		void render();

		void startGame();
		void endGame(GameResult result);

		int getMinesCount();
		float getRemainingTime();
	};
}