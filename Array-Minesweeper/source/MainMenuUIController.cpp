#include "../header/MainMenuUIController.h"
#include "../header/GameService.h"
#include "../header/GraphicService.h"
#include "../header/SoundService.h"
#include "../header/EventService.h"

MainMenuUIController::MainMenuUIController() { game_window = nullptr; }

void MainMenuUIController::initialize()
{
    game_window = ServiceLocator::getInstance()->getGameWindow();
    initializeButtons();
}

void MainMenuUIController::initializeButtons()
{
    if (loadButtonTexturesFromFile())
    {
        setButtonSprites();
        scaleAllButttons();
        positionButtons();
    }
}

bool MainMenuUIController::loadButtonTexturesFromFile()
{
    return play_button_texture.loadFromFile("assets/textures/play_button.png") &&
        instructions_button_texture.loadFromFile("assets/textures/instructions_button.png") &&
        quit_button_texture.loadFromFile("assets/textures/quit_button.png");
}

void MainMenuUIController::setButtonSprites()
{
    play_button_sprite.setTexture(play_button_texture);
    instructions_button_sprite.setTexture(instructions_button_texture);
    quit_button_sprite.setTexture(quit_button_texture);
}

void MainMenuUIController::scaleAllButttons()
{
    scaleButton(&play_button_sprite);
    scaleButton(&instructions_button_sprite);
    scaleButton(&quit_button_sprite);
}

void MainMenuUIController::scaleButton(sf::Sprite* button_to_scale)
{
    button_to_scale->setScale(
        button_width / button_to_scale->getTexture()->getSize().x,
        button_height / button_to_scale->getTexture()->getSize().y
    );
}

void MainMenuUIController::positionButtons()
{
    float x_position = calculateLeftOffsetForButton();

    play_button_sprite.setPosition({ x_position, 500.f });
    instructions_button_sprite.setPosition({ x_position, 700.f });
    quit_button_sprite.setPosition({ x_position, 900.f });
}

float MainMenuUIController::calculateLeftOffsetForButton()
{
    return (static_cast<float>(game_window->getSize().x) / 2) - button_width / 2;
}

void MainMenuUIController::update()
{
    handleButtonInteractions();
}

void MainMenuUIController::render()
{
    ServiceLocator::getInstance()->getGraphicService()->drawBackground();
    game_window->draw(play_button_sprite);
    game_window->draw(instructions_button_sprite);
    game_window->draw(quit_button_sprite);
}

void MainMenuUIController::handleButtonInteractions()
{
    sf::Vector2f mouse_position = sf::Vector2f(sf::Mouse::getPosition(*game_window));

    if (clickedButton(&play_button_sprite, mouse_position))
    {
        printf("Clicked Play Button \n");
        ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::BUTTON_CLICK);
    }

    if (clickedButton(&instructions_button_sprite, mouse_position))
    {
        printf("Clicked Instruction Button \n");
        ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::BUTTON_CLICK);
    }

    if (clickedButton(&quit_button_sprite, mouse_position))
        game_window->close();
}

bool MainMenuUIController::clickedButton(sf::Sprite* button_sprite, sf::Vector2f mouse_position)
{
    return ServiceLocator::getInstance()->getEventService()->pressedLeftMouseButton() &&
        button_sprite->getGlobalBounds().contains(mouse_position);
}