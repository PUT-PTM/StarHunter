#include "Sprite.h"

Sprite::Sprite(std::string path, float posX, float posY){
	bitmap = al_load_bitmap(path.c_str());
	if(!bitmap)
		throw new MyException("Could not load bitmap.");

	this->positionX = posX;
	this->positionY = posY;
	this->scaleDirty = false;
}

Sprite::~Sprite(){
	if(bitmap)
		al_destroy_bitmap(bitmap);
}

void Sprite::setPosition(float posX, float posY){
	positionX = posX;
	positionY = posY;
}

void Sprite::setScale(float sc){
	if(sc < 0)
		throw new MyException("Scale cannot be less than zero.");
	scale = sc;
	if(scale != 1.0f)
		scaleDirty = true;
	else
		scaleDirty = false;
}

float Sprite::getPositionX(){
	if(positionX > 810) positionX = -10;
	else if(positionX < -10) positionX = 810;
	return positionX;
}

float Sprite::getPositionY(){
	if(positionY >610) positionY = -10;
	else if(positionY < -10) positionY = 610;
	return positionY;
}

float Sprite::getWidth(){
	return al_get_bitmap_width(bitmap);
}

float Sprite::getHeight(){
	return al_get_bitmap_height(bitmap);
}

void Sprite::draw(){
	bool t = scaleDirty;
	if(!scaleDirty){
		al_draw_bitmap(
		bitmap,
		positionX, positionY,
		0);
	}
	else{
		al_draw_scaled_bitmap(
		bitmap,
		0, 0,
		getWidth(), getHeight(),
		positionX, positionY,
		getWidth() * scale, getHeight() * scale, 
		0);
	}
}

bool Sprite::collidesWith(Sprite s){
	return false;
}