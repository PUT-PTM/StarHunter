#pragma once
#include <thread>
#include <iostream>
#include "hid.h"
#include "Display.h"
#include "Player.h"
#include "InputManager.h"
#include "GameTimer.h"
#include "SpaceBackground.h"
#include "Star.h"
#include "Sound.h"


class Game{
private:
	Display display;
	InputManager inputManager;
	GameTimer timer;
	Player player;
	SpaceBackground background;
	Star star;
	Sound sound;

	float oldPosX, oldPosY;

	bool end, draw;
	int score;
	std::thread *drawingAndTimersRelatedLogicThread;

	void initializeSound();
	void startInitializingSound();
	void setupInput();
	void logicLoop();
	void startDrawingAndTimersRelatedLogic();
	void stopDrawingAndTimersRelatedLogic();
	void drawingAndTimersRelatedLogicLoop();
public:
	Game();
	void run();
};