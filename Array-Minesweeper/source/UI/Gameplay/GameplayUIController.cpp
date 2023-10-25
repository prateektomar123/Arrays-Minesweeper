#include "../../header/UI/Gameplay/GameplayUIController.h"
#include "../../header/Main/GameService.h"
#include "../../header/Main/GraphicService.h"
#include "../../header/Sound/SoundService.h"
#include "../../header/Event/EventService.h"
#include "../../header/Global/Config.h"
#include "../../header/Global/ServiceLocator.h"
#include <sstream>
#include <iomanip>

namespace UI
{
	namespace GameplayUI
	{
		using namespace Global;
		using namespace Main;
		using namespace UIElement;
		using namespace Sound;

		GameplayUIController::GameplayUIController()
		{
			game_window = nullptr;
		}

		GameplayUIController::~GameplayUIController()
		{
		}

		void GameplayUIController::initialize()
		{
			game_window = ServiceLocator::getInstance()->getGraphicService()->getGameWindow();
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
			int mines_count = ServiceLocator::getInstance()->getGameplayService()->getMinesCount();

			std::stringstream stream;
			stream << std::setw(3) << std::setfill('0') << mines_count;
			std::string string_mine_count = stream.str();

			sf::Vector2f mine_count_text_position(mine_text_left_offset, mine_text_top_offset);
			ServiceLocator::getInstance()->getGraphicService()->drawText(string_mine_count, mine_count_text_position, font_size, FontType::DS_DIGIB, sf::Color::Red);
		}

		void GameplayUIController::drawRemainingTimer()
		{
			int remaining_time = ServiceLocator::getInstance()->getGameplayService()->getRemainingTime();

			std::stringstream stream;
			stream << std::setw(3) << std::setfill('0') << remaining_time;
			std::string string_remaining_time = stream.str();

			sf::Vector2f remaining_time_text_position(timer_text_left_offset, timer_text_top_offset);
			ServiceLocator::getInstance()->getGraphicService()->drawText(string_remaining_time, remaining_time_text_position, font_size, FontType::DS_DIGIB, sf::Color::Red);
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
	}
}