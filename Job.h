/*
 * Job.h
 *
 *  Created on: 1 de out de 2016
 *      Author: johannes
 */

#ifndef JOB_H_
#define JOB_H_

#include <iostream>
#include <vector>

using namespace std;

class Job {
private:
	int _PID;
	int _call;
	int _duration;

	/** Exclusive use by RR **/
	int _lastingTime;
	int _waitTime = 0;
	int _retTime = 0;
	int _awsTime = 0;

public:
	Job(int pid, int start, int duration);
	int getCall(void){return this->_call;};
	int getDuration(void){return this->_duration;};

	/** Exclusive use by RR **/
	int getLasting(void){return this->_lastingTime;};
	bool decreaseTime(int i);
	void setWait(int i){this->_waitTime = i;};
	void setRet(int i){this->_retTime = i;};
	void setAws(int i){this->_awsTime = i;};
	int getWait(void){return this->_waitTime;};
	int getRet(void){return this->_retTime;};
	int getAws(void){return this->_awsTime;};
	int getPID(void){return this->_PID;};
};

#endif /* JOB_H_ */
