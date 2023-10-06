#pragma once
#include <SFML/Graphics/RenderWindow.hpp>

class SplashScreenUIController;
class MainMenuUIController;

class UIService
{
private:
	SplashScreenUIController* splash_screen_controller;
	MainMenuUIController* main_menu_controller;

	sf::RenderWindow* game_window;

	void createControllers();
	void initializeControllers();
	void destroy();

public:
	UIService();
	~UIService();

	void initialize();
	void update();
	void render();

	void showSplashScreen();
};