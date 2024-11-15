#pragma once
#include <sfml/Graphics.hpp>
#include "../../header/UI/UIElement/ButtonView.h"
#include "BoardView.h"


namespace Gameplay
{
    namespace Board
    {
        class BoardController
        {
        public:
            static const int number_of_rows = 9;
            static const int number_of_colums = 9;
            static const int mines_count = 8;

            BoardController();
            ~BoardController();

            void initialize();
            void update();
            void render();
            void reset();

        private:
            BoardView* board_view;

            void resetBoard();
            void createBoard();
            void destroy();
            void deleteBoard();
        };
    }
}