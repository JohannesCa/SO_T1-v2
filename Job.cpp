/*
 * Job.cpp
 *
 *  Created on: 1 de out de 2016
 *      Author: johannes
 */

#include "Job.h"

Job::Job(int pid, int start, int duration):
	_PID(pid),
	_call(start),
	_duration(duration),
	_lastingTime(duration)
{
	;
}

bool Job::decreaseTime(int d) // Return if it's the first time the job is beeing executed
{
	bool FirstTime = this->_duration == this->_lastingTime;

	this->_lastingTime -= d <= this->_lastingTime? d : 0;

	return FirstTime;
}
