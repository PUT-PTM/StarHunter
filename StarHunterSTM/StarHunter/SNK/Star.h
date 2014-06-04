#pragma once
#include <iostream>
#include <time.h>

#include "Display.h"
#include "Entity.h"
#include "Sprite.h"
#include "IAffectingObject.h"

class Star : public Entity{
protected:	
	Sprite* sprite;
	int usableWidth, usableHeight;
	float displayWidth, displayHeight;
	float emptySpaceScale, emptySpaceWidth, emptySpaceHeight;
	
	IAffectingObject *affectingObject;
	
	bool validateNewPosition(Entity e);
public:
	Star(float pX, float pY, float displayWidth, float displayHeight);
	virtual ~Star();
	void generateNewPositionBasedOnPlayerPosition(Entity player);
	void generateNewPosition();
	void setPosition(float pX, float pY);
	void attachSprite(Sprite* starBitmap);
	void attachEffect(IAffectingObject *affectingObject);
	void affect(Player *player);
	void setupParameters();	
	void draw();
};