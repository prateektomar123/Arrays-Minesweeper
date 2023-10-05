#pragma once
#include <chrono>

class TimeService
{
private:
	std::chrono::time_point<std::chrono::steady_clock> previous_time;
	float delta_time;
	bool b_first_frame;

	void updateDeltaTime();

public:
	TimeService();
	~TimeService();

	void initialize();
	void update();

	float getDeltaTime();
};