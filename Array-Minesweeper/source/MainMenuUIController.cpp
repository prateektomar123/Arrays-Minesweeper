#include "../header/MainMenuUIController.h"
#include "../header/GameService.h"
#include "../header/GraphicService.h"
#include "../header/SoundService.h"
#include "../header/Instructions.h"

MainMenuUIController::MainMenuUIController()
{
    game_window = nullptr;
}

MainMenuUIController::~MainMenuUIController()
{
    onDestroy();
}

void MainMenuUIController::initialize()
{
    game_window = ServiceLocator::getInstance()->getGameWindow();
    initializeButtons();
    initializeInstructions();
    setMainMenuUIState(MainMenuUIState::MENU);
}

void MainMenuUIController::initializeInstructions()
{
    instructions = new Instructions();
    instructions->initialize();
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
        quit_button_texture.loadFromFile("assets/textures/quit_button.png") &&
        menu_button_texture.loadFromFile("assets/textures/menu_button.png");
}

void MainMenuUIController::setButtonSprites()
{
    play_button_sprite.setTexture(play_button_texture);
    instructions_button_sprite.setTexture(instructions_button_texture);
    quit_button_sprite.setTexture(quit_button_texture);
    menu_button_sprite.setTexture(menu_button_texture);
}

void MainMenuUIController::scaleAllButttons()
{
    scaleButton(&play_button_sprite);
    scaleButton(&instructions_button_sprite);
    scaleButton(&quit_button_sprite);
    scaleButton(&menu_button_sprite);
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
    float x_position = (static_cast<float>(game_window->getSize().x) / 2) - button_width / 2;

    play_button_sprite.setPosition({ x_position, 400.f });
    instructions_button_sprite.setPosition({ x_position, 600.f });
    quit_button_sprite.setPosition({ x_position, 800.f });
    menu_button_sprite.setPosition({ x_position, 800.f });
}

void MainMenuUIController::update()
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

void MainMenuUIController::render()
{
    ServiceLocator::getInstance()->getGraphicService()->drawBackground();

    switch (current_main_menu_ui_state)
    {
    case MainMenuUIState::MENU:
        drawMenuScreenUI();
        break;
    case MainMenuUIState::INSTRUCTION:
        drawInstructionScreenUI();
        break;
    }
}

bool MainMenuUIController::pressedMouseButton() { return sf::Mouse::isButtonPressed(sf::Mouse::Left); }

void MainMenuUIController::handleButtonInteractions()
{
    if (mouse_button_pressed) return;

    switch (current_main_menu_ui_state)
    {
    case MainMenuUIState::MENU:
        handleMenuButtonInteractions();
        break;
    case MainMenuUIState::INSTRUCTION:
        handleInstructionButtonInteractions();
        break;
    }
}

void MainMenuUIController::handleMenuButtonInteractions()
{
    sf::Vector2f mouse_position = sf::Vector2f(sf::Mouse::getPosition(*game_window));

    if (clickedButton(&play_button_sprite, mouse_position))
    {
        onClickPlayButton();
    }

    if (clickedButton(&instructions_button_sprite, mouse_position))
    {
        onClickInstructionButton();
    }

    if (clickedButton(&quit_button_sprite, mouse_position))
    {
        onClickQuitButton();
    }
}

void MainMenuUIController::handleInstructionButtonInteractions()
{
    sf::Vector2f mouse_position = sf::Vector2f(sf::Mouse::getPosition(*game_window));

    if (clickedButton(&menu_button_sprite, mouse_position))
    {
        onClickMenuButton();
    }
}

bool MainMenuUIController::clickedButton(sf::Sprite* button_sprite, sf::Vector2f mouse_position)
{
    return button_sprite->getGlobalBounds().contains(mouse_position);
}

void MainMenuUIController::setMainMenuUIState(MainMenuUIState state)
{
    current_main_menu_ui_state = state;
}

void MainMenuUIController::drawInstructionScreenUI()
{
    game_window->draw(menu_button_sprite);
    instructions->render();
}

void MainMenuUIController::drawMenuScreenUI()
{
    game_window->draw(play_button_sprite);
    game_window->draw(instructions_button_sprite);
    game_window->draw(quit_button_sprite);
}

void MainMenuUIController::onClickPlayButton()
{
    ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::BUTTON_CLICK);
    GameService::setGameState(GameState::GAMEPLAY);
}

void MainMenuUIController::onClickInstructionButton()
{
    setMainMenuUIState(MainMenuUIState::INSTRUCTION);
    ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::BUTTON_CLICK);
}

void MainMenuUIController::onClickQuitButton()
{
    game_window->close();
}

void MainMenuUIController::onClickMenuButton()
{
    setMainMenuUIState(MainMenuUIState::MENU);
    ServiceLocator::getInstance()->getSoundService()->playSound(SoundType::BUTTON_CLICK);
}

void MainMenuUIController::onDestroy()
{
    delete instructions;
}