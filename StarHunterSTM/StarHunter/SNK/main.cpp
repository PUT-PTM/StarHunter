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
		std::cout << e.getMessage() << std::endl;
		std::cin.sync();
		std::cin.get();
	}	

	return 0;
}