#include "../header/Cell.h"
#include "../header/SoundService.h"
#include "../header/ServiceLocator.h"

Cell::Cell()
{
    reset();
}

CellState Cell::getCellState()
{
    return cell_state;
}

CellType Cell::getCellType()
{
    return cell_type;
}

void Cell::setCellState(CellState state)
{
    cell_state = state;
}

void Cell::setCellType(CellType type)
{
    cell_type = type;
}

int Cell::getMinesAround()
{
    return mines_around;
}

void Cell::reset()
{
    mines_around = 0;
    cell_state = CellState::HIDDEN;
    cell_type = CellType::EMPTY;
}