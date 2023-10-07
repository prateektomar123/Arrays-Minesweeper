#pragma once
#include <SFML/Graphics.hpp>

enum class CellState
{
    HIDDEN,
    OPEN,
    FLAGGED,
};

enum class CellType
{
    EMPTY,
    ONE,
    TWO,
    THREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    MINE,
};

class Cell
{
private:
    CellState cell_state;
    CellType cell_type;

    int mines_around;

public:
    Cell();

    CellState getCellState();
    CellType getCellType();
    void setCellState(CellState state);
    void setCellType(CellType type);
    int getMinesAround();
    void reset();
};