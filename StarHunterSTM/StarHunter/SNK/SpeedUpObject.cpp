#include "SpeedUpObject.h"

SpeedUpObject::SpeedUpObject() : affectingTime(4), endFlag(false)
{}

SpeedUpObject::~SpeedUpObject()
{
	endFlag = true;
	while(!mQueue.empty())
	{
		ThreadWorker* t = mQueue.front();
		t->join();
		mQueue.pop();
		delete t;	
	}
}

SpeedUpObject::ThreadWorker::ThreadWorker()
{
	this->done = false;
}

SpeedUpObject::ThreadWorker::~ThreadWorker()
{
	delete this->t;
}

void SpeedUpObject::ThreadWorker::join()
{
	this->t->join();
}

void SpeedUpObject::undo(Player* player, bool *done)
{
	StopWatch watch;
	watch.restart();
	while(watch.elapsedSeconds().count() < affectingTime && !endFlag)
	{
		Sleep(50);
	}
	player->multiplyDistancePerFrameBy(0.5f);
	*done = true;
}

void SpeedUpObject::affect(Player* player)
{
	player->multiplyDistancePerFrameBy(2.0f);
	ThreadWorker * worker = new ThreadWorker();
	worker->t = new std::thread(&SpeedUpObject::undo, this, player, &worker->done);
	mQueue.push(worker);
}