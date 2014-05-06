#pragma once
#include <iostream>
#include <time.h>

#include "Display.h"
#include "Entity.h"
#include "Sprite.h"

class Star : public Entity{
protected:	
	Sprite sprite;
	int usableWidth, usableHeight;
	float emptySpaceScale, emptySpaceWidth, emptySpaceHeight;
	void generateNewPosition();
	bool validateNewPosition(Entity e);
public:
	Star(float pX, float pY, float displayWidth, float displayHeight);
	void generateNewPositionBasedOnPlayerPosition(Entity player);
	void setPosition(float pX, float pY);
	void draw();
};

