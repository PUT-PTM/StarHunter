#pragma once

#include <list>

class STMInputManager{
public:
	enum STMInputEvent{
		STM_UP,
		STM_DOWN,
		STM_LEFT,
		STM_RIGHT,
		STM_NONE
	};
	void registerSTMInput();
	bool isKeyDown(STMInputEvent ev);
	STMInputEvent lastKeyDown();
private:

	bool up, down, left, right;
	std::list<STMInputEvent> eventsList;
};