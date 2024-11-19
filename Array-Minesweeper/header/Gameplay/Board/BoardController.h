#pragma once
#include <sfml/Graphics.hpp>
#include "../../header/Gameplay/Cell/CellController.h"
#include "../Cell/CellView.h"
#include "../Cell/CellController.h"
#include "../Cell/CellView.h"

namespace Gameplay
{
    namespace Board
    {

        class BoardView;

        class BoardController
        {
        public:
            static const int number_of_rows = 9;
            static const int number_of_colums = 9;
            static const int mines_count = 8;
            CellController* board[number_of_rows][number_of_colums];
            BoardController();
            ~BoardController();

            int getMinesCount();

            void initialize();
            void update();
            void flagCell(sf::Vector2i cell_position);
            void render();
            void reset();

        private:
            BoardView* board_view;
            Cell::CellController* cell;


            int flagged_cells;
            void createBoard();
            void initializeCells();
            void openCell(sf::Vector2i cell_position);
            void processCellInput(Cell::CellController* cell_controller, UI::UIElement::ButtonType button_type);
            void destroy();
            void resetBoard();
            void deleteBoard();
        };
    }
}