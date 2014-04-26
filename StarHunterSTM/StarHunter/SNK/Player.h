#pragma once
#include "Entity.h"
#include "TiledSprite.h"
#include "InputManager.h"

class Player : Entity{
private:
	TiledSprite tiledSprite;
	InputManager::MoveEventType direction;
	const int startingRegionY;
	const int startingRegionX;
	int regionNumberX, regionNumberY;
	float distance;
	bool animation;

public:
	Player(float pX, float pY);

	void move();
	void move(float pDistanceX, float pDistanceY);
	void changeDirection(InputManager::MoveEventType newDirection);
	void setSpeed(float pDistance);
	void setPosition(float pDistanceX, float pDistanceY);
	void animate();
	void draw();
};