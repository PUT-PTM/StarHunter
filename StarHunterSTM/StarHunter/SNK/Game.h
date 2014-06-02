#pragma once
#include <thread>
#include <iostream>
#include "hid.h"

#include "InputManager.h"
#include "GameTimer.h"
#include "AllegroStopWatch.h"
#include "SpaceBackground.h"
#include "ResourcesManager.h"

#include "Display.h"
#include "Player.h"
#include "StarYellow.h"
#include "StarGreen.h"
#include "StarBlue.h"
#include "StarRed.h"
#include "Sound.h"
#include "Gui.h"


class Game{
private:
	enum GameState{
		NotStarted,
		Started,
		Paused
	};
	Display display;
	InputManager inputManager;
	ResourcesManager resourcesManager;
	GameTimer timer;
	int maxTime;
	AllegroStopWatch watch;
	Player player;
	SpaceBackground background;
	StarYellow starYellow;
	StarGreen starGreen;
	StarBlue starBlue;
	StarRed starRed;
	Sound sound;
	Gui gui;
	GameState state;

	bool end, draw;
	int score;
	int change;		


	std::thread *drawingAndTimersRelatedLogicThread;
	std::thread *startInitializingSountThread;

	void restartGame();
	void pauseGame();
	void startGame();
	void initializeBitmaps();
	void initializeFonts();
	void initializeSound();
	void startInitializingSound();
	void setupInput();
	void logicLoop();
	void startDrawingAndTimersRelatedLogic();
	void stopDrawingAndTimersRelatedLogic();
	void drawingAndTimersRelatedLogicLoop();
public:
	Game();
	~Game();
	void run();
	
};