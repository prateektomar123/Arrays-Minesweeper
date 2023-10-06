#pragma once
#include <SFML/Graphics.hpp>
#include <random>

class Cell;

class Board
{
private:
    const int number_of_rows = 9;
    const int number_of_colums = 9;
    const int mines_count = 8;
    const float max_move_time = 31.f;
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

    float move_timer;
    int flagged_cells;

    bool b_left_mouse_button_pressed;
    bool b_right_mouse_button_pressed;
    bool b_first_click;
    bool b_game_over;

    std::vector<std::vector<Cell*>> cells;
    sf::RenderWindow* game_window;

    // To generate random values.
    std::default_random_engine random_engine;

    // To give random seed to generator.
    std::random_device random_device;

    sf::Texture board_texture;
    sf::Sprite board_sprite;

    sf::Texture cell_texture;
    sf::Sprite cell_sprite;

    void createCells();
    Cell* createCell();
    void initializeBoardImage();
    void scaleBoardImage();
    void setBoardImagePosition();
    void initializeCellImage();
    void scaleCellImage();
    void handleMouseInteractions();
    sf::Vector2i getCellFromMousePosition();
    void updateMoveTimer();
    void drawAllCells();
    void drawCell(int row, int col);
    void flagCell(int x, int y);
    void openCell(int x, int y);
    void openEmptyCells(int x, int y);
    void openAllCells();
    void populateBoard(int x, int y);
    int countMinesAround(int x, int y);
    void gameOver();
    void resetCell(int row, int col);
    void resetVariables();
    void deleteCells();

public:
    Board();
    ~Board();

    void initialize();
    void update();
    void render();

    void resetBoard();
    int getMinesCount();
    float getMoveTimer();
};