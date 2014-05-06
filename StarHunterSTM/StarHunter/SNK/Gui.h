#pragma once
#include <allegro5\allegro_font.h>

class Gui{	
protected:
	ALLEGRO_FONT *textFont;
	int score;
	bool fontLoaded;
	
public:
	Gui();
	~Gui();
	void attachFont(ALLEGRO_FONT *textFont);
	void drawScore();
	void setScore(int score);
	int getScore();


};