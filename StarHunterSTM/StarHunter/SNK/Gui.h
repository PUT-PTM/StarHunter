#pragma once
#include <allegro5\allegro_font.h>

class Gui{	
protected:
	ALLEGRO_FONT *textFont, *bigTextFont;
	ALLEGRO_COLOR fontColor;
	const int fontSize;
	int score, time;
	float scorePositionX, scorePositionY;
	float timePositionX, timePositionY;
	float onPausedTextPositionX, onPausedTextPositionY;

	void setupPositions(float displayWidth, float displayHeight);	
	void drawScore();
	void drawTime();
public:
	Gui(float displayWidth, float displayHeight);
	void attachFonts(ALLEGRO_FONT *textFont, ALLEGRO_FONT *bigTextFont);
	void draw();
	void drawOnPause();
	void setScore(int score);
	void setTime(int time);
};