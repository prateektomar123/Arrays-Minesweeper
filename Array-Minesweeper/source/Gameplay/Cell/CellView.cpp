#include "../../header/Gameplay/Cell/CellView.h"

#include <iostream>

#include "../../header/Gameplay/Cell/CellModel.h"
#include "../../header/Gameplay/Cell/CellController.h"
#include "../../header/Global/Config.h"
#include "../../header/Global/ServiceLocator.h"
#include "../../header/Gameplay/GameplayService.h"
#include "../../header/Sound/SoundService.h"

namespace Gameplay
{
    namespace Cell
    {
        using namespace UI::UIElement;
        using namespace Global;
        

        CellView::CellView(CellController* controller)
        {
            cell_controller = controller;
            cell_button = new ButtonView();
        }

        CellView::~CellView() { delete (cell_button); }

        void CellView::initialize(float width, float height)
        {
            initializeButtonImage(width, height);
        }


        void CellView::initializeButtonImage(float width, float height)
        {
            cell_button->initialize("Cell", Config::cells_texture_path, width * slice_count, height, new Vector2f(0, 0));
        }

        void CellView::setCellTexture()
        {
            int index = static_cast<int>(cell_controller->getCellValue());

            switch (cell_controller->getCellState())
            {
            case::Gameplay::Cell::CellState::HIDDEN:
                cell_button->setTextureRect(sf::IntRect(10 * tile_size, 0, tile_size, tile_size));
                break;

            case::Gameplay::Cell::CellState::OPEN:
                cell_button->setTextureRect(sf::IntRect(index * tile_size, 0, tile_size, tile_size));
                break;

            case::Gameplay::Cell::CellState::FLAGGED:
                cell_button->setTextureRect(sf::IntRect(11 * tile_size, 0, tile_size, tile_size));
                break;
            }
        }
        void CellView::update()
        {
            cell_button->update();
        }

        void CellView::render()
        {
            cell_button->render();
        }
    }
}