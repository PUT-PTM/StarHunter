#include "AllegroInitializer.h"
#include "Game.h"

int main(){
	AllegroInitializer::initialize();
	Game game;
	game.run();

	return 0;
}