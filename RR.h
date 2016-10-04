/*
 * RR.h
 *
 *  Created on: 3 de out de 2016
 *      Author: johannes
 */

#ifndef RR_H_
#define RR_H_

#include <iostream>
#include <vector>
#include "Job.h"

using namespace std;

namespace Scheduler {

typedef vector<Job*> JobList;
typedef vector<Job*>::iterator JobIt;

class RR {
private:
	JobList _Joblist;
	int _quantum;

	double _AvgWaitTime;
	double _AvgRetTime;
	double _AvgAwsTime;

public:
	RR(JobList* in, int q);
	~RR(void);

	double getAvgWait(void){return this->_AvgWaitTime;};
	double getAvgRet(void){return this->_AvgRetTime;};
	double getAvgAws(void){return this->_AvgAwsTime;};
};

} /* namespace Scheduler */

#endif /* RR_H_ */
