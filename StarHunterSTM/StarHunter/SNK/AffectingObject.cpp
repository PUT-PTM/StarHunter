#include "AffectingObject.h"

AffectingObject::AffectingObject() : affectingTime(4), endFlag(false)
{}

AffectingObject::~AffectingObject()
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

AffectingObject::ThreadWorker::ThreadWorker()
{
	this->done = false;
}

AffectingObject::ThreadWorker::~ThreadWorker()
{
	delete this->t;
}

void AffectingObject::ThreadWorker::join()
{
	this->t->join();
}