#define ALLEGRO_STATICLINK

#include "AllegroInitializer.h"
#include "Game.h"
#include <iostream>


int main(){
	AllegroInitializer::initialize();
	

	try{
		AllegroInitializer::initialize();
		Game game;
		game.run();
	}
	catch(MyException e){
		al_show_native_message_box(
			0,
			"Error",
			"",
			e.getMessage().c_str(),
			0,
			ALLEGRO_MESSAGEBOX_ERROR);
	}	

	return 0;
};