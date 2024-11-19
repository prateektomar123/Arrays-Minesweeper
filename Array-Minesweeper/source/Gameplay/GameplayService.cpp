#include "../../header/Gameplay/GameplayService.h"

namespace Gameplay
{
	GameplayService::GameplayService()
	{
		gameplay_controller = nullptr;
		createController();
	}

	GameplayService::~GameplayService()
	{
		destroy();
	}

	void GameplayService::createController()
	{
		gameplay_controller = new GameplayController();
	}

	void GameplayService::initialize()
	{
		
	}

	void GameplayService::update()
	{
		
	}

	void GameplayService::render()
	{
		
	}

	void GameplayService::startGame()
	{
		
	}

	void GameplayService::endGame(GameResult result)
	{
		// This function forwards the result of the game to the controller's endGame function.
		gameplay_controller->endGame(result); // Trigger the endGame logic in the controller.
	}
	float GameplayService::getRemainingTime()
	{
		return gameplay_controller->getRemainingTime();
	}
	int GameplayService::getMinesCount()
	{
		return gameplay_controller->getMinesCount();
	}
	void GameplayService::destroy()
	{
		delete(gameplay_controller);
	}
}