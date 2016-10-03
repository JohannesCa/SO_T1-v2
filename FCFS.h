/*
 * FCFS.h
 *
 *  Created on: 2 de out de 2016
 *      Author: johannes
 */

#ifndef FCFS_H_
#define FCFS_H_

#include <iostream>
#include <vector>
#include "Job.h"

using namespace std;

namespace Scheduler {

typedef vector<Job*> JobList;
typedef vector<Job*>::iterator JobIt;

class FCFS {
private:
	JobList _Joblist;
	double _AvgWaitTime;
	double _AvgRetTime;
public:
	FCFS(JobList* in);
	~FCFS(void);

	double getAvgWait(void){return this->_AvgWaitTime;};
	double getAvgRet(void){return this->_AvgRetTime;};
};

} /* namespace Scheduler */

#endif /* FCFS_H_ */
