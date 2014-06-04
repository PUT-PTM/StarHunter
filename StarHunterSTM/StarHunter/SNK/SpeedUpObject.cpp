#include "SpeedUpObject.h"

void SpeedUpObject::undo(Player* player, bool *done, StopWatch *watch)
{
	watch->restart();
	while(watch->elapsedSeconds().count() < affectingTime && !endFlag)
	{
		Sleep(50);
	}
	player->multiplyDistancePerFrameBy(1.0f / 1.6f);
	*done = true;
}

void SpeedUpObject::affect(Player* player)
{
		if(mQueue.size() > 0)
			mQueue.back()->watch.restart();
		player->multiplyDistancePerFrameBy(1.6f);
		ThreadWorker * worker = new ThreadWorker();
		worker->t = new std::thread(&SpeedUpObject::undo, this, player, &worker->done, &worker->watch);
		mQueue.push(worker);
}