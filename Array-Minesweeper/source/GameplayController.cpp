#include "../header/GameplayController.h"
#include "../header/Cell.h"
#include "../header/EventService.h"
#include "../header/ServiceLocator.h"
#include "../header/SoundService.h"
#include "../header/GraphicService.h"

/*
// This constructor uses a specific C++ feature called member initializer list to initialize class members.
// In this case, it initializes the 'random_engine' member and provides it with an initial value.
// The syntax for member initializer list is : member_name(initial_value)
*/
GameplayController::GameplayController() : random_engine(random_device())
{
    game_window = nullptr;
    createBoard();
}

GameplayController::~GameplayController() { deleteBoard(); }

void GameplayController::initialize()
{
    game_window = ServiceLocator::getInstance()->getGameWindow();

    initializeBoardImage();
    initializeCellImage();
    resetBoard();
}

void GameplayController::createBoard()
{
    board = new Cell**[number_of_rows];

    for (int a = 0; a < number_of_rows; a++)
    {
        board[a] = new Cell*[number_of_colums];

        for (int b = 0; b < number_of_colums; b++)
        {
            board[a][b] = new Cell();
        }
    }
}

void GameplayController::initializeBoardImage()
{
    if (board_texture.loadFromFile("assets/textures/board.png"))
    {
        board_texture.setSmooth(true);
        board_sprite.setTexture(board_texture);
        scaleBoardImage();
        setBoardImagePosition();
    }
}

void GameplayController::scaleBoardImage()
{
    // Calculate the scaling factor to fit the entire height
    float scaleFactor = static_cast<float>(game_window->getSize().y) / board_texture.getSize().y;
    board_sprite.setScale(scaleFactor, scaleFactor);

    board_width = board_texture.getSize().x * scaleFactor;
    board_height = board_texture.getSize().y * scaleFactor;
}

void GameplayController::setBoardImagePosition()
{
    board_sprite.setPosition((game_window->getSize().x - board_sprite.getGlobalBounds().width) / 2.0f, 0.0f);
}

void GameplayController::initializeCellImage()
{
    if (cell_texture.loadFromFile("assets/textures/cells.jpeg"))
    {
        cell_texture.setSmooth(true);
        cell_sprite.setTexture(cell_texture);
        scaleCellImage();
    }
}

void GameplayController::scaleCellImage()
{
    cell_width = calculateCellWidth();
    cell_height = calculateCellHeight();

    float scaleFactor = cell_height / tile_height;
    cell_sprite.setScale(scaleFactor, scaleFactor);
}

float GameplayController::calculateCellWidth()
{
    return (board_width - board_width_offset) / static_cast<float>(number_of_colums);
}

float GameplayController::calculateCellHeight()
{
    return (board_height - board_height_offset) / static_cast<float>(number_of_rows);
}

void GameplayController::update()
{
    handleMouseInteractions();
}

void GameplayController::render()
{
    game_window->draw(board_sprite);
    drawAllCells();
}

void GameplayController::drawAllCells()
{
    for (int row = 0; row < number_of_rows; ++row)
    {
        for (int col = 0; col < number_of_colums; ++col)
        {
            drawCell(row, col);
        }
    }
}

void GameplayController::drawCell(int row, int col)
{
    float x = cells_left_offset + col * cell_width;
    float y = cells_top_offset + row * cell_height;

    int index = static_cast<int>(board[row][col]->getCellType());

    switch (board[row][col]->getCellState())
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

void GameplayController::handleMouseInteractions()
{
    sf::Vector2i cellIndex = getCellFromMousePosition();
    if (!isValidCellIndex(cellIndex)) return;

    EventService* event_service = ServiceLocator::getInstance()->getEventService();

    if (event_service->pressedLeftMouseButton())
    {
        openCell(cellIndex.x, cellIndex.y);
    }

    if (event_service->pressedRightMouseButton())
    {
        flagCell(cellIndex.x, cellIndex.y);
    }
}

sf::Vector2i GameplayController::getCellFromMousePosition()
{
    sf::Vector2i mouse_position = sf::Mouse::getPosition(*game_window);

    sf::Vector2f adjusted_mouse_position(static_cast<float>(mouse_position.x) - cells_left_offset,
        static_cast<float>(mouse_position.y) - cells_top_offset);

    // Calculate cell coordinates based on the adjusted mouse position
    int cell_column = static_cast<int>(adjusted_mouse_position.x / cell_width);
    int cell_row = static_cast<int>(adjusted_mouse_position.y / cell_height);

    return sf::Vector2i(cell_row, cell_column);
}

bool GameplayController::isValidCellIndex(sf::Vector2i cellIndex)
{
    return cellIndex.x >= 0 && cellIndex.x < number_of_rows && 
        cellIndex.y >= 0 && cellIndex.y < number_of_colums;
}

void GameplayController::openCell(int x, int y)
{
    if (board[x][y]->getCellState() != CellState::FLAGGED)
    {
        board[x][y]->setCellState(CellState::OPEN);
        ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::BUTTON_CLICK);
    }
}

void GameplayController::flagCell(int x, int y)
{
    switch (board[x][y]->getCellState())
    {
    case::CellState::FLAGGED:
        board[x][y]->setCellState(CellState::HIDDEN);
        break;
    case::CellState::HIDDEN:
        board[x][y]->setCellState(CellState::FLAGGED);
        break;
    }

    ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::FLAG);
}

void GameplayController::restart() { resetBoard(); }

void GameplayController::resetBoard()
{
    for (int row = 0; row < number_of_rows; ++row)
    {
        for (int col = 0; col < number_of_colums; ++col)
        {
            resetCell(row, col);
        }
    }

    move_timer = max_move_time;
}

void GameplayController::resetCell(int row, int col)
{
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int randomNumber = std::rand() % 9;

    board[row][col]->setCellState(CellState::HIDDEN);
    board[row][col]->setCellType(static_cast<CellType>(randomNumber));
}

void GameplayController::deleteBoard()
{
    for (int a = 0; a < number_of_rows; a++)
    {
        for (int b = 0; b < number_of_colums; b++)
        {
            delete board[a][b];
        }

        delete[] board[a];
    }

    delete[] board;
}

int GameplayController::getMinesCount()
{
    return mines_count;
}

float GameplayController::getRemainingTimer()
{
    return move_timer;
}