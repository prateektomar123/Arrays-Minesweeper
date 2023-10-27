#include "../../header/Gameplay/GameplayController.h"
#include "../../header/Gameplay/Board/BoardController.h"
#include "../../header/Global/TimeService.h"
#include "../../header/Global/ServiceLocator.h"
#include "../../header/Main/GameService.h"

namespace Gameplay
{
    using namespace Main;
    using namespace Board;
    using namespace Global;
    using namespace Cell;
    using namespace UI::UIElement;

    GameplayController::GameplayController() { board_controller = new BoardController(); }

    GameplayController::~GameplayController() { delete (board_controller); }

    void GameplayController::initialize() { board_controller->initialize(); }

    void GameplayController::update()
    {
        updateRemainingTime();
        if (isGameOver()) processGameOver();

        board_controller->update(); 
    }

    void GameplayController::render() { board_controller->render(); }

    void GameplayController::processCellInput(CellController* cell_controller, ButtonType button_type) 
    {
        board_controller->processCellInput(cell_controller, button_type); 
    }

    void GameplayController::processGameOver()
    {
        switch (board_controller->getBoardState())
        {
        case BoardState::GAME_OVER:
            GameService::setGameState(GameState::CREDITS);
            break;
        default:
            gameOver();
            break;
        }
    }

    void GameplayController::updateRemainingTime() 
    {
        remaining_time -= ServiceLocator::getInstance()->getTimeService()->getDeltaTime();
    }

    bool GameplayController::isGameOver() { return (remaining_time <= 1); }

    void GameplayController::gameOver()
    {
        remaining_time = restart_time;
        board_controller->setBoardState(BoardState::GAME_OVER);
    }

    void GameplayController::restart() 
    { 
        board_controller->reset(); 
        remaining_time = max_level_duration;
    }

    int GameplayController::getMinesCount() { return board_controller->getMinesCount(); }

    float GameplayController::getRemainingTime() { return remaining_time; }
}