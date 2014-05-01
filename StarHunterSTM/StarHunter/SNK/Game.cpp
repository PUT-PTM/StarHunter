#include "Game.h"

Game::Game() :
	display(800, 600),
	inputManager(display),
	player(
		display.getWidth() / 2.0f, display.getHeight() / 2.0f,
		display.getWidth(), display.getHeight()),
		background(&display)
{
	drawingAndTimersRelatedLogicThread = nullptr;
	end = false;
	draw = true;

	setup();
}

void Game::setup(){
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

void Game::startDrawingAndTimersRelatedLogic(){
	drawingAndTimersRelatedLogicThread = new std::thread(&Game::drawingAndTimersRelatedLogicLoop, this);
}

void Game::stopDrawingAndTimersRelatedLogic(){
	drawingAndTimersRelatedLogicThread->join();
	delete drawingAndTimersRelatedLogicThread;
	drawingAndTimersRelatedLogicThread = nullptr;
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
			}
			else{													// Animation timer
				player.animate();
			}

			draw = true;
		}

		if(draw){
			display.clear();

			background.draw();
			player.draw();

			display.flip();
			draw = false;
		}
	}
}