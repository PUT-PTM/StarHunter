#include "Entity.h"

Entity::Entity(float pX, float pY, float pWidth, float pHeight){
	positionX = pX;
	positionY = pY;
	width = pWidth;
	height = pHeight;
}

bool Entity::collidesWith(Entity e){
	if(this->getPositionX() + this->getWidth() / 2.0f > e.getPositionX() - e.getWidth() / 2.0f ||
		this->getPositionX() - this->getWidth() / 2.0f < e.getPositionX() + e.getWidth() / 2.0f)
		if(this->getPositionY() - this->getHeight() / 2.0f < e.getPositionY() + e.getHeight() / 2.0f ||
			this->getPositionY() + this->getHeight() / 2.0f > e.getPositionY() - e.getHeight() / 2.0f)
			return true;
	return false;
}

void Entity::setPosition(float pX, float pY){
	positionX = pX;
	positionY = pY;
}

float Entity::getPositionX(){
	return positionX;
}

float Entity::getPositionY(){
	return positionY;
}

void Entity::setWidth(float pWidth){
	width = pWidth;
}

void Entity::setHeight(float pHeight){
	height = pHeight;
}

float Entity::getWidth(){
	return width;
}

float Entity::getHeight(){
	return height;
}

