/*
 * SJF.cpp
 *
 *  Created on: 2 de out de 2016
 *      Author: johannes
 */

#include "SJF.h"

namespace Scheduler {

bool BurstComp(Job* a, Job* b);
bool CallComp(Job* a, Job* b);
void Copy(JobList* a, JobList* src);
void Clear(JobList* a);
void pprint(JobList* a);

SJF::SJF(JobList* in)
{
	Copy(&this->_Joblist, in);

	/*** sort hereee ***/

	this->Sort();

	/*** end sorting ***/

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

void SJF::Sort(void)
{
	JobList CallOrd;  // Call Ordered
	JobList BurstOrd; // Burst Ordered
	JobList SJFList;  // Shortest Job First List

	Copy(&CallOrd, &this->_Joblist);
	Copy(&BurstOrd, &this->_Joblist);

	sort(CallOrd.begin(), CallOrd.end(), CallComp);
	sort(BurstOrd.begin(), BurstOrd.end(), BurstComp);

	SJFList.push_back(CallOrd[0]);

	for(JobIt it = BurstOrd.begin(); it != BurstOrd.end(); ++it){
		if(((*it)->getCall() == CallOrd[0]->getCall()) && ((*it)->getDuration() == CallOrd[0]->getDuration())){
			BurstOrd.erase(it);
			break;
		}
	}
	CallOrd.erase(CallOrd.begin());

	JobIt ii = BurstOrd.begin();
	int cur_time = SJFList[0]->getDuration();

	while(!BurstOrd.empty()){
		if((*ii)->getCall() <= cur_time){
			SJFList.push_back(*ii);
			BurstOrd.erase(ii);
			cur_time += (*ii)->getDuration();
			ii = BurstOrd.begin();
		}else
			++ii;
	}

	Clear(&this->_Joblist);
	Copy(&this->_Joblist, &SJFList);

	Clear(&CallOrd);
	Clear(&BurstOrd);
}

SJF::~SJF()
{
	Clear(&this->_Joblist);
}

void SJF::print(void)
{
	for(unsigned int i = 0; i < this->_Joblist.size(); ++i)
		printf("%i, %i\n", this->_Joblist[i]->getCall(), this->_Joblist[i]->getDuration());
}


bool BurstComp(Job* a, Job* b)
{
	return a->getDuration() < b->getDuration();
}

bool CallComp(Job* a, Job* b)
{
	if(a->getCall() == b->getCall())
		return a->getDuration() < b->getDuration();
	else
		return a->getCall() < b->getCall();
}

void Copy(JobList* a, JobList* src)
{
	a->clear();
	for(JobIt it = src->begin(); it != src->end(); ++it)
		a->push_back(new Job(**it));
}

void Clear(JobList* a)
{
	for(JobIt it = a->begin(); it != a->end(); ++it)
		delete *it;
	a->clear();
}

void pprint(JobList* a)
{
	for(unsigned int i = 0; i < a->size(); ++i)
		printf("%i, %i\n", (*a)[i]->getCall(), (*a)[i]->getDuration());;
}

} /* namespace Scheduler */
