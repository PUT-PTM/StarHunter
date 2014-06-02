#pragma once
#include <iostream>
#include <time.h>

#include "Display.h"
#include "Star.h"
#include "Sprite.h"
#include "Entity.h"

class StarYellow : public Star{
protected:	
	Sprite* sprite;
	int usableWidth, usableHeight;
	float displayWidth, displayHeight;
	float emptySpaceScale, emptySpaceWidth, emptySpaceHeight;

	void setupParameters();	
	bool validateNewPosition(Entity e);
public:
	StarYellow(float pX, float pY, float displayWidth, float displayHeight);
	~StarYellow();
	void generateNewPositionBasedOnPlayerPosition(Entity player);
	void generateNewPosition();
	void setPosition(float pX, float pY);
	void attachBitmap(ALLEGRO_BITMAP* starBitmap);
	void draw();
	//int affect(Entity player,int score);
};

