#pragma once

class GameplayController;

class GameplayService
{
private:
	GameplayController* gameplay_controller;

	void createControllers();
	void destroy();

public:
	GameplayService();
	~GameplayService();

	void initialize();
	void update();
	void render();

	void startGame();
	int getMinesCount();
	float getRemainingTime();

	GameplayController* getGameplayController();
};