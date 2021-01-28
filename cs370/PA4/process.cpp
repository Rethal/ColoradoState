#include <cmath>
#include <process.h>

using namespace std;
ofstream outtahere;

int process::driver(vector<process>& Processes) {
	if (!openOutFile()) return -1;
	//if (!writeFile()) return -1;
	FCFS(Processes);
	PreSJF(Processes);
	NonSJF(Processes);
	Priority(Processes);
	Lottery(Processes);
	return 0;
}
bool process::openOutFile() {
	outtahere.open("output");
	if (!outtahere) {
		cerr << "error: could not open output file " << endl;
		return false;
	}
	return true;
}

//bool process::writeFile()
//{
//	for (vector<double>::const_iterator iter = poseDistances.begin(); iter != poseDistances.end(); iter++) {
//		audi << *iter << endl;
//	}
//	return !(audi.fail());
//}
int process::FCFS(vector<process>& Processes) {
	//sort by arrival
	sort(Processes.begin(), Processes.end(), byArrivalTime());
	double totalwaitTime = 0;
	double TAT = 0;
	//sort arrivals by burst
	for (unsigned int i = 0; i < Processes.size(); i++) {
		double bytime = Processes[i].arrivalTime;
		int startSort = i;
		while (Processes[i].arrivalTime == bytime) {
			i++;
		}
		sort(Processes.begin() + startSort, Processes.begin() + i, byBurstTime());
		i--;
	}
	double arrival = 0;
	for (unsigned int i = 0; i < Processes.size(); i++) {
		if (i == 0) {
			//set initial arrival time
			arrival = Processes[i].arrivalTime;	
		}
		else {
			//remove non-waited time from TAT
			if (Processes[i].arrivalTime != arrival) {
				int difference = Processes[i].arrivalTime - arrival;
				arrival = Processes[i].arrivalTime;
				totalwaitTime = totalwaitTime - difference;
			}
		}
		Processes[i].waitTime = totalwaitTime;
		TAT = totalwaitTime + Processes[i].burstDuration;
		Processes[i].thisTat = TAT;
		totalwaitTime = TAT;
	}
	FCFSPrint(Processes);
	return 0;
}

void process::FCFSPrint(const vector<process>& Processes) {
	outtahere << "************************************************************" << endl << endl << "FCFS SCHEDULING ALGORITHM :" << endl
		<< endl << "==============================================================" << endl;
	outtahere << "Process	AT	BT	WT	TAT" << endl;
	for (unsigned int i = 0; i < Processes.size(); i++) {
		outtahere << "P" << Processes[i].processID << "	" << Processes[i].arrivalTime << "	" << Processes[i].totalBurst << "	" 
			<< Processes[i].waitTime << ".0" << "	" << Processes[i].thisTat << ".0" << endl;
	}
	double throughput = 0;
	double AWT = 0;
	double ATT = 0;
	throughput = (Processes.size() / (Processes[Processes.size() - 1].thisTat + Processes[Processes.size()-1].arrivalTime));
	for (unsigned int i = 0; i < Processes.size(); i++) {
		AWT += Processes[i].waitTime;
		ATT += Processes[i].thisTat;
	}
	AWT = AWT / Processes.size();
	ATT = ATT / Processes.size();
	outtahere << setprecision(8);
	outtahere << endl << "average waiting time : " << AWT << endl;
	outtahere << endl << "average turnaround time: " << ATT << endl;
	outtahere << endl << "throughput: " << throughput << endl;
	outtahere << endl << "============================================================" << endl;
}

int process::PreSJF(vector<process>& Processes) {
	//create ready queue and a running slot
	//loop by second
	//decrease each process' remaining time
	//any time an incoming process has lower remaining time than one running, add the running one to a ready queue and the new one to be running
	//make the ready queue a vector that also runs by the incrementer, and sort it by remaining burst time any time a new one enters
	//time = 0; while ready list != empty and completed list != size of original list, increment time

	//reset timers
	for (unsigned int i = 0; i < Processes.size(); i++) {
		Processes[i].waitTime = 0;
		Processes[i].thisTat = 0;
		Processes[i].burstDuration = Processes[i].totalBurst;
	}
	vector<process> readyQueue;
	vector<process> runSlot;
	vector<process> finishList;
	vector<process> orderList;
	int time = 0;
	int orderer = 0;
	//make entire output
	while (finishList.size() != Processes.size()) {
		unsigned int totSize = readyQueue.size() + runSlot.size() + finishList.size();
		//fill ready queue at given arrival time
		if (totSize != Processes.size()) {
			for (unsigned int i = 0; i < Processes.size(); i++) {
				if (Processes[i].arrivalTime == time) {
					readyQueue.push_back(Processes[i]);
				}
			}
		}
		//if there's an element in ready queue and none in runslot, add the appropriate one
		if (runSlot.size() == 0 && readyQueue.size() != 0) {
			int minBurst = readyQueue[0].burstDuration;
			for (unsigned int i = 0; i < readyQueue.size(); i++) {
				if (readyQueue[i].burstDuration < minBurst) {
					minBurst = readyQueue[i].burstDuration;
				}
			}
			//contains algorithm: if there is a started process, add it to the running slot, otherwise add the next equally short method
			while (runSlot.size() == 0) {
				int saved = -1;
				for (unsigned int i = 0; i < readyQueue.size(); i++) {
					if (readyQueue[i].burstDuration == minBurst && runSlot.size() == 0 && readyQueue[i].order != -1) {
						if (saved == -1) {
							saved = i;
						}
						if (saved != -1 && readyQueue[saved].order > readyQueue[i].order) {
							saved = i;
						}
					}
				}
				if (saved != -1) {
					runSlot.push_back(readyQueue[saved]);
					readyQueue.erase(readyQueue.begin() + saved);
				}
				for (unsigned int i = 0; i < readyQueue.size(); i++) {
					if (readyQueue[i].burstDuration == minBurst && runSlot.size() == 0) {
						if (readyQueue[i].order == -1) {
							readyQueue[i].order = orderer;
							orderer++;
						}
						runSlot.push_back(readyQueue[i]);
						readyQueue.erase(readyQueue.begin()+i);
					}
				}
			}
		}
		//if there's an element in runslot
		if (runSlot.size() == 1) {
			int minBurst = runSlot[0].burstDuration;
			for (unsigned int i = 0; i < readyQueue.size(); i++) {
				if (readyQueue[i].burstDuration < minBurst) {
					minBurst = readyQueue[i].burstDuration;
				}
			}
			//if the runslot element has longer runtime remaining than any in the ready queue
			if (runSlot[0].burstDuration != minBurst) {
				readyQueue.push_back(runSlot[0]);
				runSlot.erase(runSlot.begin());
				//contains algorithm: if there is a started process, add it to the running slot, otherwise add the next equally short method
				while (runSlot.size() == 0) {
					int saved = -1;
					for (unsigned int i = 0; i < readyQueue.size(); i++) {
						if (readyQueue[i].burstDuration == minBurst && runSlot.size() == 0 && readyQueue[i].order != -1) {
							if (saved == -1) {
								saved = i;
							}
							if (saved != -1 && readyQueue[saved].order > readyQueue[i].order) {
								saved = i;
							}
						}
					}
					if (saved != -1) {
						runSlot.push_back(readyQueue[saved]);
						readyQueue.erase(readyQueue.begin() + saved);
					}
					for (unsigned int i = 0; i < readyQueue.size(); i++) {
						if (readyQueue[i].burstDuration == minBurst && runSlot.size() == 0) {
							if (readyQueue[i].order == -1) {
								readyQueue[i].order = orderer;
								orderer++;
							}
							runSlot.push_back(readyQueue[i]);
							readyQueue.erase(readyQueue.begin()+i);
						}
					}
				}
			}
			//increment all wait times in ready queue, decrement remaining burst in runslot, if runslot is finished move to finishList
			for (unsigned int i = 0; i < readyQueue.size(); i++) {
				readyQueue[i].waitTime += 1;
			}
			runSlot[0].burstDuration -= 1;
			//if running algorithm now completed, move it to finish queue
			if (runSlot[0].burstDuration == 0) {
				runSlot[0].thisTat = time - runSlot[0].arrivalTime + 1;
				finishList.push_back(runSlot[0]);
				runSlot.erase(runSlot.begin());
			}
		}
		time++;
	}
	//organize processes by order in which they began
	orderer = 0;
	while (orderList.size() != finishList.size()) {
		for (unsigned int i = 0; i < finishList.size(); i++) {
			if (finishList[i].order == orderer) {
				orderList.push_back(finishList[i]);
			}
		}
		orderer++;
	}
	PreSJFPrint(orderList);
	return 0;
}
void process::PreSJFPrint(const vector<process>& Processes) {
	outtahere << "************************************************************" << endl << endl << "SJF PREEMPTIVE SCHEDULING ALGORITHM:" << endl
		<< endl << "==============================================================" << endl;
	outtahere << "Process	AT	BT	WT	TAT" << endl;
	for (unsigned int i = 0; i < Processes.size(); i++) {
		outtahere << "P" << Processes[i].processID << "	" << Processes[i].arrivalTime << "	" << Processes[i].totalBurst << "	"
			<< Processes[i].waitTime << ".0" << "	" << Processes[i].thisTat << ".0" << endl;
	//	P518    1       10      604.0   614.0
	}
	double throughput = 0;
	double AWT = 0;
	double ATT = 0;
	throughput = (Processes.size() / (Processes[Processes.size() - 1].thisTat + Processes[Processes.size() - 1].arrivalTime));
	for (unsigned int i = 0; i < Processes.size(); i++) {
		AWT += Processes[i].waitTime;
		ATT += Processes[i].thisTat;
	}
	AWT = AWT / Processes.size();
	ATT = ATT / Processes.size();
	outtahere << setprecision(8);
	outtahere << endl << "average waiting time : " << AWT << endl;
	outtahere << endl << "average turnaround time: " << ATT << endl;
	outtahere << endl << "throughput: " << throughput << endl;
	outtahere << endl << "============================================================" << endl << endl;
	
}


int process::NonSJF(vector<process>& Processes) {
	//same as pre but with no removal from the runtime slot
	for (unsigned int i = 0; i < Processes.size(); i++) {
		Processes[i].waitTime = 0;
		Processes[i].thisTat = 0;
		Processes[i].burstDuration = Processes[i].totalBurst;
	}
	vector<process> readyQueue;
	vector<process> runSlot;
	vector<process> finishList;
	vector<process> orderList;
	int time = 0;
	int orderer = 0;
	//make entire output
	while (finishList.size() != Processes.size()) {
		unsigned int totSize = readyQueue.size() + runSlot.size() + finishList.size();
		//fill ready queue at given arrival time
		if (totSize != Processes.size()) {
			for (unsigned int i = 0; i < Processes.size(); i++) {
				if (Processes[i].arrivalTime == time) {
					readyQueue.push_back(Processes[i]);
				}
			}
		}
		//if there's an element in ready queue and none in runslot, add the appropriate one
		if (runSlot.size() == 0 && readyQueue.size() != 0) {
			int minBurst = readyQueue[0].burstDuration;
			for (unsigned int i = 0; i < readyQueue.size(); i++) {
				if (readyQueue[i].burstDuration < minBurst) {
					minBurst = readyQueue[i].burstDuration;
				}
			}
			//contains algorithm: if there is a started process, add it to the running slot, otherwise add the next equally short method
			while (runSlot.size() == 0) {
				int saved = -1;
				for (unsigned int i = 0; i < readyQueue.size(); i++) {
					if (readyQueue[i].burstDuration == minBurst && runSlot.size() == 0 && readyQueue[i].order != -1) {
						if (saved == -1) {
							saved = i;
						}
						if (saved != -1 && readyQueue[saved].order > readyQueue[i].order) {
							saved = i;
						}
					}
				}
				if (saved != -1) {
					runSlot.push_back(readyQueue[saved]);
					readyQueue.erase(readyQueue.begin() + saved);
				}
				for (unsigned int i = 0; i < readyQueue.size(); i++) {
					if (readyQueue[i].burstDuration == minBurst && runSlot.size() == 0) {
						if (readyQueue[i].order == -1) {
							readyQueue[i].order = orderer;
							orderer++;
						}
						runSlot.push_back(readyQueue[i]);
						readyQueue.erase(readyQueue.begin() + i);
					}
				}
			}
		}
		//if there's an element in runslot
		if (runSlot.size() == 1) {
			//increment all wait times in ready queue, decrement remaining burst in runslot, if runslot is finished move to finishList
			for (unsigned int i = 0; i < readyQueue.size(); i++) {
				readyQueue[i].waitTime += 1;
			}
			runSlot[0].burstDuration -= 1;
			//if running algorithm now completed, move it to finish queue
			if (runSlot[0].burstDuration == 0) {
				runSlot[0].thisTat = time - runSlot[0].arrivalTime + 1;
				finishList.push_back(runSlot[0]);
				runSlot.erase(runSlot.begin());
			}
		}
		time++;
	}
	//organize processes by order in which they began
	orderer = 0;
	while (orderList.size() != finishList.size()) {
		for (unsigned int i = 0; i < finishList.size(); i++) {
			if (finishList[i].order == orderer) {
				orderList.push_back(finishList[i]);
			}
		}
		orderer++;
	}
	NonSJFPrint(orderList);
	return 0;
}
void process::NonSJFPrint(const vector<process>& Processes) {
	
	outtahere << "************************************************************" << endl << endl << "SJF NON - PREEMPTIVE SCHEDULING ALGORITHM :" << endl
		<< endl << "==============================================================" << endl;
	outtahere << "Process	AT	BT	WT	TAT" << endl;
	for (unsigned int i = 0; i < Processes.size(); i++) {
		outtahere << "P" << Processes[i].processID << "	" << Processes[i].arrivalTime << "	" << Processes[i].totalBurst << "	"
			<< Processes[i].waitTime << ".0" << "	" << Processes[i].thisTat << ".0" << endl;
		//	P518    1       10      604.0   614.0
	}
	double throughput = 0;
	double AWT = 0;
	double ATT = 0;
	throughput = (Processes.size() / (Processes[Processes.size() - 1].thisTat + Processes[Processes.size() - 1].arrivalTime));
	for (unsigned int i = 0; i < Processes.size(); i++) {
		AWT += Processes[i].waitTime;
		ATT += Processes[i].thisTat;
	}
	AWT = AWT / Processes.size();
	ATT = ATT / Processes.size();
	outtahere << setprecision(8);
	outtahere << endl << "average waiting time : " << AWT << endl;
	outtahere << endl << "average turnaround time: " << ATT << endl;
	outtahere << endl << "throughput: " << throughput << endl;
	outtahere << endl << "============================================================" << endl << endl;
}

int process::Priority(vector<process>& Processes) {
	//reset timers
	for (unsigned int i = 0; i < Processes.size(); i++) {
		Processes[i].waitTime = 0;
		Processes[i].thisTat = 0;
		Processes[i].burstDuration = Processes[i].totalBurst;
	}
	vector<process> readyQueue;
	vector<process> runSlot;
	vector<process> nextSlot;
	vector<process> finishList;
	int time = 0;
	while (finishList.size() != Processes.size()) {
		//fill queue
		for (unsigned int i = 0; i < Processes.size(); i++) {
			if (Processes[i].arrivalTime == time) {
				readyQueue.push_back(Processes[i]);
			}
		}
		if (runSlot.size() == 0 && readyQueue.size() != 0) {
			int prio = readyQueue[0].priority;
			//find lowest priority in queue
			for (unsigned int i = 0; i < readyQueue.size(); i++) {
				if (readyQueue[i].priority < prio) {
					prio = readyQueue[i].priority;
				}
			}
			//move lowest priority lowest burst into next slot
			for (unsigned int i = 0; i < readyQueue.size(); i++) {
				if (readyQueue[i].priority == prio) {
					if (nextSlot.size() == 0 || (readyQueue[i].burstDuration < nextSlot[0].burstDuration)) {
						if (nextSlot.size() != 0) {
							readyQueue.push_back(nextSlot[0]);
							nextSlot.clear();
						}
						nextSlot.push_back(readyQueue[i]);
						readyQueue.erase(readyQueue.begin() + i);
					}
				}
			}
		}
		//move next slot into run slot	
		if (nextSlot.size() != 0 && runSlot.size() == 0) {
			runSlot.push_back(nextSlot[0]);
			nextSlot.clear();
		}
		if (runSlot.size() == 1) {
			runSlot[0].burstDuration--;
			if (runSlot[0].burstDuration == 0) {
				runSlot[0].thisTat = time - runSlot[0].arrivalTime + 1;
				finishList.push_back(runSlot[0]);
				runSlot.clear();
			}
			for (unsigned int i = 0; i < readyQueue.size(); i++) {
				readyQueue[i].waitTime++;
			}
		}
		time++;
	}
	PrioPrint(finishList);
	return 0;
}
void process::PrioPrint(const vector<process>& Processes) {
	outtahere << "************************************************************" << endl << endl << "SJF NON - PREEMPTIVE SCHEDULING ALGORITHM :" << endl
		<< endl << "==============================================================" << endl;
	outtahere << "Process	AT	BT	Prio	WT	TAT" << endl;
	for (unsigned int i = 0; i < Processes.size(); i++) {
		outtahere << "P" << Processes[i].processID << "	" << Processes[i].arrivalTime << "	" << Processes[i].totalBurst << "	" << Processes[i].priority << "	"
			<< Processes[i].waitTime << ".0" << "	" << Processes[i].thisTat << ".0" << endl;
		//	P518    1       10      604.0   614.0
	}
	double throughput = 0;
	double AWT = 0;
	double ATT = 0;
	throughput = (Processes.size() / (Processes[Processes.size() - 1].thisTat + Processes[Processes.size() - 1].arrivalTime));
	for (unsigned int i = 0; i < Processes.size(); i++) {
		AWT += Processes[i].waitTime;
		ATT += Processes[i].thisTat;
	}
	AWT = AWT / Processes.size();
	ATT = ATT / Processes.size();
	outtahere << setprecision(8);
	outtahere << endl << "average waiting time : " << AWT << endl;
	outtahere << endl << "average turnaround time: " << ATT << endl;
	outtahere << endl << "throughput: " << throughput << endl;
	outtahere << endl << "============================================================" << endl << endl;
}
int process::Lottery(vector<process>& Processes) {
	//reset timers
	int MINTICK = Processes[0].tickets[0];
	int MAXTICK = 0;
	for (unsigned int i = 0; i < Processes.size(); i++) {
		Processes[i].waitTime = 0;
		Processes[i].thisTat = 0;
		Processes[i].burstDuration = Processes[i].totalBurst;
		for (unsigned int j = 0; j < Processes[i].tickets.size(); j++) {
			if (Processes[i].tickets[j] < MINTICK) {
				MINTICK = Processes[i].tickets[j];
			}
			if (Processes[i].tickets[j] > MAXTICK) {
				MAXTICK = Processes[i].tickets[j];
			}
		}
	}
	vector<process> readyQueue;
	vector<process> runSlot;
	vector<process> nextSlot;
	vector<process> finishList;
	int time = 0;
	//while finished not size of processes
	while (finishList.size() != Processes.size()) {
		//create queue of all by arrival time
		int ticket = randlimit(MINTICK,MAXTICK);
		//if one in queue has ticket
		//add it to runspot, remove from queue (else draw new ticket)
		//while runspot not complete, run time
		//add runspot to finish list, remove from runspot
		//find process with most tickets
		//push each value of vector onto the vector
		for (unsigned int i = 0; i < Processes.size(); i++) {
			if (Processes[i].arrivalTime == time) {
				readyQueue.push_back(Processes[i]);
			}
		}
		if (runSlot.size() == 0 && readyQueue.size() != 0) {
			//cout << ticket << endl;
			for (unsigned int i = 0; i < readyQueue.size(); i++) {
				for (unsigned int j = 0; j < readyQueue[i].tickets.size(); j++) {
					if (readyQueue[i].tickets[j] == ticket) {
						readyQueue[i].useTick = ticket;
						runSlot.push_back(readyQueue[i]);
						readyQueue.erase(readyQueue.begin() + i);
						//cout << "here" << endl;
					}
				}
			}
		}
		if (runSlot.size() == 1) {
			runSlot[0].burstDuration--;
			if (runSlot[0].burstDuration == 0) {
				runSlot[0].thisTat = time - runSlot[0].arrivalTime + 1;
				finishList.push_back(runSlot[0]);
				unsigned int tickSize = 0;
				unsigned int saved = 0;
				if (readyQueue.size() != 0) {
					for (unsigned int i = 0; i < readyQueue.size(); i++) {
						if (readyQueue[i].tickets.size() > tickSize) {
							tickSize = readyQueue[i].tickets.size();
							saved = i;
						}
					}
					for (unsigned int i = 0; i < runSlot[0].tickets.size(); i++) {
						readyQueue[saved].tickets.push_back(runSlot[0].tickets[i]);
					}
				}
				runSlot.erase(runSlot.begin());
			}
			for (unsigned int i = 0; i < readyQueue.size(); i++) {
				readyQueue[i].waitTime++;
			}		
		}
		time++;
	}
	LottoPrint(finishList);
	return 0;
}
void process::LottoPrint(const vector<process>& Processes) {
	outtahere << "************************************************************" << endl << endl << "LOTTERY SCHEDULING ALGORITHM :" << endl
		<< endl << "==============================================================" << endl;
	outtahere << "Process	AT	BT	Tick	WT	TAT" << endl;
	for (unsigned int i = 0; i < Processes.size(); i++) {
		outtahere << "P" << Processes[i].processID << "	" << Processes[i].arrivalTime << "	" << Processes[i].totalBurst << "	" << Processes[i].useTick << "	"
			<< Processes[i].waitTime << ".0" << "	" << Processes[i].thisTat << ".0" << endl;
		//	P518    1       10      604.0   614.0
	}
	double throughput = 0;
	double AWT = 0;
	double ATT = 0;
	throughput = (Processes.size() / (Processes[Processes.size() - 1].thisTat + Processes[Processes.size() - 1].arrivalTime));
	for (unsigned int i = 0; i < Processes.size(); i++) {
		AWT += Processes[i].waitTime;
		ATT += Processes[i].thisTat;
	}
	AWT = AWT / Processes.size();
	ATT = ATT / Processes.size();
	outtahere << setprecision(8);
	outtahere << endl << "average waiting time : " << AWT << endl;
	outtahere << endl << "average turnaround time: " << ATT << endl;
	outtahere << endl << "throughput: " << throughput << endl;
	outtahere << endl << "============================================================" << endl << endl;
}

//code taken from stack overflow
unsigned int process::randlimit(int min, int max)
{
	int r;
	const int range = 1 + max - min;
	const int buckets = RAND_MAX / range;
	const int limit = buckets * range;
	do
	{
		r = rand();
	} while (r >= limit);

	return min + (r / buckets);
}
//exit();