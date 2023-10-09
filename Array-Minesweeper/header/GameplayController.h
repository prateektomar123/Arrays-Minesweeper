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

    const float max_move_time = 30.f;

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

    float move_timer;

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

    void scaleCellImage();
    float calculateCellWidth();
    float calculateCellHeight();

    void handleMouseInteractions();
    bool isValidCellIndex(sf::Vector2i cellIndex);
    sf::Vector2i getCellFromMousePosition();

    void drawAllCells();
    void drawCell(int row, int col);
    void flagCell(int x, int y);
    void openCell(int x, int y);
    void resetBoard();
    void resetCell(int row, int col);
    void deleteBoard();

public:
	GameplayController();
	~GameplayController();

	void initialize();
	void update();
	void render();

	void restart();
	int getMinesCount();
	float getRemainingTimer();
};