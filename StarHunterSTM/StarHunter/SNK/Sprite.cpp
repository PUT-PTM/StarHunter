#include "Sprite.h"

Sprite::Sprite(std::string path, float posX, float posY){
	bitmap = al_load_bitmap(path.c_str());
	if(!bitmap)
		throw new MyException("Could not load bitmap.");

	this->positionX = posX;
	this->positionY = posY;
	this->scaleDirty = false;
}

Sprite::Sprite(ALLEGRO_BITMAP *bitmap, float posX, float posY){
	this->bitmap = bitmap;
	this->positionX = posX;
	this->positionY = posY;
	this->scaleDirty = false;
}

Sprite::Sprite(const Sprite &s){
	bitmap = al_clone_bitmap(s.bitmap);
	positionX = s.positionX;
	positionY = s.positionY;
	scaleDirty = s.scaleDirty;
	scale = s.scale;
}

Sprite::~Sprite(){
	if(bitmap){
		al_destroy_bitmap(bitmap);
		bitmap = 0;
	}
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
	return positionX;
}

float Sprite::getPositionY(){
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
		positionX - getWidth() / 2.0f, positionY - getHeight() / 2.0f,
		0);
	}
	else{
		float scaledWidth = getWidth() * scale;
		float scaleHeight = getHeight() * scale;
		al_draw_scaled_bitmap(
		bitmap,
		0, 0,
		getWidth(), getHeight(),
		positionX - scaledWidth /2.0f, positionY - scaleHeight / 2.0f,
		scaledWidth, scaleHeight, 
		0);
	}
}

bool Sprite::collidesWith(Sprite s){
	return false;
}

ALLEGRO_BITMAP* Sprite::getAllegroBitmap(){
	return bitmap;
}