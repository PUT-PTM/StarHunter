#pragma once
#include <iostream>
#include <time.h>

#include "Display.h"
#include "Star.h"
#include "Sprite.h"
#include "GameTimer.h"

class StarBlue : public Star{
protected:	
	Sprite* sprite;
	int usableWidth, usableHeight;
	float displayWidth, displayHeight;
	float emptySpaceScale, emptySpaceWidth, emptySpaceHeight;

	void setupParameters();	
	bool validateNewPosition(Entity e);
public:
	StarBlue(float pX, float pY, float displayWidth, float displayHeight);
	~StarBlue();
	void generateNewPositionBasedOnPlayerPosition(Entity player);
	void generateNewPosition();
	void setPosition(float pX, float pY);
	void attachBitmap(ALLEGRO_BITMAP* starBitmap);
	void draw();
	//void affect(GameTimer timer);
};

