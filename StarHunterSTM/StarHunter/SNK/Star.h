#pragma once
#include "Entity.h"
#include "TiledSprite.h"
#include "Player.h"
#include <time.h>
#include <allegro5\\allegro_image.h>
#include <iostream>


class Star : public Entity{

	//generateNewPosition(Entity player);*/

protected:
	
		ALLEGRO_BITMAP* starmap;
		
		float heightStar();
		float widthStar();
public:
	Star(float Px, float Py);
	void generateNewPosition(Entity e);
	//bool collidesWith(Entity e);
	void draw();
	~Star();
	void write(Entity e);


};

