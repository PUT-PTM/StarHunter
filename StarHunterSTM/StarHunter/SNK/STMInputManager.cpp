#include "STMInputManager.h"

STMInputManager::STMInputManager(){
	initializeParameters();
	clearBuffer();
}

void STMInputManager::initializeParameters(){
	registering = connected = left = up  = false;
	bufferDirty = true;
	lastCallTime = 0;
	intervalInMiliseconds = 100;
	loop = nullptr;
	lastEvent = STMInputEvent::STM_NONE;
}

void STMInputManager::clearBuffer(){
	if(bufferDirty)
	{
		bufferDirty = false;
		for(int i = 0; i < 64; i++)
			buffer_in[i] = 0;
	}
}

STMInputManager::STMInputEvent STMInputManager::getLastEvent(){
	return lastEvent;
}

bool STMInputManager::connect(){
	connected = FindTheHID();
	return connected;
}

void STMInputManager::registerSTMInput(){
	if(!connected)
		throw new MyException("STM is not connected.");
	if(!registering)
		loop = new std::thread(&STMInputManager::loopMethod, this);
}

void STMInputManager::stopRegisteringSTMInput(){
	registering = false;
	loop->join();
	delete loop;
	loop = 0;
}

void STMInputManager::loopMethod(){
	clearBuffer();
	registering = bufferDirty = true;
	while(registering){
		ReadInputReport(buffer_in);
		getEventFromRaw();
	}
}

void STMInputManager::collectRawInput(){

}

void STMInputManager::getEventFromRaw(){
	float v = buffer_in[2];
	v -= 5.0f;

	if((int)buffer_in[1] > 0)
		left = true;
	else
		left = false;

	if(v < 0)
		up = true;
	else
		up = false;

	double valueY = abs(v) * 1.10f;
	double valueX = abs(buffer_in[1]);

	if(valueY > 12.0f || valueX > 12.0f){
		if(abs(valueY) > valueX){
			if(up)
				lastEvent = STMInputEvent::STM_UP;
			else
				lastEvent = STMInputEvent::STM_DOWN;
		}
		else{
			if(left)
				lastEvent = STMInputEvent::STM_LEFT;
			else
				lastEvent = STMInputEvent::STM_RIGHT;
		}
	}

}





