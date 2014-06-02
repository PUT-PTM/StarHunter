#include "Game.h"

Game::Game() :
	display(800, 600),
	inputManager(display),
	player(
		display.getWidth() / 2.0f, display.getHeight() / 2.0f,
		display.getWidth(), display.getHeight()),
	background(&display),
	gui(display.getWidth(), display.getHeight()),
	starYellow(50, 50, display.getWidth(), display.getHeight()),
	starGreen(100, 100, display.getWidth(), display.getHeight()),
	starBlue(200, 200, display.getWidth(), display.getHeight()),
	starRed(300, 300, display.getWidth(), display.getHeight())
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


	startInitializingSound();
	initializeBitmaps();
	initializeFonts();
	setupInput();
}

Game::~Game(){
	startInitializingSountThread->join();
	resourcesManager.unloadSounds();
}

void Game::initializeBitmaps(){
	resourcesManager.loadBitmaps();
	display.setIcon(resourcesManager.starYellowBitmap);
	player.attachBitmap(resourcesManager.playerSheetBitmap);
	background.attachBitmap(resourcesManager.backgroundBitmap);

	starYellow.attachBitmap(resourcesManager.starYellowBitmap);
	starGreen.attachBitmap(resourcesManager.starGreenBitmap);
	starBlue.attachBitmap(resourcesManager.starBlueBitmap);
	starRed.attachBitmap(resourcesManager.starRedBitmap);

	starYellow.generateNewPosition();
	starYellow.generateNewPositionBasedOnPlayerPosition(player);
	starGreen.generateNewPosition();
	
	starBlue.generateNewPosition();
	starRed.generateNewPosition();
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
			background.changeDirection(inputEvent.getLastMove());
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

					// Nowe gwiazdki, prawdopodobienstwo 2:1:1:1 (star, green, blue, red)
					if(change == 0 || change == 1)
						if(player.collidesWith(starYellow))
				{
					if(state != Started)
						startGame();
					
					change = (std::rand()% 5 ) + 0;

					switch(change)
					{
					case 0:
					case 1:
					starYellow.generateNewPositionBasedOnPlayerPosition(player);
					break;
					case 2:
					starGreen.generateNewPositionBasedOnPlayerPosition(player);
					break;
					case 3:
					starBlue.generateNewPositionBasedOnPlayerPosition(player);
					break;
					default:
					starRed.generateNewPositionBasedOnPlayerPosition(player);
					break;
					}
					
					sound.playStarSoundEffect();
					//score = starYellow.affect(player, score);
					
				};
				
						if(change == 2)
				if(player.collidesWith(starGreen))
				{
					
					if(state != Started)
						startGame();
					change = (std::rand()% 5 ) + 0;

					switch(change)
					{
					case 0:
					case 1:
					starYellow.generateNewPositionBasedOnPlayerPosition(player);
					break;
					case 2:
					starGreen.generateNewPositionBasedOnPlayerPosition(player);
					break;
					case 3:
					starBlue.generateNewPositionBasedOnPlayerPosition(player);
					break;
					default:
					starRed.generateNewPositionBasedOnPlayerPosition(player);
					break;
					}
					
					sound.playStarSoundEffect();
					score--;
					gui.setScore(score);
					
				};

						if(change == 3)
				if(player.collidesWith(starBlue))
				{
					
					if(state != Started)
						startGame();
					change = (std::rand()% 5 ) + 0;

					switch(change)
					{
					case 0:
					case 1:
					starYellow.generateNewPositionBasedOnPlayerPosition(player);
					break;
					case 2:
					starGreen.generateNewPositionBasedOnPlayerPosition(player);
					break;
					case 3:
					starBlue.generateNewPositionBasedOnPlayerPosition(player);
					break;
					default:
					starRed.generateNewPositionBasedOnPlayerPosition(player);
					break;
					}

					sound.playStarSoundEffect();
					timer.setAnimation(15);
					
				};


						if(change == 4)
				if(player.collidesWith(starRed))
				{
					
					if(state != Started)
						startGame();
					change = (std::rand()% 5 ) + 0;

					switch(change)
					{
					case 0:
					case 1:
					starYellow.generateNewPositionBasedOnPlayerPosition(player);
					break;
					case 2:
					starGreen.generateNewPositionBasedOnPlayerPosition(player);
					break;
					case 3:
					starBlue.generateNewPositionBasedOnPlayerPosition(player);
					break;
					default:
					starRed.generateNewPositionBasedOnPlayerPosition(player);
					break;
					}

					sound.playStarSoundEffect();
					score += 2;
					gui.setScore(score);
					
				};
				
				

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

			switch(change)
			{
				case 0:
				case 1:
			starYellow.draw();	
			break;
				case 2:
			starGreen.draw();
			break;
				case 3:
			starBlue.draw();
			break;
				default:
			starRed.draw();
			break;
			}

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