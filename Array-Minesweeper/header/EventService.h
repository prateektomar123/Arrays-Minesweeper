#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class EventService
{
private:
	sf::Event game_event;
	sf::RenderWindow* game_window;

	bool is_mouse_button_pressed;

	bool isGameWindowOpen();
	bool gameWindowWasClosed();
	bool hasQuitGame();
	bool isKeyboardEvent();

public:
	EventService();
	~EventService();

	void initialize();
	void processEvents();
	
	bool pressedEscapeKey();
	bool pressedLeftMouseButton();
	bool pressedRightMouseButton();
};