#include "SpaceBackground.h"

SpaceBackground::SpaceBackground(Display *display){
	for(Sprite *s : tiles)
		s = 0;
	this->display = display;
	speed =  1.0f;
	direction = InputManager::MoveEventType::NONE;
	initializeTile();
}

SpaceBackground::~SpaceBackground(){
	for(Sprite *s : tiles){
		delete s;
	}
}

void SpaceBackground::initializeTile(){
	ALLEGRO_BITMAP* tileBitmap = al_create_bitmap(display->getWidth(), display->getHeight());
	tileCenter = new Sprite(tileBitmap, display->getWidth() / 2.0f, display->getHeight() / 2.0f);
	al_set_target_bitmap(tileBitmap);
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_set_target_backbuffer(display->getAllegroDisplay());

	drawStars();
	setupSprites();
}

void SpaceBackground::setupSprites(){
	Sprite *tileUp = new Sprite(*tileCenter);
	tileUp->setPosition(
		display->getWidth() / 2.0f,
		display->getHeight() / 2.0f - display->getHeight());

	Sprite *tileLeft = new Sprite(*tileCenter);
	tileLeft->setPosition(
		display->getWidth() / 2.0f - display->getWidth(),
		display->getHeight() / 2.0f);

	Sprite *tileLeftUp = new Sprite(*tileCenter);
	tileLeftUp->setPosition(
		display->getWidth() / 2.0f - display->getWidth(),
		display->getHeight() / 2.0f - display->getHeight());

	Sprite *tileLeftDown = new Sprite(*tileCenter);
	tileLeftDown->setPosition(
		display->getWidth() / 2.0f - display->getWidth(),
		display->getHeight() / 2.0f + display->getHeight());

	Sprite *tileDown = new Sprite(*tileCenter);
	tileDown->setPosition(
		display->getWidth() / 2.0f,
		display->getHeight() / 2.0f + display->getHeight());

	Sprite *tileRight = new Sprite(*tileCenter);
	tileRight->setPosition(
		display->getWidth() / 2.0f + display->getWidth(),
		display->getHeight() / 2.0f);

	Sprite *tileRightDown = new Sprite(*tileCenter);
	tileRightDown->setPosition(
		display->getWidth() / 2.0f + display->getWidth(),
		display->getHeight() / 2.0f + display->getHeight());

	Sprite *tileRightUp = new Sprite(*tileCenter);
	tileRightUp->setPosition(
		display->getWidth() / 2.0f + display->getWidth(),
		display->getHeight() / 2.0f - display->getHeight());


	tiles.push_back(tileUp);
	tiles.push_back(tileLeft);
	tiles.push_back(tileLeftUp);
	tiles.push_back(tileLeftDown);
	tiles.push_back(tileCenter);
	tiles.push_back(tileDown);
	tiles.push_back(tileRight);
	tiles.push_back(tileRightDown);
	tiles.push_back(tileRightUp);
}

void SpaceBackground::drawStars(){
	ALLEGRO_BITMAP* star = al_load_bitmap("assets/gfx/backgroundStar.png");
	if(!star)
		throw new MyException("Could not load 'backgroundStar.png'");
	float starWidth = al_get_bitmap_width(star);
	float starHeight = al_get_bitmap_height(star);


	srand(time(NULL));
	int seedSize = (rand() % 100) + 200;
	al_set_target_bitmap(tileCenter->getAllegroBitmap());
	for(int i = 0; i < seedSize; i++){
		float scale = randScale();
		float scaledWidth = starWidth * scale;
		float scaledHeight = starHeight * scale;
		int posX = (rand() % (int)(tileCenter->getWidth() - scaledWidth)) + scaledWidth / 2.0f;
		int posY = (rand() % (int)(tileCenter->getHeight() - scaledHeight)) + scaledHeight / 2.0f;

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

void SpaceBackground::changeDirection(InputManager::MoveEventType newDirection){
	direction = newDirection;
}

void SpaceBackground::move(){
	switch(direction){
	case InputManager::MoveEventType::LEFT:
		moveTiles(-speed, 0);
		break;
	case InputManager::MoveEventType::RIGHT:
		moveTiles(speed, 0);
		break;
	case InputManager::MoveEventType::UP:
		moveTiles(0, -speed);
		break;
	case InputManager::MoveEventType::DOWN:
		moveTiles(0, speed);
		break;
	}

	keepInBounds();
}

void SpaceBackground::moveTiles(float distanceX, float distanceY){
	for(Sprite *s : tiles)
		s->setPosition(
		s->getPositionX() - distanceX,
		s->getPositionY() - distanceY);
}

void SpaceBackground::keepInBounds(){
	if(tileCenter->getPositionX() < -tileCenter->getWidth() / 2.0f)
		moveTiles(-tileCenter->getWidth(), 0);
	else if(tileCenter->getPositionX() > display->getWidth() + tileCenter->getWidth() / 2.0f)
		moveTiles(tileCenter->getWidth(), 0);
	else if(tileCenter->getPositionY() < -display->getHeight() / 2.0f)
		moveTiles(0, display->getHeight());
	else if(tileCenter->getPositionY() > display->getHeight() + display->getHeight() / 2.0f)
		moveTiles(0, display->getHeight());
}

void SpaceBackground::draw(){
	for(Sprite *s : tiles)
		s->draw();
}

