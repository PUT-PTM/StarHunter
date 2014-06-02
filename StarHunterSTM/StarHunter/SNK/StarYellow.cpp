#include "StarYellow.h"

StarYellow::StarYellow(float pX, float pY, float displayWidth, float displayHeight) : 
	Star(pX, pY, 0, 0)
{
	this->displayWidth = displayWidth;
	this->displayHeight = displayHeight;
	sprite = nullptr;
	srand(time(NULL));
}

StarYellow::~StarYellow(){
	if(sprite)
		delete sprite;
}

void StarYellow::setupParameters(){
	setWidth(sprite->getWidth());
	setHeight(sprite->getHeight());

	emptySpaceScale = 3.0f;
	emptySpaceWidth = getWidth() * emptySpaceScale;
	emptySpaceHeight = getHeight() * emptySpaceScale;
	usableWidth = displayWidth - getWidth();
	usableHeight = displayHeight - getHeight();
}

void StarYellow::attachBitmap(ALLEGRO_BITMAP* starBitmap){
	if(sprite)
		delete sprite;
	sprite = new Sprite(starBitmap);
	setupParameters();
}

void StarYellow::generateNewPositionBasedOnPlayerPosition(Entity player){
	while(!validateNewPosition(player))
		generateNewPosition();
};

void StarYellow::generateNewPosition(){
	float newPositionX = rand() % usableWidth + getWidth() / 2.0f;
	float newPositionY = rand() % usableHeight + getHeight() / 2.0f;
	this->setPosition(newPositionX, newPositionY);
}

bool StarYellow::validateNewPosition(Entity e){
	if(this->getPositionX() + this->emptySpaceWidth / 2.0f > e.getPositionX() - e.getWidth() / 2.0f &&
		this->getPositionX() - this->emptySpaceWidth / 2.0f < e.getPositionX() + e.getWidth() / 2.0f &&
		  this->getPositionY() - this->emptySpaceHeight / 2.0f < e.getPositionY() + e.getHeight() / 2.0f &&
			this->getPositionY() + this->emptySpaceHeight / 2.0f > e.getPositionY() - e.getHeight() / 2.0f)
			return false;
	 return true;
}

void StarYellow::setPosition(float pX, float pY){
	sprite->setPosition(pX, pY);
	Entity::setPosition(pX, pY);
}

void StarYellow::draw(){
	sprite->draw();
};
/*
int StarYellow::affect(Entity player, int score)
{
	score++;
	return score ;
}*/
