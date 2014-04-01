#include "AllegroManager.h"
#include "Display.h"
#include "TiledSprite.h"

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

int main(){
	AllegroManager::initializeAllegro();
	Display display(800, 600);
	bool end = false;

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

		ALLEGRO_EVENT event;        
        al_wait_for_event(queue, &event);
		 
		if(event.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch(event.keyboard.keycode)   
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
			}

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