#pragma once
#include "../../header/Gameplay/GameplayController.h"

namespace Gameplay
{
	class GameplayService
	{
	private:
		GameplayController* gameplay_controller;

		void createControllers();
		void destroy();

	public:
		GameplayService();
		~GameplayService();

		void initialize();
		void update();
		void render();

		int getMinesCount();
		float getRemainingTime();

		GameplayController* getGameplayController();
	};
}