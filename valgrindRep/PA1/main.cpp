//Reads in two files: the first is the "read" filename and the second is the "write" filename.
#include <iostream>
#include <fstream>
#include <sstream>
#include <PoseDisplay.h>
#include <Point3D.h>
#include <stick.h>
using namespace std;
int main(int argc, char *argv[]) {
	//string a = "", b = "";
	//cout << "Enter the filename to read from: " << endl;
	//cin >> a;
	if (!(argc == 3)) {
		cerr << "error: Please input two parameters" << endl;
		return -1;
	}
	ifstream inFile(argv[1]);
	if (!inFile.good()) {
		cerr << "error: Filename not recognized" << endl;
		return -1;
	}
	//cout << "Enter the filename to write to: " << endl;
	//cin >> b;
	PoseDisplay pose(argv[2]);
	//PoseDisplay pose(b, false);
	if (stick::filePose(inFile, pose) != 0) {
		return -1;
	}
}
