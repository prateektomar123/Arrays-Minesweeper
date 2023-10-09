#include "../header/SplashScreenUIController.h"
#include "../header/GameService.h"
#include "../header/GraphicService.h"
#include "../header/SoundService.h"

SplashScreenUIController::SplashScreenUIController()
{
    game_window = nullptr;
}

void SplashScreenUIController::initialize()
{
    game_window = ServiceLocator::getInstance()->getGameWindow();

    initializeVariables();
    initializeOutscalLogo();
}

void SplashScreenUIController::update()
{
    if (elapsed_time < splash_screen_time)
    {
        float deltaTime = clock.restart().asSeconds();
        elapsed_time += deltaTime;
        updateLogo(deltaTime);
    }
    else
    {
        logoAnimationComplete();
    }
}

void SplashScreenUIController::render() { game_window->draw(outscal_logo_sprite); }

void SplashScreenUIController::initializeVariables() { elapsed_time = 0.0f; }

void SplashScreenUIController::initializeOutscalLogo()
{
    loadOutscalTexture();
    outscal_logo_sprite.setTexture(outscal_logo_texture);
    setPositionToCenter();
}

void SplashScreenUIController::loadOutscalTexture()
{
    if (!tryLoadingOutscalLogo())
        printf("ERROR :: UIService :: Unable to find Outscal Logo Texture");
}

bool SplashScreenUIController::tryLoadingOutscalLogo() { return outscal_logo_texture.loadFromFile("assets/textures/outscal_logo.png"); }

void SplashScreenUIController::setPositionToCenter()
{
    sf::Vector2u windowSize = game_window->getSize();
    sf::Vector2u logoSize = outscal_logo_texture.getSize();
    outscal_logo_sprite.setPosition((windowSize.x - logoSize.x) / 2.0f, (windowSize.y - logoSize.y) / 2.0f);
}

void SplashScreenUIController::updateLogo(float deltaTime)
{
    if (elapsed_time <= 3.0f)
        showLogoWithFade();
    else
        hideLogoWithFade();
}

// Calculate the alpha value based on elapsed time (e.g., linear interpolation)
void SplashScreenUIController::showLogoWithFade()
{
    float alpha = std::min(1.0f, elapsed_time / logo_animation_time); // Gradually becomes visible over 2 seconds
    outscal_logo_sprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha * 255)));
}

// Once the logo is fully visible, start fading out after 2 seconds.
void SplashScreenUIController::hideLogoWithFade()
{
    float alpha = std::max(0.0f, 1.0f - ((elapsed_time - 3.0f) / logo_animation_time));
    outscal_logo_sprite.setColor(sf::Color(255, 255, 255, static_cast<sf::Uint8>(alpha * 255)));
}

void SplashScreenUIController::logoAnimationComplete()
{
    ServiceLocator::getInstance()->getSoundService()->playBackgroundMusic();
    GameService::setGameState(GameState::MAIN_MENU);
}

void SplashScreenUIController::showSplashScreen()
{
    // Reset the Clock:
    clock.restart();
    elapsed_time = 0.0f;
}