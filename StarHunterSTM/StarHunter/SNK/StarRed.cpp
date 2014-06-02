#include "StarRed.h"

StarRed::StarRed(float pX, float pY, float displayWidth, float displayHeight) : 
	Star(pX, pY, 0, 0)
{
	this->displayWidth = displayWidth;
	this->displayHeight = displayHeight;
	sprite = nullptr;
	srand(time(NULL));
}

StarRed::~StarRed(){
	if(sprite)
		delete sprite;
}

void StarRed::setupParameters(){
	setWidth(sprite->getWidth());
	setHeight(sprite->getHeight());

	emptySpaceScale = 3.0f;
	emptySpaceWidth = getWidth() * emptySpaceScale;
	emptySpaceHeight = getHeight() * emptySpaceScale;
	usableWidth = displayWidth - getWidth();
	usableHeight = displayHeight - getHeight();
}

void StarRed::attachBitmap(ALLEGRO_BITMAP* starBitmap){
	if(sprite)
		delete sprite;
	sprite = new Sprite(starBitmap);
	setupParameters();
}

void StarRed::generateNewPositionBasedOnPlayerPosition(Entity player){
	while(!validateNewPosition(player))
		generateNewPosition();
};

void StarRed::generateNewPosition(){
	float newPositionX = rand() % usableWidth + getWidth() / 2.0f;
	float newPositionY = rand() % usableHeight + getHeight() / 2.0f;
	this->setPosition(newPositionX, newPositionY);
}

bool StarRed::validateNewPosition(Entity e){
	if(this->getPositionX() + this->emptySpaceWidth / 2.0f > e.getPositionX() - e.getWidth() / 2.0f &&
		this->getPositionX() - this->emptySpaceWidth / 2.0f < e.getPositionX() + e.getWidth() / 2.0f &&
		  this->getPositionY() - this->emptySpaceHeight / 2.0f < e.getPositionY() + e.getHeight() / 2.0f &&
			this->getPositionY() + this->emptySpaceHeight / 2.0f > e.getPositionY() - e.getHeight() / 2.0f)
			return false;
	 return true;
}

void StarRed::setPosition(float pX, float pY){
	sprite->setPosition(pX, pY);
	Entity::setPosition(pX, pY);
}

void StarRed::draw(){
	sprite->draw();
};
/*
int StarRed::affect(Entity player, int score)
{
	score += 2;
	return score;
}
*/