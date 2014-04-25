#pragma once

#include <allegro5\allegro.h>
#include "Display.h"

class AllegroInputManager{
private:
	ALLEGRO_DISPLAY* display;
	ALLEGRO_EVENT_QUEUE *queue;
public:
	AllegroInputManager(ALLEGRO_DISPLAY *display);
	AllegroInputManager(Display &display);
	~AllegroInputManager();

	void registerInput();
	ALLEGRO_EVENT getEvent();
};