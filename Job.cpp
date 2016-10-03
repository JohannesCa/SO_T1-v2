/*
 * Job.cpp
 *
 *  Created on: 1 de out de 2016
 *      Author: johannes
 */

#include "Job.h"

Job::Job(int start, int duration):
	_duration(duration),
	_call(start),
	_lastingTime(duration)
{
	;
}
