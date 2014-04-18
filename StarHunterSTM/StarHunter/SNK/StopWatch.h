#pragma once

#include <chrono>

using namespace std::chrono;

microseconds intervalInMicroSeconds(const high_resolution_clock::time_point& t1, const high_resolution_clock::time_point& t0);

milliseconds intervalInMiliSeconds(const high_resolution_clock::time_point& t1,const high_resolution_clock::time_point& t0);

class StopWatch
{
	high_resolution_clock::time_point start_;
public:
	StopWatch();
	high_resolution_clock::time_point restart();
	microseconds elapsedUs();
	milliseconds elapsedMs();
};