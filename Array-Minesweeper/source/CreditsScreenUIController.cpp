#include "../header/CreditsScreenUIController.h"
#include "../header/ServiceLocator.h"
#include "../header/GameService.h"
#include "../header/GraphicService.h"
#include "../header/SoundService.h"

CreditsScreenUIController::CreditsScreenUIController()
{
    game_window = nullptr;
}

CreditsScreenUIController::~CreditsScreenUIController()
{
}

void CreditsScreenUIController::initialize()
{
    game_window = ServiceLocator::getInstance()->getGameWindow();
    initializeButtons();
}

void CreditsScreenUIController::initializeButtons()
{
    if (loadButtonTexturesFromFile())
    {
        setButtonSprites();
        scaleAllButttons();
        positionButtons();
    }
}

bool CreditsScreenUIController::loadButtonTexturesFromFile()
{
    return quit_button_texture.loadFromFile("assets/textures/quit_button.png") &&
        menu_button_texture.loadFromFile("assets/textures/menu_button.png");
}

void CreditsScreenUIController::setButtonSprites()
{
    quit_button_sprite.setTexture(quit_button_texture);
    menu_button_sprite.setTexture(menu_button_texture);
}

void CreditsScreenUIController::scaleAllButttons()
{
    scaleButton(&quit_button_sprite);
    scaleButton(&menu_button_sprite);
}

void CreditsScreenUIController::scaleButton(sf::Sprite* button_to_scale)
{
    button_to_scale->setScale(
        button_width / button_to_scale->getTexture()->getSize().x,
        button_height / button_to_scale->getTexture()->getSize().y
    );
}

void CreditsScreenUIController::positionButtons()
{
    float x_position = (static_cast<float>(game_window->getSize().x) / 2) - button_width / 2;

    menu_button_sprite.setPosition({ x_position, 600.f });
    quit_button_sprite.setPosition({ x_position, 800.f });
}

void CreditsScreenUIController::update()
{
    if (pressedMouseButton())
    {
        handleButtonInteractions();
        mouse_button_pressed = true;
    }
    else
    {
        mouse_button_pressed = false;
    }
}

void CreditsScreenUIController::render()
{
    ServiceLocator::getInstance()->getGraphicService()->drawBackground();
    game_window->draw(menu_button_sprite);
    game_window->draw(quit_button_sprite);
    drawGameTitle();
}

bool CreditsScreenUIController::pressedMouseButton() { return sf::Mouse::isButtonPressed(sf::Mouse::Left); }

void CreditsScreenUIController::handleButtonInteractions()
{
    sf::Vector2f mouse_position = sf::Vector2f(sf::Mouse::getPosition(*game_window));

    if (clickedButton(&quit_button_sprite, mouse_position))
    {
        onClickQuitButton();
    }

    if (clickedButton(&menu_button_sprite, mouse_position))
    {
        onClickMenuButton();
    }
}

bool CreditsScreenUIController::clickedButton(sf::Sprite* button_sprite, sf::Vector2f mouse_position)
{
    return button_sprite->getGlobalBounds().contains(mouse_position);
}

void CreditsScreenUIController::onClickQuitButton()
{
    game_window->close();
}

void CreditsScreenUIController::onClickMenuButton()
{
    GameService::setGameState(GameState::MAIN_MENU);
    ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::BUTTON_CLICK);
}

void CreditsScreenUIController::drawGameTitle()
{
    ServiceLocator::getInstance()->getGraphicService()->drawText(game_window_title, top_offset, font_size, FontType::BUBBLE_BOBBLE);
}