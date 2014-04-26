#include <iostream>
#include "hid.h"
#include "AllegroInitializer.h"
#include "Display.h"
#include "Player.h"
#include "InputManager.h"
#include "GameTimer.h"

int main(){
	AllegroInitializer::initialize();
	Display display(800, 600);
	InputManager inputManager(display);
	GameTimer timer;
	Player player(display.getWidth() / 2.0f, display.getHeight() / 2.0f);

	//inputManager.connectSTM();
	//inputManager.registerSTM();
	inputManager.registerAllegro();
	timer.start();

	bool end = false;
	bool draw = true;
	while(!end){
		InputManager::InputEvent inputEvent;
		inputEvent = inputManager.getEvent();

		if(inputEvent.exitInitialized())
			end = true;

		player.changeDirection(inputEvent.getLastMove());

		GameTimer::TimerTickType timerType = timer.getTimerTick();
		if(timerType != GameTimer::TimerTickType::NONE)
		{
			if(timerType == GameTimer::TimerTickType::MAIN)		// Main timer
				player.move();
			else												// Animation timer
				player.animate();

			draw = true;
		}		

		if(draw){
			display.clear();
			player.draw();
			display.flip();
			draw = false;
		}
	}

	inputManager.endRegistering();
	return 0;
}