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
	float x = getRegionWidth();
	float y = getRegionHeight();
	al_draw_bitmap_region(
		bitmap,
		column * getRegionWidth(),
		row * getRegionHeight(),
		getRegionWidth(),
		getRegionHeight(),
		positionX - getRegionWidth() / 2.0f,
		positionY - getRegionHeight() / 2.0f,
		0);
}

float TiledSprite::getRegionWidth(){
	return regionWidth;
}

float TiledSprite::getRegionHeight(){
	return regionHeight;
}

int TiledSprite::getColumnsCount(){
	return columnsCount;
}

int TiledSprite::getRowsCount(){
	return rowsCount;
}

