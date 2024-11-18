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
	float GameplayService::getRemainingTime()
	{
		return gameplay_controller->getRemainingTime();
	}
	
	void GameplayService::destroy()
	{
		delete(gameplay_controller);
	}
}