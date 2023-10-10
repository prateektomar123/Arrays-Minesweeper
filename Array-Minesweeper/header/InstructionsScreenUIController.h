#pragma once
#include <SFML/Graphics.hpp>
#include "../header/IUIController.h"

class InstructionsScreenUIController : public IUIController
{
private:
	static const int number_of_instructions = 7;
	const float top_offset = 97.f;
	const float text_spacing = 95.f;
	const int font_size = 50;

	sf::String instructions[number_of_instructions] = { "The 'Mines' are hidden in a grid of cells",
														"'Number' cell tell's you, how many 'Mines' are adjacent to that cell",
														"You can use the number 'Clues' to solve the game by opening all of the safe cells",
														"If you click on a 'Mine' you 'Lose' the game!",
														"Open squares with the 'Left Mouse Button' and put 'Flags' with the 'Right Mouse Button'",
														"If you open a 'Empty' square, the adjacent 'Empty' squares will automatically open",
														"A counter shows the number of 'Mines' and a 'Clock' shows your time in seconds." };


	// Constants:
	const float button_width = 400.f;
	const float button_height = 140.f;

	sf::RenderWindow* game_window;

	sf::Texture menu_button_texture;
	sf::Sprite menu_button_sprite;

	void initializeButtons();
	bool loadButtonTexturesFromFile();
	void setButtonSprites();

	void scaleAllButttons();
	void scaleButton(sf::Sprite* button_to_scale);
	void positionButtons();

	void handleButtonInteractions();
	bool clickedButton(sf::Sprite*, sf::Vector2f);
	void onClickMenuButton();

	void drawInstructions();

public:
	InstructionsScreenUIController();
	~InstructionsScreenUIController();

	void initialize() override;
	void update() override;
	void render() override;
	void show() override;
};
