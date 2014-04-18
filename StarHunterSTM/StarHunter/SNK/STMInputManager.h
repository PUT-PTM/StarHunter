#pragma once

#include <list>
#include <thread>
#include <chrono>
#include "math.h"
#include "hid.h"
#include "MyException.h"
#include "StopWatch.h"


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
	char buffer_in[64];

	double averageY, averageX;
	unsigned count;

	std::chrono::milliseconds maxIntervalInMiliseconds;
	StopWatch watch;

	STMInputEvent lastEvent;
	std::thread* loop; 
	std::list<STMInputEvent> eventsList;

	void initializeParameters();
	void clearBuffer();
	void loopMethod();
	void collectRawInput();
	void getEventFromRaw(double rawX, double rawY);
};



