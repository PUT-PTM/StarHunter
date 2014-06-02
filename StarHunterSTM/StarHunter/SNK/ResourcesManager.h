#pragma once
#include <allegro5\allegro.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_ttf.h>
#include <allegro5\\allegro_font.h>
#include "MyException.h"

class ResourcesManager{
public:
	ALLEGRO_BITMAP *backgroundBitmap;
	ALLEGRO_BITMAP *playerSheetBitmap;
	ALLEGRO_BITMAP *starYellowBitmap;
	ALLEGRO_BITMAP *starGreenBitmap;
	ALLEGRO_BITMAP *starBlueBitmap;
	ALLEGRO_BITMAP *starRedBitmap;
	ALLEGRO_BITMAP *icon;

	ALLEGRO_SAMPLE *starCatchEffectSample;
	ALLEGRO_SAMPLE *mainBackgroundThemeSample;

	ALLEGRO_FONT *textFont;
	ALLEGRO_FONT *bigTextFont;
	
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