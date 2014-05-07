#include "STMInputManager.h"
#include <iostream>
STMInputManager::STMInputManager() :
	valueNeededToChangeDirection(12.0f),
	valueNeededToThrowEvent(6.0f),
	yOffset(4.5f)
{
	initializeParameters();
	clearBuffer();
}

STMInputManager::~STMInputManager(){
	endRegisteringInput();
}

void STMInputManager::initializeParameters(){
	registering = connected = left = up  = false;
	bufferDirty = true;
	maxIntervalInMiliseconds = std::chrono::milliseconds(100);
	averageX = averageY = count = 0;
	loop = nullptr;
	currentEvent = STMInputEvent::STM_NONE;
}

void STMInputManager::clearBuffer(){
	if(bufferDirty)
	{
		bufferDirty = false;
		for(int i = 0; i < 64; i++)
			buffer_in[i] = 0;
	}
}

STMInputManager::STMInputEvent STMInputManager::getEvent(){
	return currentEvent;
}

bool STMInputManager::connect(){
	connected = FindTheHID();
	return connected;
}

void STMInputManager::registerInput(){
	if(!connected)
		throw new MyException("STM is not connected.");
	if(!registering)
		loop = new std::thread(&STMInputManager::loopMethod, this);
}

void STMInputManager::endRegisteringInput(){
	if(registering){
		registering = false;
		loop->join();
		delete loop;
		loop = 0;
	}
}

void STMInputManager::loopMethod(){
	clearBuffer();
	registering = bufferDirty = true;
	while(registering){
		ReadInputReport(buffer_in);
		collectRawInput();
	}
}

void STMInputManager::collectRawInput(){
	count++;
	averageX += (double)buffer_in[2];
	averageY += (double)buffer_in[1];

	if(watch.elapsedMs() > maxIntervalInMiliseconds){
		averageX /= count;
		averageY /= count;
		getEventFromRaw(averageX, averageY);
		averageX = averageY = count = 0;

		watch.restart();
	}
}

void STMInputManager::getEventFromRaw(double rawX, double rawY){

	rawY -= yOffset;

	if(rawX < 0)
		left = true;
	else
		left = false;

	if(rawY < 0)
		up = true;
	else
		up = false;

	double valueY = abs(rawY);
	double valueX = abs(rawX);

	std::cout << valueY << "  "  << valueX << std::endl;

	if(valueY > valueNeededToChangeDirection ||
		valueX > valueNeededToChangeDirection){
		if(valueY > valueX){
			if(up)
				currentEvent = STMInputEvent::STM_UP;
			else
				currentEvent = STMInputEvent::STM_DOWN;
		}
		else{
			if(left)
				currentEvent = STMInputEvent::STM_LEFT;
			else
				currentEvent = STMInputEvent::STM_RIGHT;
		}
	}
	else if(valueY < valueNeededToThrowEvent &&
		valueX < valueNeededToThrowEvent)
		currentEvent = STMInputEvent::STM_NONE;

}





