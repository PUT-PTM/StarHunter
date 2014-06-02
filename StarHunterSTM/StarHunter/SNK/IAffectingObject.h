#pragma once

#include "Player.h"

class IAffectingObject{
public:
	virtual void affect(Player* player) = 0;
};