#pragma once

#include <time.h>
#include <vector>
#include <thread>
#include "Sprite.h"
#include "Display.h"
#include "InputManager.h"
#include "MyException.h"

class SpaceBackground{
private:
	Display *display;
	std::vector<Sprite *> tiles;
	Sprite *tileCenter;
	InputManager::MoveEventType direction;
	float displayWidth, displayHeight;
	float speed;

	void initializeTile();
	void setupSprites();
	void drawStars();
	float randScale();
	void moveTiles(float distanceX, float distanceY);
	void keepInBounds();
public:
	SpaceBackground(Display *display);
	~SpaceBackground();

	void draw();
	void move();
	void changeDirection(InputManager::MoveEventType newDirection);
};