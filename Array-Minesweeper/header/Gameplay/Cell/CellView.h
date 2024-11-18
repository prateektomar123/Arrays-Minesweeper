#pragma once
#include "../../header/UI/UIElement/ButtonView.h"

namespace Gameplay
{
    namespace Cell
    {
        class CellController;

        class CellView
        {
        private:

            const int tile_size = 32;
            const int slice_count = 12;

            UI::UIElement::ButtonView* cell_button;
            CellController* cell_controller;

            void initializeButtonImage(float width, float height);
            void setCellTexture();

        public:
            CellView(CellController* controller);
            ~CellView();

            void initialize(float width, float height);
            void update();
            void render();
        };
    }
}