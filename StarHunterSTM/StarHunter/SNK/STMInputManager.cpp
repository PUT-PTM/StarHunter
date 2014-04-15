#include "STMInputManager.h"

STMInputManager::STMInputManager(){
	registering = connected = left = up  = false;
	bufferDirty = true;
	lastEvent = STMInputEvent::STM_NONE;
	loop = 0;

	clearBuffer();
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

void STMInputManager::getEventFromRaw(){
	if((int)buffer_in[1] > 0)
		left = true;
	else
		left = false;

	if((int)buffer_in[2] < 0)
		up = true;
	else
		up = false;

	double valueY = abs(buffer_in[2]) * 1.3f;
	double valueX = abs(buffer_in[1]);
	if(abs(valueX - valueY) > 10){
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





