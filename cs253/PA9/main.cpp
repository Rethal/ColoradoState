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
	int desiredArgs = 2;
	if (argc != desiredArgs) {
		cerr << "error: Please input " << desiredArgs-1 << " parameters" << endl;
		return -1;
	}
	//PA 9
	ifstream inFile(argv[1]);
	stick Stickman(inFile);
	multistick SelfieStick(Stickman);
	if (SelfieStick.LastFrame == -1) {
		return -1;
	}
	////PA 7 & 8
	//multistick AllFile(argc, argv);
	//if (AllFile.FailOrFile == -1) {
	//	return -1;
	//}
	//else {
	//	cout << argv[AllFile.FailOrFile] << endl;
	//}
	//PA pre-7 (all below)
	/*ifstream inFile(argv[1]);
	ifstream inFile2(argv[2]);
	string distanceType(argv[argc-1]);
	if (distanceType != "avg" && distanceType != "med" && distanceType != "Linf" && distanceType != "L2") {
		cerr << "error: must select a valid distance type" << endl;
		return -1;
	}*/
	//PA 1-4
	/*if (desiredArgs == 4) {
		string outFile(argv[3]);
		
	}*/
	/*if (!inFile.good()) {
		cerr << "error: Filename not recognized" << endl;
		return -1;
	}*/
	/*PoseDisplay pose(argv[2]);
	if (stick::filePose(inFile, pose, outFile) != 0) {
		return -1;
	}*/
	/*stick Stickman(inFile);
	stick Secondman(inFile2);*/
//	multistick Twins();
	//PA4
	/*if (Stickman.fileDistPrintMulti(Stickman, Secondman, outFile) != 0) {
		cerr << "error: failed" << endl;
		return -1;
	}*/
	//PA3
	//if (Stickman.fileDistPrint(inFile, outFile) != 0) {
	//	//cerr << "failed" << endl;
	//	return -1;
	//}
	//cout << "success" << endl;
	//PA5
	//PA6
	/*if (Stickman.dynamicMatch(Stickman, Secondman, distanceType) != 0) {
		cerr << "error: failed" << endl;
		return -1;
	}*/
}
