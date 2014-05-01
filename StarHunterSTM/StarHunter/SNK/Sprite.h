#pragma once
#include <string>

#include <allegro5\allegro.h>
#include <allegro5\\allegro_image.h>

#include "MyException.h"

class Sprite{
protected:
	ALLEGRO_BITMAP* bitmap;
	float positionX, positionY, scale;
	bool scaleDirty;

	void loadBitmap();
public:
	// throws MyException
	Sprite(std::string texturePath, float positionX = 0, float positionY = 0);
	Sprite(ALLEGRO_BITMAP* bitmap, float positionX = 0, float positionY = 0);
	Sprite(const Sprite& s);

	~Sprite();

	void draw();
	void setPosition(float positionX, float positionY);
	float getPositionX();
	float getPositionY();
	void setScale(float scale);
	float getWidth();
	float getHeight();
	ALLEGRO_BITMAP* getAllegroBitmap();
	virtual bool collidesWith(Sprite);
};