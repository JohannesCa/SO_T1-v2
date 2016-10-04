/*
 * RR.cpp
 *
 *  Created on: 3 de out de 2016
 *      Author: johannes
 */

#include "RR.h"

namespace Scheduler {

void Copy(JobList* a, JobList* src);
void Clear(JobList* a);

RR::RR(JobList* in, int q):
	_quantum(q)
{
	Copy(&this->_Joblist, in);

	JobList ReadyJobs;
	JobList NotReadyJobs;

	unsigned int n = this->_Joblist.size();

	int cur_time = 0;

	ReadyJobs.push_back(this->_Joblist[0]);

	for(unsigned int i = 1; i < n; ++i){
		if(this->_Joblist[i]->getCall() == ReadyJobs[0]->getCall())
			ReadyJobs.push_back(this->_Joblist[i]);
		else
			NotReadyJobs.push_back(this->_Joblist[i]);
	}

	while(!NotReadyJobs.empty()){
		while(!ReadyJobs.empty()){
			if(ReadyJobs[0]->getLasting() != 0){
				bool getAws;

				if(this->_quantum < ReadyJobs[0]->getDuration()){

					JobIt aux = ReadyJobs.begin();
					getAws = (*aux)->decreaseTime(this->_quantum);

					ReadyJobs.erase(aux);

					cur_time += this->_quantum + ReadyJobs[0]->getCall();
					if(getAws)
						(*aux)->setAws(cur_time - ReadyJobs[0]->getCall());

					while(!NotReadyJobs.empty()){
						if(cur_time >= NotReadyJobs[0]->getCall()){
							ReadyJobs.push_back(NotReadyJobs[0]);
							NotReadyJobs.erase(NotReadyJobs.begin());
						}else
							break;
					}

					ReadyJobs.push_back(*aux);

				}else{

					getAws = ReadyJobs[0]->decreaseTime(ReadyJobs[0]->getLasting());
					cur_time += ReadyJobs[0]->getLasting() + ReadyJobs[0]->getCall();

					ReadyJobs[0]->setRet(cur_time - ReadyJobs[0]->getCall());

					if(getAws)
						ReadyJobs[0]->setAws(cur_time - ReadyJobs[0]->getCall());

					ReadyJobs.erase(ReadyJobs.begin());

					}

				while(!NotReadyJobs.empty()){
					if(cur_time >= NotReadyJobs[0]->getCall()){
						ReadyJobs.push_back(NotReadyJobs[0]);
						NotReadyJobs.erase(NotReadyJobs.begin());
					}else
						break;

				}

			}else{
				ReadyJobs.erase(ReadyJobs.begin());
			}
		}
	}

	for(JobIt it = this->_Joblist.begin(); it != this->_Joblist.end(); ++it)
		(*it)->setWait((*it)->getRet() - (*it)->getDuration() - (*it)->getCall());

	double WaitTimeSum = 0;
	double RetTimeSum = 0;
	double AwsTimeSum = 0;

	for(unsigned int i = 0; i < n; ++i){
		cout << "i: " << i << " n: " << n << endl;

		printf("%f += this->_Joblist[%i]->getWait() = [%i]\n", WaitTimeSum, i, this->_Joblist[i]->getWait());
		WaitTimeSum += this->_Joblist[i]->getWait();

		printf("%f += this->_Joblist[%i]->getRet() = [%i]\n", RetTimeSum, i, this->_Joblist[i]->getRet());
		RetTimeSum += this->_Joblist[i]->getRet();

		printf("%f += this->_Joblist[%i]->getAws() = [%i]\n", AwsTimeSum, i, this->_Joblist[i]->getAws());
		AwsTimeSum += this->_Joblist[i]->getAws();
	}

	this->_AvgWaitTime = WaitTimeSum/n;
	this->_AvgRetTime = RetTimeSum/n;
	this->_AvgAwsTime = AwsTimeSum/n;

/*
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
	double AwsTimeSum = 0;

	for(unsigned int i = 0; i < n; ++i){
		WaitTimeSum += WaitTime[i];
		RetTimeSum += RetTime[i];
		RetTimeSum += RetTime[i];
	}

	this->_AvgWaitTime = WaitTimeSum/n;
	this->_AvgRetTime = RetTimeSum/n;
	this->_AvgAwsTime = AwsTimeSum/n;
*/
}

RR::~RR()
{
	//Clear(&this->_Joblist);
}

} /* namespace Scheduler */
