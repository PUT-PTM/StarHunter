#pragma once

#include "IAffectingObject.h"

class NoAffectObject : public IAffectingObject{
public:
	void affect(Player* player);
};