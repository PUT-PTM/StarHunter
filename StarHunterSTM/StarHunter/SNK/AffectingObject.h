#pragma once

#include "IAffectingObject.h"
#include "StopWatch.h"
#include <future>
#include <queue>

class AffectingObject : public IAffectingObject{
protected:
	class ThreadWorker{
	public:
		std::thread* t;
		bool done;
		StopWatch watch;

		ThreadWorker();
		~ThreadWorker();
		void join();
	};
	std::queue<ThreadWorker*> mQueue;

	int affectingTime;
	virtual void undo(Player* player, bool *done, StopWatch *watch) = 0;

	bool endFlag;
public:
	AffectingObject();
	~AffectingObject();
	void affect(Player* player) = 0;
};