#pragma once
#include "../../header/Gameplay/Board/BoardController.h"
#include "../../header/Gameplay/Cell/CellController.h"
#include "../../header/UI/UIElement/ButtonView.h"
#include <SFML/Graphics.hpp>

namespace Gameplay
{
    class GameplayController
    {
    private:
        const float max_level_duration = 301.f;
        const float restart_time = 11.f;

        float remaining_time;

        void updateRemainingTime();
        bool isGameOver();
        void gameOver();
 
    public:
        GameplayController();
        ~GameplayController();

        void initialize();
        void update();
        void render();

        void processCellInput(Cell::CellController* cell_controller, UI::UIElement::ButtonType button_type);
        void processGameOver();

        void restart();
        int getMinesCount();
        float getRemainingTime();
    };
}