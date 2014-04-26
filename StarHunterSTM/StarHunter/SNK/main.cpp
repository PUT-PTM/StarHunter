#include <iostream>
#include "AllegroInitializer.h"
#include "Display.h"
#include "TiledSprite.h"
#include "hid.h"
#include "InputManager.h"
#include "GameTimer.h"


void iterate(int &i, int max){
	i++;
	if(i > max)
		i = 0;
}

int main(){
	typedef InputManager::MoveEventType DIR;

	AllegroInitializer::initialize();
	Display display(800, 600);
	InputManager inputManager(display);
	GameTimer timer;
	bool end = false;


	TiledSprite player("assets/gfx/playerSheet.png", 3, 4);
	player.setPosition(display.getWidth() / 2.0f, display.getHeight() / 2.0f);

	DIR dir = DIR::UP;
	DIR newDir = dir;
	float speed = 3.0f;
	int animationRegionCounter = 0;

	//inputManager.connectSTM();
	//inputManager.registerSTM();
	inputManager.registerAllegro();

	timer.start();
	bool draw = true;
	while(!end){
		float x = 0, y = 0;

		InputManager::InputEvent inputEvent;
		inputEvent = inputManager.getEvent();

		if(inputEvent.exitInitialized())
			end = true;

		newDir = inputEvent.getLastMove();
		if(dir != newDir){
			animationRegionCounter = 1;
			dir = newDir;
		}

		GameTimer::TimerTickType timerType = timer.getTimerTick();
		if(timerType != GameTimer::TimerTickType::NONE)
		{
			if(timerType == GameTimer::TimerTickType::MAIN){
				switch(dir)
				{
				case DIR::DOWN:
					newDir = DIR::DOWN;
					y += speed;
					break;
				case DIR::UP:
					newDir = DIR::UP;
					y -= speed;
					break;
				case DIR::LEFT:
					newDir = DIR::LEFT;
					x -= speed;
					break;
				case DIR::RIGHT:
					newDir = DIR::RIGHT;
					x += speed;
					break;
				}
			}
			else
				iterate(animationRegionCounter, player.getColumnsCount() - 1);

			draw = true;
		}
		player.setPosition(player.getPositionX() + x, player.getPositionY() + y);

		if(draw){
			display.clear();
			player.drawRegion(dir, animationRegionCounter);
			display.flip();
			draw = false;
		}
	}

	inputManager.endRegistering();
	return 0;
}