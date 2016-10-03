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

typedef struct timeval Time;

class Job {
private:
	int _duration;
	int _call;
	int _lastingTime;

public:
	Job(int start, int duration);
	int getCall(void){return this->_call;};
	int getDuration(void){return this->_duration;};
	int getLating(void){return this->_lastingTime;};
	void decreaseTime(int i){this->_lastingTime -= i;};
};

#endif /* JOB_H_ */
