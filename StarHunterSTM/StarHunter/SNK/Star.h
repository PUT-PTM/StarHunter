#pragma once
#include <iostream>
#include <time.h>

#include "Display.h"
#include "Entity.h"
#include "Sprite.h"

class Star : public Entity{
protected:	
	Sprite* sprite;
	int usableWidth, usableHeight;
	float displayWidth, displayHeight;
	float emptySpaceScale, emptySpaceWidth, emptySpaceHeight;

	void setupParameters();	
	bool validateNewPosition(Entity e);
public:
	Star(float pX, float pY, float displayWidth, float displayHeight);
	~Star();
	void generateNewPositionBasedOnPlayerPosition(Entity player);
	void generateNewPosition();
	void setPosition(float pX, float pY);
	void attachBitmap(ALLEGRO_BITMAP* starBitmap);
	void draw();
};

