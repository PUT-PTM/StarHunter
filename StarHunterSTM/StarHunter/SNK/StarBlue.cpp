#include "StarBlue.h"

StarBlue::StarBlue(float pX, float pY, float displayWidth, float displayHeight) : 
	Star(pX, pY, 0, 0)
{
	this->displayWidth = displayWidth;
	this->displayHeight = displayHeight;
	sprite = nullptr;
	srand(time(NULL));
}

StarBlue::~StarBlue(){
	if(sprite)
		delete sprite;
}

void StarBlue::setupParameters(){
	setWidth(sprite->getWidth());
	setHeight(sprite->getHeight());

	emptySpaceScale = 3.0f;
	emptySpaceWidth = getWidth() * emptySpaceScale;
	emptySpaceHeight = getHeight() * emptySpaceScale;
	usableWidth = displayWidth - getWidth();
	usableHeight = displayHeight - getHeight();
}

void StarBlue::attachBitmap(ALLEGRO_BITMAP* starBitmap){
	if(sprite)
		delete sprite;
	sprite = new Sprite(starBitmap);
	setupParameters();
}

void StarBlue::generateNewPositionBasedOnPlayerPosition(Entity player){
	while(!validateNewPosition(player))
		generateNewPosition();
};

void StarBlue::generateNewPosition(){
	float newPositionX = rand() % usableWidth + getWidth() / 2.0f;
	float newPositionY = rand() % usableHeight + getHeight() / 2.0f;
	this->setPosition(newPositionX, newPositionY);
}

bool StarBlue::validateNewPosition(Entity e){
	if(this->getPositionX() + this->emptySpaceWidth / 2.0f > e.getPositionX() - e.getWidth() / 2.0f &&
		this->getPositionX() - this->emptySpaceWidth / 2.0f < e.getPositionX() + e.getWidth() / 2.0f &&
		  this->getPositionY() - this->emptySpaceHeight / 2.0f < e.getPositionY() + e.getHeight() / 2.0f &&
			this->getPositionY() + this->emptySpaceHeight / 2.0f > e.getPositionY() - e.getHeight() / 2.0f)
			return false;
	 return true;
}

void StarBlue::setPosition(float pX, float pY){
	sprite->setPosition(pX, pY);
	Entity::setPosition(pX, pY);
}

void StarBlue::draw(){
	sprite->draw();
};

