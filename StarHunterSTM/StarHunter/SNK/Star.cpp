#include "Star.h"

Star::Star(float pX, float pY, float displayWidth, float displayHeight) : 
	Entity(pX, pY, 0, 0),
	sprite("assets/gfx/star.png")
{
	setWidth(sprite.getWidth());
	setHeight(sprite.getHeight());

	emptySpaceScale = 3.0f;
	emptySpaceWidth = getWidth() * emptySpaceScale;
	emptySpaceHeight = getHeight() * emptySpaceScale;
	usableWidth = displayWidth - getWidth();
	usableHeight = displayHeight - getHeight();

	srand(time(NULL));	
	generateNewPosition();
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
	sprite.setPosition(pX, pY);
	Entity::setPosition(pX, pY);
}

void Star::draw(){
	sprite.draw();
};
