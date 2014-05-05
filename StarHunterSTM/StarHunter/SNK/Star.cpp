#include "Star.h"

Star::Star(float Px, float Py) : Entity(Px, Py, 0, 0)
{
	starmap = al_load_bitmap("assets/gfx/star.png");
	if(!starmap)
		throw new MyException("Could not load starmap.");

	this->positionX = Px;
	this->positionY = Py;
	
};


// DO DOPRACOWANIA
void Star::write(Entity e){
//	std::cout << e.getPositionX;
}
;

void Star::generateNewPosition(Entity e){
srand(time(NULL));

/*
do{
	positionX = rand()%760;
}while(((e.getPositionX() - this->getPositionX() + this->getWidth()) < -100) &&
	((e.getPositionX() + e.getWidth() - this->getPositionX()) > 100));


do{
positionY = rand()%560;
}while(((e.getPositionY() - this->getPositionY() + this->getHeight()) < -100) &&
	((e.getPositionY() + e.getHeight() - this->getPositionY()) > 100));
*/
while((e.getPositionX() + 100) > this->positionX && (e.getPositionX() - 100) < this->positionX)
this->positionX = rand()%560;
while((e.getPositionY() + 100) > this->positionY && (e.getPositionY() - 100) < this->positionY)
this->positionY = rand()%560;
};

void Star::draw(){
	al_draw_bitmap(starmap,  getPositionX(), getPositionY(), 0);
};


float Star::widthStar(){
	return al_get_bitmap_width(starmap);

};

float Star::heightStar(){
	return height = al_get_bitmap_height(starmap);
};

Star::~Star(){
	al_destroy_bitmap(starmap);
};
/*
bool Star::collidesWith(Entity e){
	if(this->getPositionX() + this->getWidth() / 2.0f > e.getPositionX() - e.getWidth() / 2.0f ||
		this->getPositionX() - this->getWidth() / 2.0f < e.getPositionX() + e.getWidth() / 2.0f)
		if(this->getPositionY() - this->getHeight() / 2.0f < e.getPositionY() + e.getHeight() / 2.0f ||
			this->getPositionY() + this->getHeight() / 2.0f > e.getPositionY() - e.getHeight() / 2.0f)
			return true;
	return false;
	}*/
