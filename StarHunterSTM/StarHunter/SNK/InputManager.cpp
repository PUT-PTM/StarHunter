#include "InputManager.h"

InputManager::InputEvent::InputEvent(){
	moveType = NONE;
	exit = enter = false;
}

InputManager::MoveEventType InputManager::InputEvent::getLastMove(){
	return moveType;
}

bool InputManager::InputEvent::enterPressed(){
	return enter;
}

bool InputManager::InputEvent::exitInitialized(){
	return exit;
}

InputManager::InputManager(Display &display) : allegroInputManager(display)
{
	lastMove = NONE;
}

void InputManager::connectSTM(){
	stmInputManager.connect();
}

void InputManager::registerSTM(){
	stmInputManager.registerInput();
}

void InputManager::registerAllegro(){
	allegroInputManager.registerInput();
}

void InputManager::endRegistering(){
	stmInputManager.endRegisteringInput();
}

InputManager::InputEvent InputManager::getEvent(){
	InputEvent ev;	

	setInputEvent(ev);
	return ev;
}

void InputManager::setInputEvent(InputManager::InputEvent &ev){
	ev.moveType = stmEventToMoveEvent(stmInputManager.getEvent());

	ALLEGRO_EVENT allEv = allegroInputManager.getEvent();
	if(allEv.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		ev.exit = true;
	if(allEv.type == ALLEGRO_EVENT_KEY_DOWN){
		switch(allEv.keyboard.keycode){
		case ALLEGRO_KEY_ESCAPE:
			ev.exit = true;
			break;
		case ALLEGRO_KEY_ENTER:
			ev.enter = true;
			break;
		case ALLEGRO_KEY_UP:
			ev.moveType = UP;
			break;
		case ALLEGRO_KEY_DOWN:
			ev.moveType = DOWN;
			break;
		case ALLEGRO_KEY_LEFT:
			ev.moveType = LEFT;
			break;
		case ALLEGRO_KEY_RIGHT:
			ev.moveType = RIGHT;
			break;
		}
	}

	if(ev.moveType == NONE)
		ev.moveType = lastMove;
	else
		lastMove = ev.moveType;
}

InputManager::MoveEventType InputManager::stmEventToMoveEvent(STMInputManager::STMInputEvent stmEv){
	InputManager::MoveEventType ev;

	switch(stmEv){
	case STMInputManager::STMInputEvent::STM_UP:
		ev = UP;
		break;
	case STMInputManager::STMInputEvent::STM_DOWN:
		ev = DOWN;
		break;
	case STMInputManager::STMInputEvent::STM_LEFT:
		ev = LEFT;
	break;
	case STMInputManager::STMInputEvent::STM_RIGHT:
		ev = RIGHT;
		break;
	case STMInputManager::STMInputEvent::STM_NONE:
		ev = NONE;
		break;
	}

	return ev;
}