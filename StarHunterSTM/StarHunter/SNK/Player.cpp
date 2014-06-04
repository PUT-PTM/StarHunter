#include "Player.h"

Player::Player(float pX, float pY, float displayWidth, float displayHeight) :
	Entity(pX, pY, 0, 0),
	amountOfRegionsHorizontally(3),
	amountOfRegionsVertically(4),
	startingRegionX(0),
	startingRegionY(1),
	maximalDistancePerFrame(6.5f),
	minimalDistancePerFrame(2.5f)
{
	this->setWidth(50); // Real player width
	this->setHeight(60); // Real player height
	
	this->displayWidth = displayWidth;
	this->displayHeight = displayHeight;
	distance = 2.5f;
	animation = false;
	direction = InputManager::MoveEventType::NONE;
	regionNumberX = startingRegionX;
	regionNumberY = startingRegionY;
	tiledSprite = nullptr;

	directionInversed = false;
}

Player::~Player(){
	if(tiledSprite){
		delete tiledSprite;
		tiledSprite = nullptr;
	}
}

void Player::attachBitmap(ALLEGRO_BITMAP* playerSheet){
	if(tiledSprite)
		delete tiledSprite;
	tiledSprite = new TiledSprite(playerSheet, amountOfRegionsHorizontally, amountOfRegionsVertically);
	tiledSprite->setPosition(this->getPositionX(), this->getPositionY());
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

	keepInBounds();
}

void Player::keepInBounds(){
	if(this->getPositionX() < 0 - this->getWidth() / 2.0f)
		this->setPosition(
		displayWidth,
		this->getPositionY());
	else if(this->getPositionX() > displayWidth + this->getWidth() / 2.0f)
		this->setPosition(
		0,
		this->getPositionY());
	else if(this->getPositionY() < 0 - this->getHeight() / 2.0f)
		this->setPosition(
		this->getPositionX(),
		displayHeight);
	else if(this->getPositionY() > displayHeight + this->getHeight() / 2.0f)
		this->setPosition(
		this->getPositionX(),
		0);
}

void Player::multiplyDistancePerFrameBy(float value)
{
	lock.acquire();
	float newDistance = distance * value;
	if(newDistance > maximalDistancePerFrame)
		newDistance = maximalDistancePerFrame;
	else if(newDistance < minimalDistancePerFrame)
		newDistance = minimalDistancePerFrame;
	distance = newDistance;
	lock.release();
}

bool Player::isCurrentDistancPerFrameMaximal()
{
	return (distance >= maximalDistancePerFrame);
}

void Player::setPosition(float pX, float pY){
	Entity::setPosition(pX, pY);
	tiledSprite->setPosition(this->getPositionX(), this->getPositionY());
}

void Player::changeDirection(InputManager::MoveEventType newDirection){
	if(directionInversed)
		inverse(newDirection);
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

void Player::inverse(InputManager::MoveEventType &newDirection)
{
		switch(newDirection){
	case InputManager::MoveEventType::DOWN:
		newDirection = InputManager::MoveEventType::UP;
		break;
	case InputManager::MoveEventType::UP:
		newDirection = InputManager::MoveEventType::DOWN;
		break;
	case InputManager::MoveEventType::RIGHT:
		newDirection = InputManager::MoveEventType::LEFT;
		break;
	case InputManager::MoveEventType::LEFT:
		newDirection = InputManager::MoveEventType::RIGHT;
		break;
	}
}

void Player::inverseDirections(bool flag)
{
	directionInversed = flag;
}

bool Player::isDirectionsInversed()
{
	return directionInversed;
}

InputManager::MoveEventType Player::getCurrentDirection()
{
	return direction;
}

void Player::animate(){
	if(animation){
		regionNumberY++;
		if(regionNumberY >= tiledSprite->getColumnsCount())
			regionNumberY = 0;
	}
}

void Player::draw(){
	tiledSprite->drawRegion(regionNumberX, regionNumberY);
}