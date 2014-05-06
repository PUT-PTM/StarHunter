#include "Game.h"

Game::Game() :
	display(800, 600),
	inputManager(display),
	player(
	display.getWidth() / 2.0f, display.getHeight() / 2.0f,
	display.getWidth(), display.getHeight()),
	background(&display),
	star(50, 50, display.getWidth(), display.getHeight())
{
	drawingAndTimersRelatedLogicThread = nullptr;
	end = false;
	draw = true;
	score = 0;


	startInitializingSound();
	initializeBitmaps();
	initializeFonts();
	setupInput();
}

Game::~Game(){
	resourcesManager.unloadSounds();
}

void Game::initializeBitmaps(){
	resourcesManager.loadBitmaps();
	player.attachBitmap(resourcesManager.playerSheetBitmap);
	background.attachBitmap(resourcesManager.backgroundBitmap);
	star.attachBitmap(resourcesManager.starBitmap);
	star.generateNewPosition();
	star.generateNewPositionBasedOnPlayerPosition(player);
}

void Game::initializeFonts(){
	resourcesManager.loadFonts();
	gui.attachFont(resourcesManager.textFont);
}

void Game::startInitializingSound(){
	std::thread *t = new std::thread(&Game::initializeSound, this);
}

void Game::initializeSound(){
	resourcesManager.loadSounds();
	sound.attachSamples(resourcesManager.mainBackgroundThemeSample, resourcesManager.starCatchEffectSample);
	sound.prepare();
	sound.playBackgroundMusic();
}

void Game::setupInput(){

	//inputManager.connectSTM();
	//inputManager.registerSTM();
	inputManager.registerAllegro();
}

void Game::run(){
	timer.start();

	startDrawingAndTimersRelatedLogic();
	logicLoop();
	stopDrawingAndTimersRelatedLogic();

	timer.stop();
}

void Game::startDrawingAndTimersRelatedLogic(){
	drawingAndTimersRelatedLogicThread = new std::thread(&Game::drawingAndTimersRelatedLogicLoop, this);
}

void Game::stopDrawingAndTimersRelatedLogic(){
	drawingAndTimersRelatedLogicThread->join();
	delete drawingAndTimersRelatedLogicThread;
	drawingAndTimersRelatedLogicThread = nullptr;
}

void Game::logicLoop(){
	while(!end){
		InputManager::InputEvent inputEvent;
		inputEvent = inputManager.getEvent();

		if(inputEvent.exitInitialized())
			end = true;

		player.changeDirection(inputEvent.getLastMove());
		background.changeDirection(inputEvent.getLastMove());
	}
}

void Game::drawingAndTimersRelatedLogicLoop(){
	al_set_target_backbuffer(display.getAllegroDisplay()); // set target in new thread
	while(!end){
		GameTimer::TimerTickType timerType = timer.getTimerTick();
		if(timerType != GameTimer::TimerTickType::NONE)
		{
			if(timerType == GameTimer::TimerTickType::MAIN){		// Main timer
				background.move();
				player.move();

				if(player.collidesWith(star))
				{
					star.generateNewPositionBasedOnPlayerPosition(player);
					sound.playStarSoundEffect();
					score++;
					gui.setScore(score);
				};

				draw = true;
			}
			else{													// Animation timer
				player.animate();
			}		
		}

		if(draw){
			display.clear();
			
			background.draw();
			star.draw();
			player.draw();
			gui.drawScore();
			display.flip();
			draw = false;
			
		}
	}
}