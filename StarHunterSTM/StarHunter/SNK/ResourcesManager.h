#pragma once
#include <allegro5\allegro.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\\allegro_font.h>
#include "MyException.h"

class ResourcesManager{
public:
	ALLEGRO_BITMAP* backgroundBitmap;
	ALLEGRO_BITMAP* playerSheetBitmap;
	ALLEGRO_BITMAP* starBitmap;

	ALLEGRO_SAMPLE *starCatchEffectSample;
	ALLEGRO_SAMPLE *mainBackgroundThemeSample;

	ALLEGRO_FONT * textFont;
	
	ResourcesManager();
	//throws MyException
	void loadBitmaps();
	void unloadBitmaps();
	//throws MyException
	void loadFonts();
	void unloadFonts();
	//throws MyException
	void loadSounds();
	void unloadSounds();
};