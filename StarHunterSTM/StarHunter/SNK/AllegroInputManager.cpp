#include "AllegroInputManager.h"

AllegroInputManager::AllegroInputManager(ALLEGRO_DISPLAY* display){
	this->display = display;
}

AllegroInputManager::AllegroInputManager(Display &display){
	this->display = display.getAllegroDisplay();
}

AllegroInputManager::~AllegroInputManager(){
	al_destroy_event_queue(queue);
}

void AllegroInputManager::registerInput(){
	queue = al_create_event_queue();
	al_register_event_source(queue, al_get_keyboard_event_source());
	al_register_event_source(queue, al_get_display_event_source(display));
}

ALLEGRO_EVENT AllegroInputManager::getEvent(){
	ALLEGRO_EVENT ev;

	al_get_next_event(queue, &ev);
	return ev;
}