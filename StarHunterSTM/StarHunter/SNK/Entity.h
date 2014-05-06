#pragma once

class Entity{
protected:
	float width, height;
	float positionX, positionY;

	float oldPosX, oldPosY;
public:
	Entity(float pX, float pY, float pWidth, float pHeight);

	bool collidesWith(Entity e);
	virtual void setPosition(float pX, float pY);
	float getPositionX();
	float getPositionY();
	void setWidth(float pWidth);
	void setHeight(float pHeight);
	float getWidth();
	float getHeight();
};