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


}

RR::~RR()
{
	;
}

} /* namespace Scheduler */
