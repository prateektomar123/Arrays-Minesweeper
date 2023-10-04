#include "../header/Board.h"
#include "../header/Cell.h"
#include "../header/EventService.h"
#include "../header/ServiceLocator.h"
#include "../header/SoundService.h"
#include "../header/GraphicService.h"

Board::Board() : random_engine(random_device())
{
    game_window = nullptr;
    b_left_mouse_button_pressed = false;
    b_right_mouse_button_pressed = false;

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
}

void Board::render()
{
    game_window->draw(board_sprite);
    drawAllCells();
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

void Board::openCell(int x, int y)
{
    if (cells[x][y]->getCellState() != CellState::FLAGGED)
    {
        cells[x][y]->setCellState(CellState::OPEN);
        ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::BUTTON_CLICK);
    }
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

int Board::getMinesCount()
{
    return mines_count;
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
}

void Board::resetCell(int row, int col)
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int randomNumber = std::rand() % 9;

    cells[row][col]->setCellState(CellState::HIDDEN);
    cells[row][col]->setCellType(static_cast<CellType>(randomNumber));
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