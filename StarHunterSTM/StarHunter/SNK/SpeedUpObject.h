#pragma once

#include "IAffectingObject.h"
#include "StopWatch.h"
#include <future>
#include <queue>

class SpeedUpObject : public IAffectingObject{
private:
	class ThreadWorker{
	public:
		std::thread* t;
		bool done;

		ThreadWorker();
		~ThreadWorker();
		void join();
	};
	std::queue<ThreadWorker*> mQueue;

	const int affectingTime;
	void undo(Player* player, bool *done);

	bool endFlag;
public:
	SpeedUpObject();
	~SpeedUpObject();
	void affect(Player* player);
};