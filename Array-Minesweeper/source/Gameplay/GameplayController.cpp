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

        
    }
    void GameplayController::endGame(GameResult result)
    {
        // The switch statement handles the different possible outcomes of the game.
        switch (result)
        {
            // In case the game is won, the gameWon() method is called.
        case GameResult::WON:
            gameWon();
            break;
            // In case the game is lost, the gameLost() method is called.
        case GameResult::LOST:
            gameLost();
            break;
            // The default case is not used here as all possible game outcomes should be WON or LOST.
        default:
            // No action is needed for default case.
            break;
        }
    }
    void GameplayController::gameLost()
    {
        // Implement game lost specific logic here.
    }

    void GameplayController::gameWon()
    {
        // Implement game won specific logic here.
    }

    void GameplayController::render() {  }

    void GameplayController::updateRemainingTime()
    {
        
        remaining_time -= ServiceLocator::getInstance()->getTimeService()->getDeltaTime();
    }
    void GameplayController::beginGameOverTimer() { remaining_time = game_over_time; }

    bool GameplayController::isTimeOver() { return (remaining_time <= 1); }

    void GameplayController::restart()
    {
        
        board_service->resetBoard();
        remaining_time = max_level_duration;
    }

    void GameplayController::showCredits() { GameService::setGameState(GameState::CREDITS); }

    void GameplayController::gameLost()
    {
        if (game_result == GameResult::NONE)
        {
            game_result = GameResult::LOST;
            beginGameOverTimer();
           /* board_service->showBoard();
            board_service->setBoardState(BoardState::COMPLETED);*/
        }
        else
        {
            showCredits();
        }

    }

    int GameplayController::getMinesCount() { return board_service->getMinesCount(); }

    float GameplayController::getRemainingTime() { return remaining_time; }

   

     
}