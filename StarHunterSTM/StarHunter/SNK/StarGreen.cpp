#include "StarGreen.h"

StarGreen::StarGreen(float pX, float pY, float displayWidth, float displayHeight) : 
	Star(pX, pY, 0, 0)
{
	this->displayWidth = displayWidth;
	this->displayHeight = displayHeight;
	sprite = nullptr;
	srand(time(NULL));
}

StarGreen::~StarGreen(){
	if(sprite)
		delete sprite;
}

void StarGreen::setupParameters(){
	setWidth(sprite->getWidth());
	setHeight(sprite->getHeight());

	emptySpaceScale = 3.0f;
	emptySpaceWidth = getWidth() * emptySpaceScale;
	emptySpaceHeight = getHeight() * emptySpaceScale;
	usableWidth = displayWidth - getWidth();
	usableHeight = displayHeight - getHeight();
}

void StarGreen::attachBitmap(ALLEGRO_BITMAP* starBitmap){
	if(sprite)
		delete sprite;
	sprite = new Sprite(starBitmap);
	setupParameters();
}

void StarGreen::generateNewPositionBasedOnPlayerPosition(Entity player){
	while(!validateNewPosition(player))
		generateNewPosition();
};
void StarGreen::generateNewPosition(){
	float newPositionX = rand() % usableWidth + getWidth() / 2.0f;
	float newPositionY = rand() % usableHeight + getHeight() / 2.0f;
	this->setPosition(newPositionX, newPositionY);
}

bool StarGreen::validateNewPosition(Entity e){
	if(this->getPositionX() + this->emptySpaceWidth / 2.0f > e.getPositionX() - e.getWidth() / 2.0f &&
		this->getPositionX() - this->emptySpaceWidth / 2.0f < e.getPositionX() + e.getWidth() / 2.0f &&
		  this->getPositionY() - this->emptySpaceHeight / 2.0f < e.getPositionY() + e.getHeight() / 2.0f &&
			this->getPositionY() + this->emptySpaceHeight / 2.0f > e.getPositionY() - e.getHeight() / 2.0f)
			return false;
	 return true;
}

void StarGreen::setPosition(float pX, float pY){
	sprite->setPosition(pX, pY);
	Entity::setPosition(pX, pY);
}

void StarGreen::draw(){
	sprite->draw();
};
/*
int StarGreen::affect(Entity player, int score){
	return score--;
}
*/