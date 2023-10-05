#include "../header/TimeService.h"

TimeService::TimeService()
{
}

TimeService::~TimeService()
{
}


void TimeService::initialize()
{
	previous_time = std::chrono::steady_clock::now();
	delta_time = 0;
}

void TimeService::update()
{
	updateDeltaTime();
}

float TimeService::getDeltaTime()
{
	return delta_time;
}

void TimeService::updateDeltaTime()
{
	int delta = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - previous_time).count();
	previous_time += std::chrono::microseconds(delta);

	delta_time = static_cast<float>(delta) / static_cast<float>(1000000);
}