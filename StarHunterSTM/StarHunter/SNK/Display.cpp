#include "Display.h"

Display::Display(int width, int height){
	display = al_create_display(width, height);
 
    if(!display)
		throw new MyException("Could not create Allegro Display");
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

int Display::getWidth(){
	return al_get_display_width(display);
}

int Display::getHeight(){
	return al_get_display_height(display);
}