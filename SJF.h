/*
 * SJF.h
 *
 *  Created on: 2 de out de 2016
 *      Author: johannes
 */

#ifndef SJF_H_
#define SJF_H_

#include <iostream>
#include <vector>
#include "Job.h"
#include <algorithm>

using namespace std;

typedef vector<Job*> JobList;
typedef vector<Job*>::iterator JobIt;

namespace Scheduler {

class SJF {
private:
	JobList _Joblist;
	double _AvgWaitTime;
	double _AvgRetTime;
	double _AvgAwsTime;
	void Sort(void);
public:
	SJF(JobList* in);
	~SJF(void);

	double getAvgWait(void){return this->_AvgWaitTime;};
	double getAvgRet(void){return this->_AvgRetTime;};
	double getAwsRet(void){return this->_AvgAwsTime;};

	void print(void);
};

} /* namespace Scheduler */

#endif /* SJF_H_ */
