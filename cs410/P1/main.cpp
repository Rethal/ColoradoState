#include <iostream>
#include <fstream>
#include <sstream>
#include "plyHeader.h"
using namespace std;
int main(int argc, char *argv[]) {
	int desiredArgs = 2;
	if (argc != desiredArgs) {
		cerr << "error: Please input " << desiredArgs - 1 << " parameters" << endl;
		return -1;
	}
	ifstream inFile(argv[1]);
	HEADER head(inFile);
	head.projOneRun(argv[1]);
}
