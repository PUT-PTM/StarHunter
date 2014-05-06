#include "Gui.h"



Gui::Gui(){
	fontLoaded = false;
	score = 0;
}

Gui::~Gui(){
	al_destroy_font(textFont);
}

void Gui::attachFont(ALLEGRO_FONT * textFont){
	this->textFont = textFont;
	fontLoaded = true;
}

void Gui::drawScore(){
		if(textFont){
		al_draw_textf(textFont, al_map_rgb(255,255,160), 750, 10, 2, "score: %i", score);
				
	}
}

void Gui::setScore(int score){
	this->score = score;
}
int Gui::getScore(){
	return this->score;
}
