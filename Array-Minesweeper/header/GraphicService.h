#pragma once
#include <SFML/Graphics.hpp>

enum class FontType
{
	BUBBLE_BOBBLE,
	DS_DIGIB,
};

class GraphicService
{
private:
	const int frame_rate = 60;
	const int default_font_size = 55;

	const std::string game_window_title = "Outscal Presents - Minesweeper";

	const int game_window_width = 1920;
	const int game_window_height = 1080;

	const sf::Color window_color = sf::Color(200, 200, 0, 255);

	const float background_alpha = 85.f;

	sf::VideoMode video_mode;
	sf::RenderWindow* game_window;

	sf::Font font_bubble_bobble;
	sf::Font font_DS_DIGIB;
	sf::Text text;

	sf::Texture background_texture;
	sf::Sprite background_sprite;

	void configureVideoMode();
	void onDestroy();

	void initializeText();
	bool loadFont();
	void setDefaultText();
	void setTextPosition(float y_position);
	void setFont(FontType font_type);
	void initializeBackgroundImage();
	void setBackgroundAlpha();
	void scaleBackgroundImage();

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

	void drawText(sf::String text_value, sf::Vector2f text_position, int text_font_size, FontType font_type = FontType::BUBBLE_BOBBLE, sf::Color color = sf::Color::White);
	void drawText(sf::String text_value, float text_y_position, FontType font_type = FontType::BUBBLE_BOBBLE);
	void drawText(sf::String text_value, float text_y_position, int text_font_size, FontType font_type = FontType::BUBBLE_BOBBLE);
	void drawBackground();
};