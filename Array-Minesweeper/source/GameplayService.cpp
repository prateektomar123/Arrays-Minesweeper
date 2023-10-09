#include "../header/GameplayService.h"
#include "../header/GameplayController.h"
#include "../header/GameService.h"

GameplayService::GameplayService()
{
	gameplay_controller = nullptr;
	createControllers();
}

GameplayService::~GameplayService()
{
	destroy();
}

void GameplayService::createControllers()
{
	gameplay_controller = new GameplayController();
}

void GameplayService::initialize()
{
	gameplay_controller->initialize();
}

void GameplayService::update()
{
	switch (GameService::getGameState())
	{
	case::GameState::GAMEPLAY:
		gameplay_controller->update();
		break;
	}
}

void GameplayService::render()
{
	switch (GameService::getGameState())
	{
	case::GameState::GAMEPLAY:
		gameplay_controller->render();
		break;
	}
}

GameplayController* GameplayService::getGameplayController()
{
	return gameplay_controller;
}

void GameplayService::destroy()
{
	delete(gameplay_controller);
}