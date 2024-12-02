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
        using namespace Sound;

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
            sf::Vector2f cell_screen_position = getCellScreenPosition(width, height);

            cell_button->initialize("Cell", Config::cells_texture_path, width * slice_count, height, cell_screen_position);

            registerButtonCallback();
        }

        sf::Vector2f CellView::getCellScreenPosition(float width, float height)
        {
            sf::Vector2i cell_index = cell_controller->getCellPosition();

            float x_screen_position = cell_left_offset + cell_index.y * width;
            float y_screen_position = cell_top_offset + cell_index.x * height;

            return sf::Vector2f(x_screen_position, y_screen_position);
        }

        void CellView::update()
        {
            cell_button->update();
        }

        void CellView::render()
        {
            setCellTexture();
            cell_button->render();
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

        void CellView::registerButtonCallback()
        {
            cell_button->registerCallbackFuntion(std::bind(&CellView::cellButtonCallback, this, std::placeholders::_1));
        }

        void CellView::cellButtonCallback(ButtonType button_type)
        {
            ServiceLocator::getInstance()->getBoardService()->processCellInput(cell_controller, button_type);
        }
    }
}