#pragma once
#include <SFML/Graphics.hpp>
#include "../header/IUIController.h"

class CreditsScreenUIController : public IUIController
{
private:
	const sf::String game_window_title = "Outscal Presents - Minesweeper";
	const float button_width = 400.f;
	const float button_height = 140.f;
	const float top_offset = 300.f;
	const int font_size = 100;

	sf::RenderWindow* game_window;

	sf::Texture quit_button_texture;
	sf::Sprite quit_button_sprite;

	sf::Texture menu_button_texture;
	sf::Sprite menu_button_sprite;

	void initializeButtons();
	bool loadButtonTexturesFromFile();
	void setButtonSprites();

	void scaleAllButttons();
	void scaleButton(sf::Sprite* button_to_scale);
	void positionButtons();
	float calculateLeftOffsetForButton();

	bool pressedMouseButton();
	void handleButtonInteractions();
	bool clickedButton(sf::Sprite*, sf::Vector2f);

	void onClickQuitButton();
	void onClickMenuButton();

	void drawGameTitle();

public:
	CreditsScreenUIController();

	void initialize();
	void update();
	void render();
	void show() override;
};