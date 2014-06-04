#include "Game.h"

Game::Game() :
	display(800, 600),
	inputManager(display),
	player(
	display.getWidth() / 2.0f, display.getHeight() / 2.0f,
	display.getWidth(), display.getHeight()),
	background(&display),
	gui(display.getWidth(), display.getHeight()),
	star(50, 50, display.getWidth(), display.getHeight())
{
	drawingAndTimersRelatedLogicThread = nullptr;
	maxTime = 60;
	end = false;
	draw = true;
	score = 0;
	change = 0;
	timer.setAnimation(8);
	state = NotStarted;
	gui.setTime(maxTime);

	star.attachEffect(&noEffect);

	startInitializingSound();
	initializeBitmaps();
	initializeFonts();
	setupInput();

	srand(time(NULL));
}

Game::~Game(){
	startInitializingSountThread->join();

	delete yellowStar;
	delete blueStar;
	delete redStar;

	resourcesManager.unloadSounds();
	resourcesManager.unloadFonts();
	resourcesManager.unloadBitmaps();
}

void Game::initializeBitmaps(){
	resourcesManager.loadBitmaps();
	display.setIcon(resourcesManager.starYellowBitmap);
	player.attachBitmap(resourcesManager.playerSheetBitmap);
	background.attachBitmap(resourcesManager.backgroundBitmap);

	yellowStar = new Sprite(resourcesManager.starYellowBitmap);
	blueStar = new Sprite(resourcesManager.starBlueBitmap);
	redStar = new Sprite(resourcesManager.starRedBitmap);

	star.attachSprite(yellowStar);
	star.setupParameters();

	star.generateNewPosition();
	star.generateNewPositionBasedOnPlayerPosition(player);
}

void Game::initializeFonts(){
	resourcesManager.loadFonts();
	gui.attachFonts(resourcesManager.textFont, resourcesManager.bigTextFont);
}

void Game::startInitializingSound(){
	startInitializingSountThread = new std::thread(&Game::initializeSound, this);
}

void Game::initializeSound(){
	resourcesManager.loadSounds();
	sound.attachSamples(resourcesManager.mainBackgroundThemeSample, resourcesManager.starCatchEffectSample);
	sound.prepare();
	sound.playBackgroundMusic();
}

void Game::setupInput(){
	if(inputManager.connectSTM())
		inputManager.registerSTM();
	inputManager.registerAllegro();
}

void Game::run(){
	timer.start();


	startDrawingAndTimersRelatedLogic();
	logicLoop();
	stopDrawingAndTimersRelatedLogic();

	timer.stop();
}

void Game::startDrawingAndTimersRelatedLogic(){
	drawingAndTimersRelatedLogicThread = new std::thread(&Game::drawingAndTimersRelatedLogicLoop, this);
}

void Game::stopDrawingAndTimersRelatedLogic(){
	drawingAndTimersRelatedLogicThread->join();
	delete drawingAndTimersRelatedLogicThread;
	drawingAndTimersRelatedLogicThread = nullptr;
}

void Game::logicLoop(){
	while(!end){
		InputManager::InputEvent inputEvent;
		inputEvent = inputManager.getEvent();

		if(inputEvent.exitInitialized())
			end = true;
		if(state != Paused){
			player.changeDirection(inputEvent.getLastMove());
			background.changeDirection(player.getCurrentDirection());
			if(state != NotStarted){
				int elapsedSeconds = (int)watch.getElapsedSeconds();
				gui.setTime(maxTime - elapsedSeconds);

				if(elapsedSeconds >= maxTime)
					pauseGame();
			}
		}
		else if(inputEvent.enterPressed())
			restartGame();
		Sleep(0);
	}
}

void Game::drawingAndTimersRelatedLogicLoop(){
	al_set_target_backbuffer(display.getAllegroDisplay()); // set target in new thread
	srand(time(NULL));


	std::cout << change;
	while(!end){
		GameTimer::TimerTickType timerType = timer.getTimerTick();
		if(timerType != GameTimer::TimerTickType::NONE)
		{
			if(timerType == GameTimer::TimerTickType::MAIN){		// Main timer
				if(state != Paused){
					background.move();
					player.move();

					if(star.collidesWith(player))
					{
						if(state == NotStarted)
							startGame();
						score++;
						gui.setScore(score);
						sound.playStarSoundEffect();
						star.affect(&player);
						star.generateNewPositionBasedOnPlayerPosition(player);
						changeStar();
					}
				}

				draw = true;
			}
			else{													// Animation timer
				if(state != Paused)
					player.animate();
			}		
		}

		if(draw){
			display.clear();

			background.draw();
			star.draw();
			player.draw();
			gui.draw();
			if(state == Paused)
				gui.drawOnPause();

			display.flip();
			draw = false;

		}
	}
}

void Game::restartGame(){
	state = NotStarted;
	score = 0;

	gui.setScore(score);
	gui.setTime(maxTime);
	watch.restart();
}

void Game::startGame(){
	state = Started;
	watch.restart();
}

void Game::pauseGame(){
	state = Paused;
}

void Game::changeStar()
{
	int random = rand() % 11;
	if(random < 8)
		changeStarToYellow();
	else if(random < 10)
		changeStarToBlue();
	else
		changeStarToRed();
}

void Game::changeStarToYellow()
{
	star.attachSprite(yellowStar);
	star.attachEffect(&noEffect);
}

void Game::changeStarToBlue()
{
	star.attachSprite(blueStar);
	star.attachEffect(&speedUpEffect);
}

void Game::changeStarToRed()
{
	star.attachSprite(redStar);
	star.attachEffect(&inverseEffect);
}