#include "StopWatch.h"

microseconds intervalInMicroSeconds(const high_resolution_clock::time_point& t1, const high_resolution_clock::time_point& t0)
{
	return duration_cast<microseconds>(t1 - t0);
}

milliseconds intervalInMiliSeconds(const high_resolution_clock::time_point& t1,const high_resolution_clock::time_point& t0)
{
	return duration_cast<milliseconds>(t1 - t0);
}

seconds intervalInSeconds(const high_resolution_clock::time_point& t1,const high_resolution_clock::time_point& t0)
{
	return duration_cast<seconds>(t1 - t0);
}

StopWatch::StopWatch() : 
	start_(high_resolution_clock::now())
{}

high_resolution_clock::time_point StopWatch::restart() 
{ 
	start_ = high_resolution_clock::now(); 
	return start_;
}

microseconds StopWatch::elapsedUs()    
{ 
	return intervalInMicroSeconds(high_resolution_clock::now(), start_);
}

milliseconds StopWatch::elapsedMs()    
{ 
	return intervalInMiliSeconds(high_resolution_clock::now(), start_);
}

seconds StopWatch::elapsedSeconds()
{
	return intervalInSeconds(high_resolution_clock::now(), start_);
}