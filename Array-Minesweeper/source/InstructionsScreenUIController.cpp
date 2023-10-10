#include "../header/InstructionsScreenUIController.h"
#include "../header/ServiceLocator.h"
#include "../header/GraphicService.h"
#include "../header/GameService.h"
#include "../header/SoundService.h"
#include "../header/EventService.h"

InstructionsScreenUIController::InstructionsScreenUIController() { }

InstructionsScreenUIController::~InstructionsScreenUIController() { }

void InstructionsScreenUIController::initialize()
{
    game_window = ServiceLocator::getInstance()->getGameWindow();
    initializeButtons();
}

void InstructionsScreenUIController::update() 
{
    handleButtonInteractions();
}

void InstructionsScreenUIController::render()
{
    ServiceLocator::getInstance()->getGraphicService()->drawBackground();
    game_window->draw(menu_button_sprite);
    drawInstructions();
}

void InstructionsScreenUIController::initializeButtons()
{
    if (loadButtonTexturesFromFile())
    {
        setButtonSprites();
        scaleAllButttons();
        positionButtons();
    }
}

bool InstructionsScreenUIController::loadButtonTexturesFromFile()
{
    return menu_button_texture.loadFromFile("assets/textures/menu_button.png");
}

void InstructionsScreenUIController::setButtonSprites()
{
    menu_button_sprite.setTexture(menu_button_texture);
}

void InstructionsScreenUIController::scaleAllButttons()
{
    scaleButton(&menu_button_sprite);
}

void InstructionsScreenUIController::scaleButton(sf::Sprite* button_to_scale)
{
    button_to_scale->setScale(
        button_width / button_to_scale->getTexture()->getSize().x,
        button_height / button_to_scale->getTexture()->getSize().y
    );
}

void InstructionsScreenUIController::positionButtons()
{
    float x_position = (static_cast<float>(game_window->getSize().x) / 2) - button_width / 2;
    menu_button_sprite.setPosition({ x_position, 800.f });
}

void InstructionsScreenUIController::show() { }

void InstructionsScreenUIController::drawInstructions()
{
    for (int i = 0; i < number_of_instructions; i++)
    {
        ServiceLocator::getInstance()->getGraphicService()->drawText(instructions[i], top_offset + (text_spacing * i), font_size);
    }
}

void InstructionsScreenUIController::handleButtonInteractions()
{
    sf::Vector2f mouse_position = sf::Vector2f(sf::Mouse::getPosition(*game_window));

    if (clickedButton(&menu_button_sprite, mouse_position))
    {
        onClickMenuButton();
    }
}

bool InstructionsScreenUIController::clickedButton(sf::Sprite* button_sprite, sf::Vector2f mouse_position)
{
    return ServiceLocator::getInstance()->getEventService()->pressedLeftMouseButton() &&
        button_sprite->getGlobalBounds().contains(mouse_position);
}

void InstructionsScreenUIController::onClickMenuButton()
{
    GameService::setGameState(GameState::MAIN_MENU);
    ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::BUTTON_CLICK);
}