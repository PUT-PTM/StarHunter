#pragma once

#include "AllegroInputManager.h"
#include "STMInputManager.h"

class InputManager{
public:
	enum MoveEventType{
		DOWN = 0,
		LEFT,
		RIGHT,
		UP,
		NONE
	};

	class InputEvent{
		friend class InputManager;
	public:	
		InputEvent();

		MoveEventType getLastMove();
		bool exitInitialized();
		bool enterPressed();
	private:
		MoveEventType moveType;
		bool exit, enter;
	};

	InputManager(Display &display);
	bool connectSTM();
	void registerSTM();
	void registerAllegro();
	void endRegistering();
	InputEvent getEvent();

private:
	AllegroInputManager allegroInputManager;
	STMInputManager stmInputManager;
	MoveEventType lastMove;

	void setInputEvent(InputEvent &ev);
	MoveEventType stmEventToMoveEvent(STMInputManager::STMInputEvent ev);
};