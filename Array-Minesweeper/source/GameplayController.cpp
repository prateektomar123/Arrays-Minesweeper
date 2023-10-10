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
    initializeCells();
    resetBoard();
}

void GameplayController::createBoard()
{
    for (int a = 0; a < number_of_rows; a++)
    {
        for (int b = 0; b < number_of_colums; b++)
        {
            board[a][b] = new Cell(a, b);
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
    float scaleFactor = calculateBoardImageScaleFactor();
    board_sprite.setScale(scaleFactor, scaleFactor);

    board_width = board_sprite.getGlobalBounds().getSize().x;
    board_height = board_sprite.getGlobalBounds().getSize().y;
}

float GameplayController::calculateBoardImageScaleFactor()
{
    // Calculate the scaling factor to fit the entire height
    return static_cast<float>(game_window->getSize().y) / board_texture.getSize().y;
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

void GameplayController::initializeCells()
{
    for (int a = 0; a < number_of_rows; a++)
    {
        for (int b = 0; b < number_of_colums; b++)
        {
            board[a][b]->initialize(cell_width, cell_height);
        }
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
    ServiceLocator::getInstance()->getGraphicService()->drawBackground();
    game_window->draw(board_sprite);
    drawAllCells();
}

void GameplayController::drawAllCells()
{
    for (int row = 0; row < number_of_rows; ++row)
    {
        for (int col = 0; col < number_of_colums; ++col)
        {
            board[row][col]->drawCell(&cell_sprite);
        }
    }
}

void GameplayController::handleMouseInteractions()
{
    sf::Vector2i cellIndex = getCellFromMousePosition();
    if (!isValidCellIndex(cellIndex)) return;

    EventService* event_service = ServiceLocator::getInstance()->getEventService();

    if (event_service->pressedLeftMouseButton())
    {
        board[cellIndex.x][cellIndex.y]->openCell();
    }

    if (event_service->pressedRightMouseButton())
    {
        board[cellIndex.x][cellIndex.y]->flagCell();
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

void GameplayController::restart() { resetBoard(); }

void GameplayController::resetBoard()
{
    for (int row = 0; row < number_of_rows; ++row)
    {
        for (int col = 0; col < number_of_colums; ++col)
        {
            board[row][col]->reset();
        }
    }

    remaining_time = max_level_duration;
}

void GameplayController::deleteBoard()
{
    for (int a = 0; a < number_of_rows; a++)
    {
        for (int b = 0; b < number_of_colums; b++)
        {
            delete board[a][b];
        }
    }
}

int GameplayController::getMinesCount()
{
    return mines_count;
}

float GameplayController::getRemainingTime()
{
    return remaining_time;
}