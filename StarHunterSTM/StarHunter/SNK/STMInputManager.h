#pragma once

#include <list>
#include <thread>
#include "hid.h"
#include "MyException.h"
#include "math.h"

class STMInputManager{
public:
	enum STMInputEvent{
		STM_UP,
		STM_DOWN,
		STM_LEFT,
		STM_RIGHT,
		STM_NONE
	};
	STMInputManager();

	bool connect();
	void registerSTMInput();
	void stopRegisteringSTMInput();
	//bool isKeyDown(STMInputEvent ev);
	STMInputEvent getLastEvent();
private:
	bool connected, registering, bufferDirty;
	bool up, left;
	STMInputEvent lastEvent;
	char buffer_in[64];

	std::thread* loop; 
	std::list<STMInputEvent> eventsList;

	void clearBuffer();
	void loopMethod();
	void getEventFromRaw();
};



