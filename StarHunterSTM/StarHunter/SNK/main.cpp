#include "AllegroManager.h"
#include "Display.h"
#include "TiledSprite.h"
#include "hid.h"
#include <iostream>



enum DIR{
	DOWN = 0,
	LEFT,
	RIGHT,
	UP
};

void iterate(int &i, int max){
	i++;
	if(i > max)
		i = 0;
}

/// coœ dodane

char buffer_in[64];
int move = 1;
int T[2];
//




int kat = 15;  // wartosc k¹ta nachylenia


int main(){
	AllegroManager::initializeAllegro();
	Display display(800, 600);
	bool end = false;

	/////
	for (int i=0;i<64;i++) {
		//buffer_out[i]=0;	
		buffer_in[i]=0;
	}
	////
	FindTheHID();

	ALLEGRO_TIMER *timer = al_create_timer(1.0 / 60);
	ALLEGRO_TIMER *animationTimer = al_create_timer(1.0 / 5);
    ALLEGRO_EVENT_QUEUE *queue = al_create_event_queue();
	al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_timer_event_source(timer));
	al_register_event_source(queue, al_get_timer_event_source(animationTimer));

	TiledSprite player("assets/gfx/playerSheet.png", 3, 4);
	player.setPosition(display.getWidth() / 2.0f, display.getHeight() / 2.0f);

	DIR dir = UP;
	DIR newDir = dir;
	float speed = 5.0f;
	int animationRegionCounter = 0;

	bool draw = true;
	al_start_timer(timer);
	al_start_timer(animationTimer);
	while(!end){
		float x = 0, y = 0;
		//dodane, wczytanie wartoœci z STM
		ReadInputReport(buffer_in);
		//dodane  zmiana wartoœci na mo¿liwoœæ poruszania sie
		
	T[0] = (int)buffer_in[1];
	T[1] = (int)buffer_in[2];
		///dodane
		if (T[0] < -kat)  move = 0;
		if (T[0] >  kat)  move = 1;
		if (T[1] < -kat)  move = 2;
		if (T[1] >  kat)  move = 3;;
		//


		ALLEGRO_EVENT event;        
        al_wait_for_event(queue, &event);
		 
		//if(event.type == ALLEGRO_EVENT_KEY_DOWN)
		{

		//dodane
				switch (move)
		{
		case 0:
		newDir = UP;
		break;
		case 1:
		newDir = DOWN	;
		break;
		case 2:
		newDir = LEFT;
		break;
		case 3:
		newDir = RIGHT;	
		break;
		}		
				//dodane
				if(event.keyboard.keycode == ALLEGRO_KEY_ESCAPE)	
					end = true;

			/*switch(event.keyboard.keycode)   
			{                                    
			case ALLEGRO_KEY_DOWN:           
				newDir = DOWN;
				break;
			case ALLEGRO_KEY_UP:
				newDir = UP;
				break;
			case ALLEGRO_KEY_LEFT:
				newDir = LEFT;
				break;
			case ALLEGRO_KEY_RIGHT:
				newDir = RIGHT;
				break;
			case ALLEGRO_KEY_ESCAPE:
				end = true;
				break;
			}*/

			if(dir != newDir){
				animationRegionCounter = 1;
				dir = newDir;
			}
		};


		if(event.type == ALLEGRO_EVENT_TIMER)
		{
			if(event.timer.source == timer){
				switch(dir)
				{
				case DOWN:
					newDir = DOWN;
					y += speed;
					break;
				case UP:
					newDir = UP;
					y -= speed;
					break;
				case LEFT:
					newDir = LEFT;
					x -= speed;
					break;
				case RIGHT:
					newDir = RIGHT;
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
		}
	}

	return 0;
}