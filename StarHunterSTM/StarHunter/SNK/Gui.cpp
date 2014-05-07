#include "Gui.h"



Gui::Gui(float displayWidth, float displayHeight)
	: fontColor(al_map_rgb(255, 255, 160)),
	fontSize(2)
{
	time = 0;
	score = 0;
	textFont = nullptr;
	setupPositions(displayWidth, displayHeight);
}

Gui::~Gui(){
	al_destroy_font(textFont);
}

void Gui::setupPositions(float displayWidth, float displayHeight){
	scorePositionX = displayWidth / 50.0f;
	scorePositionY = displayHeight / 60.0f;
	timePositionX = displayWidth / 1.275f;
	timePositionY = scorePositionY;
	onPausedTextPositionX = displayWidth / 2.0f;
	onPausedTextPositionY = displayHeight / 2.0f;
}

void Gui::attachFonts(ALLEGRO_FONT *textFont, ALLEGRO_FONT *bigTextFont){
	this->textFont = textFont;
	this->bigTextFont = bigTextFont;
}

void Gui::drawScore(){
	al_draw_textf(textFont, fontColor, scorePositionX, scorePositionY, ALLEGRO_ALIGN_LEFT, "score: %2d", score);	
}

void Gui::drawTime(){
	al_draw_textf(textFont, fontColor, timePositionX, timePositionY, ALLEGRO_ALIGN_LEFT, "time: %2d", time);
}

void Gui::draw(){
	drawScore();
	drawTime();
}

void Gui::drawOnPause(){
	al_draw_textf(
		bigTextFont,
		fontColor,
		onPausedTextPositionX,
		onPausedTextPositionY - 55,
		ALLEGRO_ALIGN_CENTER,
		"Your score: %2d",
		score);
	al_draw_textf(
		bigTextFont,
		fontColor,
		onPausedTextPositionX,
		onPausedTextPositionY + 45,
		ALLEGRO_ALIGN_CENTER,
		"Press ENTER to play again");
}

void Gui::setTime(int time){
	this->time = time;
}

void Gui::setScore(int score){
	this->score = score;
}
