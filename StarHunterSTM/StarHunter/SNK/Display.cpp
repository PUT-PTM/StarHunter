#include "Display.h"

Display::Display(int width, int height){
	display = al_create_display(width, height);
	al_set_window_title(display, "StarHunter");
 
    if(!display)
		throw new MyException("Could not create Allegro Display");
	this->width = width;
	this->height = height;
	clear();
	flip();
}

Display::~Display(){
	if(display)
		al_destroy_display(display);
}

void Display::flip(){
	al_flip_display();
}

void Display::clear(){
	al_clear_to_color(al_map_rgb(0, 0, 0));
}

void Display::clearToColor(ALLEGRO_COLOR color){
	al_clear_to_color(color);
}

ALLEGRO_DISPLAY* Display::getAllegroDisplay(){
	return display;
}

int Display::getWidth(){
	return width;
}

int Display::getHeight(){
	return height;
}