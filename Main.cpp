/*
 * Main.cpp
 *
 *  Created on: 25 de set de 2016
 *      Author: johannes
 */

#include <iostream>
#include <fstream>
#include "Job.h"
#include "FCFS.h"

using namespace std;

typedef vector<Job*> JobList;
typedef vector<Job*>::iterator JobIt;

JobList LoadedJobsList;

bool PrepareJobs(string fName);

int main(int argc, char **argv)
{
	PrepareJobs("inputs");

	Scheduler::FCFS fcfs(&LoadedJobsList);
	Scheduler::

	printf("FCFS %3.1f %3.1f", fcfs.getAvgWait(), fcfs.getAvgRet());

	return 0;
}


bool PrepareJobs(string fName) // Return if the file either exists or not
{
	bool ret = true;

	string line;
	ifstream input;
	input.open(fName, ios::in);

	if(!input)
		ret = false;
	else{
		while(getline(input, line)){
			int i;
			int beg, dur; // Begin, Duration
			string Buff;

			for(i = 0; line[i] != ' '; ++i)
				Buff += line[i];

			beg = stoi(Buff);
			Buff.clear();

			for(++i; line[i] != '\0'; ++i)
				Buff += line[i];

			dur = stoi(Buff);
			LoadedJobsList.push_back(new Job(beg, dur));
		}
	}

	return ret;
}
