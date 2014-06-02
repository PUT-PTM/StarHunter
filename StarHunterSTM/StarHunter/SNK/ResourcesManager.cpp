#include "ResourcesManager.h"

ResourcesManager::ResourcesManager(){
	backgroundBitmap = nullptr;
	playerSheetBitmap = nullptr;
	starYellowBitmap = nullptr;
	starGreenBitmap = nullptr;
	starBlueBitmap = nullptr;
	starRedBitmap = nullptr;

	starCatchEffectSample = nullptr;
	mainBackgroundThemeSample = nullptr;

	textFont = nullptr;
}

void ResourcesManager::loadBitmaps(){
	backgroundBitmap = al_load_bitmap("assets/gfx/background.png");
	playerSheetBitmap = al_load_bitmap("assets/gfx/playerSheet.png");
	starYellowBitmap = al_load_bitmap("assets/gfx/star.png");
	starGreenBitmap = al_load_bitmap("assets/gfx/stargreen.png");
	starBlueBitmap = al_load_bitmap("assets/gfx/starblue.png");
	starRedBitmap = al_load_bitmap("assets/gfx/starred.png");
	icon = al_load_bitmap("assets/gfx/star.ico");
	if(!backgroundBitmap || !playerSheetBitmap || !starYellowBitmap || icon)
		throw MyException("Could not load bitmap.");
}

void ResourcesManager::unloadBitmaps(){
	if(backgroundBitmap){
		al_destroy_bitmap(backgroundBitmap);
		backgroundBitmap = nullptr;
	}
	if(playerSheetBitmap){
		al_destroy_bitmap(playerSheetBitmap);
		playerSheetBitmap = nullptr;
	}
	if(starYellowBitmap){
		al_destroy_bitmap(starYellowBitmap);
		starYellowBitmap = nullptr;
	}
	if(starGreenBitmap){
		al_destroy_bitmap(starGreenBitmap);
		starGreenBitmap = nullptr;
	}
	if(starBlueBitmap){
		al_destroy_bitmap(starBlueBitmap);
		starBlueBitmap = nullptr;
	}
	if(starRedBitmap){
		al_destroy_bitmap(starRedBitmap);
		starRedBitmap = nullptr;
	}
}

void ResourcesManager::loadFonts(){
	textFont = al_load_font("assets/gfx/font.ttf", 35, 0);
	bigTextFont = al_load_font("assets/gfx/font.ttf", 50, 0);
	if(!textFont || !bigTextFont)
		throw MyException("Could not load font");
}
void ResourcesManager::unloadFonts(){
	if(textFont){
		al_destroy_font(textFont);
		textFont = nullptr;
	}	
}

void ResourcesManager::loadSounds(){
	starCatchEffectSample = al_load_sample("assets/sounds/star.ogg");
	mainBackgroundThemeSample = al_load_sample("assets/sounds/background.ogg");
	if(!starCatchEffectSample || !mainBackgroundThemeSample)
		throw MyException("Could not load sound.");
}
void ResourcesManager::unloadSounds(){
	if(starCatchEffectSample){
		al_destroy_sample(starCatchEffectSample);
		starCatchEffectSample = nullptr;
	}
	if(mainBackgroundThemeSample){
		al_destroy_sample(mainBackgroundThemeSample);
		mainBackgroundThemeSample = nullptr;
	}
}
