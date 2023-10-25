#pragma once
#include <SFML/Graphics.hpp>

namespace Gameplay
{
    namespace Board
    {
        enum class CellState
        {
            HIDDEN,
            OPEN,
            FLAGGED,
        };

        enum class CellType
        {
            EMPTY,
            ONE,
            TWO,
            THREE,
            FOUR,
            FIVE,
            SIX,
            SEVEN,
            EIGHT,
            MINE,
        };

        class Cell
        {
        private:
            const float cell_top_offset = 274.f;
            const float cell_left_offset = 583.f;

            const int tile_height = 32;
            const int tile_width = 16;

            sf::RenderWindow* game_window;

            CellState cell_state;
            CellType cell_type;

            float cell_width;
            float cell_height;

            int x_index;
            int y_index;
            int mines_around;

        public:
            Cell(int x, int y);

            void initialize(float cell_width, float cell_height);
            void drawCell(sf::Sprite* cell_sprite);
            void flagCell();
            void openCell();

            CellState getCellState();
            CellType getCellType();
            void setCellState(CellState state);
            void setCellType(CellType type);
            int getMinesAround();
            void reset();
        };
    }
}