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
