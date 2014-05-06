#include "ResourcesManager.h"

ResourcesManager::ResourcesManager(){
	backgroundBitmap = nullptr;
	playerSheetBitmap = nullptr;
	starBitmap = nullptr;

	starCatchEffectSample = nullptr;
	mainBackgroundThemeSample = nullptr;
}

void ResourcesManager::loadBitmaps(){
	backgroundBitmap = al_load_bitmap("assets/gfx/background.png");
	playerSheetBitmap = al_load_bitmap("assets/gfx/playerSheet.png");
	starBitmap = al_load_bitmap("assets/gfx/star.png");
	if(!backgroundBitmap || !playerSheetBitmap || !starBitmap)
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
	if(starBitmap){
		al_destroy_bitmap(starBitmap);
		starBitmap = nullptr;
	}
}

void ResourcesManager::loadFonts(){
}
void ResourcesManager::unloadFonts(){
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
