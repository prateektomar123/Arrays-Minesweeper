#include "../header/GameplayUIController.h"
#include "../header/ServiceLocator.h"
#include "../header/GraphicService.h"
#include "../header/GameplayService.h"
#include "../header/GameplayController.h"
#include "../header/SoundService.h"
#include "../header/EventService.h"

GameplayUIController::GameplayUIController()
{
	game_window = nullptr;
}

GameplayUIController::~GameplayUIController()
{
}

void GameplayUIController::initialize()
{
	game_window = ServiceLocator::getInstance()->getGameWindow();
	initializeButtonImage();
}

void GameplayUIController::update()
{
	handleButtonInteractions();
}

void GameplayUIController::render()
{
	drawRestartButton();
	drawMinesCount();
	drawRemainingTimer();
}

void GameplayUIController::show() { }

void GameplayUIController::initializeButtonImage()
{
	if (restart_button_texture.loadFromFile("assets/textures/cells.jpeg") &&
		outscal_logo_texture.loadFromFile("assets/textures/outscal_logo_start.png"))
	{
		restart_button_texture.setSmooth(true);
		outscal_logo_texture.setSmooth(true);

		restart_button_sprite.setTexture(restart_button_texture);
		restart_button_sprite.setTextureRect(sf::IntRect(10 * tile_height, 0, tile_height, tile_height));
		outscal_logo_sprite.setTexture(outscal_logo_texture);

		scaleButtonImage();
		setButtonImagePosition();
	}
}

void GameplayUIController::scaleButtonImage()
{
	restart_button_sprite.setScale(button_width / restart_button_sprite.getLocalBounds().width, 
								button_height / restart_button_sprite.getLocalBounds().height);

	outscal_logo_sprite.setScale(button_width / outscal_logo_sprite.getLocalBounds().width,
		button_height / outscal_logo_sprite.getLocalBounds().height);
}
void GameplayUIController::setButtonImagePosition()
{
	restart_button_sprite.setPosition(restart_button_left_offset, restart_button_top_offset);
	outscal_logo_sprite.setPosition(restart_button_left_offset, restart_button_top_offset);
}

void GameplayUIController::drawRestartButton()
{
	game_window->draw(restart_button_sprite);
	game_window->draw(outscal_logo_sprite);
}

void GameplayUIController::drawMinesCount()
{
	int mines_count = ServiceLocator::getInstance()->getGameplayService()->getGameplayController()->getMinesCount();

	sf::Vector2f mine_count_text_position(mine_text_left_offset, mine_text_top_offset);
	std::string string_mine_count = std::to_string(mines_count);
	ServiceLocator::getInstance()->getGraphicService()->drawText(string_mine_count, mine_count_text_position, font_size, FontType::DS_DIGIB, sf::Color::Red);
}

void GameplayUIController::drawRemainingTimer()
{
	int move_timer = ServiceLocator::getInstance()->getGameplayService()->getGameplayController()->getRemainingTimer();

	sf::Vector2f move_timer_text_position(timer_text_left_offset, timer_text_top_offset);
	std::string string_move_timer = std::to_string(static_cast<int>(move_timer));
	ServiceLocator::getInstance()->getGraphicService()->drawText(string_move_timer, move_timer_text_position, font_size, FontType::DS_DIGIB, sf::Color::Red);
}

void GameplayUIController::handleButtonInteractions()
{
	EventService* event_service = ServiceLocator::getInstance()->getEventService();
	sf::Vector2f mouse_position = sf::Vector2f(sf::Mouse::getPosition(*game_window));

	if (event_service->pressedLeftMouseButton() && clickedButton(&restart_button_sprite, mouse_position))
	{
		ServiceLocator::getInstance()->getGameplayService()->getGameplayController()->restart();
		ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::BUTTON_CLICK);
	}
}

bool GameplayUIController::clickedButton(sf::Sprite* button_sprite, sf::Vector2f mouse_position)
{
	return button_sprite->getGlobalBounds().contains(mouse_position);
}