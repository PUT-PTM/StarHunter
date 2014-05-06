#pragma once
#include "Entity.h"
#include "TiledSprite.h"
#include "InputManager.h"

class Player : public Entity{
private:
	TiledSprite* tiledSprite;
	const int amountOfRegionsVertically;
	const int amountOfRegionsHorizontally;
	InputManager::MoveEventType direction;
	const int startingRegionY;
	const int startingRegionX;
	float displayWidth, displayHeight;
	int regionNumberX, regionNumberY;
	float distance;
	bool animation;

	void keepInBounds();
public:
	Player(float pX, float pY, float displayWidth, float displayHeight);
	~Player();

	void move();
	void move(float pDistanceX, float pDistanceY);
	void attachBitmap(ALLEGRO_BITMAP* playerSheet);
	void changeDirection(InputManager::MoveEventType newDirection);
	void setDistancePerFrame(float pDistance);
	void setPosition(float pDistanceX, float pDistanceY);
	void animate();
	void draw();
};