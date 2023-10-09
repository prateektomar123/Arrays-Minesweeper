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
	initializeBackgroundImage();
}

sf::RenderWindow* GraphicService::createGameWindow()
{
	configureVideoMode();
	return new sf::RenderWindow(video_mode, game_window_title, sf::Style::Fullscreen);
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
	setDefaultText();
}

bool GraphicService::loadFont()
{
	return font_bubble_bobble.loadFromFile("assets/fonts/bubbleBobble.ttf") &&
		font_DS_DIGIB.loadFromFile("assets/fonts/DS_DIGIB.ttf");
}

void GraphicService::setDefaultText()
{
	text.setFont(font_bubble_bobble);
	text.setCharacterSize(default_font_size);
	text.setFillColor(sf::Color::White);
}

void GraphicService::drawText(sf::String text_value, sf::Vector2f text_position, int text_font_size, FontType font_type, sf::Color color)
{
	text.setCharacterSize(text_font_size);
	text.setFillColor(color);
	setFont(font_type);
	text.setString(text_value);
	text.setPosition(text_position);

	game_window->draw(text);
	setDefaultText();
}

void GraphicService::drawText(sf::String text_value, float text_y_position, int text_font_size, FontType font_type)
{
	text.setCharacterSize(text_font_size);
	drawText(text_value, text_y_position, font_type);
}

void GraphicService::drawText(sf::String text_value, float text_y_position, FontType font_type)
{
	text.setString(text_value);
	setTextPosition(text_y_position);
	setFont(font_type);

	game_window->draw(text);
	setDefaultText();
}

// Position of text will be center alligned on x-axis.
void GraphicService::setTextPosition(float y_position)
{
	sf::FloatRect textBounds = text.getLocalBounds();

	float x_position = (game_window->getSize().x - textBounds.width) / 2;
	text.setPosition(x_position, y_position);
}

void GraphicService::setFont(FontType font_type)
{
	switch (font_type)
	{
	case FontType::BUBBLE_BOBBLE:
		text.setFont(font_bubble_bobble);
		break;
	case FontType::DS_DIGIB:
		text.setFont(font_DS_DIGIB);
		break;
	}
}

void GraphicService::initializeBackgroundImage()
{
	if (background_texture.loadFromFile("assets/textures/minesweeper_bg.png"))
	{
		background_sprite.setTexture(background_texture);
		setBackgroundAlpha();
		scaleBackgroundImage();
	}
}

void GraphicService::setBackgroundAlpha()
{
	sf::Color color = background_sprite.getColor();
	color.a = background_alpha;
	background_sprite.setColor(color);
}


void GraphicService::scaleBackgroundImage()
{
	background_sprite.setScale(
		static_cast<float>(game_window->getSize().x) / background_sprite.getTexture()->getSize().x,
		static_cast<float>(game_window->getSize().y) / background_sprite.getTexture()->getSize().y
	);
}

void GraphicService::drawBackground()
{
	game_window->draw(background_sprite);
}