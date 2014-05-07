#pragma once

#include <allegro5/allegro.h>

class AllegroStopWatch{
private:
	float startTime;
public:
	AllegroStopWatch();
	void restart();
	float getElapsedSeconds();
};