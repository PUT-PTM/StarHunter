#include "SpaceBackground.h"

SpaceBackground::SpaceBackground(Display *display){
	tileBitmap = 0;
	this->display = display;
	speed =  1.0f;
	direction = InputManager::MoveEventType::NONE;
	initializeTile();
}

SpaceBackground::~SpaceBackground(){
	al_destroy_bitmap(tileBitmap);
}

void SpaceBackground::initializeTile(){
	tileBitmap = al_create_bitmap(display->getWidth(), display->getHeight());

	drawStars();
	setupPositions();
}

void SpaceBackground::drawStars(){
	ALLEGRO_BITMAP* star = al_load_bitmap("assets/gfx/backgroundStar.png");
	if(!star)
		throw new MyException("Could not load 'backgroundStar.png'");
	float starWidth = al_get_bitmap_width(star);
	float starHeight = al_get_bitmap_height(star);


	srand(time(NULL));
	int seedSize = (rand() % 100) + 200;
	al_set_target_bitmap(tileBitmap);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	for(int i = 0; i < seedSize; i++){
		float scale = randScale();
		float scaledWidth = starWidth * scale;
		float scaledHeight = starHeight * scale;
		int posX = (rand() % (int)(display->getWidth() - scaledWidth)) + scaledWidth / 2.0f;
		int posY = (rand() % (int)(display->getHeight() - scaledHeight)) + scaledHeight / 2.0f;

		al_draw_scaled_bitmap(
			star,
			0, 0,
			starWidth, starHeight,
			posX - scaledWidth / 2.0f,
			posY - scaledHeight / 2.0f,
			scaledWidth, scaledHeight,
			0);
	}
	al_set_target_backbuffer(display->getAllegroDisplay());
	al_destroy_bitmap(star);	
}

float SpaceBackground::randScale(){
	int i = rand() % 100;
	if(i < 85){
		return 0.2f;
	}
	else if(i < 95)
		return i / 300.0f;
	else
		return i / 250.0f;
}

void SpaceBackground::setupPositions(){

	tilePositions.push_back( // CENTER TILE
		std::pair<float, float> (
		display->getWidth() / 2.0f,
		display->getHeight() / 2.0f));

	tilePositions.push_back( // UP TILE
		std::pair<float, float> (
		display->getWidth() / 2.0f,
		display->getHeight() / 2.0f - display->getHeight()));

	tilePositions.push_back( // LEFT TILE
		std::pair<float, float> (
		display->getWidth() / 2.0f - display->getWidth(),
		display->getHeight() / 2.0f));

	tilePositions.push_back( // LEFT UP TILE
		std::pair<float, float> (
		display->getWidth() / 2.0f - display->getWidth(),
		display->getHeight() / 2.0f - display->getHeight()));

	tilePositions.push_back( // LEFT DOWN TILE
		std::pair<float, float> (
		display->getWidth() / 2.0f - display->getWidth(),
		display->getHeight() / 2.0f + display->getHeight()));

	tilePositions.push_back( // DOWN TILE
		std::pair<float, float> (
		display->getWidth() / 2.0f,
		display->getHeight() / 2.0f + display->getHeight()));

	tilePositions.push_back( // RIGHT TILE
		std::pair<float, float> (
		display->getWidth() / 2.0f + display->getWidth(),
		display->getHeight() / 2.0f));

	tilePositions.push_back( // RIGHT DOWN TILE
		std::pair<float, float> (
		display->getWidth() / 2.0f + display->getWidth(),
		display->getHeight() / 2.0f + display->getHeight()));

	tilePositions.push_back( // RIGHT UP TILE
		std::pair<float, float> (
		display->getWidth() / 2.0f + display->getWidth(),
		display->getHeight() / 2.0f - display->getHeight()));
}

void SpaceBackground::changeDirection(InputManager::MoveEventType newDirection){
	direction = newDirection;
}

void SpaceBackground::move(){
	switch(direction){
	case InputManager::MoveEventType::LEFT:
		moveTiles(speed, 0);
		break;
	case InputManager::MoveEventType::RIGHT:
		moveTiles(-speed, 0);
		break;
	case InputManager::MoveEventType::UP:
		moveTiles(0, speed);
		break;
	case InputManager::MoveEventType::DOWN:
		moveTiles(0, -speed);
		break;
	}

	keepInBounds();
}

void SpaceBackground::moveTiles(float distanceX, float distanceY){
	for(std::pair<float, float> &position : tilePositions){
		position.first += distanceX;
		position.second += distanceY;
	}
}

void SpaceBackground::keepInBounds(){
	float width, height;
	width = display->getWidth();
	height = display->getHeight();

	if(getCenterPosition().first < 0)
		moveTiles(width, 0);
	else if(getCenterPosition().first > width / 2.0f)
		moveTiles(-width, 0);
	if(getCenterPosition().second < 0)
		moveTiles(0, height);
	else if(getCenterPosition().second > height / 2.0f)
		moveTiles(0, -height);
}

std::pair<float, float> &SpaceBackground::getCenterPosition(){
	return tilePositions.front();
}

void SpaceBackground::draw(){
	for(std::pair<float, float> position : tilePositions)
		al_draw_bitmap(tileBitmap, position.first, position.second, 0);
}

