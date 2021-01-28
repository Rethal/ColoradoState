//Main Header by Brent Grundman
//CS253
//829460164
#ifndef STICK_FIGURE
#define STICK_FIGURE
#include <iostream>
#include <fstream>
#include <sstream>
#include <PoseDisplay.h>
#include <Point3D.h>
#include <cmath>
using namespace std; 
class stick {
public:
	static int filePose(ifstream& inFile, PoseDisplay& pose);
	static int legalFile(ifstream& inFile, PoseDisplay& pose);
	static int checkLine(istringstream& iss, int lineCount);
	static double findSpineX();
	static double findSpineY();
	static double findSpineZ();
	static void shiftVector(double shift, vector<double>& values);
	static int makePoses();
	static double greatestAbs();
	static bool sameLems();
	static int scaleVector(double scale, vector<double>& values);
	static void newBase();
};
#endif