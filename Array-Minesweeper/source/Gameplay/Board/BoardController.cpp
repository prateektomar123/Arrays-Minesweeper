#include "../../header/Gameplay/Board/BoardController.h"
#include "../../header/Gameplay/Board/BoardView.h"
#include "../../header/Gameplay/Cell/CellController.h"
#include "../../header/Gameplay/Cell/CellModel.h"
#include "../../header/Global/ServiceLocator.h"
#include "../../header/Sound/SoundService.h"

namespace Gameplay
{
	namespace Board
	{
		using namespace Cell;
		using namespace Global;
		

		BoardController::BoardController()
		{
			board_view = new BoardView(this);
			createBoard();
		}

		BoardController::~BoardController()
		{
			destroy();
		}

		void BoardController::createBoard()
		{
			for (int i = 0; i < number_of_colums; i++)
			{
				cells[i] = new CellController(i); //Passing Cell Index in Cell Controller's constructor
			}
		}

		void BoardController::initialize()
		{
			board_view->initialize();
			initializeCells();
		}
		void BoardController::initializeCells()
		{
			float cell_width = board_view->getCellWidth();
			float cell_height = board_view->getCellHeight();

			for (int i = 0; i < number_of_colums; i++)
			{
				cells[i]->initialize(cell_width, cell_height);
			}
		}
		void BoardController::update()
		{
			board_view->update();
			for (int i = 0; i < number_of_colums; i++)
			{
				cells[i]->update();
			}
		}

		void BoardController::render()
		{
			board_view->render();
			for (int i = 0; i < number_of_colums; i++)
			{
				cells[i]->update();
			}
		}

		void BoardController::reset()
		{
			for (int i = 0; i < number_of_colums; i++)
			{
				cells[i]->reset();
			}
		}

		void BoardController::deleteBoard()
		{
			for (int i = 0; i < number_of_colums; i++)
			{
				delete(cells[i]);
			}
		}

		void BoardController::destroy()
		{
			deleteBoard();
			delete(board_view);
		}
	}
}