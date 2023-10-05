#include "../header/GameplayController.h"
#include "../header/GameService.h"
#include "../header/Board.h"

GameplayController::GameplayController()
{
	board = nullptr;
	createBoard();
}

GameplayController::~GameplayController()
{
	delete(board);
}

void GameplayController::createBoard()
{
	board = new Board();
}

void GameplayController::initialize()
{
	board->initialize();
}

void GameplayController::update()
{
	board->update();
}

void GameplayController::render()
{
	board->render();
}

void GameplayController::restart()
{
	board->resetBoard();
}

float GameplayController::getMinesCount()
{
	return board->getMinesCount();
}

float GameplayController::getRemainingTimer()
{
	return board->getMoveTimer();
}
