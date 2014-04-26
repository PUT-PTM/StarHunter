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
	std::thread *drawingThread;
	void setup();
	void startDrawing();
	void stopDrawing();
	void logicLoop();
	void drawingLoop();
public:
	Game();
	void run();
};