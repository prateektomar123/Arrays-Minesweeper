#include "../../header/Gameplay/GameplayService.h"

namespace Gameplay
{
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

	void GameplayService::startGame()
	{
		gameplay_controller->restart();
	}

	void GameplayService::processCellInput(Cell::CellController* cell_controller, UI::UIElement::ButtonType button_type)
	{
		gameplay_controller->processCellInput(cell_controller, button_type);
	}

	int GameplayService::getMinesCount()
	{
		return gameplay_controller->getMinesCount();
	}

	float GameplayService::getRemainingTime()
	{
		return gameplay_controller->getRemainingTime();
	}

	void GameplayService::destroy()
	{
		delete(gameplay_controller);
	}

	void GameplayService::onCellOpen()
	{
		gameplay_controller->onCellOpen();
	}

	void GameplayService::onBlast()
	{
		gameplay_controller->onBlast();
	}
}