#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>

class EventService
{
private:
	sf::Event game_event;
	sf::RenderWindow* game_window;

	bool isGameWindowOpen();
	bool gameWindowWasClosed();
	bool hasQuitGame();
	bool isKeyboardEvent();
	bool pressedEscapeKey();

public:
	EventService();
	~EventService();

	void initialize();
	void processEvents();
};