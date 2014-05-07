#pragma once
#include "allegro5\allegro.h"
#include "MyException.h"

class Display{
private:
	ALLEGRO_DISPLAY *display;
	int width, height;
public:
	//throws MyException
	Display(int width, int height);

	~Display();

	void flip();
	void clear();
	void clearToColor(ALLEGRO_COLOR color);
	ALLEGRO_DISPLAY* getAllegroDisplay();
	int getWidth();
	int getHeight();
	void setIcon(ALLEGRO_BITMAP *icon);
};