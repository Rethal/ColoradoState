//Reads in two files: the first is the "read" filename and the second is the "write" filename.
#include <iostream>
#include <fstream>
#include <sstream>
#include <PoseDisplay.h>
#include <Point3D.h>
#include <stick.h>
#include <multistick.h>
using namespace std;
int main(int argc, char *argv[]) {
	int desiredArgs = 4;
	if (!(argc == desiredArgs)) {
		cerr << "error: Please input" << desiredArgs-1 << "parameters" << endl;
		return -1;
	}
	ifstream inFile(argv[1]);
	ifstream inFile2(argv[2]);
	string outFile(argv[3]);
	if (!inFile.good()) {
		cerr << "error: Filename not recognized" << endl;
		return -1;
	}
	/*PoseDisplay pose(argv[2]);
	if (stick::filePose(inFile, pose, outFile) != 0) {
		return -1;
	}*/
	stick Stickman(inFile, outFile);
	stick Secondman(inFile2, outFile);
//	multistick Twins();
	if (Stickman.fileDistPrintMulti(Stickman, Secondman, outFile) != 0) {
		cerr << "error: failed" << endl;
		return -1;
	}
	//if (Stickman.fileDistPrint(inFile, outFile) != 0) {
	//	//cerr << "failed" << endl;
	//	return -1;
	//}
	//cout << "success" << endl;
}
