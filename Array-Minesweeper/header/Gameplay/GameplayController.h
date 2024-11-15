#pragma once
#include "../../header/Gameplay/Board/BoardService.h"
#include "../../header/UI/UIElement/ButtonView.h"
#include <SFML/Graphics.hpp>

namespace Gameplay
{
	using namespace Gameplay::Board;
	class GameplayController
	{
	private:
		const float max_level_duration = 301.0f;
		const float game_over_time = 11.f;
		BoardService* board_service;
	};
}