#include "../../header/Gameplay/Board/Cell.h"
#include "../../header/Sound/SoundService.h"
#include "../../header/Global/ServiceLocator.h"

namespace Gameplay
{
    namespace Board
    {
        using namespace Global;
        using namespace Sound;

        Cell::Cell(int x, int y)
        {
            reset();
            x_index = x;
            y_index = y;
        }

        void Cell::initialize(float width, float height)
        {
            game_window = ServiceLocator::getInstance()->getGraphicService()->getGameWindow();
            cell_width = width;
            cell_height = height;
        }

        CellState Cell::getCellState()
        {
            return cell_state;
        }

        CellType Cell::getCellType()
        {
            return cell_type;
        }

        void Cell::setCellState(CellState state)
        {
            cell_state = state;
        }

        void Cell::setCellType(CellType type)
        {
            cell_type = type;
        }

        int Cell::getMinesAround()
        {
            return mines_around;
        }

        void Cell::drawCell(sf::Sprite* cell_sprite)
        {
            float x = cell_left_offset + y_index * cell_width;
            float y = cell_top_offset + x_index * cell_height;

            int index = static_cast<int>(cell_type);

            switch (cell_state)
            {
            case::Gameplay::Board::CellState::HIDDEN:
                cell_sprite->setTextureRect(sf::IntRect(10 * tile_height, 0, tile_height, tile_height));
                break;

            case::Gameplay::Board::CellState::OPEN:
                cell_sprite->setTextureRect(sf::IntRect(index * tile_height, 0, tile_height, tile_height));
                break;

            case::Gameplay::Board::CellState::FLAGGED:
                cell_sprite->setTextureRect(sf::IntRect(11 * tile_height, 0, tile_height, tile_height));
                break;
            }

            cell_sprite->setPosition(x, y);
            game_window->draw(*cell_sprite);
        }

        void Cell::openCell()
        {
            if (cell_state != CellState::FLAGGED)
            {
                setCellState(CellState::OPEN);
                ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::BUTTON_CLICK);
            }
        }

        void Cell::flagCell()
        {
            switch (cell_state)
            {
            case::Gameplay::Board::CellState::FLAGGED:
                setCellState(CellState::HIDDEN);
                break;
            case::Gameplay::Board::CellState::HIDDEN:
                setCellState(CellState::FLAGGED);
                break;
            }

            ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::FLAG);
        }

        void Cell::reset()
        {
            std::srand(static_cast<unsigned int>(std::time(nullptr)));
            int randomNumber = std::rand() % 9;

            setCellState(CellState::HIDDEN);
            setCellType(static_cast<CellType>(randomNumber));
            mines_around = 0;
        }
    }
}