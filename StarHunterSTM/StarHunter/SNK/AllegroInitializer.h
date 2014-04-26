#pragma once

#include <allegro5\allegro.h>
#include <allegro5\allegro_native_dialog.h>
#include <allegro5\\allegro_image.h>
#include <allegro5\allegro_primitives.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>

#include "MyException.h"

class AllegroInitializer{
private:
	AllegroInitializer();
	static bool initialized;
public:
	// throws MyException
	static void initialize(){
		if(!initialized){
			if(!al_init())
				throw new MyException("Could not Initialize Allegro");

			al_init_image_addon();
			al_init_primitives_addon();
			al_install_keyboard();
			al_install_audio();
			al_init_acodec_addon();
			initialized = true;
		}
	}
};