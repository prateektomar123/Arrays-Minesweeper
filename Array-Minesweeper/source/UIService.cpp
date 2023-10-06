#include "../header/UIService.h"
#include "../header/GameService.h"
#include "../header/GraphicService.h"
#include "../header/MainMenuUIController.h"
#include "../header/SplashScreenUIController.h"

UIService::UIService() 
{ 
	splash_screen_controller = nullptr;
	main_menu_controller = nullptr;
	game_window = nullptr;

	createControllers();
}

void UIService::createControllers()
{
	splash_screen_controller = new SplashScreenUIController();
	main_menu_controller = new MainMenuUIController();
}

UIService::~UIService()
{
	destroy();
}

void UIService::initialize()
{
	game_window = ServiceLocator::getInstance()->getGameWindow();

	initializeControllers();
}

void UIService::update()
{
	switch (GameService::getGameState())
	{
	case GameState::SPLASH_SCREEN:
		splash_screen_controller->update();
		break;
	case GameState::MAIN_MENU:
		main_menu_controller->update();
		break;
	}
}

void UIService::render()
{
	switch (GameService::getGameState())
	{
	case GameState::SPLASH_SCREEN:
		splash_screen_controller->render();
		break;
	case GameState::MAIN_MENU:
		main_menu_controller->render();
		break;
	}
}

void UIService::showSplashScreen()
{
	splash_screen_controller->showSplashScreen();
}

void UIService::initializeControllers()
{
	splash_screen_controller->initialize();
	main_menu_controller->initialize();
}

void UIService::destroy()
{
	delete(splash_screen_controller);
	delete(main_menu_controller);
}