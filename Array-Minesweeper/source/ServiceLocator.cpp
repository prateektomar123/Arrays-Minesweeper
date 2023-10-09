#include "../header/ServiceLocator.h"
#include "../header/EventService.h"
#include "../header/GraphicService.h"
#include "../header/SoundService.h"
#include "../header/UIService.h"
#include "../header/GameplayService.h"
#include "../header/TimeService.h"

ServiceLocator::ServiceLocator() 
{ 
	graphic_service = nullptr;
	event_service = nullptr;
	time_service = nullptr;
	sound_service = nullptr;
	ui_service = nullptr;
	gameplay_service = nullptr;
	game_window = nullptr;

	createServices(); 
}

ServiceLocator::~ServiceLocator() { clearAllServices(); }

void ServiceLocator::createServices()
{
	event_service = new EventService();
	graphic_service = new GraphicService();
	time_service = new TimeService();
	sound_service = new SoundService();
	ui_service = new UIService();
	gameplay_service = new GameplayService();
}

void ServiceLocator::initialize()
{
	graphic_service->initialize();
	sound_service->initialize();
	time_service->initialize();

	game_window = graphic_service->getGameWindow();

	event_service->initialize();
	ui_service->initialize();
	gameplay_service->initialize();
}

void ServiceLocator::update()
{
	graphic_service->update();
	time_service->update();
	event_service->update();
	gameplay_service->update();
	ui_service->update();
}

void ServiceLocator::render()
{
	graphic_service->render();
	gameplay_service->render();
	ui_service->render();
}

void ServiceLocator::clearAllServices()
{
	delete(ui_service);
	delete(graphic_service);
	delete(sound_service);
	delete(event_service);
	delete(gameplay_service);
	delete(time_service);
}

ServiceLocator* ServiceLocator::getInstance()
{
	static ServiceLocator instance;
	return &instance;
}

sf::RenderWindow* ServiceLocator::getGameWindow() { return game_window; }

EventService* ServiceLocator::getEventService() { return event_service; }

GraphicService* ServiceLocator::getGraphicService() { return graphic_service; }

TimeService* ServiceLocator::getTimeService() { return time_service; }

SoundService* ServiceLocator::getSoundService() { return sound_service; }

UIService* ServiceLocator::getUIService() { return ui_service; }

GameplayService* ServiceLocator::getGameplayService()
{
	return gameplay_service;
}

void ServiceLocator::deleteServiceLocator() { delete(this); }