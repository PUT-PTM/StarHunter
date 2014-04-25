#include <iostream>
#include "AllegroInitializer.h"
#include "Display.h"
#include "TiledSprite.h"
#include "hid.h"
#include "InputManager.h"


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
	bool end = false;


	ALLEGRO_TIMER *timer = al_create_timer(1.0 / 100);
	ALLEGRO_TIMER *animationTimer = al_create_timer(1.0 / 5);
	ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
	al_register_event_source(queue, al_get_timer_event_source(timer));
	al_register_event_source(queue, al_get_timer_event_source(animationTimer));

	TiledSprite player("assets/gfx/playerSheet.png", 3, 4);
	player.setPosition(display.getWidth() / 2.0f, display.getHeight() / 2.0f);

	DIR dir = DIR::UP;
	DIR newDir = dir;
	float speed = 3.0f;
	int animationRegionCounter = 0;

	//inputManager.connectSTM();
	//inputManager.registerSTM();
	inputManager.registerAllegro();

	bool draw = true;
	al_start_timer(timer);
	al_start_timer(animationTimer);
	while(!end){
		float x = 0, y = 0;


		ALLEGRO_EVENT event;        
		al_wait_for_event(queue, &event);

		InputManager::InputEvent inputEvent;
		inputEvent = inputManager.getEvent();

		if(inputEvent.exitInitialized())
			end = true;

		newDir = inputEvent.getLastMove();
		if(dir != newDir){
			animationRegionCounter = 1;
			dir = newDir;
		}


		if(event.type == ALLEGRO_EVENT_TIMER)
		{
			if(event.timer.source == timer){
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