#pragma once

#include <queue>
#include <mutex>

template<typename X>
class ThreadSafeQueue{
private:
	std::mutex mtx;
	std::queue<X>* queue;
public:
	ThreadSafeQueue(){
		queue = new std::queue<X>;
	}
	~ThreadSafeQueue(){
		delete queue;
	}

	bool empty(){
		return queue->empty();
	}

	void push(X value){
		mtx.lock();
		queue->push(value);
		mtx.unlock();
	}

	X popFront(){
		X returnValue = queue->front();
		queue->pop();
		return returnValue;
	}

	void clear(){
		mtx.lock();
		delete queue;
		queue = new std::queue<X>;
		mtx.unlock();
	}
};