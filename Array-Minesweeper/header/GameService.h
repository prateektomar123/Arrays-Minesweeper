#pragma once
#include "ServiceLocator.h"

enum class GameState
{
	BOOT,
	SPLASH_SCREEN,
	MAIN_MENU,
	GAMEPLAY,
};

class GameService
{
private:
	const int frame_rate = 60;
	
	static GameState current_state;
	ServiceLocator* service_locator;
	sf::RenderWindow* game_window;

	void initialize();
	void initializeVariables();
	void showSplashScreen();
	void destroy();

public:
	GameService();
	virtual ~GameService();

	void ignite();
	void update();
	void render();
	bool isRunning();

	static void setGameState(GameState new_state);
	static GameState getGameState();
};
