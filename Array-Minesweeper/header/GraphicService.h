#pragma once
#include <SFML/Graphics.hpp>

class GraphicService
{
private:
	const int frame_rate = 60;
	const int font_size = 55;
	const std::string game_window_title = "Outscal Presents - Array Jumper";
	const int game_window_width = 1920;
	const int game_window_height = 1080;
	const sf::Color window_color = sf::Color(200, 200, 0, 255);

	sf::VideoMode video_mode;
	sf::RenderWindow* game_window;

	sf::Font font;
	sf::Text text;

	void configureVideoMode();
	void onDestroy();

	void initializeText();
	bool loadFont();
	void setupText();
	void setTextPosition(float y_position);

public:
	GraphicService();
	~GraphicService();

	sf::RenderWindow* createGameWindow();

	void initialize();
	void update();
	void render();
	bool isGameWindowOpen();
	void setFrameRate(int);
	sf::RenderWindow* getGameWindow();

	void drawText(sf::String text_value, sf::Vector2f text_position);
	void drawText(sf::String text_value, float text_y_position);
	void drawText(sf::String text_value, float text_y_position, int text_font_size);
};