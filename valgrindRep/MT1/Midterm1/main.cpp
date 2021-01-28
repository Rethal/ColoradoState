//Reads in two files: the first is the "read" filename and the second is the "write" filename.
#include <iostream>
#include <fstream>
#include <sstream>
#include <PoseDisplay.h>
#include <Point3D.h>
#include <stick.h>
using namespace std;
int main(int argc, char *argv[]) {
	if (!(argc == 3)) {
		cerr << "error: Please input two parameters" << endl;
		return -1;
	}
	ifstream inFile(argv[1]);
	string outFile(argv[2]);
	if (!inFile.good()) {
		cerr << "error: Filename not recognized" << endl;
		return -1;
	}
	/*PoseDisplay pose(argv[2]);
	if (stick::filePose(inFile, pose, outFile) != 0) {
		return -1;
	}*/
	stick Stickman(inFile, outFile);
	if (Stickman.fileDistPrint() != 0) {
		//cerr << "failed" << endl;
		return -1;
	}
	//cout << "success" << endl;
}
