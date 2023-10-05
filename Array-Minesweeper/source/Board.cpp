#include "../header/Board.h"
#include "../header/Cell.h"
#include "../header/EventService.h"
#include "../header/ServiceLocator.h"
#include "../header/SoundService.h"
#include "../header/GraphicService.h"
#include "../header/TimeService.h"

Board::Board() : random_engine(random_device())
{
    game_window = nullptr;
    b_left_mouse_button_pressed = true;
    b_right_mouse_button_pressed = true;
    
    createCells();
}

Board::~Board()
{
    deleteCells();
}

void Board::initialize()
{
    game_window = ServiceLocator::getInstance()->getGameWindow();

    initializeBoardImage();
    initializeCellImage();
    resetBoard();
}

void Board::createCells()
{
    // Here we're adding cells to the cells vector.
    for (int a = 0; a < number_of_rows; a++)
    {
        std::vector<Cell*> cell_row;

        for (int b = 0; b < number_of_colums; b++)
        {    
            Cell* cell = createCell();
            cell_row.push_back(cell);
        }

        cells.push_back(cell_row);
    }
}

Cell* Board::createCell()
{
    Cell* cell = new Cell();
    return cell;
}

void Board::initializeBoardImage()
{
    if (board_texture.loadFromFile("assets/textures/board.png"))
    {
        board_texture.setSmooth(true);
        board_sprite.setTexture(board_texture);
        scaleBoardImage();
        setBoardImagePosition();
    }
}

void Board::scaleBoardImage()
{
   // Calculate the scaling factor to fit the entire height
   float scaleFactor = static_cast<float>(game_window->getSize().y) / board_texture.getSize().y;
   board_sprite.setScale(scaleFactor, scaleFactor);

   board_width = board_texture.getSize().x * scaleFactor;
   board_height = board_texture.getSize().y * scaleFactor;
}

void Board::setBoardImagePosition()
{
    board_sprite.setPosition((game_window->getSize().x - board_sprite.getGlobalBounds().width) / 2.0f, 0.0f);
}

void Board::initializeCellImage()
{
    if (cell_texture.loadFromFile("assets/textures/cells.jpeg"))
    {
        cell_texture.setSmooth(true);
        cell_sprite.setTexture(cell_texture);
        scaleCellImage();
    }
}

void Board::scaleCellImage()
{
    cell_width = (board_width - board_width_offset) / static_cast<float>(number_of_colums);
    cell_height = (board_height - board_height_offset) / static_cast<float>(number_of_rows);

    float scaleFactor = cell_height / tile_height;
    cell_sprite.setScale(scaleFactor, scaleFactor);
}

void Board::update()
{
    handleMouseInteractions();
    updateMoveTimer();
}

void Board::render()
{
    game_window->draw(board_sprite);
    drawAllCells();
}

void Board::updateMoveTimer()
{
    move_timer -= ServiceLocator::getInstance()->getTimeService()->getDeltaTime();

    if (move_timer <= 1)
    {
        resetBoard();
    }
}

void Board::drawAllCells()
{
    for (int row = 0; row < number_of_rows; ++row) 
    {
        for (int col = 0; col < number_of_colums; ++col) 
        {
            drawCell(row, col);
        }
    }
}

void Board::drawCell(int row, int col)
{
    float x = cells_left_offset + col * cell_width;
    float y = cells_top_offset + row * cell_height;

    int index = static_cast<int>(cells[row][col]->getCellType());

    switch (cells[row][col]->getCellState())
    {
    case::CellState::HIDDEN:
        cell_sprite.setTextureRect(sf::IntRect(10 * tile_height, 0, tile_height, tile_height));
        break;

    case::CellState::OPEN: 
        cell_sprite.setTextureRect(sf::IntRect(index * tile_height, 0, tile_height, tile_height));
        break;

    case::CellState::FLAGGED:
        cell_sprite.setTextureRect(sf::IntRect(11 * tile_height, 0, tile_height, tile_height));
        break;
    }

    cell_sprite.setPosition(x, y);
    game_window->draw(cell_sprite);
}

void Board::handleMouseInteractions()
{
    EventService* event_service = ServiceLocator::getInstance()->getEventService();
    sf::Vector2i cellIndex = getCellFromMousePosition();

    if (!b_left_mouse_button_pressed && event_service->pressedLeftMouseButton() && cellIndex.x != -1 && cellIndex.y != -1) 
    {
        openCell(cellIndex.x, cellIndex.y);
        b_left_mouse_button_pressed = true;
    }

    if (!b_right_mouse_button_pressed && event_service->pressedRightMouseButton() && cellIndex.x != -1 && cellIndex.y != -1)
    {  
        flagCell(cellIndex.x, cellIndex.y);
        b_right_mouse_button_pressed = true;
    }

    if (!event_service->pressedLeftMouseButton())
    {
        b_left_mouse_button_pressed = false;
    }

    if (!event_service->pressedRightMouseButton())
    {
        b_right_mouse_button_pressed = false;
    }
}

sf::Vector2i Board::getCellFromMousePosition()
{
    sf::Vector2i mouse_position = sf::Mouse::getPosition(*game_window);

    sf::Vector2f adjusted_mouse_position(static_cast<float>(mouse_position.x) - cells_left_offset,
        static_cast<float>(mouse_position.y) - cells_top_offset);

    // Calculate cell coordinates based on the adjusted mouse position
    int cell_column = static_cast<int>(adjusted_mouse_position.x / cell_width);
    int cell_row = static_cast<int>(adjusted_mouse_position.y / cell_height);

    // Check if the adjusted mouse position falls within any cell
    if (cell_column >= 0 && cell_column < number_of_colums && cell_row >= 0 && cell_row < number_of_rows) {
        return sf::Vector2i(cell_row, cell_column);
    }

    return sf::Vector2i(-1, -1);
}

void Board::flagCell(int x, int y)
{
    switch(cells[x][y]->getCellState())
    {
    case::CellState::FLAGGED:
        cells[x][y]->setCellState(CellState::HIDDEN);
        break;
    case::CellState::HIDDEN:
        cells[x][y]->setCellState(CellState::FLAGGED);
        break;
    }

    ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::FLAG);
}

void Board::openCell(int x, int y)
{
    if (cells[x][y]->getCellState() != CellState::FLAGGED || cells[x][y]->getCellState() != CellState::OPEN)
    {
        if (b_first_click)
        {
            populateBoard(x, y);
            b_first_click = false;
        }

        switch (cells[x][y]->getCellType())
        {
        case::CellType::EMPTY:
            openEmptyCells(x, y);
            break;
        default:
            cells[x][y]->setCellState(CellState::OPEN);
            break;
        }

        move_timer = max_move_time;
        ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::BUTTON_CLICK);
    }
}

void Board::populateBoard(int x, int y)
{
    // Co-ordinate distribution i.e. selecting random position for mines.
    std::uniform_int_distribution<int> x_distribution(0, number_of_colums - 1);
    std::uniform_int_distribution<int> y_distribution(0, number_of_rows - 1);

    // Generate mines.
    for (int a = 0; a < mines_count; a++)
    {
        int i = static_cast<int>(x_distribution(random_engine));
        int j = static_cast<int>(y_distribution(random_engine));

        // If the cell is already mine or it's a cell that the player wants to open.
        if (cells[i][j]->getCellType() == CellType::MINE || (x == i && y == j))
        {
            a--;
        }
        else
        {
            cells[i][j]->setCellType(CellType::MINE);
        }
    }

    for(int a = 0; a < number_of_rows; a++)
    {
        for (int b = 0; b < number_of_colums; b++)
        {
            if (cells[a][b]->getCellType() != CellType::MINE)
            {
                CellType type = static_cast<CellType>(countMinesAround(a, b));
                cells[a][b]->setCellType(type);
            }
        }
    }
}

void Board::openEmptyCells(int x, int y)
{
    if (cells[x][y]->getCellState() == CellState::OPEN || cells[x][y]->getCellType() != CellType::EMPTY) return;

    cells[x][y]->setCellState(CellState::OPEN);

    for (int a = -1; a < 2; a++)
    {
        for (int b = -1; b < 2; b++)
        {
            // Check for cells inside grid.
            if ((a == 0 && b == 0) || (a + x < 0 || b + y < 0 || number_of_colums == a + x || number_of_rows == b + y))
            {
                continue;
            }

            openEmptyCells(a + x, b + y);
        }
    }
}

int Board::countMinesAround(int x, int y)
{
    int mines_around = 0;

    for (int a = -1; a < 2; a++)
    {
        for (int b = -1; b < 2; b++)
        {
            if ((a == 0 && b == 0) || (a + x < 0 || b + y < 0 || number_of_colums == a + x || number_of_rows == b + y))
            {
                continue;
            }

            if (cells[a + x][b + y]->getCellType() == CellType::MINE)
            {
                mines_around++;
            }
        }
    }

    return mines_around;
}

int Board::getMinesCount()
{
    return mines_count;
}

float Board::getMoveTimer()
{
    return move_timer;
}

void Board::resetBoard()
{
    for (int row = 0; row < number_of_rows; ++row)
    {
        for (int col = 0; col < number_of_colums; ++col)
        {
            resetCell(row, col);
        }
    }

    b_first_click = true;
    move_timer = max_move_time;
}

void Board::resetCell(int row, int col)
{
    cells[row][col]->setCellState(CellState::HIDDEN);
    cells[row][col]->setCellType(static_cast<CellType>(CellType::EMPTY));
}

void Board::deleteCells()
{
    for (int a = 0; a < number_of_rows; a++)
    {
        std::vector<Cell*> cell_row;

        for (int b = 0; b < number_of_colums; b++)
        {
            delete(cells[a][b]);
        }
    }
}