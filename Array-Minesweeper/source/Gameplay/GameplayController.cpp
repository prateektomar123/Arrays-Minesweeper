#include "../../header/Gameplay/GameplayController.h"
#include "../../header/Gameplay/Board/BoardController.h"
#include "../../header/Global/TimeService.h"
#include "../../header/Global/ServiceLocator.h"

namespace Gameplay
{
    using namespace Board;
    using namespace Global;

    GameplayController::GameplayController() { board_controller = new BoardController(); }

    GameplayController::~GameplayController() { delete (board_controller); }

    void GameplayController::initialize() { board_controller->initialize(); }

    void GameplayController::update()
    {
        updateRemainingTime();
        board_controller->update(); 
    }

    void GameplayController::render() { board_controller->render(); }

    void GameplayController::updateRemainingTime() { remaining_time -= ServiceLocator::getInstance()->getTimeService()->getDeltaTime(); }

    void GameplayController::restart() 
    { 
        board_controller->reset(); 
        remaining_time = max_level_duration;
    }

    int GameplayController::getMinesCount() { return BoardController::mines_count; }

    float GameplayController::getRemainingTime() { return remaining_time; }
}