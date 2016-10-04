/*
 * FCFS.cpp
 *
 *  Created on: 2 de out de 2016
 *      Author: johannes
 */

#include "FCFS.h"

namespace Scheduler {

void Copy(JobList* a, JobList* src);
void Clear(JobList* a);

FCFS::FCFS(JobList* in)
{
	Copy(&this->_Joblist, in);

	unsigned int n = this->_Joblist.size();

	double WaitTime[n];
	double RetTime[n];

	WaitTime[0] = 0;
	RetTime[0] = this->_Joblist[0]->getDuration();

	int cur_time = RetTime[0] + this->_Joblist[0]->getCall();

	for(unsigned int i = 1; i < n; ++i){
		WaitTime[i] = cur_time - this->_Joblist[i]->getCall();
		cur_time += this->_Joblist[i]->getDuration();
		RetTime[i] = cur_time - this->_Joblist[i]->getCall();
	}

	double WaitTimeSum = 0;
	double RetTimeSum = 0;

	for(unsigned int i = 0; i < n; ++i){
		WaitTimeSum += WaitTime[i];
		RetTimeSum += RetTime[i];
	}

	this->_AvgWaitTime = WaitTimeSum/n;
	this->_AvgRetTime = RetTimeSum/n;
	this->_AvgAwsTime = this->_AvgRetTime;
}

FCFS::~FCFS()
{
	Clear(&this->_Joblist);
}

} /* namespace Scheduler */
