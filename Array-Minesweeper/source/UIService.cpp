#include "../header/UIService.h"
#include "../header/GameService.h"
#include "../header/GraphicService.h"
#include "../header/MainMenuUIController.h"
#include "../header/SplashScreenUIController.h"
#include "../header/GameplayUIController.h"
#include "../header/CreditsScreenUIController.h"

UIService::UIService() 
{ 
	splash_screen_controller = nullptr;
	main_menu_controller = nullptr;
	gameplay_ui_controller = nullptr;
	credits_screen_ui_controller = nullptr;
	game_window = nullptr;

	createControllers();
}

void UIService::createControllers()
{
	splash_screen_controller = new SplashScreenUIController();
	main_menu_controller = new MainMenuUIController();
	gameplay_ui_controller = new GameplayUIController();
	credits_screen_ui_controller = new CreditsScreenUIController();
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
	case GameState::GAMEPLAY:
		gameplay_ui_controller->update();
		break;
	case GameState::CREDITS:
		credits_screen_ui_controller->update();
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
	case GameState::GAMEPLAY:
		gameplay_ui_controller->render();
		break;
	case GameState::CREDITS:
		credits_screen_ui_controller->render();
		break;
	}
}

void UIService::show()
{
	switch (GameService::getGameState())
	{
	case GameState::SPLASH_SCREEN:
		splash_screen_controller->show();
		break;
	case GameState::MAIN_MENU:
		main_menu_controller->show();
		break;
	case GameState::GAMEPLAY:
		gameplay_ui_controller->show();
		break;
	}
}

void UIService::initializeControllers()
{
	splash_screen_controller->initialize();
	main_menu_controller->initialize();
	gameplay_ui_controller->initialize();
	credits_screen_ui_controller->initialize();
}

void UIService::destroy()
{
	delete(splash_screen_controller);
	delete(main_menu_controller);
	delete(gameplay_ui_controller);
	delete(credits_screen_ui_controller);
}