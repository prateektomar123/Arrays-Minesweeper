#include "../../header/Gameplay/GameplayController.h"
#include "../../header/Gameplay/Board/BoardService.h"
#include "../../header/Time/TimeService.h"
#include "../../header/Global/ServiceLocator.h"
#include "../../header/Main/GameService.h"

namespace Gameplay
{
    using namespace Main;
    using namespace Board;
    using namespace Global;
    using namespace Cell;
    using namespace UI::UIElement;
    using namespace Time;

    GameplayController::~GameplayController() { board_service = nullptr; }

    void GameplayController::initialize() 
    {
        board_service = ServiceLocator::getInstance()->getBoardService();
    }

    void GameplayController::update()
    {
        updateRemainingTime();

        if (isTimeOver())
            processTimerOver();
    }

    void GameplayController::render() {  }

    void GameplayController::processCellInput(CellController* cell_controller, ButtonType button_type)
    {
        board_service->processCellInput(cell_controller, button_type);
    }

    void GameplayController::processTimerOver()
    {
        switch (board_service->getBoardState())
        {
        case Gameplay::Board::BoardState::FIRST_CELL:
            beginGameOverTimer();
            break;
        case Gameplay::Board::BoardState::PLAYING:
            beginGameOverTimer();
            break;
        case Gameplay::Board::BoardState::COMPLETED:
            gameOver();
            break;
        default:
            break;
        }
    }

    void GameplayController::beginGameOverTimer()
    {
        remaining_time = restart_time;
        board_service->onBeginGameOverTimer();
        board_service->setBoardState(BoardState::COMPLETED);
    }

    void GameplayController::updateRemainingTime()
    {
        if (game_end_type == GameEndType::WON)
            return;
        remaining_time -= ServiceLocator::getInstance()->getTimeService()->getDeltaTime();
    }

    bool GameplayController::isTimeOver() { return (remaining_time <= 1); }

    void GameplayController::gameOver()
    {
        game_end_type = GameEndType::OVER; //--------------------------------------------------------USELESS
        GameService::setGameState(GameState::CREDITS);
    }

    void GameplayController::gameWon()
    {
        game_end_type = GameEndType::WON;
        board_service->onGameWon();
    }





    void GameplayController::restart()
    {
        game_end_type = GameEndType::NONE;
        board_service->resetBoard();
        remaining_time = max_level_duration;
    }

    int GameplayController::getMinesCount() { return board_service->getMinesCount(); }

    float GameplayController::getRemainingTime() { return remaining_time; }
    
    void GameplayController::onCellOpen()
    {
        if (board_service->areAllCellOpen())
        {
            gameWon();
        }
    }

    void GameplayController::onBlast()
    {
        beginGameOverTimer();
    }
}