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
	gameplay_controller->update();
}

void GameplayService::render()
{
	gameplay_controller->render();
}

int GameplayService::getMinesCount()
{
	return gameplay_controller->getMinesCount();
}

float GameplayService::getRemainingTime()
{
	return gameplay_controller->getRemainingTime();
}

GameplayController* GameplayService::getGameplayController()
{
	return gameplay_controller;
}

void GameplayService::destroy()
{
	delete(gameplay_controller);
}