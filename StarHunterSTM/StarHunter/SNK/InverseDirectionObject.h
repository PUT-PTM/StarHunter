#pragma once

#include "AffectingObject.h"
#include "StopWatch.h"
#include <future>
#include <queue>

class InverseDirectionObject : public AffectingObject{
private:
	void undo(Player* player, bool *done, StopWatch *watch);

public:

	void affect(Player* player);
};