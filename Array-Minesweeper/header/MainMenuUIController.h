#pragma once
#include <SFML/Graphics.hpp>
#include "../header/IUIController.h"

class Instructions;

enum class MainMenuUIState
{
	MENU,
	INSTRUCTION,
};

class MainMenuUIController : public IUIController
{
private:
	// Constants:
	const float button_width = 400.f;
	const float button_height = 140.f;

	MainMenuUIState current_main_menu_ui_state;

	sf::RenderWindow* game_window;
	Instructions* instructions;

	sf::Texture play_button_texture;
	sf::Sprite play_button_sprite;

	sf::Texture instructions_button_texture;
	sf::Sprite instructions_button_sprite;

	sf::Texture quit_button_texture;
	sf::Sprite quit_button_sprite;

	sf::Texture menu_button_texture;
	sf::Sprite menu_button_sprite;

	void initializeInstructions();
	void initializeButtons();
	bool loadButtonTexturesFromFile();
	void setButtonSprites();

	void scaleAllButttons();
	void scaleButton(sf::Sprite* button_to_scale);
	void positionButtons();

	void handleButtonInteractions();
	void handleMenuButtonInteractions();
	void handleInstructionButtonInteractions();
	bool clickedButton(sf::Sprite*, sf::Vector2f);

	void setMainMenuUIState(MainMenuUIState state);
	void drawInstructionScreenUI();
	void drawMenuScreenUI();

	void onClickPlayButton();
	void onClickInstructionButton();
	void onClickQuitButton();
	void onClickMenuButton();

	void onDestroy();

public:
	MainMenuUIController();
	~MainMenuUIController();

	void initialize() override;
	void update() override;
	void render() override;
	void show() override;
};