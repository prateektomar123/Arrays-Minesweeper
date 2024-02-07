#pragma once
#include "../../header/Gameplay/GameplayController.h"
#include "../../header/Gameplay/Cell/CellController.h"
#include "../../header/UI/UIElement/ButtonView.h"

namespace Gameplay
{
	class GameplayService
	{
	private:
		GameplayController* gameplay_controller;

		void createController();
		void destroy();

	public:
		GameplayService();
		~GameplayService();

		void initialize();
		void update();
		void render();

		void startGame();
		void processCellInput(Cell::CellController* cell_controller, UI::UIElement::ButtonType button_type);

		int getMinesCount();
		float getRemainingTime();
		
		void onCellOpen();
		void onBlast();
	};
}