#pragma once
#include <SFML/Graphics.hpp>

class Instructions
{
private:
	const int number_of_instructions = 7;
	const float top_offset = 97.f;
	const float text_spacing = 95.f;
	const int font_size = 50;

	const sf::String instruction_string_one = "The 'Mines' are hidden in a grid of cells";
	const sf::String instruction_string_two = "'Number' cell tell's you, how many 'Mines' are adjacent to that cell";
	const sf::String instruction_string_three = "You can use the number 'Clues' to solve the game by opening all of the safe cells";
	const sf::String instruction_string_four = "If you click on a 'Mine' you 'Lose' the game!";
	const sf::String instruction_string_five = "Open squares with the 'Left Mouse Button' and put 'Flags' with the 'Right Mouse Button'";
	const sf::String instruction_string_six = "If you open a 'Empty' square, the adjacent 'Empty' squares will automatically open";
	const sf::String instruction_string_seven = "A counter shows the number of 'Mines' and a 'Clock' shows your time in seconds.";

	sf::String* instructions;

	void initializeInstructions();
	void drawInstructions();
	void onDestroy();

public:
	Instructions();
	~Instructions();

	void initialize();
	void update();
	void render();
};
