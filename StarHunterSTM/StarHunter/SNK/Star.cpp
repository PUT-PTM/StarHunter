#include "Star.h"

Star::Star(float pX, float pY, float displayWidth, float displayHeight) : 
	Entity(pX, pY, 0, 0)
{
	this->displayWidth = displayWidth;
	this->displayHeight = displayHeight;
	sprite = nullptr;
	srand(time(NULL));
}

Star::~Star(){
	if(sprite)
		delete sprite;
}

void Star::setupParameters(){
	setWidth(sprite->getWidth());
	setHeight(sprite->getHeight());

	emptySpaceScale = 3.0f;
	emptySpaceWidth = getWidth() * emptySpaceScale;
	emptySpaceHeight = getHeight() * emptySpaceScale;
	usableWidth = displayWidth - getWidth();
	usableHeight = displayHeight - getHeight();
}

void Star::attachBitmap(ALLEGRO_BITMAP* starBitmap){
	if(sprite)
		delete sprite;
	sprite = new Sprite(starBitmap);
	setupParameters();
}

void Star::generateNewPositionBasedOnPlayerPosition(Entity player){
	while(!validateNewPosition(player))
		generateNewPosition();
};

void Star::generateNewPosition(){
	float newPositionX = rand() % usableWidth + getWidth() / 2.0f;
	float newPositionY = rand() % usableHeight + getHeight() / 2.0f;
	this->setPosition(newPositionX, newPositionY);
}

bool Star::validateNewPosition(Entity e){
	if(this->getPositionX() + this->emptySpaceWidth / 2.0f > e.getPositionX() - e.getWidth() / 2.0f &&
		this->getPositionX() - this->emptySpaceWidth / 2.0f < e.getPositionX() + e.getWidth() / 2.0f &&
		  this->getPositionY() - this->emptySpaceHeight / 2.0f < e.getPositionY() + e.getHeight() / 2.0f &&
			this->getPositionY() + this->emptySpaceHeight / 2.0f > e.getPositionY() - e.getHeight() / 2.0f)
			return false;
	 return true;
}

void Star::setPosition(float pX, float pY){
	sprite->setPosition(pX, pY);
	Entity::setPosition(pX, pY);
}

void Star::draw(){
	sprite->draw();
};
