#pragma once

#include "Sprite.h"

class TiledSprite : public Sprite{
private:
	float regionWidth, regionHeight;
	int rowsCount, columnsCount;

	void countRegionSize();
public:
	TiledSprite(
		std::string texturePath,
		int columnsCount,
		int rowsCount,
		float positionX = 0.0,
		float positionY = 0.0
		);

	void drawRegion(int row, int column);
	float getRegionWidth();
	float getRegionHeight();
	int getColumnsCount();
	int getRowsCount();
};