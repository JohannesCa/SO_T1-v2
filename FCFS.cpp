/*
 * FCFS.cpp
 *
 *  Created on: 2 de out de 2016
 *      Author: johannes
 */

#include "FCFS.h"

namespace Scheduler {

FCFS::FCFS(JobList* in)
{
	for(JobIt it = in->begin(); it != in->end(); ++it)
		this->_Joblist.push_back(new Job(**it));

	int n = this->_Joblist.size();

	int WaitTime[n];
	int RetTime[n];
	int initTime = this->_Joblist[0]->getCall();

	WaitTime[0] = 0;//this->_Joblist[0]->getCall();
	RetTime[0] = this->_Joblist[0]->getDuration();

	for(int i = 1; i < n; ++i){
		WaitTime[i] = RetTime[i-1] > (this->_Joblist[i]->getCall() - initTime)? RetTime[i-1] : (this->_Joblist[i]->getCall() - initTime);
		RetTime[i] = WaitTime[i] + this->_Joblist[i]->getDuration();
	}

	int WaitTimeSum = 0;
	int RetTimeSum = 0;

	for(int i = 0; i < n; ++i){
		WaitTimeSum += WaitTime[i];
		RetTimeSum += RetTime[i];
	}

	this->_AvgWaitTime = WaitTimeSum/n;
	this->_AvgRetTime = RetTimeSum/n;
}

FCFS::~FCFS()
{
	for(JobIt it = this->_Joblist.begin(); it != this->_Joblist.end(); ++it)
		delete (*it);

	this->_Joblist.clear();
}

} /* namespace Scheduler */