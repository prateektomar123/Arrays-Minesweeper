#pragma once
#include "../../header/Gameplay/Board/BoardService.h"
#include "../../header/Gameplay/Cell/CellController.h"
#include "../../header/UI/UIElement/ButtonView.h"
#include <SFML/Graphics.hpp>

namespace Gameplay
{
    using namespace Gameplay::Board;

    enum class GameEndType
    {
        NONE,
        OVER,
        WON
    };
    class GameplayController
    {
    private:
        const float max_level_duration = 301.0f;
        const float restart_time = 11.f;
        BoardService* board_service;

        float remaining_time;
        GameEndType game_end_type;

        void updateRemainingTime();
        bool isTimeOver();
        void gameOver();
        void gameWon();
        void processTimerOver();
        void beginGameOverTimer();
 
    public:
        ~GameplayController();

        void initialize();
        void update();
        void render();

        void processCellInput(Cell::CellController* cell_controller, UI::UIElement::ButtonType button_type);

        void restart();
        int getMinesCount();
        float getRemainingTime();
        
        void onCellOpen();
        void onBlast();
    };
}