#include "../header/GameplayController.h"
#include "../header/GameService.h"
#include "../header/ServiceLocator.h"
#include "../header/Cell.h"
#include "../header/EventService.h"
#include "../header/SoundService.h"
#include "../header/GraphicService.h"
#include "../header/TimeService.h"

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
    updateRemainingTimer();
    checkGameWinCondition();
}

void GameplayController::render()
{
    ServiceLocator::getInstance()->getGraphicService()->drawBackground();
    game_window->draw(board_sprite);
    drawAllCells();
}

void GameplayController::updateRemainingTimer()
{
    remaining_time -= ServiceLocator::getInstance()->getTimeService()->getDeltaTime();

    if (remaining_time <= 1)
    {
        if (b_game_over)
        {
            GameService::setGameState(GameState::CREDITS);
        }
        else
        {
            gameOver();
        }
    }
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
    if (b_first_click)
    {
        populateBoard(x, y);
        b_first_click = false;
    }
    
    switch (board[x][y]->getCellType())
    {
    case::CellType::EMPTY:
        openEmptyCells(x, y);
        break;
    case::CellType::MINE:
        gameOver();
        break;
    }

    board[x][y]->openCell();
}

void GameplayController::flagCell(int x, int y)
{
    switch (board[x][y]->getCellState())
    {
    case::CellState::FLAGGED:
        flagged_cells--;
        break;
    case::CellState::HIDDEN:
        flagged_cells++;
        break;
    }

    board[x][y]->flagCell();
}

void GameplayController::openEmptyCells(int x, int y)
{
    if (board[x][y]->getCellState() == CellState::OPEN) return;

    board[x][y]->openCell(false);

    for (int a = -1; a < 2; a++)
    {
        for (int b = -1; b < 2; b++)
        {
            // Check for cells inside grid.
            if ((a == 0 && b == 0) || (a + x < 0 || b + y < 0 || number_of_colums == a + x || number_of_rows == b + y))
            {
                continue;
            }

            if (board[x][y]->getCellType() == CellType::EMPTY)
            {
                openEmptyCells(a + x, b + y);
            }
        }
    }
}

void GameplayController::openAllCells()
{
    if (b_first_click)
    {
        populateBoard(0, 0);
    }

    for (int a = 0; a < number_of_rows; ++a)
    {
        for (int b = 0; b < number_of_colums; ++b)
        {
            board[a][b]->openCell();
        }
    }
}

void GameplayController::populateBoard(int x, int y)
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
        if (board[i][j]->getCellType() == CellType::MINE || (x == i && y == j))
        {
            a--;
        }
        else
        {
            board[i][j]->setCellType(CellType::MINE);
        }
    }

    for (int a = 0; a < number_of_rows; a++)
    {
        for (int b = 0; b < number_of_colums; b++)
        {
            if (board[a][b]->getCellType() != CellType::MINE)
            {
                CellType type = static_cast<CellType>(countMinesAround(a, b));
                board[a][b]->setCellType(type);
            }
        }
    }
}

int GameplayController::countMinesAround(int x, int y)
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

            if (board[a + x][b + y]->getCellType() == CellType::MINE)
            {
                mines_around++;
            }
        }
    }

    return mines_around;
}

void GameplayController::checkGameWinCondition()
{
    if (b_game_over) return;

    int total_cell_count = number_of_rows * number_of_colums;
    int open_cell_count = 0;

    for (int a = 0; a < number_of_rows; a++)
    {
        for (int b = 0; b < number_of_colums; b++)
        {
            if (board[a][b]->getCellState() == CellState::OPEN)
            {
                open_cell_count++;
            }
        }
    }

    if (total_cell_count - open_cell_count == mines_count)
    {
        gameOver();
    }
}

void GameplayController::gameOver()
{
    openAllCells();

    b_game_over = true;
    remaining_time = restart_time;
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

    resetVariables();
}

void GameplayController::resetVariables()
{
    b_game_over = false;
    b_first_click = true;
    remaining_time = max_level_duration;
    flagged_cells = 0;
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
    return mines_count - flagged_cells;
}

float GameplayController::getRemainingTime()
{
    return remaining_time;
}
