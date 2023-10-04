#pragma once
#include <SFML/Graphics.hpp>
#include <random>

class Cell;

class Board
{
private:
    const int number_of_rows = 9;
    const int number_of_colums = 9;

    const float top_offset = 274.f;
    const float left_offset = 583.f;

    const float board_height_offset = 325.f;
    const float board_width_offset = 115.f;

    const int tile_height = 32;
    const int tile_width = 16;

    float board_height;
    float board_width;

    float cell_width;
    float cell_height;

    bool b_left_mouse_button_pressed;
    bool b_right_mouse_button_pressed;

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
    void drawAllCells();
    void drawCell(int row, int col);
    void flagCell(int x, int y);
    void openCell(int x, int y);
    void deleteCells();

public:
    Board();
    ~Board();

    void initialize();
    void update();
    void render();
};