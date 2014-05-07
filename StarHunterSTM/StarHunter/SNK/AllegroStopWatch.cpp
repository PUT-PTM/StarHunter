#include "AllegroStopWatch.h"

AllegroStopWatch::AllegroStopWatch(){
	restart();
}

void AllegroStopWatch::restart(){
	startTime = al_get_time();
}

float AllegroStopWatch::getElapsedSeconds(){
	return al_get_time() - startTime;
}