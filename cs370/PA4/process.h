#ifndef PROCESS_DEFINITION
#define PROCESS_DEFINITION
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <string>
using std::string;
#include<vector>
using std::vector;
#include<utility>
using std::pair;
#include<fstream>
using std::ofstream;
#include <iomanip>

using namespace std;
class process {
public:
	process(int PID, int AT, int BD, int P, vector<int> TK) : processID(PID), arrivalTime(AT), burstDuration(BD), totalBurst(BD), priority(P), tickets(TK) {
	}
	int FCFS(vector<process>& Processes);
	void FCFSPrint(const vector<process>& Processes);

	int PreSJF(vector<process>& Processes);
	void PreSJFPrint(const vector<process>& Processes);

	int NonSJF(vector<process>& Processes);
	void NonSJFPrint(const vector<process>& Processes);

	int Priority(vector<process>& Processes);
	void PrioPrint(const vector<process>& Processes);

	int Lottery(vector<process>& Processes);
	void LottoPrint(const vector<process>& Processes);

	int driver(vector<process>& Processes);
	bool openOutFile();

	unsigned int randlimit(int min, int max);

	//exit();

	int processID;
	int arrivalTime;
	double waitTime;
	double thisTat;
	int burstDuration;
	int totalBurst;
	int priority;
	int order = -1;
	vector<int> tickets;
	int useTick;
	
};

struct byArrivalTime{
	bool operator() (const process& process1, const process& process2)
	{
		return (process1.arrivalTime < process2.arrivalTime);
	}
};

struct byBurstTime {
	bool operator() (const process& process1, const process& process2) {
		return (process1.burstDuration < process2.burstDuration);
	}
};

struct byPriority {
	bool operator() (const process& process1, const process& process2) {
		return (process1.priority < process2.priority);
	}
};


#endif