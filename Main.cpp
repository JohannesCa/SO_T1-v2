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
#include "SJF.h"
#include "RR.h"

using namespace std;

typedef vector<Job*> JobList;
typedef vector<Job*>::iterator JobIt;

JobList LoadedJobsList;

bool PrepareJobs(string fName);


int main(int argc, char **argv)
{
	if(argc != 2){
		cerr << ">> Use:\t$ ./so-t1-v2 <file name>\n\n";
		return -1;
	}

	if(!PrepareJobs(argv[1])){
		cerr << "[ERROR] The file '" << argv[1] << "' doesn't exist!\n";
		return -1;
	}

	Scheduler::FCFS fcfs(&LoadedJobsList);
	Scheduler::SJF sjf(&LoadedJobsList);
	Scheduler::RR rr(&LoadedJobsList, 2);

	printf("FCFS %3.1f %3.1f %3.1f\n", fcfs.getAvgRet(), fcfs.getAvgWait(), fcfs.getAvgWait());
	printf("SJF %3.1f %3.1f %3.1f\n", sjf.getAvgRet(), sjf.getAvgWait(), sjf.getAvgWait());
	printf("RR %3.1f %3.1f %3.1f\n", rr.getAvgRet(), rr.getAvgAws(), rr.getAvgWait());

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
		int pid = 0;
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
			LoadedJobsList.push_back(new Job(pid++, beg, dur));
		}
	}

	return ret;
}
