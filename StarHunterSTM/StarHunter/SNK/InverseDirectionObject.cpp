#include "InverseDirectionObject.h"

void InverseDirectionObject::undo(Player* player, bool *done, StopWatch *watch)
{
	watch->restart();
	while(watch->elapsedSeconds().count() < affectingTime && !endFlag)
	{
		Sleep(50);
	}
	player->inverseDirections(false);
	*done = true;
}

void InverseDirectionObject::affect(Player* player)
{
		if(mQueue.size() > 0)
			mQueue.back()->watch.restart();
		player->inverseDirections(true);
		ThreadWorker * worker = new ThreadWorker();
		worker->t = new std::thread(&InverseDirectionObject::undo, this, player, &worker->done, &worker->watch);
		mQueue.push(worker);
}