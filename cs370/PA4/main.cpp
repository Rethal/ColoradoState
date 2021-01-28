//1,39,50,27,9959 - 10000
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <process.h>
using namespace std;
int main(int argc, char *argv[]) {
	int desiredArgs = 3;
	if (!(argc == desiredArgs)) {
		cerr << "error: Please input " << desiredArgs - 1 << " parameters" << endl;
		return -1;
	}
	//get filename and seed
	ifstream inFile(argv[1]);
	int seed = atoi(argv[2]);
	// set the seed
	srand(seed);

	int PID, AT, BD, P, tickMin, tickMax;
	vector<int> TK;
	string line = "";
	char throwaway = ' ';
	vector<process> processList;

	while (getline(inFile, line)) {
		istringstream iss;
		iss.str(line);
		iss >> PID;
		iss >> throwaway;
		iss >> AT;
		iss >> throwaway;
		iss >> BD;
		iss >> throwaway;
		iss >> P;
		iss >> throwaway;
		iss >> tickMin;
		iss >> throwaway;
		iss >> tickMax;
		for (int i = tickMin; i <= tickMax; i++) {
			TK.push_back(i);
		}
		process newProc(PID, AT, BD, P, TK);
		processList.push_back(newProc);
		TK.clear();
	}
	//processList[0].FCFS(processList);
	//processList[0].PreSJF(processList);
	//processList[0].NonSJF(processList);
	processList[0].driver(processList);
}
