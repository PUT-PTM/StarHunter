#include "Game.h"

Game::Game() :
	display(800, 600),
	inputManager(display),
	player(display.getWidth() / 2.0f, display.getHeight() / 2.0f)
{
	drawingThread = nullptr;
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
	startDrawing();
	logicLoop();
	stopDrawing();
	timer.stop();
}

void Game::logicLoop(){
		while(!end){
		InputManager::InputEvent inputEvent;
		inputEvent = inputManager.getEvent();

		if(inputEvent.exitInitialized())
			end = true;

		player.changeDirection(inputEvent.getLastMove());

		GameTimer::TimerTickType timerType = timer.getTimerTick();
		if(timerType != GameTimer::TimerTickType::NONE)
		{
			if(timerType == GameTimer::TimerTickType::MAIN){		// Main timer
				player.move();
			}
			else{													// Animation timer
				player.animate();
			}

			draw = true;
		}
	}
}

void Game::startDrawing(){
	drawingThread = new std::thread(&Game::drawingLoop, this);
}

void Game::stopDrawing(){
	drawingThread->join();
	delete drawingThread;
	drawingThread = nullptr;
}

void Game::drawingLoop(){
	al_set_target_backbuffer(display.getAllegroDisplay()); // set target in new thread
	while(!end){
		if(draw){
			display.clear();

			player.draw();

			display.flip();
			draw = false;
		}
	}
}