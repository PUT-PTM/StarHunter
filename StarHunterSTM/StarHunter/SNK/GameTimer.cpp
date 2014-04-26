#include "GameTimer.h"

GameTimer::GameTimer(){
	mainTimer = al_create_timer(1.0 / 100);
	animationTimer = al_create_timer(1.0 / 5);
	queue = al_create_event_queue();
	al_register_event_source(queue, al_get_timer_event_source(mainTimer));
	al_register_event_source(queue, al_get_timer_event_source(animationTimer));
	stopped = true;
}
GameTimer::~GameTimer(){
	stop();
	al_destroy_event_queue(queue);
	al_destroy_timer(mainTimer);
	al_destroy_timer(animationTimer);	
}

void GameTimer::start(){
	if(stopped){
		stopped = false;
		al_start_timer(mainTimer);
		al_start_timer(animationTimer);
	}
}

void GameTimer::stop(){
	if(!stopped){
		stopped = true;
		al_stop_timer(mainTimer);
		al_stop_timer(animationTimer);
	}
}

GameTimer::TimerTickType GameTimer::getTimerTick(){
	TimerTickType type = NONE;

	ALLEGRO_EVENT ev;
	al_get_next_event(queue, &ev);
	if(ev.type == ALLEGRO_EVENT_TIMER){
		if(ev.timer.source == mainTimer)
			type = MAIN;
		else
			type = ANIMATION;
	}
	return type;
}

