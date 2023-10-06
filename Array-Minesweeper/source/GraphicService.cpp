#include "../header/GraphicService.h"

GraphicService::GraphicService()
{
	game_window = nullptr;
}

GraphicService::~GraphicService()
{
	onDestroy();
}

void GraphicService::initialize()
{
	game_window = createGameWindow();
	setFrameRate(frame_rate);
	initializeText();
}

sf::RenderWindow* GraphicService::createGameWindow()
{
	configureVideoMode();
	sf::RenderWindow* window = new sf::RenderWindow(video_mode, game_window_title, sf::Style::Fullscreen);
	return window;
}

void GraphicService::configureVideoMode()
{
	video_mode = *(new sf::VideoMode(game_window_width, game_window_height, sf::VideoMode::getDesktopMode().bitsPerPixel));
}

void GraphicService::onDestroy()
{
	delete(game_window);
}

void GraphicService::setFrameRate(int frame_rate_to_set)
{
	game_window->setFramerateLimit(frame_rate_to_set);
}

void GraphicService::update() { }

void GraphicService::render() { }

bool GraphicService::isGameWindowOpen()
{
	return game_window->isOpen();
}

sf::RenderWindow* GraphicService::getGameWindow()
{
	return game_window;
}

void GraphicService::initializeText()
{
	loadFont();
	setupText();
}

bool GraphicService::loadFont()
{
	return font.loadFromFile("assets/fonts/bubbleBobble.ttf");
}

void GraphicService::setupText()
{
	text.setFont(font);
	text.setCharacterSize(font_size);
	text.setFillColor(sf::Color::White);
}

void GraphicService::drawText(sf::String text_value, sf::Vector2f text_position)
{
	text.setString(text_value);
	text.setPosition(text_position);
	game_window->draw(text);
}

void GraphicService::drawText(sf::String text_value, float text_y_position, int text_font_size)
{
	text.setCharacterSize(text_font_size);
	drawText(text_value, text_y_position);
	text.setCharacterSize(font_size);
}

void GraphicService::drawText(sf::String text_value, float text_y_position)
{
	text.setString(text_value);
	setTextPosition(text_y_position);
	game_window->draw(text);
}

// Position of text will be center alligned on x-axis.
void GraphicService::setTextPosition(float y_position)
{
	sf::FloatRect textBounds = text.getLocalBounds();

	float x_position = (game_window->getSize().x - textBounds.width) / 2;
	text.setPosition(x_position, y_position);
}