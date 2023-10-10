#pragma once
#include <SFML/Graphics.hpp>
#include <random>

class Cell;

class GameplayController
{
private:
    static const int number_of_rows = 9;
    static const int number_of_colums = 9;

    const int mines_count = 8;
    const float max_level_duration = 301.f;
    const float restart_time = 11.f;

    const float cells_top_offset = 274.f;
    const float cells_left_offset = 583.f;

    const float board_height_offset = 325.f;
    const float board_width_offset = 115.f;

    const int tile_height = 32;
    const int tile_width = 16;

    float board_height;
    float board_width;

    float cell_width;
    float cell_height;

    float remaining_time;
    int flagged_cells;

    bool b_first_click;
    bool b_game_over;

    Cell* board[number_of_rows][number_of_colums];

    sf::RenderWindow* game_window;

    // To generate random values.
    std::default_random_engine random_engine;

    // To give random seed to generator.
    std::random_device random_device;

    sf::Texture board_texture;
    sf::Sprite board_sprite;

    sf::Texture cell_texture;
    sf::Sprite cell_sprite;

    void createBoard();
    void initializeBoardImage();
    void scaleBoardImage();
    float calculateBoardImageScaleFactor();
    void setBoardImagePosition();
    void initializeCellImage();
    void initializeCells();

    void scaleCellImage();
    float calculateCellWidth();
    float calculateCellHeight();

    void handleMouseInteractions();
    bool isValidCellIndex(sf::Vector2i cellIndex);
    sf::Vector2i getCellFromMousePosition();

    void updateMoveTimer();
    void drawAllCells();
    void openEmptyCells(int x, int y);
    void openAllCells();
    void populateBoard(int x, int y);
    int countMinesAround(int x, int y);
    void checkGameWinCondition();
    void gameOver();
    void resetBoard();
    void resetVariables();
    void deleteBoard();

public:
	GameplayController();
	~GameplayController();

	void initialize();
	void update();
	void render();

	void restart();
	int getMinesCount();
	float getRemainingTime();
};