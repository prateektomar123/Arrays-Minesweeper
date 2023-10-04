#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

class Board;

class GameplayController
{
private:
	Board* board;
	float move_timer = 30.f;

	void createBoard();

public:
	GameplayController();
	~GameplayController();

	void initialize();
	void update();
	void render();

	void restart();
	float getMinesCount();
	float getRemainingTimer();
};