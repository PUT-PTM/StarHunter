#include "Player.h"

Player::Player(float pX, float pY) :
	Entity(pX, pY, 0, 0),
	tiledSprite("assets/gfx/playerSheet.png", 3, 4),
	startingRegionX(0),
	startingRegionY(1)
{
	this->setWidth(tiledSprite.getRegionWidth());
	this->setHeight(tiledSprite.getRegionHeight());

	distance = 3.0f;
	animation = false;
	direction = InputManager::MoveEventType::NONE;
	regionNumberX = startingRegionX;
	regionNumberY = startingRegionY;
	tiledSprite.setPosition(this->getPositionX(), this->getPositionY());
}

void Player::move(){
	switch(direction){
	case InputManager::MoveEventType::DOWN:
		move(0,distance);
		break;
	case InputManager::MoveEventType::UP:
		move(0, -distance);
		break;
	case InputManager::MoveEventType::RIGHT:
		move(distance, 0);
		break;
	case InputManager::MoveEventType::LEFT:
		move(-distance, 0);
		break;
	}
}

void Player::move(float pDistanceX, float pDistanceY){
	this->setPosition(
		this->getPositionX() + pDistanceX,
		this->getPositionY() + pDistanceY
		);
}

void Player::setSpeed(float pDistance){
	distance = pDistance;
}

void Player::setPosition(float pX, float pY){
	Entity::setPosition(pX, pY);
	tiledSprite.setPosition(this->getPositionX(), this->getPositionY());
}

void Player::changeDirection(InputManager::MoveEventType newDirection){
	if(direction != newDirection){
		regionNumberY = startingRegionY;
		if(newDirection != InputManager::MoveEventType::NONE){
			animation = true;
			regionNumberX = newDirection;
		}
		else{
			animation = false;
			regionNumberX = 0;
		}
		direction = newDirection;
	}	
}

void Player::animate(){
	if(animation){
		regionNumberY++;
		if(regionNumberY >= tiledSprite.getColumnsCount())
			regionNumberY = 0;
	}
}

void Player::draw(){
	tiledSprite.drawRegion(regionNumberX, regionNumberY);
}