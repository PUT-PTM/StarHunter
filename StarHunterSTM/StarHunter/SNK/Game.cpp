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
	star.generateNewPositionBasedOnPlayerPosition(player);
	
	startInitializingSound();
	setupInput();
}

void Game::startInitializingSound(){
	std::thread *t = new std::thread(&Game::initializeSound, this);
}

void Game::initializeSound(){
	sound.loadSamples();
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

		if(player.collidesWith(star))
		{
			
			sound.playStarSoundEffect();
			score++;
			std::cout << "Score: " <<  score << std::endl;
			std::cout << al_get_time() << std::endl;
			std::cout << "Player position: " << player.getPositionX() << " | " << player.getPositionY() << std::endl;
			std::cout << "Star old position: " << star.getPositionX() << " | " << star.getPositionY() << std::endl;	
			star.generateNewPositionBasedOnPlayerPosition(player);
			std::cout << "Star new position: " << star.getPositionX() << " | " << star.getPositionY() << std::endl;			
			std::cout << std::endl;
		};
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
			
			display.flip();
			draw = false;
		}
	}
}