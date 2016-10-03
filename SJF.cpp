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
	for(JobIt it = in->begin(); it != in->end(); ++it)
		this->_Joblist.push_back(new Job(**it));

	/*** sort hereee ***/

	this->Sort();

	/*** end sorting ***/

	unsigned int n = this->_Joblist.size();

	double WaitTime[n];
	double RetTime[n];
	double initTime = this->_Joblist[0]->getCall();

	WaitTime[0] = 0;//this->_Joblist[0]->getCall();
	RetTime[0] = this->_Joblist[0]->getDuration();

	for(unsigned int i = 1; i < n; ++i){
		WaitTime[i] = RetTime[i-1] > (this->_Joblist[i]->getCall() - initTime)? RetTime[i-1] : (this->_Joblist[i]->getCall() - initTime);
		RetTime[i] = WaitTime[i] + this->_Joblist[i]->getDuration();
	}

	double WaitTimeSum = 0;
	double RetTimeSum = 0;

	for(unsigned int i = 0; i < n; ++i){
		WaitTimeSum += WaitTime[i];
		RetTimeSum += RetTime[i];
	}

	this->_AvgWaitTime = WaitTimeSum/n;
	this->_AvgRetTime = RetTimeSum/n;
}

void SJF::Sort(void)
{
	//printf("> Unsorted:\n");
	//this->print();

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
/*
	cout << endl;
	pprint(&CallOrd);
	cout << endl;
	pprint(&BurstOrd);
*/
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

	Copy(&this->_Joblist, &SJFList);

	Clear(&CallOrd);
	Clear(&BurstOrd);
/*
	printf("> Sorted:\n");
	this->print();
*/
}

SJF::~SJF()
{
	for(JobIt it = this->_Joblist.begin(); it != this->_Joblist.end(); ++it)
		delete (*it);

	this->_Joblist.clear();
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
	Clear(a);
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
