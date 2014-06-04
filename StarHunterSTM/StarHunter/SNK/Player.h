#pragma once
#include "Entity.h"
#include "TiledSprite.h"
#include "InputManager.h"
#include "Lock.h"

class Player : public Entity{
private:
	TiledSprite* tiledSprite;
	const int amountOfRegionsVertically;
	const int amountOfRegionsHorizontally;
	const int maximalDistancePerFrame;
	const int minimalDistancePerFrame;
	InputManager::MoveEventType direction;
	const int startingRegionY;
	const int startingRegionX;
	float displayWidth, displayHeight;
	int regionNumberX, regionNumberY;
	float distance;
	bool animation;

	bool directionInversed;

	Lock lock;

	void keepInBounds();
	void inverse(InputManager::MoveEventType &newDirection);
public:
	Player(float pX, float pY, float displayWidth, float displayHeight);
	~Player();

	void move();
	void move(float pDistanceX, float pDistanceY);
	void attachBitmap(ALLEGRO_BITMAP* playerSheet);
	void changeDirection(InputManager::MoveEventType newDirection);
	void multiplyDistancePerFrameBy(float value);
	bool isCurrentDistancPerFrameMaximal();
	InputManager::MoveEventType getCurrentDirection();
	bool isDirectionsInversed();
	void inverseDirections(bool flag);

	void setPosition(float pDistanceX, float pDistanceY);
	void animate();
	void draw();
};