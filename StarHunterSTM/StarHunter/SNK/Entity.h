#pragma once

class Entity{
protected:
	float width, height;
	float positionX, positionY;
public:
	Entity(float pX, float pY, float width, float height);

	bool collidesWith(Entity e);
};