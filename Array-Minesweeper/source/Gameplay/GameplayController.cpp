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

    void GameplayController::render() {  }

    void GameplayController::updateRemainingTime()
    {
        
        remaining_time -= ServiceLocator::getInstance()->getTimeService()->getDeltaTime();
    }

    bool GameplayController::isTimeOver() { return (remaining_time <= 1); }

    void GameplayController::restart()
    {
        
        board_service->resetBoard();
        remaining_time = max_level_duration;
    }

    int GameplayController::getMinesCount() { return board_service->getMinesCount(); }

    float GameplayController::getRemainingTime() { return remaining_time; }

   

     
}