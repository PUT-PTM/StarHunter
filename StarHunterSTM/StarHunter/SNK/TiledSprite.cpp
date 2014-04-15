#include "TiledSprite.h"

TiledSprite::TiledSprite(
	std::string texturePath,
	int columnsCount,
	int rowsCount,
	float positionX,
	float positionY 
	) :
Sprite(texturePath, positionX, positionY)
{
	this->rowsCount = rowsCount;
	this->columnsCount = columnsCount;
	countRegionSize();
}

void TiledSprite::countRegionSize(){
	regionWidth = getWidth() / columnsCount;
	regionHeight = getHeight() / rowsCount;
}

void TiledSprite::drawRegion(int row, int column){
	al_draw_bitmap_region(
		bitmap,
		column * getWidth(),
		row * getHeight(),
		getWidth(),
		getHeight(),
		positionX,
		positionY,
		0);
}

float TiledSprite::getTextureWidth(){
	return al_get_bitmap_width(bitmap);
}

float TiledSprite::getTextureHeight(){
	return al_get_bitmap_width(bitmap);
}

float TiledSprite::getWidth(){
	return regionWidth;
}

float TiledSprite::getHeight(){
	return regionHeight;
}

int TiledSprite::getColumnsCount(){
	return columnsCount;
}

int TiledSprite::getRowsCount(){
	return rowsCount;
}

