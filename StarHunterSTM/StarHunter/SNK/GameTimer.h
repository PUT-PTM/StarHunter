#pragma once

#include <thread>
#include "allegro5\allegro.h"

class GameTimer{
public:
	enum TimerTickType{
		MAIN,
		ANIMATION,
		NONE
	};

	GameTimer();
	~GameTimer();
	void start();
	void stop();
	TimerTickType getTimerTick();
private:
	ALLEGRO_TIMER *mainTimer, *animationTimer;
	ALLEGRO_EVENT_QUEUE *queue;
	bool stopped;

	void timersLoop();
};