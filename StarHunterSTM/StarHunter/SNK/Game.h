#pragma once
#include <thread>
#include "hid.h"
#include "Display.h"
#include "Player.h"
#include "InputManager.h"
#include "GameTimer.h"

class Game{
private:
	Display display;
	InputManager inputManager;
	GameTimer timer;
	Player player;

	bool end, draw;
	std::thread *drawingAndTimersRelatedLogicThread;
	void setup();
	void logicLoop();
	void startDrawingAndTimersRelatedLogic();
	void stopDrawingAndTimersRelatedLogic();
	void drawingAndTimersRelatedLogicLoop();	
public:
	Game();
	void run();
};